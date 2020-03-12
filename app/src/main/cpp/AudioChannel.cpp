//
// Created by octop on 2020/3/2.
//

#include "AudioChannel.h"

AudioChannel::AudioChannel(int id,AVCodecContext *avCodecContext) : BaseChannel(id, avCodecContext) {

}


/**
 * 解码 并 播放音频
 */
void AudioChannel::play() {

    //设置播放标志位为 1 , 代表当前正在播放中
    isPlaying = 1;

    // 设置 编码数据 , 解码数据 , 两个队列的运行状态
    avFrames.setWork(1);
    avPackets.setWork(1);

    // I . 解码音频

}