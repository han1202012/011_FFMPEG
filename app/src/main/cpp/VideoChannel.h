//
// Created by octop on 2020/3/2.
//

#ifndef INC_011_FFMPEG_VIDEOCHANNEL_H
#define INC_011_FFMPEG_VIDEOCHANNEL_H


#include "BaseChannel.h"

/**
 * 主要工作 : 解码视频 , 并播放视频
 */
class VideoChannel : BaseChannel {
public:
    VideoChannel(int id);

    /**
     * 解码并播放视频 1
     */
    void play();

    /**
     * 解码操作
     */
    void decode();


private:

    /**
     * 解码操作 所在的线程 id
     */
    pthread_t pid_decode;

};


#endif //INC_011_FFMPEG_VIDEOCHANNEL_H
