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


#include "safe_queue.h"

class BaseChannel {

public:



    //此处传入的 id 参数 , 直接设置给 id 成员变量
    //  通过初始化列表 , 初始化成员变量
    //  初始化列表项 id(id) 解读 : 括号外部的 id 表示成员变量名称 , 括号内部的 id 表示参数 id
    BaseChannel(int id):id(id){}

    //此处需要声明为虚方法 , 因为子类需要继承父类的方法
    //  如果不生命虚函数 , 那么调用析构函数时 , 只会调用父类的析构函数 , 不会调用子类的析构函数
    virtual ~BaseChannel(){

        //析构方法中需要将 SafeQueue<AVPacket*> avPackets; 成员变量释放掉

        //AVPacket* 结构体指针使用的是 av_packet_alloc() 方法在堆内存中创建的
        //  需要使用专门的释放方法 void av_packet_free(AVPacket **pkt) , 注意传入的是二维指针

        //设置一个回调函数 , 该回调函数会在调用 clear() 方法时 , 将清除的元素释放
        avPackets.setReleaseHandle(BaseChannel::releaseAVPacket);

        //清除队列
        avPackets.clear();

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
     * 开始播放
     *
     * 这是一个纯虚函数 , 相当于 Java 中的抽象方法
     * 子类继承了 BaseChannel 类 , 必须要实现该纯虚函数
     */
    virtual void play() = 0;





    /**
     * 存储当前解析类型对应的 音视频流 索引序号
     */
    int id;

    /**
     * 安全队列 , 存放音视频流中的真数据包 AVPacket 结构体指针
     */
    SafeQueue<AVPacket*> avPackets;

    /**
     * 当前是否正在播放中
     */
    bool isPlaying;

};


#endif //INC_011_FFMPEG_BASECHANNEL_H
