//
// Created by octop on 2020/3/2.
//

#include "AudioChannel.h"

AudioChannel::AudioChannel(int id,AVCodecContext *avCodecContext) : BaseChannel(id, avCodecContext) {

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

    // I . 解码音频

    //启动解码线程
    pthread_create(&pid_decode , 0 , audio_decode , this);

    // II . 播放视频

    //启动播放线程
    pthread_create(&pid_decode , 0 , audio_decode , this);


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

// 缓冲队列播放器使用的输出混音器设置的辅助效果
static const SLEnvironmentalReverbSettings reverbSettings =
        SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;

/**
 * 实现播放方法
 *
 * 在该方法中使用 OpenSL ES 播放音频
 */
void AudioChannel::playback() {

    // I . 创建 OpenSLES 引擎并获取引擎的接口 ( 相关代码拷贝自 Google 官方示例 native-audio )

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
    const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean req[1] = {SL_BOOLEAN_FALSE};
    result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, ids, req);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // 实现输出混音器
    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

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


    //III . 创建播放器







}