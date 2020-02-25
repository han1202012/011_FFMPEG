//
// Created by octopus on 2020/2/25.
//

#include "FFMPEG.h"
#include <cstring>

// 注意 FFMPEG 是 C 开发的 , 在 C++ 中使用需要使用 extern "C" 进行兼容
extern "C"{
#include <libavcodec/avcodec.h>
}

//构造方法
FFMPEG::FFMPEG(const char *dataSource) {

    //拷贝一份 dataSource 字符串 , 因为该参数中传入的字符串后面可能会被回收
    int strlength = strlen(dataSource);

    //赋值给成员变量
    this->dataSource = new char[strlength];

    //拷贝字符串
    strcpy(this->dataSource, dataSource);



}

FFMPEG::~FFMPEG() {

    //释放字符串成员变量 , 防止 dataSource 指向的内存出现泄漏
    delete dataSource;

}