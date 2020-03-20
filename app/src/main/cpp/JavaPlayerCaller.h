//
// Created by octop on 2020/3/2.
// 作用 : 在 C/C++ 层调用 Java 层函数的帮助类
//       反射 Java 类 , 并调用其方法
//

#ifndef INC_011_FFMPEG_JAVAPLAYERCALLER_H
#define INC_011_FFMPEG_JAVAPLAYERCALLER_H

#include <jni.h>

class JavaPlayerCaller {

public:

    //构造方法
    JavaPlayerCaller(JavaVM *vm, JNIEnv *env, jobject instance);

    //析构方法
    ~JavaPlayerCaller();

    //错误回调方法 , 通过该方法回调错误信息给 Java 层
    void onError(int thread, int errorCode);

    //准备回调方法
    void onPrepare(int thread);

private:

    /*
     * 跨线程相关 :
     *      JNIEnv * 是不能跨线程使用的
     *      如果在线程中反射调用 Java 方法
     *      必须重新获取对应线程的 JNIEnv *env
     */
    JavaVM *vm;
    JNIEnv *env;
    jobject instance;

    //onError 方法对应的 方法 ID
    jmethodID onErrorId;

    //onPrepare 方法对应的 方法 ID
    jmethodID onPrepareId;

};


#endif //INC_011_FFMPEG_JAVAPLAYERCALLER_H
