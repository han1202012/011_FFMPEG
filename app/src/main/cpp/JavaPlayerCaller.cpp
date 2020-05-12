//
// Created by octop on 2020/3/2.
//

#include "JavaPlayerCaller.h"

JavaPlayerCaller::JavaPlayerCaller(JavaVM *vm, JNIEnv *env, jobject instance) {

    /*
     * 如果在子线程调用 Java 方方法
     *      需要借助 JavaVM * vm , 获取子线程的 JNIEnv *env 进行反射调用
     *
     * 如果在主线程调用 Java 方法
     *      可以直接调用主线程传入的 JNIEnv *env 进行反射调用
     *
     * 注意 : jobject 如果要跨方法 , 跨线程调用 , 需要创建全局引用 , 不要使用局部引用
     */

    this->vm = vm;
    this->env = env;
    this->instance = env->NewGlobalRef(instance);


    //初始化 onError 方法反射信息
    jclass clazz = env->GetObjectClass(instance);

    //Java 中对应的方法 public void onError(int errorCode)
    this->onErrorId = env->GetMethodID(clazz, "onError", "(I)V");

    //Java 中对应的 public void onPrepare()
    this->onPrepareId = env->GetMethodID(clazz, "onPrepare", "()V");

    //Java 中对应的 public void onProgress()
    this->onProgressId = env->GetMethodID(clazz, "onProgress", "(I)V");


}

/**
 * 析构方法
 */
JavaPlayerCaller::~JavaPlayerCaller() {

    //释放全局引用
    //注意线程 : 该 env 是主线程的 env
    //  如果在子线程中调用该方法 , 会导致崩溃
    env->DeleteGlobalRef(instance);

}

/**
 * 判断 thread 是否是主线程
 *      如果是主线程 :
 *      如果是子线程 :
 *
 *
 * @param thread
 * @param errorCode
 */
void JavaPlayerCaller::onError(int thread, int errorCode) {

    if(thread == 1){

        //主线程 : 可以直接使用 JNIEnv * 指针
        this->env->CallVoidMethod(instance, onErrorId, errorCode);

    }else{

        //子线程 : 需要通过 JavaVM * 获取该子线程的 JNIEnv *
        JNIEnv *env_thread;

        //Java 虚拟机 调用附加线程的方法 , 可以获取当前线程的 JNIEnv* 指针
        vm->AttachCurrentThread(&env_thread, 0);

        //调用 Java 方法
        env_thread->CallVoidMethod(instance, onErrorId, errorCode);

        //解除线程附加
        vm->DetachCurrentThread();

    }

}

void JavaPlayerCaller::onPrepare(int thread) {

    if(thread == 1){

        //主线程 : 可以直接使用 JNIEnv * 指针
        this->env->CallVoidMethod(instance, onPrepareId);

    }else{

        //子线程 : 需要通过 JavaVM * 获取该子线程的 JNIEnv *
        JNIEnv *env_thread;

        //Java 虚拟机 调用附加线程的方法 , 可以获取当前线程的 JNIEnv* 指针
        vm->AttachCurrentThread(&env_thread, 0);

        //调用 Java 方法
        env_thread->CallVoidMethod(instance, onPrepareId);

        //解除线程附加
        vm->DetachCurrentThread();

    }

}


/**
 * 回调 Java 的进度条更新方法
 * @param thread
 * @param progress
 */
void JavaPlayerCaller::onProgress(int thread, int progress) {
    if(thread == 1){

        //主线程 : 可以直接使用 JNIEnv * 指针
        this->env->CallVoidMethod(instance, onProgressId, progress);

    }else{

        //子线程 : 需要通过 JavaVM * 获取该子线程的 JNIEnv *
        JNIEnv *env_thread;

        //Java 虚拟机 调用附加线程的方法 , 可以获取当前线程的 JNIEnv* 指针
        vm->AttachCurrentThread(&env_thread, 0);

        //调用 Java 方法
        env_thread->CallVoidMethod(instance, onProgressId, progress);

        //解除线程附加
        vm->DetachCurrentThread();

    }
}