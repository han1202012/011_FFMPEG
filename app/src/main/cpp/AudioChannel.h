//
// Created by octop on 2020/3/2.
//

#ifndef INC_011_FFMPEG_AUDIOCHANNEL_H
#define INC_011_FFMPEG_AUDIOCHANNEL_H

#include "BaseChannel.h"

#include <android/log.h>

// OpenSLES 头文件
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

//音频重采样 , 注意兼容 C
extern "C"{
#include <libswresample/swresample.h>
};

class AudioChannel : public BaseChannel {
public:
    AudioChannel(int id, AVCodecContext *avCodecContext, AVRational time_base);
    ~AudioChannel();

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

    /**
     * 获取要播放的 PCM 采样数据
     * @return
     */
    int getPCM();

    /**
     * 存放重采样后的数据缓冲区  , 声明在 public 中目的是为了在外部也可以访问
     */
    uint8_t *data;

    void stop();

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
    SLObjectItf engineObject = NULL;

    /**
     * OpenSLES 引擎接口
     * typedef const struct SLEngineItf_ * const * SLEngineItf;
     * 该类型是一个二维指针
     */
    SLEngineItf engineEngine = NULL;


    /**
     * 输出混音器对象
     * 输出声音 , 添加各种音效 ( 混响 , 重低音 , 环绕音 , 均衡器 等 ) , 都要通过混音器实现
     */
    SLObjectItf outputMixObject = NULL;

    /**
     * 输出混音器混响效果器
     */
    SLEnvironmentalReverbItf outputMixEnvironmentalReverb = NULL;

    // 缓冲队列播放器使用的输出混音器设置的辅助效果
    SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;


    /**
     * 缓冲队列播放器接口
     */
    SLObjectItf bqPlayerObject = NULL;

    /**
     * 播放器接口
     */
    SLPlayItf bqPlayerPlay;

    /**
     * 缓冲队列接口
     */
    SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;

    /**
     * 效果器接口
     */
    SLEffectSendItf bqPlayerEffectSend;


    /**
     * 采样率
     */
    SLmilliHertz bqPlayerSampleRate = 0;


    /**
     * 音量控制接口
     */
    SLVolumeItf bqPlayerVolume;

    /**
     * 音频重采样上下文
     */
    SwrContext *swrContext = 0;

};


#endif //INC_011_FFMPEG_AUDIOCHANNEL_H
