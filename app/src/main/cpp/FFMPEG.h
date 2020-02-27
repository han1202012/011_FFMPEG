//
// Created by octopus on 2020/2/25.
//

#ifndef INC_011_FFMPEG_FFMPEG_H
#define INC_011_FFMPEG_FFMPEG_H

#include <pthread.h>
#include <cstring>

// 注意 FFMPEG 是 C 开发的 , 在 C++ 中使用需要使用 extern "C" 进行兼容
extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

//封装对视频的操作
class FFMPEG {


public: //类中默认都是私有的, 如果共有需要指定 public

    //构造函数
    FFMPEG(const char* dataSource);

    //析构函数
    ~FFMPEG();

    //播放器准备方法
    void prepare();

    void _prepare();
private:

    //保存数据源
    char* dataSource;

    //子线程id
    pthread_t pid;

    AVFormatContext *formatContext;

};


#endif //INC_011_FFMPEG_FFMPEG_H
