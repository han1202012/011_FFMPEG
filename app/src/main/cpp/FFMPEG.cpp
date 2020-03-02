//
// Created by octopus on 2020/2/25.
//

#include "FFMPEG.h"

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

//prepare 方法调用的子线程执行内容
void* pthread_prepare(void* args){

    //将 args 参数转为 FFMPEG 对象
    FFMPEG *ffmpeg = static_cast<FFMPEG *>(args);

    //调用 ffmpeg 对象的 _prepare() 方法
    ffmpeg->_prepare();

    //线程函数必须 return
    return 0;

}

//实际的准备方法
void FFMPEG::_prepare() {

    /*
     * 初始化网络 :
     *      默认状态下 , FFMPEG 是不允许联网的
     *      必须调用该函数 , 初始化网络后才能进行联网
     */
    avformat_network_init();


    //0 . 注册组件
    //      如果是 4.x 之前的版本需要执行该步骤
    //      4.x 及之后的版本 , 就没有该步骤了
    //av_register_all();

    //1 . 打开音视频地址
    //      地址类型 : ① 文件类型 , ② 音视频流
    //  参数解析 :
    //      AVFormatContext **ps :  封装了文件格式相关信息的结构体 , 如视频宽高 , 音频采样率等信息 ;
    //                              该参数是 二级指针 , 意味着在方法中会修改该指针的指向 ,
    //                              该参数的实际作用是当做返回值用的
    //      const char *url :   视频资源地址, 文件地址 / 网络链接
    //  返回值说明 : 返回 0 , 代表打开成功 , 否则失败
    //              失败的情况 : 文件路径错误 , 网络错误
    //int avformat_open_input(AVFormatContext **ps, const char *url, AVInputFormat *fmt, AVDictionary **options);
    formatContext = 0;
    int open_result = avformat_open_input(&formatContext, dataSource, 0, 0);

    //如果返回值不是 0 , 说明打开视频文件失败 , 需要将错误信息在 Java 层进行提示
    if(open_result){

    }

}

//播放器准备方法
void FFMPEG::prepare() {

    //创建线程进行准备工作
    //  在线程中进行音视频文件或文件流解析
    pthread_create(&pid, 0, pthread_prepare, this);

}