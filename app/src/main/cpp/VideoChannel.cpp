//
// Created by octop on 2020/3/2.
//

#include "VideoChannel.h"

VideoChannel::VideoChannel(int id) : BaseChannel(id) {}


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
 * 解码 并 播放视频
 *
 * 注意 : 解码 播放操作 非常耗时 , 这个操作不能阻塞调用的方法 , 因此需要在线程中执行该操作
 */
void VideoChannel::play() {

    //设置播放标志位为 1 , 代表当前正在播放中
    isPlaying = 1;

    //创建并执行解码线程
    pthread_create(&pid_decode , 0 , decode_thread , this);

}

/**
 * 解码操作
 *
 * 循环遍历队列 , 从队列中取出数据 , 并解码
 */
void VideoChannel::decode() {

    //从线程安全队列中获取的视频数据包
    AVPacket * avPacket = 0;

    while (isPlaying){

        //这里需要修改 avPacket 指针的指向
        //  使用 AVPacket ** 二维指针 参数 , 或者使用 AVPacket * 一维引用类型参数
        avPackets.pop(avPacket);

    }


}