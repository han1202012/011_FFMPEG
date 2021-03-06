//
// Created by octop on 2020/3/5.
//

#ifndef INC_011_FFMPEG_BASECHANNEL_H
#define INC_011_FFMPEG_BASECHANNEL_H

//C++ 中导入 FFMPEG 包 , 必须添加 extern "C"
//  因为 FFMPEG 是使用 C 实现的 , 其方法和函数库都是 C 的
//  这里要做 C / C++ 兼容
extern "C"{
#include <libavcodec/avcodec.h>
};

//导入转换图像格式的库 SwsContext 定义在该库中
extern "C"{
#include <libswscale/swscale.h>
}


#include "SafeQueue.h"
#include "JavaPlayerCaller.h"

class BaseChannel {

public:

    //此处传入的 id 参数 , 直接设置给 id 成员变量
    //  通过初始化列表 , 初始化成员变量
    //  初始化列表项 id(id) 解读 : 括号外部的 id 表示成员变量名称 , 括号内部的 id 表示参数 id
    BaseChannel(int id, AVCodecContext *avCodecContext, AVRational time_base):id(id), avCodecContext(avCodecContext), time_base(time_base){

        //设置 SafeQueue<AVFrame *> avFrames 安全队列释放回调方法
        avFrames.setReleaseHandle(releaseAVFrame);

        //设置一个回调函数 , 该回调函数会在调用 clear() 方法时 , 将清除的元素释放
        avPackets.setReleaseHandle(BaseChannel::releaseAVPacket);

    }

    //此处需要声明为虚方法 , 因为子类需要继承父类的方法
    //  如果不生命虚函数 , 那么调用析构函数时 , 只会调用父类的析构函数 , 不会调用子类的析构函数
    virtual ~BaseChannel(){

        //析构方法中需要将 SafeQueue<AVPacket*> avPackets; 成员变量释放掉

        //AVPacket* 结构体指针使用的是 av_packet_alloc() 方法在堆内存中创建的
        //  需要使用专门的释放方法 void av_packet_free(AVPacket **pkt) , 注意传入的是二维指针

        //清除队列
        avPackets.clear();

        //释放 SafeQueue<AVFrame *> avFrames 安全队列资源
        avFrames.clear();

        if(avCodecContext){
            avcodec_close(avCodecContext);
            avcodec_free_context(&avCodecContext);
            avCodecContext = 0;
        }

    }

    /**
     * 释放 AVPacket
     * @param avPacket
     *          参数是 AVPacket* 类型的 引用类型 , & 符号是引用类型的意思
     */
    static void releaseAVPacket(AVPacket*& avPacket){
        av_packet_free(&avPacket);
    }

    /**
     * 释放 AVFrame
     * @param avFrame
     *          参数是 AVFrame* 类型的 引用类型 , & 符号是引用类型的意思
     */
    static void releaseAVFrame(AVFrame*& avFrame){
        av_frame_free(&avFrame);
    }

    void clear() {
        avPackets.clear();
        avFrames.clear();
    }

    void stopWork() {
        avPackets.setWork(0);
        avFrames.setWork(0);
    }

    void startWork() {
        avPackets.setWork(1);
        avFrames.setWork(1);
    }

    /**
     * 开始播放
     *
     * 这是一个纯虚函数 , 相当于 Java 中的抽象方法
     * 子类继承了 BaseChannel 类 , 必须要实现该纯虚函数
     */
    virtual void play() = 0;

    /**
     * 停止播放
     *      抽象方法
     */
    virtual void stop() = 0;


    /**
     * 存储当前解析类型对应的 音视频流 索引序号
     */
    int id;

    /**
     * 编码数据包队列 , 保存编码后的视频或音频 , 不能用于直接播放 , 需要先解码再使用
     * 安全队列 , 存放音视频流中的真数据包 AVPacket 结构体指针
     */
    SafeQueue<AVPacket*> avPackets;

    /**
     * 解码数据包队列 , 该音视频数据可以直接拿来播放
     * 保存解码后的图像 或 音频
     *      绘制线程中一直读取并绘制该图像 或 播放该音频
     */
    SafeQueue<AVFrame *> avFrames;

    /**
     * 当前是否正在播放中
     */
    bool isPlaying;

    /**
     * 解码器上下文
     *      从音视频流中查找编解码器 , 从编解码器中获取编解码器上下文
     */
    AVCodecContext *avCodecContext;

    /**
     * 时间单位
     */
    AVRational time_base;

    /**
     * 时间戳 : 视频帧的相对显示时间
     * 相对概念 : 这个时间是相对于开始播放的相对时间
     * 单位 : 秒
     */
    double audio_pts_second;
};


#endif //INC_011_FFMPEG_BASECHANNEL_H
