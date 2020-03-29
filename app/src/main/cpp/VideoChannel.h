//
// Created by octop on 2020/3/2.
//

#ifndef INC_011_FFMPEG_VIDEOCHANNEL_H
#define INC_011_FFMPEG_VIDEOCHANNEL_H


#include "BaseChannel.h"
#include "AudioChannel.h"

/**
 * 定义函数指针
 * 参数是解码后的图像信息
 *  uint8_t *dst_data[4];
 *  int dst_linesize[4];
 *
 *  后两个参数是图像的宽度和高度
 */
typedef void (*ShowFrameCallback)(uint8_t *, int, int, int);


/**
 * 主要工作 : 解码视频 , 并播放视频
 */
class VideoChannel : public BaseChannel {
public:


    VideoChannel(int id, AVCodecContext *avCodecContext, AVRational time_base, int fps);

    ~VideoChannel();

    /**
     * 解码并播放视频 1
     */
    void play();

    /**
     * 解码操作
     */
    void decode();

    /**
     * 显示操作
     */
    void show();

    /**
     * 设置图像绘制函数指针
     * @param callback
     */
    void setShowFrameCallback(ShowFrameCallback callback);


    /**
     * 获取音频对象
     *      主要是为了获取音频中的时间戳 , 用于进行音视频同步
     * @param audioChannel
     */
    void setAudioChannel (AudioChannel *audioChannel);


    void stop();

private:

    /**
     * 解码操作 所在的线程 id
     */
    pthread_t pid_decode;

    /**
     * 绘制线程
     */
    pthread_t pid_show;

    /**
     * 用于图像像素格式转换 YUV -> RGBA
     */
    SwsContext *swsContext = 0;

    /**
     * 图像绘制回调函数 函数指针
     */
    ShowFrameCallback callback;

    /**
     * 视频帧率 , 播放过程中会动态改变
     *  帧率越高 , 画面越流畅
     */
    int fps;

    /**
     * 音频解码播放处理对象
     *      主要用于获取音频的 pts , 用于音视频同步
     */
    AudioChannel *audioChannel;

};


#endif //INC_011_FFMPEG_VIDEOCHANNEL_H
