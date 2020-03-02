//
// Created by octop on 2020/3/2.
//

#include "JavaCallHelper.h"

JavaCallHelper::JavaCallHelper(JavaVM *vm, JNIEnv *env, jobject instance) {

    /*
     * 如果在子线程调用 Java 方方法
     *      需要借助 JavaVM * vm , 获取子线程的 JNIEnv *env 进行反射调用
     *
     * 如果在主线程调用 Java 方法
     *      可以直接调用主线程传入的 JNIEnv *env 进行反射调用
     */

    this->vm = vm;
    this->env = env;
}

JavaCallHelper::~JavaCallHelper() {

}