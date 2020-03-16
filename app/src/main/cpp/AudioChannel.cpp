//
// Created by octop on 2020/3/2.
//

#include "AudioChannel.h"

AudioChannel::AudioChannel(int id, AVCodecContext *avCodecContext, AVRational time_base) : BaseChannel(id, avCodecContext, time_base) {

    /**
     * 存放重采样后的数据缓冲区 , 这个缓冲区存储 1 秒的数据
     * 44100 Hz 采样率 , 16 位采样位数 , 双声道立体声 , 占用内存 44100 * 2 * 2 字节
     */
    data = static_cast<uint8_t *>(malloc(44100 * 2 * 2));

    //初始化内存数据
    memset(data, 0, 44100 * 2 * 2);

}

AudioChannel::~AudioChannel(){

    //释放 data 音频缓冲区
    if(data){
        free(data);
        data = 0;
    }

}




/**
 * 音频解码线程
 *
 * @param args
 * @return
 */
void* audio_decode(void* args){

    //获取参数 , 转为 AudioChannel 类型
    AudioChannel * audioChannel = static_cast<AudioChannel *>(args);

    //调用解码成员函数
    audioChannel->decode();

    //线程方法必须 return 0
    return 0;
}

/**
 * 音频播放线程
 *
 * @param args
 * @return
 */
void* audio_playback(void* args){

    //获取参数 , 转为 AudioChannel 类型
    AudioChannel * audioChannel = static_cast<AudioChannel *>(args);

    //调用播放成员函数
    audioChannel->playback();

    //线程方法必须 return 0
    return 0;
}



/**
 * 解码 并 播放音频
 */
void AudioChannel::play() {

    // I . 设置状态

    //设置播放标志位为 1 , 代表当前正在播放中
    isPlaying = 1;

    // 设置 编码数据 , 解码数据 , 两个队列的运行状态
    avFrames.setWork(1);
    avPackets.setWork(1);

    /*
     初始化音频重采样的上下文
     struct SwrContext *swr_alloc_set_opts(struct SwrContext *s,
        int64_t out_ch_layout, enum AVSampleFormat out_sample_fmt, int out_sample_rate,
        int64_t  in_ch_layout, enum AVSampleFormat  in_sample_fmt, int  in_sample_rate,
        int log_offset, void *log_ctx);
     */
    swrContext = swr_alloc_set_opts(
            0 ,                     //现在还没有 SwrContext 上下文 , 先传入 0

            //输出的音频参数
            AV_CH_LAYOUT_STEREO ,   //双声道立体声
            AV_SAMPLE_FMT_S16 ,     //采样位数 16 位
            44100 ,                 //输出的采样率

            //从编码器中获取输入音频格式
            avCodecContext->channel_layout, //输入的声道数
            avCodecContext->sample_fmt,     //输入的采样位数
            avCodecContext->sample_rate,    //输入的采样率
            0, 0    //日志参数 设置 0 即可
            );

    //注意创建完之后初始化
    swr_init(swrContext);


    // I . 解码音频

    //启动解码线程
    pthread_create(&pid_decode , 0 , audio_decode , this);

    // II . 播放视频

    //启动播放线程
    pthread_create(&pid_decode , 0 , audio_playback , this);


}

/**
 * 音频解码与视频解码代码一模一样
 */
void AudioChannel::decode() {

    //从线程安全队列中获取的视频数据包
    AVPacket *avPacket = 0;

    while (isPlaying) {

        //这里需要修改 avPacket 指针的指向
        //  使用 AVPacket ** 二维指针 参数 , 或者使用 AVPacket * 一维引用类型参数
        int result_pop = avPackets.pop(avPacket);

        //判断当前是否正在播放 , 如果没有播放 , 直接退出循环
        if (!isPlaying) {
            break;
        }

        //根据 result_pop 判断是否取出成功
        if (!result_pop) {

            //如果本次取出失败 , 不要退出循环 , 继续下一次循环 , 下次继续重新尝试获取
            continue;

        }

        /*
            解码操作 :
                将 AVPacket 发送给解码器
                解码器接收 AVPacket 数据并解码

            FFMPEG 解码与 MediaCodec 工作流程类似
         */

        /*
         *  ① 发送数据包
            将数据包发送给解码器 , 返回 0 成功 , 其它失败
                AVERROR(EAGAIN): 说明当前解码器满了 , 不能接受新的数据包了
                                 这里先将解码器的数据都处理了, 才能接收新数据
                其它错误处理 : 直接退出循环
         */
        int result_send_packet = avcodec_send_packet(avCodecContext, avPacket);

        //本次循环中 , 将 AVPacket 丢到解码器中解码完毕后 , 就可以释放 AVPacket 内存了
        releaseAVPacket(avPacket);

        if (result_send_packet != 0) {
            //发送失败 , 直接退出
            break;
        }

        //② 接收并解码数据包 , 存放在 AVFrame 中

        //用于存放解码后的数据包 , 一个 AVFrame 代表一个图像
        AVFrame *avFrame = av_frame_alloc();

        //解码器中将数据包解码后 , 存放到 AVFrame * 中 , 这里将其取出并解码
        //  返回 AVERROR(EAGAIN) : 当前状态没有输出 , 需要输入更多数据
        //  返回 AVERROR_EOF : 解码器中没有数据 , 已经读取到结尾
        //  返回 AVERROR(EINVAL) : 解码器没有打开
        int result_receive_frame = avcodec_receive_frame(avCodecContext, avFrame);

        //失败处理
        if (result_receive_frame != 0) {

            if (result_receive_frame == AVERROR(EAGAIN)) {

                //当前状态没有输出 , 需要输入更多数据
                continue;

            } else {

                //其它错误情况 , 先暂停循环
                break;
            }
        }

        //此时已经拿到了 AVFrame *avFrame , 即拿到了一个图像 , 这里再开启一个线程 , 播放该图像
        //      将该图像数据 , 放到队列中 , 此时 绘制线程从队列中获取该数据 , 并绘制该图像到播放器中
        avFrames.push(avFrame);

    }

    //上面将 AVPact * 包取出来 , 这里要将其内存释放
    //  注意这里的参数是引用类型参数
    //  释放 AVPacket *avPacket 内存 , 即修改该指针指向 , 使用 AVPacket ** 二维指针类型参数
    //      或 AVPacket &*avPacket 一维指针 引用类型参数
    releaseAVPacket(avPacket);

}


/**
 * 获取 PCM 采样数据
 * @return
 *      返回获取的 PCM 数据字节大小
 */
int AudioChannel::getPCM() {

    __android_log_print(ANDROID_LOG_INFO, "FFMPEG" , "getPCM()");

    //获取的 PCM 数据字节大小
    int pcm_data_bit_size = 0;

    // 之前将解码后的样本都 push 到了 SafeQueue<AVFrame *> avFrames 安全队列中
    //  从安全队列中获取解码后的音频数据
    AVFrame *avFrame;
    int result_pop = avFrames.pop(avFrame);

    if(!isPlaying){
        //如果当前没有播放 , 那么直接退出 , 退出前如果成功获取到了 AVFrame 数据 , 那么释放该数据
        if(result_pop){
            releaseAVFrame(avFrame);
        }
        return pcm_data_bit_size;
    }

    //OpenSLES 播放器设定播放的音频格式是 立体声 , 44100 Hz 采样 , 16位采样位数
    //  解码出来的 AVFrame 中的数据格式不确定 , 需要进行重采样

    /*
        int64_t swr_get_delay(
        struct SwrContext *s,
        int64_t base
        );

        转码的过程中 , 输入 10 个数据 , 并不一定都能处理完毕并输出 10 个数据 , 可能处理输出了 8 个数据
        还剩余 2 个数据没有处理

        那么在下一次处理的时候 , 需要将上次没有处理完的两个数据处理了 ;
        如果不处理上次的2个数据 , 那么数据会一直积压 , 如果积压数据过多 , 最终造成很大的延迟 , 甚至崩溃

        因此每次处理的时候 , 都要尝试将上次剩余没有处理的数据加入到本次处理的数据中

        如果计算出的 delay 一直等于 0 , 说明没有积压数据
     */
    int64_t delay = swr_get_delay(swrContext , avFrame->sample_rate);

    /*
        将 a 个数据 , 由 c 采样率转换成 b 采样率后 , 返回多少数据
        int64_t av_rescale_rnd(int64_t a, int64_t b, int64_t c, enum AVRounding rnd) av_const;

        下面的方法时将 avFrame->nb_samples 个数据 , 由 avFrame->sample_rate 采样率转为 44100 采样率
        返回的数据个数

        AV_ROUND_UP : 向上取整
     */
    int64_t out_count = av_rescale_rnd(
            avFrame->nb_samples + delay, //本次要处理的数据个数
            44100,
            avFrame->sample_rate ,
            AV_ROUND_UP );

    /*
     int swr_convert(
            struct SwrContext *s,   //上下文
            uint8_t **out,          //输出的缓冲区 ( 需要计算 )
            int out_count,          //输出的缓冲区最大可接受的样本个数 ( 需要计算 )
            const uint8_t **in ,    //输入的数据
            int in_count);          //输入的样本个数

    返回值 : 转换后的采样个数 , 是样本个数 , 每个样本是 16 位 , 两个字节 ;
            samples_out_count 是每个通道的样本数 , samples_out_count * 2 是立体声双声道样本个数
            samples_out_count * 2 * 2 是字节个数
     */
    int samples_per_channel_count = swr_convert(
            swrContext ,
            &data,
            out_count ,
            (const uint8_t **)avFrame->data, //普通指针转为 const 指针需要使用 const_cast 转换
            avFrame->nb_samples
            );

    //根据样本个数计算样本的字节数
    pcm_data_bit_size = samples_per_channel_count * 2 * 2;


    //计算该音频播放的 相对时间 , 相对 : 即从播放开始到现在的时间
    //  转换成秒 : 这里要注意 pts 需要转成 秒 , 需要乘以 time_base 时间单位
    //  其中 av_q2d 是将 AVRational 转为 double 类型
    audio_pts_second = avFrame->pts * av_q2d(time_base);

    return pcm_data_bit_size;
}



//每当缓冲数据播放完毕后 , 会自动回调该回调函数
// this callback handler is called every time a buffer finishes playing
void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
{
    //获取当前类 , 用于调用私有的 OpenSL ES 的相关成员变量
    AudioChannel *audioChannel = static_cast<AudioChannel *>(context);


    //获取 PCM 采样数据 , 将重采样的数据放到 AudioChannel 中的 data 成员中
    int data_size = audioChannel->getPCM();

    //开始播放
    if ( data_size > 0 ){

        //通过播放器队列接口 , 将 PCM 数据加入到该队列缓冲区后 , 就会自动播放这段音频
        //  注意 , 最后一个参数是样本字节数
        (*bq)->Enqueue(bq, audioChannel->data, data_size);
    }

}


/**
 * 实现播放方法
 *
 * 在该方法中使用 OpenSL ES 播放音频
 */
void AudioChannel::playback() {

    // I . 创建 OpenSLES 引擎并获取引擎的接口 ( 相关代码拷贝自 Google 官方示例 native-audio )
    //      参考 : https://github.com/android/ndk-samples/blob/master/native-audio/app/src/main/cpp/native-audio-jni.c

    //声明每个方法执行的返回结果 , 一般情况下返回 SL_RESULT_SUCCESS 即执行成功
    //  该类型本质是 int 类型 , 定义的是各种类型的异常
    SLresult result;

    // 创建引擎
    result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);

    // 返回 0 成功 , 否则失败 , 一旦失败就中断退出
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // 实现引擎
    result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // 获取引擎接口 , 使用该接口创建输出混音器 , 音频播放器等其它对象
    //      引擎对象不提供任何调用的方法 , 引擎调用的方法都定义在接口中
    result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;



    // II . 设置输出混音器



    //  输出声音 , 添加各种音效 ( 混响 , 重低音 , 环绕音 , 均衡器 等 ) , 都要通过混音器实现 ;

    // 创建输出混音器对象 , 可以指定一个混响效果参数 ( 该混淆参数可选 )
    const SLInterfaceID ids_engine[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean req_engine[1] = {SL_BOOLEAN_FALSE};
    result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, ids_engine, req_engine);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // 实现输出混音器
    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;



    // III . 获取混响接口 并 设置混响 ( 可能会失败 )


    // 获取环境混响接口
    // 如果环境混响效果不可用 , 该操作可能失败
    // either because the feature is not present, excessive CPU load, or
    // the required MODIFY_AUDIO_SETTINGS permission was not requested and granted
    result = (*outputMixObject)->GetInterface(outputMixObject, SL_IID_ENVIRONMENTALREVERB,
                                               &outputMixEnvironmentalReverb);
    if (SL_RESULT_SUCCESS == result) {
        result = (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(
                outputMixEnvironmentalReverb, &reverbSettings);
        (void)result;
    }




    //IV . 配置音源输入


    // 配置要播放的音频输入缓冲队列属性参数 , 缓冲区大小 , 音频格式 , 采样率 , 样本位数 , 通道数 , 样本大小端格式
    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    /*
        typedef struct SLDataFormat_PCM_ {
        SLuint32 		formatType;     //数据格式                 SL_DATAFORMAT_PCM
        SLuint32 		numChannels;    //通道数 , 左右声道 2个     2
        SLuint32 		samplesPerSec;  //采样率 44100Hz           SL_SAMPLINGRATE_44_1
        SLuint32 		bitsPerSample;  //采样位数 16位            SL_PCMSAMPLEFORMAT_FIXED_16
        SLuint32 		containerSize;  //容器大小                 SL_PCMSAMPLEFORMAT_FIXED_16
        SLuint32 		channelMask;    //通道        SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT
        SLuint32		endianness;     //小端格式                 SL_BYTEORDER_LITTLEENDIAN
    } SLDataFormat_PCM;
     */
    SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM,           //PCM 格式
                                   2,                           //两个声道
                                   SL_SAMPLINGRATE_44_1,        //采样率 44100 Hz
                                   SL_PCMSAMPLEFORMAT_FIXED_16, //采样位数 16位
                                   SL_PCMSAMPLEFORMAT_FIXED_16, //容器为 16 位
                                   SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,  //左右双声道
                                   SL_BYTEORDER_LITTLEENDIAN};  //小端格式

    // 设置音频数据源 , 配置缓冲区 ( loc_bufq ) 与 音频格式 (format_pcm)
    SLDataSource audioSrc = {&loc_bufq, &format_pcm};



    // V . 配置音频输出


    // 配置混音器 : 将 outputMixObject 混音器对象装载入 SLDataLocator_OutputMix 结构体中
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};

    // 将 SLDataLocator_OutputMix 结构体装载到 SLDataSink 中
    //  音频输出通过 loc_outmix 输出 , 实际上是通过 outputMixObject 混音器对象输出的
    SLDataSink audioSnk = {&loc_outmix, NULL};




    // VI . 创建并实现播放器


    /*
     * 创建音频播放器:
     *      如果需要效果器时 , 不支持高性能音频
     *     ( fast audio does not support when SL_IID_EFFECTSEND is required, skip it
     *          for fast audio case )
     */

    // 操作队列接口 , 如果需要 特效接口 , 添加 SL_IID_EFFECTSEND
    const SLInterfaceID ids_player[3] = {SL_IID_BUFFERQUEUE, SL_IID_VOLUME, SL_IID_EFFECTSEND,
            /*SL_IID_MUTESOLO,*/};
    const SLboolean req_player[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,
            /*SL_BOOLEAN_TRUE,*/ };


    // 创建播放器
    result = (*engineEngine)->CreateAudioPlayer(
            engineEngine,
            &bqPlayerObject,
            &audioSrc, //音频输入
            &audioSnk, //音频商户处
            bqPlayerSampleRate? 2 : 3,//
            ids_player,
            req_player);

    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // 创建播放器对象
    result = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;



    // VII . 获取播放器接口 和 缓冲队列接口


    // 获取播放器 Player 接口 : 该接口用于设置播放器状态 , 开始 暂停 停止 播放 等操作
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // 获取播放器 缓冲队列 接口 : 该接口用于控制 音频 缓冲区数据 播放
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE,
                                             &bqPlayerBufferQueue);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;




    // VIII . 注册回调函数


    // 注册缓冲区队列的回调函数 , 每次播放完数据后 , 会自动回调该函数
    //      传入参数 this , 就是 bqPlayerCallback 函数中的 context 参数
    result = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, bqPlayerCallback, this);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;



    // IX . 获取效果器接口 和 音量控制接口 ( 不是必须的 )


    // 获取效果器发送接口 ( get the effect send interface )
    bqPlayerEffectSend = NULL;
    if( 0 == bqPlayerSampleRate) {
        result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_EFFECTSEND,
                                                 &bqPlayerEffectSend);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }

#if 0   // mute/solo is not supported for sources that are known to be mono, as this is
    // get the mute/solo interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_MUTESOLO, &bqPlayerMuteSolo);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
#endif

    // 获取音量控制接口

    // 获取音量控制接口 ( get the volume interface ) [ 如果需要调节音量可以获取该接口 ]
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME, &bqPlayerVolume);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;



    // X . 设置播放状态


    // 设置播放器正在播放状态 ( set the player's state to playing )
    result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;


    // XI. 手动调用激活回调函数

    // 手动激活 , 手动调用一次 bqPlayerCallback 回调函数
    bqPlayerCallback(bqPlayerBufferQueue, this);

}