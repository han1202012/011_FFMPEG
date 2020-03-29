//
// Created by octop on 2020/3/2.
//

#include "VideoChannel.h"

//导入转换图像格式的库 SwsContext 定义在该库中
extern "C"{
#include <libswscale/swscale.h>
#include <libavutil/time.h>
}


//申请图像内存相关的 av_image_alloc 方法定义在工具库中
extern "C"{
#include <libavutil/imgutils.h>
}

/**
 * 丢弃未解码的视频帧数据 , 用于和音频同步
 *
 *      该操作调用时 处于线程互斥锁 之间 , 因此不会产生线程互斥的问题
 *
 *      针对 I / P / B 帧 , 遇到 B / P 帧直接丢弃 , 直到遇到 I 帧
 *
 * @param q
 */
void dropAVPackets(queue<AVPacket *> &q){

    //该操作的队列就是线程安全队列中的数据存储 queue
    while (!q.empty()){

        AVPacket *avPacket = q.front();

        //如果不是关键帧 , 释放并移除队列
        if(avPacket->flags != AV_PKT_FLAG_KEY){

            //注意这里的参数是引用类型参数
            BaseChannel::releaseAVPacket(avPacket);
            q.pop();

        }else{

            //如果是关键帧 , 终止丢包操作
            break;

        }

    }

}


/**
 * 丢弃解码后的视频帧数据 , 用于和音频同步
 *
 *      该操作调用时 处于线程互斥锁 之间 , 因此不会产生线程互斥的问题
 *
 *      这个随意丢弃 , 没有 I / B / P 帧种类限制 , 每一帧都是一张完整图片 , 前后没有依赖关系
 *
 *      每次丢一个包
 *
 * @param q
 */
void dropAVFrames(queue<AVFrame *> &q){

    //该操作的队列就是线程安全队列中的数据存储 queue
    if (!q.empty()){

        AVFrame *avFrame = q.front();

        //注意这里的参数是引用类型参数
        BaseChannel::releaseAVFrame(avFrame);
        q.pop();

    }

}



VideoChannel::VideoChannel(int id, AVCodecContext *avCodecContext, AVRational time_base, int fps) : BaseChannel(id, avCodecContext, time_base) {

    this->fps = fps;

    //为 avPackets 线程安全队列 , 设置丢包的函数指针 , 用以支持音视频同步
    //  设置了该函数指针之后 , 一旦回调线程安全队列的 sync 方法 , 在该方法中会和回调 dropAVPackets 方法 ;
    avPackets.setSyncHandle(dropAVPackets);

    //为 AVFrame 线程安全队列 , 设置丢弃数据帧的函数指针回调 , 用于实现音视频同步
    avFrames.setSyncHandle(dropAVFrames);
}

/**
 * 析构方法
 */
VideoChannel::~VideoChannel() {

}


/**
 * 设置音频解码播放对象
 * @param audioChannel
 */
void VideoChannel::setAudioChannel(AudioChannel *audioChannel) {

    this->audioChannel = audioChannel;

}


/**
 * 线程中的解码操作
 *
 * @param args
 *      传递的是 VideoChannel 对象 , 目的是方便调用 VideoChannel 对象的成员变量和方法
 * @return
 */
void* decode_thread (void* args){

    //调用解码成员函数
    //  需要将 void* args 参数 , 强制转换为 VideoChannel * 参数
    VideoChannel *videoChannel = static_cast<VideoChannel *>(args);

    //调用 videoChannel 对象的 decode() 方法
    videoChannel->decode();

    //注意线程函数需要 返回 0 , 否则造成不可预知错误
    return 0;
}

/**
 * 线程中的绘制操作
 *
 * @param args
 *      传递的是 VideoChannel 对象 , 目的是方便调用 VideoChannel 对象的成员变量和方法
 * @return
 */
void* show_thread (void* args){

    //调用解码成员函数
    //  需要将 void* args 参数 , 强制转换为 VideoChannel * 参数
    VideoChannel *videoChannel = static_cast<VideoChannel *>(args);

    //调用 videoChannel 对象的 decode() 方法
    videoChannel->show();

    //注意线程函数需要 返回 0 , 否则造成不可预知错误
    return 0;
}


/**
 * 解码 并 播放视频
 *
 * 注意 : 解码 播放操作 非常耗时 , 这个操作不能阻塞调用的方法 , 因此需要在线程中执行该操作
 */
void VideoChannel::play() {

    //设置播放标志位为 1 , 代表当前正在播放中
    isPlaying = 1;

    //设置两个队列的运行状态
    avFrames.setWork(1);
    avPackets.setWork(1);

    //创建并执行解码线程
    pthread_create(&pid_decode , 0 , decode_thread , this);

    //创建并执行绘制线程
    pthread_create(&pid_show , 0 , show_thread , this);


}

/**
 * 解码操作
 *
 * 循环遍历队列 , 从队列中取出数据 , 并解码
 */
void VideoChannel::decode() {

    //从线程安全队列中获取的视频数据包
    AVPacket *avPacket = 0;

    while (isPlaying){

        //这里需要修改 avPacket 指针的指向
        //  使用 AVPacket ** 二维指针 参数 , 或者使用 AVPacket * 一维引用类型参数
        int result_pop = avPackets.pop(avPacket);

        //判断当前是否正在播放 , 如果没有播放 , 直接退出循环
        if(!isPlaying){
            break;
        }

        //根据 result_pop 判断是否取出成功
        if(!result_pop){

            //如果本次取出失败 , 不要退出循环 , 继续下一次循环 , 下次继续重新尝试获取
            continue;

        }

        /*
            解码操作 :
                将 AVPacket 发送给解码器
                解码器接收 AVPacket 数据并解码

            FFMPEG 解码与 MediaCodec 工作流程类似
         */

        /*
         *  ① 发送数据包
            将数据包发送给解码器 , 返回 0 成功 , 其它失败
                AVERROR(EAGAIN): 说明当前解码器满了 , 不能接受新的数据包了
                                 这里先将解码器的数据都处理了, 才能接收新数据
                其它错误处理 : 直接退出循环
         */
        int result_send_packet = avcodec_send_packet(avCodecContext, avPacket);

        //本次循环中 , 将 AVPacket 丢到解码器中解码完毕后 , 就可以释放 AVPacket 内存了
        releaseAVPacket(avPacket);

        if(result_send_packet != 0){
            //发送失败 , 直接退出
            break;
        }

        //② 接收并解码数据包 , 存放在 AVFrame 中

        //用于存放解码后的数据包 , 一个 AVFrame 代表一个图像
        AVFrame *avFrame = av_frame_alloc();

        //解码器中将数据包解码后 , 存放到 AVFrame * 中 , 这里将其取出并解码
        //  返回 AVERROR(EAGAIN) : 当前状态没有输出 , 需要输入更多数据
        //  返回 AVERROR_EOF : 解码器中没有数据 , 已经读取到结尾
        //  返回 AVERROR(EINVAL) : 解码器没有打开
        int result_receive_frame = avcodec_receive_frame(avCodecContext, avFrame);

        //失败处理
        if(result_receive_frame != 0){

            if(result_receive_frame == AVERROR(EAGAIN)){

                //当前状态没有输出 , 需要输入更多数据
                continue;

            } else {

                //其它错误情况 , 先暂停循环
                break;
            }
        }

        //此时已经拿到了 AVFrame *avFrame , 即拿到了一个图像 , 这里再开启一个线程 , 播放该图像
        //      将该图像数据 , 放到队列中 , 此时 绘制线程从队列中获取该数据 , 并绘制该图像到播放器中
        avFrames.push(avFrame);



    }

    //上面将 AVPact * 包取出来 , 这里要将其内存释放
    //  注意这里的参数是引用类型参数
    //  释放 AVPacket *avPacket 内存 , 即修改该指针指向 , 使用 AVPacket ** 二维指针类型参数
    //      或 AVPacket &*avPacket 一维指针 引用类型参数
    releaseAVPacket(avPacket);


}

/**
 * 播放操作
 *      这里需要使用 SurfaceView 中的 Surface 画布
 *      画布创建完毕后 , 回调 surfaceCreated(SurfaceHolder holder) 方法
 *      画布大小发生改变时 , 回调 surfaceChanged(SurfaceHolder holder, int format, int width, int height) 方法
 *      此时我们在画布发生改变时 , 将 Surface 画布传到 Native 层处理
 */
void VideoChannel::show() {

    //将当前的图像内存排列样式转换成 RGBA 格式的
    //  一般的视频图像排列样式是 YUV 格式的

    /*
        struct SwsContext *sws_getContext(int srcW, int srcH, enum AVPixelFormat srcFormat,
                                  int dstW, int dstH, enum AVPixelFormat dstFormat,
                                  int flags, SwsFilter *srcFilter,
                                  SwsFilter *dstFilter, const double *param);
     */
    SwsContext *swsContext = sws_getContext(
            //源图像的 宽 , 高 , 图像像素格式
            avCodecContext->width, avCodecContext->height, avCodecContext->pix_fmt,

            //目标图像 大小不变 , 不进行缩放操作 , 只将像素格式设置成 RGBA 格式的
            avCodecContext->width, avCodecContext->height, AV_PIX_FMT_RGBA,

            //使用的转换算法 , FFMPEG 提供了许多转换算法 , 有快速的 , 有高质量的 , 需要自己测试
            SWS_BILINEAR,

            //源图像滤镜 , 这里传 NULL 即可
            0,

            //目标图像滤镜 , 这里传 NULL 即可
            0,

            //额外参数 , 这里传 NULL 即可
            0
            );


    //根据帧率 ( fps ) 计算两次图像绘制之间的间隔
    //  注意单位换算 : 实际使用的是微秒单位 , 使用 av_usleep ( ) 方法时 , 需要传入微秒单位 , 后面需要乘以 10 万
    double frame_delay = 1.0 / fps;


    //定义从安全队列中获取的 AVFrame *
    AVFrame *avFrame = 0;

    //指针数组 , 数组中存放的是指针
    uint8_t *dst_data[4];

    //普通的 int 数组
    int dst_linesize[4];

    //初始化 dst_data 和 dst_linesize , 为其申请内存 , 注意使用完毕后需要释放内存
    av_image_alloc(dst_data, dst_linesize,
                   avCodecContext->width, avCodecContext->height, AV_PIX_FMT_RGBA,
                   1);


    while (isPlaying){

        //从线程安全队列中获取 AVFrame * 图像
        int result_pop = avFrames.pop(avFrame);

        //循环终止条件
        if(!isPlaying){
            break;
        }

        /*
            转换图像像素格式

            int sws_scale(struct SwsContext *c, const uint8_t *const srcSlice[],
              const int srcStride[], int srcSliceY, int srcSliceH,
              uint8_t *const dst[], const int dstStride[]);
         */
        sws_scale(
                //SwsContext *swsContext 转换上下文
                swsContext,

                //要转换的数据内容
                avFrame->data,

                //数据中每行的字节长度
                avFrame->linesize,

                0,

                avFrame->height,

                //转换后目标图像数据存放在这里
                dst_data,

                //转换后的目标图像行数
                dst_linesize
                );


        //获取当前画面的相对播放时间 , 相对 : 即从播放开始到现在的时间
        //  该值大多数情况下 , 与 pts 值是相同的
        //  该值比 pts 更加精准 , 参考了更多的信息
        //  转换成秒 : 这里要注意 pts 需要转成 秒 , 需要乘以 time_base 时间单位
        //  其中 av_q2d 是将 AVRational 转为 double 类型
        double vedio_best_effort_timestamp_second = avFrame->best_effort_timestamp * av_q2d(time_base);

        //解码时 , 该值表示画面需要延迟多长时间在显示
        //  extra_delay = repeat_pict / (2*fps)
        //  需要使用该值 , 计算一个额外的延迟时间
        //  这里按照文档中的注释 , 计算一个额外延迟时间
        double extra_delay = avFrame->repeat_pict / ( fps * 2 );

        //计算总的帧间隔时间 , 这是真实的间隔时间
        double total_frame_delay = frame_delay + extra_delay;

        //将 total_frame_delay ( 单位 : 秒 ) , 转换成 微秒值 , 乘以 10 万
        unsigned microseconds_total_frame_delay = total_frame_delay * 1000 * 1000;

        if(vedio_best_effort_timestamp_second == 0 || !audioChannel){

            //如果播放的是第一帧 , 或者当前音频没有播放 , 就要正常播放

            //休眠 , 单位微秒 , 控制 FPS 帧率
            av_usleep(microseconds_total_frame_delay);

        }else{

            //如果不是第一帧 , 要开始考虑音视频同步问题了

            //获取音频的相对时间
            if(audioChannel != NULL) {

                //音频的相对播放时间 , 这个是相对于播放开始的相对播放时间
                double audio_pts_second = audioChannel->audio_pts_second;

                //使用视频相对时间 - 音频相对时间
                double second_delta = vedio_best_effort_timestamp_second - audio_pts_second;

                //将相对时间转为 微秒单位
                unsigned microseconds_delta = second_delta * 1000 * 1000;


                //如果 second_delta 大于 0 , 说明视频播放时间比较长 , 视频比音频快
                //如果 second_delta 小于 0 , 说明视频播放时间比较短 , 视频比音频慢

                if(second_delta > 0){

                    //视频快处理方案 : 增加休眠时间

                    //休眠 , 单位微秒 , 控制 FPS 帧率
                    av_usleep(microseconds_total_frame_delay + microseconds_delta);

                }else if(second_delta < 0){

                    //视频慢处理方案 :
                    //  ① 方案 1 : 减小休眠时间 , 甚至不休眠
                    //  ② 方案 2 : 视频帧积压太多了 , 这里需要将视频帧丢弃 ( 比方案 1 极端 )
                    if(fabs(second_delta) >= 0.05){

                        /*
                            如果音视频差距超过了 0.05 秒 , 就开始丢弃视频包 , 使用 方案 2
                            在视频播放中 , 有 AVPacket 队列 , 和 AVFrame 队列 两个队列
                            两种包都可以丢弃

                            丢包注意点 :

                            H.264 编码的帧有三种类型 , I / P / B 三种 ;
                                I 帧 ( I Frame ) : 帧内编码帧 , 可以单独解码并显示 ;

                                P 帧 ( P Frame ) : 前向预测编码帧 , 如果要解码 P 帧 , 需要参考 P 帧前面的编码帧 ;

                                I / P 帧 举例 : 在一个房间内 , 人在动 , 房间背景不懂 , I 帧是完整的画面 ,
                                               其后面的 P 帧只包含了相对于 I 帧改变的画面内容 , 大部分房间
                                               背景都需要从 I 帧提取

                                丢弃的帧不能是 I 帧

                                B 帧 ( B Frame ) : 双向预测帧 , 解码 B 帧 , 需要参考前面的编码帧 和 后面的编码帧

                                编解码的时间与空间考量 :
                                编码 : B 帧 和 P 帧 的使用 , 能大幅度减小视频的空间 ;
                                解码 :  I 帧 解码时间最短 , 最占用空间
                                        P 帧解码时间稍长 , 需要参考前面的帧进行解码 , 能小幅度节省空间
                                        B 帧解码时间最长 , 需要参考前后两帧进行解码 , 能大幅度节省空间


                             丢弃数据帧包时需要注意的操作 :
                                I 帧不能丢 , 只能丢弃 B 帧 和 P 帧 ;
                                如果丢弃 I 帧 , 就需要将 I 帧后面的 B / P 帧 都要丢掉 , 直到下一个 I 帧
                                一般情况下是将两个 I 帧之间的 B / P 帧丢弃 ; 因为丢掉一帧 B 帧或 P 帧 ,
                                    意味着后面的 B / P 帧也无法解析了 , 后面的 B / P 帧也一并丢弃 , 直到遇到 I 帧


                            B 帧 / P 帧 产生 : 在编码时 , 可以手动设置是否产生 B 帧 , 可以只产生 P 帧 ;

                         */

//#define DROP_PACKET

#ifdef DROP_AV_PACKET

                        //启动 AVPacket 队列丢包
                        avPackets.sync();

#else
                        //当前的视频帧不绘制了 , 马上释放掉
                        releaseAVFrame(avFrame);

                        //丢弃解码后的视频帧
                        avFrames.sync();

                        //终止本次循环 , 继续下一次视频帧绘制
                        continue;


#endif

                    }else{

                        //如果音视频之间差距低于 0.05 秒 , 不操作 ( 50ms )

                    }
                }

            }

        }



        //调用回调函数 , 绘制 解码后的图像

        //这里传入数组的第 0 个元素即可 , 数组第 0 个元素地址就是指针的首地址
        //  这也是释放该数据时只释放第 0 个元素就可以的原因
        callback(dst_data[0], dst_linesize[0], avCodecContext->width, avCodecContext->height);

        //本次循环中绘制完毕 , 此时可以释放绘制完毕的 AVFrame * 元素 , 传入的参数是引用类型的
        releaseAVFrame(avFrame);


    }


    //释放绘制完成后的解码后的图像
    av_freep(&dst_data[0]);

    //释放绘制完毕的 AVFrame * 元素 , 传入的参数是引用类型的
    releaseAVFrame(avFrame);

    //设置播放状态 0
    isPlaying = 0;

    //释放图像格式转换上下文对象
    sws_freeContext(swsContext);
    //swsContext = 0;
}

/**
 * 设置绘制解码后图像的回调函数
 * @param callback
 */
void VideoChannel::setShowFrameCallback(ShowFrameCallback callback) {
    this->callback = callback;
}

void VideoChannel::stop() {

    //对照 start 方法中的操作

    //设置播放状态 0
    isPlaying = 0;

    //将两个线程安全队列的工作状态设置成 0 , 即不工作
    avFrames.setWork(0);
    avPackets.setWork(0);

    //等待解码操作执行完毕
    pthread_join(pid_decode, 0);

    //等待图像绘制线程执行完毕
    pthread_join(pid_show, 0);

}
