#include <jni.h>
#include <string>
#include "FFMPEG.h"

//声明 FFMPEG 类
FFMPEG *ffmpeg = 0;

extern "C"
JNIEXPORT void JNICALL
Java_kim_hsl_ffmpeg_Player_native_1prepare(JNIEnv *env, jobject instance, jstring dataSource_) {

    //Java 中传入的视频直播流地址 , "rtmp://live.hkstv.hk.lxdns.com/live/hks"
    const char *dataSource = env->GetStringUTFChars(dataSource_, 0);

    //在 FFMPEG.cpp 中声明的构造函数
    ffmpeg = new FFMPEG(dataSource);

    //播放器准备 , 调用 ffmpeg 指针指向的类对象的 prepare() 方法
    ffmpeg->prepare();


    env->ReleaseStringUTFChars(dataSource_, dataSource);
}