//
// Created by octop on 2020/3/2.
//

#ifndef INC_011_FFMPEG_AUDIOCHANNEL_H
#define INC_011_FFMPEG_AUDIOCHANNEL_H


#include "BaseChannel.h"

class AudioChannel : public BaseChannel {
public:
    AudioChannel(int id);

    /**
     * 解码并播放音频
     */
    void play();
};


#endif //INC_011_FFMPEG_AUDIOCHANNEL_H
