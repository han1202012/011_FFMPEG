//
// Created by octopus on 2020/2/25.
//

#include "FFMPEG.h"

//构造方法
FFMPEG::FFMPEG(JavaPlayerCaller *callHelper, const char *dataSource) {

    //拷贝一份 dataSource 字符串 , 因为该参数中传入的字符串后面可能会被回收
    //  注意 strlen 获取字符串长度 , 其中不包括最后的 '\0' 结尾 , C/C++ 字符串必须包括该 '\0' 作为结尾
    //  拷贝时必须拷贝 strlen(dataSource) + 1 个字节的字符串 , 才能保证字符串完整
    int strlength = strlen(dataSource) + 1;

    //赋值给成员变量
    this->dataSource = new char[strlength];

    //拷贝字符串
    strcpy(this->dataSource, dataSource);

    //Java 反射调用类
    this->callHelper = callHelper;

}

FFMPEG::~FFMPEG() {

    //释放字符串成员变量 , 防止 dataSource 指向的内存出现泄漏
    delete dataSource;
}

//prepare 方法调用的子线程执行内容
void* pthread_prepare(void* args){

    //将 args 参数转为 FFMPEG 对象
    FFMPEG *ffmpeg = static_cast<FFMPEG *>(args);

    //调用 ffmpeg 对象的 _prepare() 方法
    ffmpeg->_prepare();

    //线程函数必须 return
    return 0;

}


/**
 * 实际的准备方法
 *      该方法是类中定义的方法
 *      之所以要绕一大圈最终还是调用类定义的方法是为了方便使用类中定义的各种数据
 *      如 : AVFormatContext *formatContext , AudioChannel *audioChannel ,
 *          VideoChannel *videoChannel 等数据
 */
void FFMPEG::_prepare() {

    /*
     * 初始化网络 :
     *      默认状态下 , FFMPEG 是不允许联网的
     *      必须调用该函数 , 初始化网络后 FFMPEG 才能进行联网
     */
    avformat_network_init();


    //0 . 注册组件
    //      如果是 4.x 之前的版本需要执行该步骤
    //      4.x 及之后的版本 , 就没有该步骤了
    //av_register_all();

    //1 . 打开音视频地址 ( 播放文件前 , 需要先将文件打开 )
    //      地址类型 : ① 文件类型 , ② 音视频流
    //  参数解析 :
    //      AVFormatContext **ps :  封装了文件格式相关信息的结构体 , 如视频宽高 , 音频采样率等信息 ;
    //                              该参数是 二级指针 , 意味着在方法中会修改该指针的指向 ,
    //                              该参数的实际作用是当做返回值用的
    //      const char *url :   视频资源地址, 文件地址 / 网络链接
    //      AVInputFormat *fmt : 打开的媒体格式 , 一般传 NULL 即可 , FFMPEG 会自动识别格式
    //      AVDictionary **options : 内部类似于 Map 集合 , 有 Key-Value 值
    //  返回值说明 : 返回 0 , 代表打开成功 , 否则失败
    //              失败的情况 : 文件路径错误 , 网络错误
    //int avformat_open_input(AVFormatContext **ps, const char *url,
    //                          AVInputFormat *fmt, AVDictionary **options);
    //
    //设置参数
    AVDictionary *options = 0;
    //设置超时时间 , 单位是微秒 , 这里设置 10秒 , 即 10 * 1000 毫秒 , 10 * 1000 * 1000 微秒
    //  注意传入的是二维指针 , 二维指针 等价于 一维引用
    av_dict_set(&options, "timeout", "10000000", 0);
    int open_result = avformat_open_input(&formatContext, dataSource, 0, 0);
    av_dict_free(&options);

    //如果返回值不是 0 , 说明打开视频文件失败 , 需要将错误信息在 Java 层进行提示
    //  这里将错误码返回到 Java 层显示即可
    if(open_result != 0){
        __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "打开媒体失败 : %s", av_err2str(open_result));
        callHelper->onError(pid, 0);
    }



    //2 . 查找媒体 地址 对应的音视频流 ( 给 AVFormatContext* 成员赋值 )
    //      方法原型 : int avformat_find_stream_info(AVFormatContext *ic, AVDictionary **options);
    //      调用该方法后 , AVFormatContext 结构体的 nb_streams 元素就有值了 ,
    //      该值代表了音视频流 AVStream 个数
    int find_result = avformat_find_stream_info(formatContext, 0);

    //如果返回值 < 0 , 说明查找音视频流失败 , 需要将错误信息在 Java 层进行提示
    //  这里将错误码返回到 Java 层显示即可
    if(find_result < 0){
        __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "查找媒体流失败 : %s", av_err2str(find_result));
        callHelper->onError(pid, 1);
    }


    //3 . 处理视频流 , 解析其中的数据流 , 获取流的各种参数 , 编解码器 , 等信息
    //      为视频 音频 解码播放准备数据

    //formatContext->nb_streams 是 音频流 / 视频流 个数 ;
    //  循环解析 视频流 / 音频流 , 一般是两个 , 一个视频流 , 一个音频流
    for(int i = 0; i < formatContext->nb_streams; i ++){

        //取出一个媒体流 ( 视频流 / 音频流 )
        AVStream *stream = formatContext->streams[i];

        //解码这个媒体流的参数信息 , 包含 码率 , 宽度 , 高度 , 采样率 等参数信息
        AVCodecParameters *codecParameters = stream->codecpar;

        //视频 / 音频 处理需要的操作 ( 获取编解码器 )

        //① 查找 当前流 使用的编码方式 , 进而查找编解码器 ( 可能失败 , 不支持的解码方式 )
        AVCodec *avCodec = avcodec_find_decoder(codecParameters->codec_id);

        //查找失败处理
        if(avCodec == NULL){
            //如果没有找到编解码器 , 回调失败 , 方法直接返回 , 后续代码不执行
            callHelper->onError(pid, 2);
            __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "查找 编解码器 失败");
            return;
        }


        //② 获取编解码器上下文
        AVCodecContext *avCodecContext = avcodec_alloc_context3(avCodec);

        //获取编解码器失败处理
        if(avCodecContext == NULL){
            callHelper->onError(pid, 3);
            __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "创建编解码器上下文 失败");
            return;
        }

        //③ 设置 编解码器上下文 参数
        //      int avcodec_parameters_to_context(AVCodecContext *codec,
        //              const AVCodecParameters *par);
        //      返回值 > 0 成功 , < 0 失败
        int parameters_to_context_result =
                avcodec_parameters_to_context(avCodecContext, codecParameters);

        //设置 编解码器上下文 参数 失败处理
        if(parameters_to_context_result < 0){
            callHelper->onError(pid, 4);
            __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "设置编解码器上下文参数 失败");
            return;
        }

        //④ 打开编解码器
        //   int avcodec_open2(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options);
        //   返回 0 成功 , 其它失败
        int open_codec_result = avcodec_open2(avCodecContext, avCodec, 0);

        //打开编解码器 失败处理
        if(open_codec_result != 0){
            callHelper->onError(pid, 5);
            __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "打开 编解码器 失败");
            return;
        }


        //获取音视频 同步校准的 PTS 的 time_base 单位
        AVRational time_base = stream->time_base;


        //一般情况下 , 视频直播流只包含 视频流 和 音频流
        if(codecParameters->codec_type == AVMEDIA_TYPE_AUDIO){

            //音频
            audioChannel = new AudioChannel(i, avCodecContext , time_base);

        }else if(codecParameters->codec_type == AVMEDIA_TYPE_VIDEO){

            //获取视频的 FPS 帧率 ( 1秒中播放的帧数 )
            /*
             该结构体由一个分子和分母组成 , 分子 / 分母就是 fps
             typedef struct AVRational{
                int num; ///< Numerator
                int den; ///< Denominator
            } AVRational;
             */
            AVRational frame_rate = stream->avg_frame_rate;

            // AVRational 结构体由一个分子和分母组成 , 分子 / 分母就是 fps
            //  也可以使用 av_q2d() 方法传入 AVRational 结构体进行计算
            //  上面两种方法都可以获取 帧率 ( FPS )
            //      FPS 的值不是固定的 , 随着视频播放 , 其帧率也会随之改变
            int fps = frame_rate.num / frame_rate.den;
            //int fps = av_q2d(frame_rate);

            //视频
            videoChannel = new VideoChannel(i, avCodecContext, time_base, fps);

            //设置视频回调函数
            videoChannel->setShowFrameCallback(callback);

        }

    }

    //没有音视频 , 向 Java 层报错
    if(!audioChannel && !videoChannel){
        callHelper->onError(pid, 6);
        __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "没有找到媒体流");
        return;
    }

    //准备完毕 , 此时可以通知 Java 层开始播放 , 2 代表子线程
    callHelper->onPrepare(2);
}

//播放器准备方法
void FFMPEG::prepare() {

    //创建线程进行准备工作
    //  在线程中进行音视频文件或文件流解析
    pthread_create(&pid, 0, pthread_prepare, this);

}


//播放音视频
void* play(void* args){

    //将线程方法参数转为 FFMPEG * 对象 , 并调用 FFMPEG 对象的 _start() 方法
    FFMPEG *ffmpeg = static_cast<FFMPEG *>(args);
    ffmpeg->_start();

    //子线程方法 , 一定要 return 0 , 否则出现很难查找的错误
    return 0;
}


//开始播放方法
void FFMPEG::start() {

    /*
        本方法主要工作 : 解码

        这里要注意线程 : 要考虑该方法在主线程调用 , 子线程调用两种情况 , 必须考虑在不同的线程调用方法的情况
     */

    //设置当前正在播放
    isPlaying = 1;

    //设置 音 / 视频 AVPacket * 队列工作状态
    //  注意判空
    if(videoChannel){
        videoChannel->avPackets.setWork(1);

        if(audioChannel){
            videoChannel->setAudioChannel(audioChannel);
        }

        //开始播放 , 这里是播放入口
        videoChannel->play();
    }

    //注意判空 , 确保执行前已经初始化
    if(audioChannel){
        audioChannel->avPackets.setWork(1);

        //开始播放音频
        audioChannel->play();
    }


    //将线程 ID 存储到 pid_play 成员变量中 , 调用 void* play(void* args) 方法作为线程的执行内容
    //      传入 this 对象作为线程函数的参数 , 使用static_cast 可以将该参数强转为 FFMPEG 对象
    pthread_create(&pid_play, 0, play , this);

}

void FFMPEG::_start() {

    //1 . 读取音视频数据包
    //      如果当前是正在播放状态 , 那么不停的读取数据包 , 并解码
    while (isPlaying){

        //如果读取本地文件 , 可能一次性读取很多包 , 一万包 , 直接 OOM
        //  如果未处理的包太多 , 休眠一会 , 再继续读取
        if(audioChannel && audioChannel->avPackets.size() > 200){
            av_usleep(10 * 1000);
            continue;
        }
        if(videoChannel && videoChannel->avPackets.size() > 200){
            av_usleep(10 * 1000);
            continue;
        }


        //读取数据包
        // AVPacket 存放编码后的音视频数据的 , 获取该数据包后 , 需要对该数据进行解码 , 解码后将数据存放在 AVFrame 中
        // AVPacket 是编码后的数据 , AVFrame 是编码前的数据

        //创建 AVPacket 空数据包
        AVPacket *avPacket = av_packet_alloc();

        /*
            读取数据包 , 并存储到 AVPacket 数据包中

            参数分析 : 一维指针 与 二维指针 参数分析
              ① 注意 : 第二个参数是 AVPacket * 类型的 , 那么传入 AVPacket *avPacket 变量
                    不能修改 avPacket 指针的指向 , 即该指针指向的结构体不能改变
                    只能修改 avPacket 指向的结构体中的元素的值
                      因此 , 传入的 avPacket 结构体指针必须先进行初始化 , 然后再传入
                          av_read_frame 函数内 , 没有修改 AVPacket *avPacket 的值 , 但是修改了结构体中元素的值
              ② 与此相对应的是 avformat_open_input 方法 , 传入 AVFormatContext ** 二维指针
                  传入的的 AVFormatContext ** 是没有经过初始化的 , 连内存都没有分配
                  在 avformat_open_input 方法中创建并初始化 AVFormatContext * 结构体指针
                  然后将该指针地址赋值给 AVFormatContext **
                      avformat_open_input 函数内修改了 AVFormatContext ** 参数的值
            返回值 0 说明读取成功 , 小于 0 说明读取失败 , 或者 读取完毕
         */
        int read_frame_result = av_read_frame(formatContext, avPacket);

        /*
            返回值处理 :
                如果返回值 == 0 , 说明读取成功 ;
                如果返回值 < 0 , 有两种情况 , 失败 或者 读取完毕 , 这两种情况要分别处理
         */
        if(read_frame_result == 0){

            //读取成功

            /*
                之前有记录每个 音视频流的属性
                    在遍历 formatContext->nb_streams 音视频流 (AVStream *) 结构体指针数组时
                    可以将每个序号索引对应的流的属性记录下来

                判定时注意 : 确保 音频流解析器 audioChannel 和 视频流解析器 videoChannel 不为空
                            然后再根据其 音 / 视 频流 ID 索引 判定该读取的帧数据是什么类型的数据
             */
            if(audioChannel && avPacket->stream_index == audioChannel->id){

                //音频流
                //将读取的音频数据帧存储到队列中
                audioChannel->avPackets.push(avPacket);

            }else if(videoChannel && avPacket->stream_index == videoChannel->id){

                //视频流处理

                //将读取的视频数据帧存储到队列中
                videoChannel->avPackets.push(avPacket);

            }


        }else if(read_frame_result == AVERROR_EOF){

            //读取完毕 , 但是当前还没有播放完毕
            if(     audioChannel->avPackets.empty() &&
                    audioChannel->avFrames.empty() &&
                    videoChannel->avPackets.empty() &&
                    videoChannel->avFrames.empty()  ){

                //只有 音频 和 视频 的所有 AVPacket 和 AVFrame 待处理队列清空了 ,
                //      才说明播放完毕 , 此时才能退出循环
                break;

            }


        }else{

            //这里 av_read_frame 读取数据帧出现错误 ,  肯定是打开文件失败 , 直接退出即可

            callHelper->onError(pid, 5);
            __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "打开 编解码器 失败");
            return;

        }

        
    }//while (isPlaying)

    //停止操作的核心
    audioChannel->stop();
    videoChannel->stop();
}
/**
 * 将图像绘制回调函数从 native-lib.cpp 中传递给 VideoChannel.h
 *
 * @param callback
 */
void FFMPEG::setShowFrameCallback(ShowFrameCallback callback) {

    this->callback = callback;

}

/**
 * 线程方法 , 在该线程中停止播放
 * @param args
 * @return
 */
void *thread_stop(void *args){

    //对照 FFMPEG 中的start 方法进行相关变量的释放

    //获取参数 , 即 FFMPEG 类对象
    FFMPEG *ffmpeg = static_cast<FFMPEG *>(args);

    //阻塞等待 pid 准备线程执行完毕 , prepare 准备完毕后执行下面的操作
    pthread_join(ffmpeg->pid, 0);

    //阻塞等待 pid_play start 开始播放 线程执行完毕
    pthread_join(ffmpeg->pid_play, 0);

    //释放音视频解码播放器
    delete ffmpeg->videoChannel;
    delete ffmpeg->audioChannel;

    //释放 编解码器 上下文对象 AVFormatContext *formatContext
    if(ffmpeg->formatContext) {
        // 先关闭读取 , 再释放上下文对象
        //      关闭网络读取 或 本地的文件输入流
        avformat_close_input(&ffmpeg->formatContext);
        avformat_free_context(ffmpeg->formatContext);
        ffmpeg->formatContext = 0;
    }

    //释放 Native 层播放器对象
    delete ffmpeg;

    //  注意判空
    /*if(ffmpeg->videoChannel){
        //视频停止播放
        ffmpeg->videoChannel->stop();
    }

    //注意判空 , 确保执行前已经初始化
    if(ffmpeg->audioChannel){
        //音频停止播放
        ffmpeg->audioChannel->stop();
    }*/


}


/**
 * 停止播放
 *  与 start 方法对应
 */
void FFMPEG::stop() {

    //设置停止播放
    isPlaying = 0;

    /*
        必须保证 prepare 执行完毕才能释放相关操作
        需要阻塞等待 prepare 执行完毕 , 但是该 stop 函数是从主线程调用的
        如果阻塞 , 会直接将主线程阻塞住 , 因此需要创建一个线程 , 进行相关变量的释放操作
     */
    pthread_create(&pid_stop, 0, thread_stop, this);

}
