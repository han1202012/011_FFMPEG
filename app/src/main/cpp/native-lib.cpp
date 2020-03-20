#include <jni.h>
#include <string>

//本地窗口 , 在 Native 层处理图像绘制
#include <android/native_window_jni.h>

#include "FFMPEG.h"

//声明 FFMPEG 类
FFMPEG *ffmpeg = 0;

/**
 * 原生绘制窗口
 */
ANativeWindow * aNativeWindow;

/**
 * 同步锁 , 静态方式初始化 , 同一个进程 , 只能出现一个 , 只要该应用不销毁 , 就一直存在
 *      该锁可以不同进行释放 , 直接使用即可
 */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//JNI_OnLoad 中获取的 Java 虚拟机对象放在这里
JavaVM *javaVM;
int JNI_OnLoad(JavaVM *vm, void *r){

    javaVM = vm;

    return JNI_VERSION_1_6;
}

/**
 * 解码后的图片绘制方法
 *
 *      注意互斥问题 : 确保该方法与 Java_kim_hsl_ffmpeg_Player_native_1prepare 方法互斥 , 要加上线程锁
 *
 * @param data
 *          RGBA 像素数据
 * @param linesize
 *
 * @param width
 *          图像的宽
 * @param height
 *          图像的高
 */
void show(uint8_t *data, int linesize, int width, int height){

    //加同步锁
    pthread_mutex_lock(&mutex);

    //首先确保 ANativeWindow * aNativeWindow 绘制载体存在 , 否则直接退出
    if(!aNativeWindow){
        //解除同步锁 , 否则一直阻塞在此处
        pthread_mutex_unlock(&mutex);
        return;
    }

    //设置 ANativeWindow 绘制窗口属性
    //  传入的参数分别是 : ANativeWindow 结构体指针 , 图像的宽度 , 图像的高度 , 像素的内存格式
    ANativeWindow_setBuffersGeometry(aNativeWindow, width, height, WINDOW_FORMAT_RGBA_8888);

    //获取 ANativeWindow_Buffer , 如果获取失败 , 直接释放相关资源退出
    ANativeWindow_Buffer aNativeWindow_Buffer;

    //如果获取成功 , 可以继续向后执行 , 获取失败 , 直接退出
    if(ANativeWindow_lock(aNativeWindow, &aNativeWindow_Buffer, 0)){
        //退出操作 , 释放 aNativeWindow 结构体指针
        ANativeWindow_release(aNativeWindow);
        aNativeWindow = 0;
        return;
    }

    //向 ANativeWindow_Buffer 填充 RGBA 像素格式的图像数据
    uint8_t *dst_data = static_cast<uint8_t *>(aNativeWindow_Buffer.bits);

    //参数中的 uint8_t *data 数据中 , 每一行有 linesize 个 , 拷贝的目标也要逐行拷贝
    //  aNativeWindow_Buffer.stride 是每行的数据个数 , 每个数据都包含一套 RGBA 像素数据 ,
    //      RGBA 数据每个占1字节 , 一个 RGBA 占 4 字节
    //  每行的数据个数 * 4 代表 RGBA 数据个数
    int dst_linesize = aNativeWindow_Buffer.stride * 4;

    //获取 ANativeWindow_Buffer 中数据的地址
    //      一次拷贝一行 , 有 像素高度 行数
    for(int i = 0; i < aNativeWindow_Buffer.height; i++){

        //计算拷贝的指针地址
        //  每次拷贝的目的地址 : dst_data + ( i * dst_linesize )
        //  每次拷贝的源地址 : data + ( i * linesize )

        memcpy(dst_data + ( i * dst_linesize ), data + ( i * linesize ), dst_linesize);

    }

    //启动绘制
    ANativeWindow_unlockAndPost(aNativeWindow);

    //解除同步锁
    pthread_mutex_unlock(&mutex);

}


extern "C"
JNIEXPORT void JNICALL
Java_kim_hsl_ffmpeg_Player_native_1prepare(JNIEnv *env, jobject instance, jstring dataSource_) {

    //Java 中传入的视频直播流地址 , "rtmp://live.hkstv.hk.lxdns.com/live/hks"
    const char *dataSource = env->GetStringUTFChars(dataSource_, 0);

    //创建 Java 调用类
    JavaPlayerCaller * javaCallHelper = new JavaPlayerCaller(javaVM, env, instance);

    //在 FFMPEG.cpp 中声明的构造函数
    ffmpeg = new FFMPEG(javaCallHelper, dataSource);

    //设置绘制图像回调函数
    ffmpeg->setShowFrameCallback(show);

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

extern "C"
JNIEXPORT void JNICALL
Java_kim_hsl_ffmpeg_Player_native_1set_1surface(JNIEnv *env, jobject instance, jobject surface) {

    //加同步锁
    pthread_mutex_lock(&mutex);

    // 将从 Java 层传递的 Surface 对象转换成 ANativeWindow 结构体
    //      如果之前已经有了 ANativeWindow 结构体 , 那么先将原来的释放掉

    //释放原来的 ANativeWindow
    if(aNativeWindow){
        ANativeWindow_release(aNativeWindow);
    }

    //转换新的 ANativeWindow
    aNativeWindow = ANativeWindow_fromSurface(env, surface);

    //解除同步锁
    pthread_mutex_unlock(&mutex);

}