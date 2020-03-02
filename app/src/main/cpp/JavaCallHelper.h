//
// Created by octop on 2020/3/2.
// 作用 : 在 C/C++ 层调用 Java 层函数的帮助类
//       反射 Java 类 , 并调用其方法
//

#ifndef INC_011_FFMPEG_JAVACALLHELPER_H
#define INC_011_FFMPEG_JAVACALLHELPER_H

#include <jni.h>

class JavaCallHelper {

public:

    //构造方法
    JavaCallHelper(JavaVM *vm, JNIEnv *env, jobject instance);

    //析构方法
    ~JavaCallHelper();

private:

    /*
     * 跨线程相关 :
     *      JNIEnv * 是不能跨线程使用的
     *      如果在线程中反射调用 Java 方法
     *      必须重新获取对应线程的 JNIEnv *env
     */
    JavaVM *vm;
    JNIEnv *env;

};


#endif //INC_011_FFMPEG_JAVACALLHELPER_H
