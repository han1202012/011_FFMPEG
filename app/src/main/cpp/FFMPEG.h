//
// Created by octopus on 2020/2/25.
//

#ifndef INC_011_FFMPEG_FFMPEG_H
#define INC_011_FFMPEG_FFMPEG_H

#include <pthread.h>
#include <cstring>
#include <android/log.h>
#include "JavaPlayerCaller.h"
#include "AudioChannel.h"
#include "VideoChannel.h"

// 注意 FFMPEG 是 C 开发的 , 在 C++ 中使用需要使用 extern "C" 进行兼容
extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/time.h>
}

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"FFMPEG",__VA_ARGS__)

//封装对视频的操作
class FFMPEG {


public: //类中默认都是私有的, 如果共有需要指定 public

    //构造函数
    FFMPEG(JavaPlayerCaller *callHelper, const char* dataSource);

    //析构函数
    ~FFMPEG();

    //播放器准备方法
    void prepare();
    //子线程中调用该方法 , 目的是可以在该方法中随意调用 FFMPEG 类对象的成员变量
    void _prepare();

    //播放器开始播放方法
    void start();
    //子线程中调用该方法 , 目的是可以在该方法中随意调用 FFMPEG 类对象的成员变量
    void _start();

    /**
     * 设置图像绘制函数指针
     * @param callback
     */
    void setShowFrameCallback(ShowFrameCallback callback);

    void stop();

    int getDuration() {
        return duration;
    }

public:

    //保存数据源
    char* dataSource;

    //准备子线程 ID
    pthread_t pid;

    //播放子线程 ID
    pthread_t pid_play;

    /**
     * 停止子线程 ID
     */
    pthread_t pid_stop;



    /**
     * 编解码器 上下文环境
     */
    AVFormatContext *formatContext = 0;

    JavaPlayerCaller *callHelper;

    //注意 : 声明指针变量时 , 需要给一个默认值 , 尽量减少出现错误的几率

    //视频的长度
    int duration;

    //解析音频流
    AudioChannel *audioChannel = 0;

    //解析视频流
    VideoChannel *videoChannel = 0;

    //记录当前是否正在进行播放
    bool isPlaying;

    //绘制视频图像的回调函数 , void (*ShowFrameCallback)(uint8_t *, int, int, int) 类型函数指针
    ShowFrameCallback callback;

};


#endif //INC_011_FFMPEG_FFMPEG_H
