//
// Created by octop on 2020/3/2.
//

#ifndef INC_011_FFMPEG_AUDIOCHANNEL_H
#define INC_011_FFMPEG_AUDIOCHANNEL_H

#include "BaseChannel.h"

// OpenSLES 头文件
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

class AudioChannel : public BaseChannel {
public:
    AudioChannel(int id,AVCodecContext *avCodecContext);

    /**
     * 解码并播放音频
     */
    void play();

    /**
     * 解码方法
     */
    void decode();

    /**
     * 播放方法
     */
    void playback();

private:

    /**
     * 解码操作线程 所在的线程 id
     */
    pthread_t pid_decode;

    /**
     * 播放线程
     */
    pthread_t pid_playback;

    /**
     * OpenSLES 引擎对象
     * typedef const struct SLObjectItf_ * const * SLObjectItf;
     * 该类型是一个二维指针 , 声明时建议初始化成 0 , 防止出现不必要的错误
     */
    static SLObjectItf engineObject = NULL;

    /**
     * OpenSLES 引擎接口
     * typedef const struct SLEngineItf_ * const * SLEngineItf;
     * 该类型是一个二维指针
     */
    static SLEngineItf engineEngine = NULL;


    /**
     * 输出混音器对象
     * 输出声音 , 添加各种音效 ( 混响 , 重低音 , 环绕音 , 均衡器 等 ) , 都要通过混音器实现
     */
    static SLObjectItf outputMixObject = NULL;

    /**
     * 输出混音器混响效果器
     */
    static SLEnvironmentalReverbItf outputMixEnvironmentalReverb = NULL;

};


#endif //INC_011_FFMPEG_AUDIOCHANNEL_H
