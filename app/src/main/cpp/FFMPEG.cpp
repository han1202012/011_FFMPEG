//
// Created by octopus on 2020/2/25.
//

#include "FFMPEG.h"

//构造方法
FFMPEG::FFMPEG(JavaCallHelper *callHelper, const char *dataSource) {

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
    delete callHelper;

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

//实际的准备方法
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
    //  返回值说明 : 返回 0 , 代表打开成功 , 否则失败
    //              失败的情况 : 文件路径错误 , 网络错误
    //int avformat_open_input(AVFormatContext **ps, const char *url,
    //                          AVInputFormat *fmt, AVDictionary **options);
    formatContext = 0;
    int open_result = avformat_open_input(&formatContext, dataSource, 0, 0);

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



        //一般情况下 , 视频直播流只包含 视频流 和 音频流
        if(codecParameters->codec_type == AVMEDIA_TYPE_AUDIO){

            //音频
            audioChannel = new AudioChannel;

        }else if(codecParameters->codec_type == AVMEDIA_TYPE_VIDEO){

            //视频
            videoChannel = new VideoChannel;

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

    //将线程 ID 存储到 pid_play 成员变量中 , 调用 void* play(void* args) 方法作为线程的执行内容
    //      传入 this 对象作为线程函数的参数 , 使用static_cast 可以将该参数强转为 FFMPEG 对象
    pthread_create(&pid_play, 0, play , this);

}

void FFMPEG::_start() {

    //1 . 读取音视频数据包


    //2 . 解码

}