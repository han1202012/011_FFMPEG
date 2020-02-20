#include <jni.h>
#include <string>

// 注意 FFMPEG 是 C 开发的 , 在 C++ 中使用需要使用 extern "C" 进行兼容
extern "C"{
#include <libavcodec/avcodec.h>
}


extern "C" JNIEXPORT jstring JNICALL
Java_kim_hsl_ffmpeg_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    return env->NewStringUTF(av_version_info());
}
