#include <jni.h>
#include <string>
#include "FFMPEG.h"

//声明 FFMPEG 类
FFMPEG *ffmpeg = 0;

//JNI_OnLoad 中获取的 Java 虚拟机对象放在这里
JavaVM *javaVM;
int JNI_OnLoad(JavaVM *vm, void *r){

    javaVM = vm;

    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT void JNICALL
Java_kim_hsl_ffmpeg_Player_native_1prepare(JNIEnv *env, jobject instance, jstring dataSource_) {

    //Java 中传入的视频直播流地址 , "rtmp://live.hkstv.hk.lxdns.com/live/hks"
    const char *dataSource = env->GetStringUTFChars(dataSource_, 0);

    //创建 Java 调用类
    JavaCallHelper * javaCallHelper = new JavaCallHelper(javaVM, env, instance);

    //在 FFMPEG.cpp 中声明的构造函数
    ffmpeg = new FFMPEG(javaCallHelper, dataSource);

    //播放器准备 , 调用 ffmpeg 指针指向的类对象的 prepare() 方法
    ffmpeg->prepare();

    //释放字符串
    env->ReleaseStringUTFChars(dataSource_, dataSource);
}


extern "C"
JNIEXPORT void JNICALL
Java_kim_hsl_ffmpeg_Player_native_1start(JNIEnv *env, jobject instance) {

    //调用本地 ffmpeg 播放器的 start() 方法
    ffmpeg->start();
}