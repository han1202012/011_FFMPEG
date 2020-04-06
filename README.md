

<br>

### 博客地址 : [https://hanshuliang.blog.csdn.net/article/details/104900964](https://hanshuliang.blog.csdn.net/article/details/104900964)

<br>

<br>

>本博客属于总结性质的博客 , 开发时可以参考该博客的代码示例 , 可以直接使用 ; 知识点比较概括 , 只描述操作流程及核心源码 , 没有具体原理说明 , 详细的原理知识去具体的单条知识点博客中查看 ; 

<br>

**代码及播放效果 :** 

**1 . GitHub 代码地址 :** [FFMPEG 直播示例](https://github.com/han1202012/011_FFMPEG)


**2 . 效果展示 :** <font color=blue>使用的是湖南卫视的直播源 rtmp://58.200.131.2:1935/livetv/hunantv 
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200406133653776.gif)



<br>
<br>

#### I . FFMPEG 播放视频流程总结

---

<br> 


**FFMPEG 播放视频流程 :** <font color=blue>视频中包含图像和音频 ; 

<br>

**1 . FFMPEG 交叉编译配置 :** [【Android FFMPEG 开发】FFMPEG 交叉编译配置 ( 下载 | 配置脚本 | 输出路径 | 函数库配置 | 程序配置 | 组件配置 | 编码解码配置 | 交叉编译配置 | 最终脚本 )](https://blog.csdn.net/shulianghan/article/details/104351312)


<br>

**2 . Android Studio 工程配置 FFMPEG :** [【Android FFMPEG 开发】Android Studio 工程配置 FFMPEG ( 动态库打包 | 头文件与函数库拷贝 | CMake 脚本配置 )](https://blog.csdn.net/shulianghan/article/details/104367747)

<br>


**3 . FFMPEG  初始化 :** <font color=orange> [【Android FFMPEG 开发】FFMPEG 初始化 ( 网络初始化 | 打开音视频 | 查找音视频流 )](https://hanshuliang.blog.csdn.net/article/details/104636151)


<br>


**4 . FFMPEG 获取 AVStream 音视频流 :** <font color=orange> [【Android FFMPEG 开发】FFMPEG 获取 AVStream 音视频流 ( AVFormatContext 结构体 | 获取音视频流信息 | 获取音视频流个数 | 获取音视频流 )](https://hanshuliang.blog.csdn.net/article/details/104652321)


<br>

**5 . FFMPEG 获取 AVCodec 编解码器 :** <font color=orange> [【Android FFMPEG 开发】FFMPEG 获取编解码器 ( 获取编解码参数 | 查找编解码器 | 获取编解码器上下文 | 设置上下文参数 | 打开编解码器 )](https://hanshuliang.blog.csdn.net/article/details/104661085)

<br>

**6 . FFMPEG 读取音视频流中的数据到 AVPacket :**  <font color=orange> [【Android FFMPEG 开发】FFMPEG 读取音视频流中的数据到 AVPacket ( 初始化 AVPacket 数据 | 读取 AVPacket )](https://blog.csdn.net/shulianghan/article/details/104746458)

<br>

**7 . FFMPEG 解码 AVPacket 数据到 AVFrame ( 音频 / 视频数据解码 ) :**  <font color=orange> [【Android FFMPEG 开发】FFMPEG 解码 AVPacket 数据到 AVFrame ( AVPacket->解码器 | 初始化 AVFrame | 解码为 AVFrame 数据 )](https://blog.csdn.net/shulianghan/article/details/104768104)

<br>

**8 . FFMPEG AVFrame 图像格式转换 YUV -> RGBA :**  <font color=orange> [【Android FFMPEG 开发】FFMPEG AVFrame 图像格式转换 YUV -> RGBA ( 获取 SwsContext | 初始化图像数据存储内存 | 图像格式转换 )](https://hanshuliang.blog.csdn.net/article/details/104772549) 

<br>

**9 . FFMPEG ANativeWindow 原生绘制 准备 :** <font color=orange> [【Android FFMPEG 开发】FFMPEG ANativeWindow 原生绘制 ( Java 层获取 Surface | 传递画布到本地 | 创建 ANativeWindow )](https://hanshuliang.blog.csdn.net/article/details/104788783)

<br>

**10 . FFMPEG ANativeWindow 原生绘制 :** [【Android FFMPEG 开发】FFMPEG ANativeWindow 原生绘制 ( 设置 ANativeWindow 缓冲区属性 | 获取绘制缓冲区 | 填充数据到缓冲区 | 启动绘制 )](https://blog.csdn.net/shulianghan/article/details/104790084)

<br>

**11 . FFMPEG 音频重采样 :** [【Android FFMPEG 开发】FFMPEG 音频重采样 ( 初始化音频重采样上下文 SwrContext | 计算音频延迟 | 计算输出样本个数 | 音频重采样 swr_convert )](https://blog.csdn.net/shulianghan/article/details/104871223)


<br>

**12 . FFMPEG 音频播放 :** [【Android FFMPEG 开发】OpenSLES 播放音频 ( 创建引擎 | 输出混音设置 | 配置输入输出 | 创建播放器 | 获取播放/队列接口 | 回调函数 | 开始播放 | 激活回调 )](https://blog.csdn.net/shulianghan/article/details/104880199)

<br>

**13 . FFMPEG 音视频同步 :** [【Android FFMPEG 开发】FFMPEG 音视频同步 ( 音视频同步方案 | 视频帧 FPS 控制 | H.264 编码 I / P / B 帧 | PTS | 音视频同步 )](https://blog.csdn.net/shulianghan/article/details/104891200)


<br>


**14 . FFMPEG 直播示例 :** [【Android FFMPEG 开发】FFMPEG 直播功能完整流程 + 源码 ( 源码交叉编译 -> AS工程配置 -> 音视频打开/读取/解码/格式转换  -> 原生绘制播放 -> 音视频同步 )](https://hanshuliang.blog.csdn.net/article/details/104900964)




<br>
<br>

#### II . FFMPEG 下载及交叉编译

---

<br> 



**1 . FFMPEG 下载 :** 

<br>

**① FFMPEG 源码下载地址 :** [http://ffmpeg.org/download.html#releases](http://ffmpeg.org/download.html#releases)

**② 本博客使用的源码下载地址 :** [https://ffmpeg.org/releases/ffmpeg-4.0.2.tar.bz2](https://ffmpeg.org/releases/ffmpeg-4.0.2.tar.bz2)
<font color=purple>( 也可以直接从博客资源中下载 )


<br> 

**2 . FFMPEG 编译 :** <font color=red>在 Ubuntu 18.04.4 中解压该源码 ; 

<br> 

**① 配置编译脚本 :** <font color=blue>在 FFMPEG 源码根目录下 , 创建 build_ffmpeg.sh 文件 , 内容如下 ; 

```shell
#!/bin/bash

# NDK 根目录
NDK_ROOT=/root/NDK/android-ndk-r17c

# TOOLCHAIN 变量指向 gcc g++ 等交叉编译工具所在的目录
TOOLCHAIN=$NDK_ROOT/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64

# gcc 编译器参数
FLAGS="-isysroot $NDK_ROOT/sysroot -isystem $NDK_ROOT/sysroot/usr/include/arm-linux-androideabi -isystem $NDK_ROOT/sources/android/support/include -D__ANDROID_API__=21 -g -DANDROID -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -mthumb -Wa,--noexecstack -Wformat -Werror=format-security -O0 -fPIC"

# 编译结果输出路径
PREFIX=./android/armeabi-v7a

# 执行 configure 脚本生成 Makefile 构建脚本
./configure \
--prefix=$PREFIX \
--enable-small \
--disable-programs \
--disable-avdevice \
--disable-encoders \
--disable-muxers \
--disable-filters \
--enable-cross-compile \
--cross-prefix=$TOOLCHAIN/bin/arm-linux-androideabi- \
--sysroot=$NDK_ROOT/platforms/android-21/arch-arm \
--extra-cflags="$FLAGS" \
--arch=arm \
--target-os=android 

# 清除之前的编译内容
make clean

# 开启新的 FFMPEG 编译
make install
```


**② 修改 Shell 脚本权限 :** 

```shell
chmod +x build_ffmpeg.sh
```


**③ 执行 Shell 脚本 :** 

```shell
./build_ffmpeg.sh
```

**④ 编译结果 :** 

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200218222558358.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2hhbjEyMDIwMTI=,size_16,color_FFFFFF,t_70)


> [【Android FFMPEG 开发】FFMPEG 交叉编译配置 ( 下载 | 配置脚本 | 输出路径 | 函数库配置 | 程序配置 | 组件配置 | 编码解码配置 | 交叉编译配置 | 最终脚本 )](https://blog.csdn.net/shulianghan/article/details/104351312)


<br>
<br>

#### III . Android Studio 配置 FFMPEG 函数库

---

<br> 



**1 . 头文件与静态库文件拷贝 :** <font color=blue>将上面编译生成的 include 和 lib 两个目录 , 拷贝到 app/src/main/cpp 目录下 ; 

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200219234001418.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2hhbjEyMDIwMTI=,size_16,color_FFFFFF,t_70)

><font color=purple>动态库拷贝到 jniLibs/armeabi-v7a 目录下 , 静态库可以拷贝到任意位置使用 ; 

<br>

**2 . 配置 Module 级别的 build.gradle 构建脚本 :** 

```java
apply plugin: 'com.android.application'

android {
    compileSdkVersion 28
    defaultConfig {
        applicationId "kim.hsl.ffmpeg"
        minSdkVersion 21
        targetSdkVersion 28
        versionCode 1
        versionName "1.0"
        testInstrumentationRunner "androidx.test.runner.AndroidJUnitRunner"


        // I . NDK 配置 1 : 配置 AS 工程中的 C/C++ 源文件的编译

        //     defaultConfig 内部的 externalNativeBuild 配置的是配置 AS 工程的 C/C++ 源文件编译参数
        //     defaultConfig 外部的 externalNativeBuild 配置的是 CMakeList.txt 或 Android1.mk 构建脚本的路径
        externalNativeBuild {
            cmake {
                cppFlags ""

                //配置编译 C/C++ 源文件为哪几个 CPU 指令集的函数库 (arm , x86 等)
                abiFilters "armeabi-v7a"
            }
        }



        // II . NDK 配置 2 : 配置 AS 工程中的 C/C++ 源文件的编译


        //配置 APK 打包 哪些动态库
        //  示例 : 如在工程中集成了第三方库 , 其提供了 arm, x86, mips 等指令集的动态库
        //        那么为了控制打包后的应用大小, 可以选择性打包一些库 , 此处就是进行该配置
        ndk{
            // 打包生成的 APK 文件指挥包含 ARM 指令集的动态库
            abiFilters "armeabi-v7a" /*, "arm64-v8a", "x86", "x86_64"*/
        }

    }


    // III . NDK 配置  : 配置 AS 工程中的 C/C++ 源文件的编译构建脚本


    // 配置 NDK 的编译脚本路径
    // 编译脚本有两种 ① CMakeList.txt ② Android.mk
    //     defaultConfig 内部的 externalNativeBuild 配置的是配置 AS 工程的 C/C++ 源文件编译参数
    //     defaultConfig 外部的 externalNativeBuild 配置的是 CMakeList.txt 或 Android1.mk 构建脚本的路径
    externalNativeBuild {

        // 配置 CMake 构建脚本 CMakeLists.txt 脚本路径
        cmake {
            path "src/main/cpp/CMakeLists.txt"
            version "3.10.2"
        }

    }

    buildTypes {
        release {
            minifyEnabled false
            proguardFiles getDefaultProguardFile('proguard-android-optimize.txt'), 'proguard-rules.pro'
        }
    }

}

dependencies {
    implementation fileTree(dir: 'libs', include: ['*.jar'])
    implementation 'androidx.appcompat:appcompat:1.1.0'
    implementation 'androidx.constraintlayout:constraintlayout:1.1.3'
    testImplementation 'junit:junit:4.12'
    androidTestImplementation 'androidx.test:runner:1.2.0'
    androidTestImplementation 'androidx.test.espresso:espresso-core:3.2.0'
}

```


<br>


**3 . 配置 CMakeList.txt 构建脚本 :** 

```shell
# I . 指定 CMake 最低版本
cmake_minimum_required(VERSION 3.4.1)

# II . 设置函数库编译
add_library( # 参数 1 : 设置生成的动态库名称
        native-lib

        # 参数 2 : 设置生成的函数库类型 : ① 静态库 STATIC ② 动态库 SHARED
        SHARED

        # 参数 3 : 配置要编译的源文件
        native-lib.cpp
        FFMPEG.cpp
        JavaPlayerCaller.cpp
        AudioChannel.cpp
        VideoChannel.cpp)

# III . 到预设的目录查找 log 库 , 将找到的路径赋值给 log-lib
#       这个路径是 NDK 的 ndk-bundle\platforms\android-29\arch-arm\usr\lib\liblog.so
#       不同的 Android 版本号 和 CPU 架构 需要到对应的目录中查找 , 此处是 29 版本 32 位 ARM 架构的日志库
#
# 可以不配置 :
#       可以不进行该配置, 直接在后面的 target_link_libraries 中链接 log 也不会出错
find_library(
        log-lib

        log)


# IV . 指定 FFMPEG 头文件查找目录
#           CMAKE_SOURCE_DIR 指的是当前的文件地址
include_directories(${CMAKE_SOURCE_DIR}/include)

# V . 指定 FFMPEG 静态库
# CMAKE_CXX_FLAGS 表示会将 C++ 的参数传给编译器
# CMAKE_C_FLAGS 表示会将 C 参数传给编译器

# 参数设置 : 传递 CMAKE_CXX_FLAGS C+= 参数给编译器时 , 在 该参数后面指定库的路径
#   CMAKE_SOURCE_DIR 指的是当前的文件地址
#   -L 参数指定动态库的查找路径
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/lib")


# V . 链接函数库
#       参数 1 : 本构建脚本要生成的动态库目标
#       参数 2 ~ ... : 后面是之前预编译的动态库或静态库 , 或引入的动态库
target_link_libraries(
        native-lib

        # FFMPEG 静态库
        # 注意这些库的顺序必须按照如下进行 , 否则会报错
        #   这些库之间有依赖的关系 , 必须按照顺序加载库 , 如 avcodec 内部依赖 avformat 库
        avfilter
        avformat
        avcodec
        avutil
        swresample
        swscale

        # 日志库
        ${log-lib}

        #FFMPEG 使用到了 libz 库 , 没有会报错
        #   FFMPEG 对于 z 的依赖是以动态库的形式进行的
        #   如果 FFMPEG 是动态库 , 那么可以不链接这个库 , 可以运行时链接这个库
        #   当前 FFMPEG 是静态库 , 需要在编译时将这个库打包到静态库中
        #   推荐使用静态库 , 静态库打包出来的库比动态库小很多 , 一倍左右
        z

        #在 Native 层使用 ANativeWindow 进行原生绘制时 , 需要链接 libandroid.so 库
        android

        #调用 OpenSLES 需要链接该库
        OpenSLES
)
```

<br>

**4 . 配置 AndroidManifest.xml :** <font color=red>主要是配置网络和音频相关的权限 ; 

```xml
<?xml version="1.0" encoding="utf-8"?>
<manifest
    xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    package="kim.hsl.ffmpeg">

    <!-- RECORD_AUDIO is needed to create an audio recorder -->
    <uses-permission android:name="android.permission.RECORD_AUDIO"></uses-permission>
    <!-- MODIFY_AUDIO_SETTINGS is needed to use audio effects such as environmental reverb -->
    <uses-permission android:name="android.permission.MODIFY_AUDIO_SETTINGS"></uses-permission>
    <!-- INTERNET is needed to use a URI-based audio player, depending on the URI -->
    <uses-permission android:name="android.permission.INTERNET"></uses-permission>

    <application
        android:allowBackup="true"
        android:icon="@mipmap/ic_launcher"
        android:label="@string/app_name"
        android:roundIcon="@mipmap/ic_launcher_round"
        android:supportsRtl="true"
        android:theme="@style/AppTheme">
        <activity android:name=".MainActivity"
            android:screenOrientation="landscape"
            android:theme="@android:style/Theme.Black.NoTitleBar.Fullscreen"
            tools:ignore="LockedOrientationActivity">
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />

                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
    </application>

</manifest>
```

<br>

>[【Android FFMPEG 开发】Android Studio 工程配置 FFMPEG ( 动态库打包 | 头文件与函数库拷贝 | CMake 脚本配置 )](https://blog.csdn.net/shulianghan/article/details/104367747)


<br>
<br>

#### IV . FFMPEG 初始化

---

<br> 

**1 . FFMPEG 初始化流程 :** <font color=blue>FFMPEG 执行任何操作前 , 都需要初始化一些环境 , 及相关数据参数 ; 

<br>

**① 网络初始化 :** <font color=red>**avformat_network_init()** 

```cpp
int avformat_network_init(void);
```

<br>

**② 打开媒体 ( 音视频 ) 地址 :** <font color=red>**avformat_open_input()** 

```cpp
int avformat_open_input(AVFormatContext **ps, const char *url, AVInputFormat *fmt, AVDictionary **options);
```

<br>

**③ 查找 ( 音 / 视频 ) 流 :** <font color=red>**avformat_find_stream_info()** 

```cpp
int avformat_find_stream_info(AVFormatContext *ic, AVDictionary **options);
```

<br>

**④ 正式操作 :** <font color=purple>对上述查找到的 音 / 视频 流进行操作 ; 

<br>
<br>

**2 . 代码示例 :** 

```cpp
    /*
     * 初始化网络 :
     *      默认状态下 , FFMPEG 是不允许联网的
     *      必须调用该函数 , 初始化网络后 FFMPEG 才能进行联网
     */
    avformat_network_init();


    //0 . 注册组件
    //      如果是 4.x 之前的版本需要执行该步骤
    //      4.x 及之后的版本 , 就没有该步骤了
    //av_register_all();

    //1 . 打开音视频地址 ( 播放文件前 , 需要先将文件打开 )
    //      地址类型 : ① 文件类型 , ② 音视频流
    //  参数解析 :
    //      AVFormatContext **ps :  封装了文件格式相关信息的结构体 , 如视频宽高 , 音频采样率等信息 ;
    //                              该参数是 二级指针 , 意味着在方法中会修改该指针的指向 ,
    //                              该参数的实际作用是当做返回值用的
    //      const char *url :   视频资源地址, 文件地址 / 网络链接
    //  返回值说明 : 返回 0 , 代表打开成功 , 否则失败
    //              失败的情况 : 文件路径错误 , 网络错误
    //int avformat_open_input(AVFormatContext **ps, const char *url,
    //                          AVInputFormat *fmt, AVDictionary **options);
    formatContext = 0;
    int open_result = avformat_open_input(&formatContext, dataSource, 0, 0);

    //如果返回值不是 0 , 说明打开视频文件失败 , 需要将错误信息在 Java 层进行提示
    //  这里将错误码返回到 Java 层显示即可
    if(open_result != 0){
        __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "打开媒体失败 : %s", av_err2str(open_result));
        callHelper->onError(pid, 0);
    }



    //2 . 查找媒体 地址 对应的音视频流 ( 给 AVFormatContext* 成员赋值 )
    //      方法原型 : int avformat_find_stream_info(AVFormatContext *ic, AVDictionary **options);
    //      调用该方法后 , AVFormatContext 结构体的 nb_streams 元素就有值了 ,
    //      该值代表了音视频流 AVStream 个数
    int find_result = avformat_find_stream_info(formatContext, 0);

    //如果返回值 < 0 , 说明查找音视频流失败 , 需要将错误信息在 Java 层进行提示
    //  这里将错误码返回到 Java 层显示即可
    if(find_result < 0){
        __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "查找媒体流失败 : %s", av_err2str(find_result));
        callHelper->onError(pid, 1);
    }
```

> [【Android FFMPEG 开发】FFMPEG 初始化 ( 网络初始化 | 打开音视频 | 查找音视频流 )](https://hanshuliang.blog.csdn.net/article/details/104636151)



<br>
<br>

#### V . FFMPEG 获取 AVStream 音视频流

---

<br> 


**1 . FFMPEG 音视频流 AVStream ( 结构体 ) 获取流程 :** 

<br>

**① 获取音视频流信息 :** <font color=red>**avformat_find_stream_info ( )** , <font color=blue>在 [【Android FFMPEG 开发】FFMPEG 初始化 ( 网络初始化 | 打开音视频 | 查找音视频流 )](https://hanshuliang.blog.csdn.net/article/details/104636151) 博客中 , FFMPEG 初始化完毕后 , 获取了音视频流 , 本博客中讲解获取该音视频流对应的编解码器 , 从获取该音视频流开始 ; 

```cpp
int avformat_find_stream_info(AVFormatContext *ic, AVDictionary **options);
```


<br>

**② 音视频流数量 :** <font color=purple>获取的音视频流信息存储在 <font color=red>**AVFormatContext \*formatContext** <font color=purple>结构体中 , nb_streams 元素的值就是音视频流的个数 ; 

```cpp
//音视频流的个数
formatContext->nb_streams
```

<br>


**③ 音视频流 :** <font color=red>**AVFormatContext \*formatContext** <font color=green>结构体中的 音视频流数组元素 <font color=red>**AVStream \*\*streams** <font color=green>元素 , 通过数组下标可以获取指定位置索引的音视频流 ; 

```cpp
//取出一个媒体流 ( 视频流 / 音频流 )
AVStream *stream = formatContext->streams[i];
```


<br>
<br>

**2 . 代码示例 :** 

```cpp
    //2 . 查找媒体 地址 对应的音视频流 ( 给 AVFormatContext* 成员赋值 )
    //      方法原型 : int avformat_find_stream_info(AVFormatContext *ic, AVDictionary **options);
    //      调用该方法后 , AVFormatContext 结构体的 nb_streams 元素就有值了 ,
    //      该值代表了音视频流 AVStream 个数
    int find_result = avformat_find_stream_info(formatContext, 0);

    //如果返回值 < 0 , 说明查找音视频流失败 , 需要将错误信息在 Java 层进行提示
    //  这里将错误码返回到 Java 层显示即可
    if(find_result < 0){
        __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "查找媒体流失败 : %s", av_err2str(find_result));
        callHelper->onError(pid, 1);
    }


    //3 . 处理视频流 , 解析其中的数据流 , 获取流的各种参数 , 编解码器 , 等信息
    //      为视频 音频 解码播放准备数据

    //formatContext->nb_streams 是 音频流 / 视频流 个数 ;
    //  循环解析 视频流 / 音频流 , 一般是两个 , 一个视频流 , 一个音频流
    for(int i = 0; i < formatContext->nb_streams; i ++){

        //取出一个媒体流 ( 视频流 / 音频流 )
        AVStream *stream = formatContext->streams[i];
     }
```

>[【Android FFMPEG 开发】FFMPEG 获取 AVStream 音视频流 ( AVFormatContext 结构体 | 获取音视频流信息 | 获取音视频流个数 | 获取音视频流 )](https://hanshuliang.blog.csdn.net/article/details/104652321)



<br>
<br>

#### VI . FFMPEG 获取编解码器

---

<br> 


**1 . FFMPEG 编解码器获取流程 :** <font color=orange>在获取音视频流  <font color=red>**AVStream \*stream** <font color=orange>之后 , 执行以下流程 ;  


<br>

**〇 获取 AVStream \* 音视频流 ( 获取编解码器前提 ) :** <font color=purple>参考博客 [【Android FFMPEG 开发】FFMPEG 获取 AVStream 音视频流 ( AVFormatContext 结构体 | 获取音视频流信息 | 获取音视频流个数 | 获取音视频流 )](https://hanshuliang.blog.csdn.net/article/details/104652321)

<br>


**① 获取音视频流的编码参数 :** <font color=red>**AVStream \*stream** <font color=blue>结构体的 <font color=red>**AVCodecParameters \*codecpar** <font color=blue>元素是音视频流的编解码参数 ; 包含 码率 , 宽度 , 高度 , 采样率 等参数信息 ; 

```cpp
//解码这个媒体流的参数信息 , 包含 码率 , 宽度 , 高度 , 采样率 等参数信息
AVCodecParameters *codecParameters = stream->codecpar;
```

<br>


**② 查找编解码器 :** <font color=orange>调用 <font color=red>**avcodec_find_decoder ( )** <font color=orange>获取当前音视频流使用的编解码器 ; 

```cpp
//① 查找 当前流 使用的编码方式 , 进而查找编解码器 ( 可能失败 , 不支持的解码方式 )
AVCodec *avCodec = avcodec_find_decoder(codecParameters->codec_id);
```

<br>


**③ 获取编解码器上下文 :** <font color=purple>调用 <font color=red>**avcodec_alloc_context3 ( )** <font color=purple>方法 , 获取编解码器上下文 ; 

```cpp
//② 获取编解码器上下文
AVCodecContext *avCodecContext = avcodec_alloc_context3(avCodec);
```

<br>

**④ 设置编解码器上下文参数 :** <font color=green>调用 <font color=red>**avcodec_parameters_to_context ( )** <font color=green>方法 , 设置编解码器的上下文参数 ; 

```cpp
//③ 设置 编解码器上下文 参数
//      int avcodec_parameters_to_context(AVCodecContext *codec,
//              const AVCodecParameters *par);
//      返回值 > 0 成功 , < 0 失败
int parameters_to_context_result =
        avcodec_parameters_to_context(avCodecContext, codecParameters);
```

<br>


**⑤ 打开编解码器 :** <font color=blue>调用 <font color=red>**avcodec_open2 ( )** <font color=blue>方法 , 打开编解码器 ; 

```cpp
//④ 打开编解码器
//   int avcodec_open2(AVCodecContext *avctx, const AVCodec *codec, 
//   返回 0 成功 , 其它失败
int open_codec_result = avcodec_open2(avCodecContext, avCodec, 0);
```

<br>
<br>

**2 . 代码示例 :** 

```cpp
        //视频 / 音频 处理需要的操作 ( 获取编解码器 )

        //① 查找 当前流 使用的编码方式 , 进而查找编解码器 ( 可能失败 , 不支持的解码方式 )
        AVCodec *avCodec = avcodec_find_decoder(codecParameters->codec_id);

        //查找失败处理
        if(avCodec == NULL){
            //如果没有找到编解码器 , 回调失败 , 方法直接返回 , 后续代码不执行
            callHelper->onError(pid, 2);
            __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "查找 编解码器 失败");
            return;
        }


        //② 获取编解码器上下文
        AVCodecContext *avCodecContext = avcodec_alloc_context3(avCodec);

        //获取编解码器失败处理
        if(avCodecContext == NULL){
            callHelper->onError(pid, 3);
            __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "创建编解码器上下文 失败");
            return;
        }

        //③ 设置 编解码器上下文 参数
        //      int avcodec_parameters_to_context(AVCodecContext *codec,
        //              const AVCodecParameters *par);
        //      返回值 > 0 成功 , < 0 失败
        int parameters_to_context_result =
                avcodec_parameters_to_context(avCodecContext, codecParameters);

        //设置 编解码器上下文 参数 失败处理
        if(parameters_to_context_result < 0){
            callHelper->onError(pid, 4);
            __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "设置编解码器上下文参数 失败");
            return;
        }

        //④ 打开编解码器
        //   int avcodec_open2(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options);
        //   返回 0 成功 , 其它失败
        int open_codec_result = avcodec_open2(avCodecContext, avCodec, 0);

        //打开编解码器 失败处理
        if(open_codec_result != 0){
            callHelper->onError(pid, 5);
            __android_log_print(ANDROID_LOG_ERROR , "FFMPEG" , "打开 编解码器 失败");
            return;
        }
```

> [【Android FFMPEG 开发】FFMPEG 获取编解码器 ( 获取编解码参数 | 查找编解码器 | 获取编解码器上下文 | 设置上下文参数 | 打开编解码器 )](https://hanshuliang.blog.csdn.net/article/details/104661085)

<br>
<br>

#### VII . FFMPEG 读取音视频流中的数据到 AVPacket ( 压缩编码后的数据包 )

---

<br> 


**1 . FFMPEG 获取 AVPacket 数据流程 :** 

<br>

**〇 前置操作 :** <font color=blue>FFMPEG 环境初始化 , <font color=green>获取 AVStream 音视频流 , <font color=red>获取 AVCodec 编解码器 , <font color=purple>然后才能进行下面的操作 ; 

<br>

**① 初始化 AVPacket 空数据包 :** <font color=red>**av_packet_alloc ( )** 

```cpp
AVPacket *avPacket = av_packet_alloc();
```

<br>

**② 读取 AVPacket 数据 :** <font color=red>**av_read_frame ( AVFormatContext \*s , AVPacket \*pkt )**

```cpp
int read_frame_result = av_read_frame(formatContext, avPacket);
```

<br>
<br>

**2 . 代码示例 :** 

```cpp
//读取数据包
// AVPacket 存放编码后的音视频数据的 , 获取该数据包后 , 需要对该数据进行解码 , 解码后将数据存放在 AVFrame 中
// AVPacket 是编码后的数据 , AVFrame 是编码前的数据
//创建 AVPacket 空数据包
AVPacket *avPacket = av_packet_alloc();
/*
    读取数据包 , 并存储到 AVPacket 数据包中
    参数分析 : 一维指针 与 二维指针 参数分析
      ① 注意 : 第二个参数是 AVPacket * 类型的 , 那么传入 AVPacket *avPacket 变量
            不能修改 avPacket 指针的指向 , 即该指针指向的结构体不能改变
            只能修改 avPacket 指向的结构体中的元素的值
              因此 , 传入的 avPacket 结构体指针必须先进行初始化 , 然后再传入
                  av_read_frame 函数内 , 没有修改 AVPacket *avPacket 的值 , 但是修改了结构体中元素的值
      ② 与此相对应的是 avformat_open_input 方法 , 传入 AVFormatContext ** 二维指针
          传入的的 AVFormatContext ** 是没有经过初始化的 , 连内存都没有分配
          在 avformat_open_input 方法中创建并初始化 AVFormatContext * 结构体指针
          然后将该指针地址赋值给 AVFormatContext **
              avformat_open_input 函数内修改了 AVFormatContext ** 参数的值
    返回值 0 说明读取成功 , 小于 0 说明读取失败 , 或者 读取完毕
 */
int read_frame_result = av_read_frame(formatContext, avPacket);
```


> [【Android FFMPEG 开发】FFMPEG 读取音视频流中的数据到 AVPacket ( 初始化 AVPacket 数据 | 读取 AVPacket )](https://blog.csdn.net/shulianghan/article/details/104746458)

<br>
<br>

#### VIII . FFMPEG AVFrame 图像格式转换 YUV -> RGBA 

---

<br> 

**1 . FFMPEG 解码 AVPacket 数据到 AVFrame 流程 :** 

<br>

**〇 前置操作 :** <font color=blue>FFMPEG 环境初始化 , <font color=green>获取 AVStream 音视频流 , <font color=red>获取 AVCodec 编解码器 , <font color=orange>读取音视频流中的数据到 AVPacket , <font color=cyan>解码 AVPacket 数据到 AVFrame , <font color=purple>然后才能进行下面的操作 ; 

<br>

**① 获取 SwsContext :** <font color=red>**sws_getContext ( )**

```cpp
SwsContext *swsContext = sws_getContext(
        //源图像的 宽 , 高 , 图像像素格式
        avCodecContext->width, avCodecContext->height, avCodecContext->pix_fmt,
        //目标图像 大小不变 , 不进行缩放操作 , 只将像素格式设置成 RGBA 格式的
        avCodecContext->width, avCodecContext->height, AV_PIX_FMT_RGBA,
        //使用的转换算法 , FFMPEG 提供了许多转换算法 , 有快速的 , 有高质量的 , 需要自己测试
        SWS_BILINEAR,
        //源图像滤镜 , 这里传 NULL 即可
        0,
        //目标图像滤镜 , 这里传 NULL 即可
        0,
        //额外参数 , 这里传 NULL 即可
        0
        );
```

<br>

**② 初始化图像数据存储空间 :** <font color=red> **av_image_alloc ( )**

```cpp
av_image_alloc(dst_data, dst_linesize,
               avCodecContext->width, avCodecContext->height, AV_PIX_FMT_RGBA,
               1);
```

<br>

**③ 转换图像格式 :** <font color=red>**sws_scale ( )**

```cpp
sws_scale(
        //SwsContext *swsContext 转换上下文
        swsContext,
        //要转换的数据内容
        avFrame->data,
        //数据中每行的字节长度
        avFrame->linesize,
        0,
        avFrame->height,
        //转换后目标图像数据存放在这里
        dst_data,
        //转换后的目标图像行数
        dst_linesize
        );
```


<br>
<br>

**2 . 代码示例 :** 

```cpp
//1 . 获取转换上下文
SwsContext *swsContext = sws_getContext(
        //源图像的 宽 , 高 , 图像像素格式
        avCodecContext->width, avCodecContext->height, avCodecContext->pix_fmt,
        //目标图像 大小不变 , 不进行缩放操作 , 只将像素格式设置成 RGBA 格式的
        avCodecContext->width, avCodecContext->height, AV_PIX_FMT_RGBA,
        //使用的转换算法 , FFMPEG 提供了许多转换算法 , 有快速的 , 有高质量的 , 需要自己测试
        SWS_BILINEAR,
        //源图像滤镜 , 这里传 NULL 即可
        0,
        //目标图像滤镜 , 这里传 NULL 即可
        0,
        //额外参数 , 这里传 NULL 即可
        0
        );

//2 . 初始化图像存储内存

//指针数组 , 数组中存放的是指针
uint8_t *dst_data[4];

//普通的 int 数组
int dst_linesize[4];

//初始化 dst_data 和 dst_linesize , 为其申请内存 , 注意使用完毕后需要释放内存
av_image_alloc(dst_data, dst_linesize,
               avCodecContext->width, avCodecContext->height, AV_PIX_FMT_RGBA,
               1);

//3 . 格式转换
sws_scale(
        //SwsContext *swsContext 转换上下文
        swsContext,
        //要转换的数据内容
        avFrame->data,
        //数据中每行的字节长度
        avFrame->linesize,
        0,
        avFrame->height,
        //转换后目标图像数据存放在这里
        dst_data,
        //转换后的目标图像行数
        dst_linesize
        );

```


>[【Android FFMPEG 开发】FFMPEG AVFrame 图像格式转换 YUV -> RGBA ( 获取 SwsContext | 初始化图像数据存储内存 | 图像格式转换 )](https://hanshuliang.blog.csdn.net/article/details/104772549) 


<br>
<br>

#### IX . ANativeWindow 原生绘制 

---

<br> 

**FFMPEG 解码 AVPacket 数据到 AVFrame 流程 :** 

<br>

**〇 前置操作 :** <font color=blue>FFMPEG 环境初始化 , <font color=green>获取 AVStream 音视频流 , <font color=red>获取 AVCodec 编解码器 , <font color=orange>读取音视频流中的数据到 AVPacket , <font color=cyan>解码 AVPacket 数据到 AVFrame , <font color=brown>AVFrame 图像格式转换 YUV -> RGBA , <font color=purple>然后才能进行下面的操作 ; 

<br>

**① Java 层获取 Surface 对象 :** <font color=blue>Surface 画布可以在 SurfaceView 的 SurfaceHolder 中获取

```java
//绘制图像的 SurfaceView
SurfaceView surfaceView;

//在 SurfaceView 回调函数中获取
SurfaceHolder surfaceHolder = surfaceView.getHolder() ; 

//获取 Surface 画布
Surface surface = surfaceHolder.getSurface() ;
```

<br>

**② 将 Surface 对象传递到 Native 层 :** <font color=green>在 SurfaceHolder.Callback 接口的 surfaceChanged 实现方法中 , 将 Surface 画布传递给 Native 层 ; 

```java
@Override
public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
    //画布改变 , 横竖屏切换 , 按下 Home 键 , 按下菜单键
    //将 Surface 传到 Native 层 , 在 Native 层绘制图像
    native_set_surface(holder.getSurface());
}

//调用该方法将 Surface 传递到 Native 层
native void native_set_surface(Surface surface);
```

**③ 设置 ANativeWindow 绘制缓冲区属性 :** <font color=red>**ANativeWindow_setBuffersGeometry ( )** 

```cpp
//设置 ANativeWindow 绘制窗口属性
//  传入的参数分别是 : ANativeWindow 结构体指针 , 图像的宽度 , 图像的高度 , 像素的内存格式
ANativeWindow_setBuffersGeometry(aNativeWindow, width, height, WINDOW_FORMAT_RGBA_8888);
```

<br>

**④ 获取 ANativeWindow_Buffer 绘制缓冲区 :** <font color=red>**ANativeWindow_lock ( )**

```cpp
//获取 ANativeWindow_Buffer , 如果获取失败 , 直接释放相关资源退出
ANativeWindow_Buffer aNativeWindow_Buffer;

//如果获取成功 , 可以继续向后执行 , 获取失败 , 直接退出
if(ANativeWindow_lock(aNativeWindow, &aNativeWindow_Buffer, 0)){
    //退出操作 , 释放 aNativeWindow 结构体指针
    ANativeWindow_release(aNativeWindow);
    aNativeWindow = 0;
    return;
}
```

**⑤ 填充图像数据到 ANativeWindow_Buffer 绘制缓冲区中 :** <font color=blue>将图像字节数据使用内存拷贝到 ANativeWindow_Buffer 结构体的 bits 字段中 ; 

```cpp
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
```

**⑥ 启动绘制 :** <font color=red>**ANativeWindow_unlockAndPost ( )** 

```cpp
//启动绘制
ANativeWindow_unlockAndPost(aNativeWindow);
```

<br>
<br>

**2 . 代码示例 :** 

```cpp
// I . 图像格式转换


//指针数组 , 数组中存放的是指针
uint8_t *dst_data[4];

//普通的 int 数组
int dst_linesize[4];

//初始化 dst_data 和 dst_linesize , 为其申请内存 , 注意使用完毕后需要释放内存
av_image_alloc(dst_data, dst_linesize,
               avCodecContext->width, avCodecContext->height, AV_PIX_FMT_RGBA,
               1);

//3 . 格式转换
sws_scale(
        //SwsContext *swsContext 转换上下文
        swsContext,
        //要转换的数据内容
        avFrame->data,
        //数据中每行的字节长度
        avFrame->linesize,
        0,
        avFrame->height,
        //转换后目标图像数据存放在这里
        dst_data,
        //转换后的目标图像行数
        dst_linesize
        );


// II . 拷贝图像数据


//1 . 向 ANativeWindow_Buffer 填充 RGBA 像素格式的图像数据
uint8_t *dst_data = static_cast<uint8_t *>(aNativeWindow_Buffer.bits);


//2 . 参数中的 uint8_t *data 数据中 , 每一行有 linesize 个 , 拷贝的目标也要逐行拷贝
//  aNativeWindow_Buffer.stride 是每行的数据个数 , 每个数据都包含一套 RGBA 像素数据 ,
//      RGBA 数据每个占1字节 , 一个 RGBA 占 4 字节
//  每行的数据个数 * 4 代表 RGBA 数据个数
int dst_linesize = aNativeWindow_Buffer.stride * 4;


//3 . 获取 ANativeWindow_Buffer 中数据的地址
//      一次拷贝一行 , 有 像素高度 行数
for(int i = 0; i < aNativeWindow_Buffer.height; i++){

    //计算拷贝的指针地址
    //  每次拷贝的目的地址 : dst_data + ( i * dst_linesize )
    //  每次拷贝的源地址 : data + ( i * linesize )
    memcpy(dst_data + ( i * dst_linesize ), data + ( i * linesize ), dst_linesize);
    
}


// III . 启动绘制
//启动绘制
ANativeWindow_unlockAndPost(aNativeWindow);

```


>[【Android FFMPEG 开发】FFMPEG ANativeWindow 原生绘制 ( Java 层获取 Surface | 传递画布到本地 | 创建 ANativeWindow )](https://hanshuliang.blog.csdn.net/article/details/104788783)
> [【Android FFMPEG 开发】FFMPEG ANativeWindow 原生绘制 ( 设置 ANativeWindow 缓冲区属性 | 获取绘制缓冲区 | 填充数据到缓冲区 | 启动绘制 )](https://blog.csdn.net/shulianghan/article/details/104790084)




<br>
<br>

#### X . FFMPEG 音频重采样

---

<br> 


**1 . FFMPEG 音频重采样流程 :** 

<br>

**〇 视频播放操作 :** <font color=blue>FFMPEG 环境初始化 , <font color=green>获取 AVStream 音视频流 , <font color=red>获取 AVCodec 编解码器 , <font color=orange>读取音视频流中的数据到 AVPacket , <font color=cyan>解码 AVPacket 数据到 AVFrame , <font color=brown>AVFrame 图像格式转换 YUV -> RGBA , <font color=magenta>ANativeWindow 原生绘制 ; 

<br>

**〇 音频播放操作 :** <font color=blue>FFMPEG 环境初始化 , <font color=green>获取 AVStream 音视频流 , <font color=red>获取 AVCodec 编解码器 , <font color=orange>读取音视频流中的数据到 AVPacket , <font color=cyan>解码 AVPacket 数据到 AVFrame , <font color=purple>然后进行下面的操作 , 音频重采样 ; 

<br>

**① 初始化音频重采样上下文 : <font color=red>struct SwrContext \*swr_alloc_set_opts( ... )<font color=black> , <font color=blue>int swr_init(struct SwrContext \*s)**

```cpp
SwrContext *swrContext = swr_alloc_set_opts(
        0 ,                     //现在还没有 SwrContext 上下文 , 先传入 0
        //输出的音频参数
        AV_CH_LAYOUT_STEREO ,   //双声道立体声
        AV_SAMPLE_FMT_S16 ,     //采样位数 16 位
        44100 ,                 //输出的采样率
        //从编码器中获取输入音频格式
        avCodecContext->channel_layout, //输入的声道数
        avCodecContext->sample_fmt,     //输入的采样位数
        avCodecContext->sample_rate,    //输入的采样率
        0, 0    //日志参数 设置 0 即可
        );
        
swr_init(swrContext);
```


<br>

**② 计算积压的延迟数据 :** <font color=red>**int64_t swr_get_delay(struct SwrContext \*s, int64_t base)** 

```cpp
int64_t delay = swr_get_delay(swrContext , avFrame->sample_rate);
```

<br>

**③ 计算本次重采样后的样本个数 :** <font color=red>**int64_t av_rescale_rnd(int64_t a, int64_t b, int64_t c, enum AVRounding rnd) av_const**

```cpp
int64_t out_count = av_rescale_rnd(
        avFrame->nb_samples + delay, //本次要处理的数据个数
        44100,
        avFrame->sample_rate ,
        AV_ROUND_UP );
```

<br>

**④ 音频重采样 :** <font color=red>**int swr_convert(struct SwrContext \*s, uint8_t \*\*out, int out_count, const uint8_t \*\*in , int in_count)** 

```cpp
int samples_per_channel_count = swr_convert(
        swrContext ,
        &data,
        out_count ,
        (const uint8_t **)avFrame->data, //普通指针转为 const 指针需要使用 const_cast 转换
        avFrame->nb_samples
        );
```

<br>

**⑤ 计算音频重采样字节数 :** <font color=blue>音频重采样 swr_convert ( ) 返回值 samples_per_channel_count  是 每个通道的样本数 ; 

```cpp
pcm_data_bit_size = samples_per_channel_count * 2 * 2;
```

<br>
<br>

**2 . 代码示例 :** 

```cpp
// I . 音频重采样输出缓冲区准备


/**
 * 存放重采样后的数据缓冲区 , 这个缓冲区存储 1 秒的数据 
 * 44100 Hz 采样率 , 16 位采样位数 , 双声道立体声 , 占用内存 44100 * 2 * 2 字节 
 */
uint8_t *data = static_cast<uint8_t *>(malloc(44100 * 2 * 2)); 

//初始化内存数据
memset(data, 0, 44100 * 2 * 2);


// II . 音频重采样上下文 初始化


/*
 设置音频重采样的上下文参数
 struct SwrContext *swr_alloc_set_opts(struct SwrContext *s,
    int64_t out_ch_layout, enum AVSampleFormat out_sample_fmt, int out_sample_rate,
    int64_t  in_ch_layout, enum AVSampleFormat  in_sample_fmt, int  in_sample_rate,
    int log_offset, void *log_ctx);
 */
swrContext = swr_alloc_set_opts(
        0 ,                     //现在还没有 SwrContext 上下文 , 先传入 0
        //输出的音频参数
        AV_CH_LAYOUT_STEREO ,   //双声道立体声
        AV_SAMPLE_FMT_S16 ,     //采样位数 16 位
        44100 ,                 //输出的采样率
        //从编码器中获取输入音频格式
        avCodecContext->channel_layout, //输入的声道数
        avCodecContext->sample_fmt,     //输入的采样位数
        avCodecContext->sample_rate,    //输入的采样率
        0, 0    //日志参数 设置 0 即可
        );
        
//注意创建完之后初始化
swr_init(swrContext);


// III . 获取延迟数据


//OpenSLES 播放器设定播放的音频格式是 立体声 , 44100 Hz 采样 , 16位采样位数
//  解码出来的 AVFrame 中的数据格式不确定 , 需要进行重采样
/*
    int64_t swr_get_delay(
    struct SwrContext *s,
    int64_t base
    );
    转码的过程中 , 输入 10 个数据 , 并不一定都能处理完毕并输出 10 个数据 , 可能处理输出了 8 个数据
    还剩余 2 个数据没有处理
    那么在下一次处理的时候 , 需要将上次没有处理完的两个数据处理了 ;
    如果不处理上次的2个数据 , 那么数据会一直积压 , 如果积压数据过多 , 最终造成很大的延迟 , 甚至崩溃
    因此每次处理的时候 , 都要尝试将上次剩余没有处理的数据加入到本次处理的数据中
    如果计算出的 delay 一直等于 0 , 说明没有积压数据
 */
int64_t delay = swr_get_delay(swrContext , avFrame->sample_rate);


// IV . 计算输出样本个数


/*
    将 a 个数据 , 由 c 采样率转换成 b 采样率后 , 返回多少数据
    int64_t av_rescale_rnd(int64_t a, int64_t b, int64_t c, enum AVRounding rnd) av_const;
    下面的方法时将 avFrame->nb_samples 个数据 , 由 avFrame->sample_rate 采样率转为 44100 采样率
    返回的数据个数
    AV_ROUND_UP : 向上取整
 */
int64_t out_count = av_rescale_rnd(
        avFrame->nb_samples + delay, //本次要处理的数据个数
        44100,
        avFrame->sample_rate ,
        AV_ROUND_UP );


// V . 音频重采样


/*
 int swr_convert(
        struct SwrContext *s,   //上下文
        uint8_t **out,          //输出的缓冲区 ( 需要计算 )
        int out_count,          //输出的缓冲区最大可接受的样本个数 ( 需要计算 )
        const uint8_t **in ,    //输入的数据
        int in_count);          //输入的样本个数
返回值 : 转换后的采样个数 , 是样本个数 , 每个样本是 16 位 , 两个字节 ;
        samples_out_count 是每个通道的样本数 , samples_out_count * 2 是立体声双声道样本个数
        samples_out_count * 2 * 2 是字节个数
 */
int samples_per_channel_count = swr_convert(
        swrContext ,
        &data,
        out_count ,
        (const uint8_t **)avFrame->data, //普通指针转为 const 指针需要使用 const_cast 转换
        avFrame->nb_samples
        );


// VI . 最终重采样后的数据字节大小


//根据样本个数计算样本的字节数
pcm_data_bit_size = samples_per_channel_count * 2 * 2;
```

>[【Android FFMPEG 开发】FFMPEG 音频重采样 ( 初始化音频重采样上下文 SwrContext | 计算音频延迟 | 计算输出样本个数 | 音频重采样 swr_convert )](https://blog.csdn.net/shulianghan/article/details/104871223)


<br>
<br>

#### XI . OpenSLES 播放音频

---

<br> 

**1 . OpenSLES 播放音频流程 :** 

<br>

**〇 视频播放操作 :** <font color=blue>FFMPEG 环境初始化 , <font color=green>获取 AVStream 音视频流 , <font color=brown>获取 AVCodec 编解码器 , <font color=orange>读取音视频流中的数据到 AVPacket , <font color=cyan>解码 AVPacket 数据到 AVFrame , <font color=brown>AVFrame 图像格式转换 YUV -> RGBA , <font color=magenta>ANativeWindow 原生绘制 ; 

<br>

**〇 音频播放操作 :** <font color=blue>FFMPEG 环境初始化 , <font color=green>获取 AVStream 音视频流 , <font color=brown>获取 AVCodec 编解码器 , <font color=orange>读取音视频流中的数据到 AVPacket , <font color=cyan>解码 AVPacket 数据到 AVFrame , <font color=purple>音频重采样 , <font color=red>然后使用 OpenSLES 播放重采样后的音频 ; 

<br>

**① 创建引擎 :** <font color=red>先创建引擎对象 , 再实现引擎对象 , 最后从引擎对象中 , 获取引擎接口 ; 

```cpp
SLresult result;

// 创建引擎
result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);

// 实现引擎
result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);

// 获取引擎接口
result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
```

 

<br>

**② 设置输出混音器 :** <font color=blue>创建输出混音器对象 , 实现输出混音器 ;

```cpp
// 创建输出混音器对象 , 可以指定一个混响效果参数 ( 该混淆参数可选 )
const SLInterfaceID ids_engine[1] = {SL_IID_ENVIRONMENTALREVERB};
const SLboolean req_engine[1] = {SL_BOOLEAN_FALSE};
result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, ids_engine, req_engine);

// 实现输出混音器
result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
```

<br>

**③  获取混响接口并设置混响 :** <font color=cyan>该步骤不是必须操作 , 另外获取混响接口可能失败 ; 

```cpp
// 获取混响接口
result = (*outputMixObject)->GetInterface(outputMixObject, SL_IID_ENVIRONMENTALREVERB,
                                           &outputMixEnvironmentalReverb);
// 设置混响
if (SL_RESULT_SUCCESS == result) {
    result = (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(
            outputMixEnvironmentalReverb, &reverbSettings);
    (void)result;
}
```

<br>

**④ 配置音源输入 :** <font color=brown>配置音频数据源缓冲队列 , 和 音源格式 ( 采样率 , 样本位数 , 通道数 , 样本大小端格式 ) ; 

```cpp
//1 . 配置音源输入

// 配置要播放的音频输入缓冲队列属性参数 , 缓冲区大小 , 音频格式 , 采样率 , 样本位数 , 通道数 , 样本大小端格式
SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};

// PCM 格式
SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM,           //PCM 格式
                               2,                           //两个声道
                               SL_SAMPLINGRATE_44_1,        //采样率 44100 Hz
                               SL_PCMSAMPLEFORMAT_FIXED_16, //采样位数 16位
                               SL_PCMSAMPLEFORMAT_FIXED_16, //容器为 16 位
                               SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,  //左右双声道
                               SL_BYTEORDER_LITTLEENDIAN};  //小端格式
                               
// 设置音频数据源 , 配置缓冲区 ( loc_bufq ) 与 音频格式 (format_pcm)
SLDataSource audioSrc = {&loc_bufq, &format_pcm};
```

<br>

**⑤ 配置音频输出 :** <font color=green>装载输出混音器对象 到 SLDataLocator_OutputMix , 在将 SLDataLocator_OutputMix 结构体装载到 SLDataSink 中 ; 

```cpp
// 配置混音器 : 将 outputMixObject 混音器对象装载入 SLDataLocator_OutputMix 结构体中
SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
// 将 SLDataLocator_OutputMix 结构体装载到 SLDataSink 中
//  音频输出通过 loc_outmix 输出 , 实际上是通过 outputMixObject 混音器对象输出的
SLDataSink audioSnk = {&loc_outmix, NULL};
```

<br>

**⑥ 创建并实现播放器 :** <font color=blue>先使用 引擎 , 音源输入 , 音频输出 , 采样率 , 接口队列ID 等参数创建播放器 , 再实现播放器对象 ; 

```cpp
// 操作队列接口 , 如果需要 特效接口 , 添加 SL_IID_EFFECTSEND
const SLInterfaceID ids_player[3] = {SL_IID_BUFFERQUEUE, SL_IID_VOLUME, SL_IID_EFFECTSEND,
        /*SL_IID_MUTESOLO,*/};
const SLboolean req_player[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,
        /*SL_BOOLEAN_TRUE,*/ };
        
// 创建播放器
result = (*engineEngine)->CreateAudioPlayer(
        engineEngine,
        &bqPlayerObject,
        &audioSrc, //音频输入
        &audioSnk, //音频商户处
        bqPlayerSampleRate? 2 : 3,//
        ids_player,
        req_player);
        
// 创建播放器对象
result = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
```

<br>

**⑦ 获取播放器接口 和 缓冲队列接口 :** <font color=magenta>获取的接口 对应 播放器创建时的接口 ID 数组参数 ; 

```cpp
// 获取播放器 Player 接口 : 该接口用于设置播放器状态 , 开始 暂停 停止 播放 等操作
result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);


// 获取播放器 缓冲队列 接口 : 该接口用于控制 音频 缓冲区数据 播放
result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE,
                                         &bqPlayerBufferQueue);
```

<br>

**⑧ 注册回调函数 :** <font color=red>按照指定的回调函数类型 , 声明并实现该回调函数 , 并将该回调函数注册给播放器缓冲队列接口 ; 

```cpp
// 注册缓冲区队列的回调函数 , 每次播放完数据后 , 会自动回调该函数
//      传入参数 this , 就是 bqPlayerCallback 函数中的 context 参数
result = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, bqPlayerCallback, this);
```

**回调函数类型 :** 

```cpp
typedef void (SLAPIENTRY *slAndroidSimpleBufferQueueCallback)(
	SLAndroidSimpleBufferQueueItf caller,
	void *pContext
);
```

**回调函数实现 :** 

```cpp
//每当缓冲数据播放完毕后 , 会自动回调该回调函数
void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
{
	...
    
    //通过播放器队列接口 , 将 PCM 数据加入到该队列缓冲区后 , 就会自动播放这段音频
    (*bq)->Enqueue(bq, audioChannel->data, data_size);

}
```

<br>

**⑨ 获取效果器接口 和 音量控制接口 :** <font color=orange>这两个接口不是必须的 , 可选选项 ; 

```cpp
    // 获取效果器发送接口 ( get the effect send interface )
    bqPlayerEffectSend = NULL;
    if( 0 == bqPlayerSampleRate) {
        result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_EFFECTSEND,
                                                 &bqPlayerEffectSend);
    }

    // 获取音量控制接口 ( get the volume interface ) [ 如果需要调节音量可以获取该接口 ]
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME, &bqPlayerVolume);
```

<br>

**⑩ 设置播放状态 :** <font color=purple>设置播放状态为 SL_PLAYSTATE_PLAYING ; 

```cpp
// 设置播放器正在播放状态 ( set the player's state to playing )
result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
```

<br>

**⑪ 手动调用激活回调函数 :** <font color=blue>第一次激活回调函数调用 , 需要手动激活 ; 

```cpp
// 手动激活 , 手动调用一次 bqPlayerCallback 回调函数
bqPlayerCallback(bqPlayerBufferQueue, this);
```

<br>
<br>

**2 . 代码示例 :** 

```cpp
    // I . 创建 OpenSLES 引擎并获取引擎的接口 ( 相关代码拷贝自 Google 官方示例 native-audio )
    //      参考 : https://github.com/android/ndk-samples/blob/master/native-audio/app/src/main/cpp/native-audio-jni.c

    //声明每个方法执行的返回结果 , 一般情况下返回 SL_RESULT_SUCCESS 即执行成功
    //  该类型本质是 int 类型 , 定义的是各种类型的异常
    SLresult result;

    // 创建引擎
    result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);

    // 返回 0 成功 , 否则失败 , 一旦失败就中断退出
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // 实现引擎
    result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // 获取引擎接口 , 使用该接口创建输出混音器 , 音频播放器等其它对象
    //      引擎对象不提供任何调用的方法 , 引擎调用的方法都定义在接口中
    result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;



    // II . 设置输出混音器



    //  输出声音 , 添加各种音效 ( 混响 , 重低音 , 环绕音 , 均衡器 等 ) , 都要通过混音器实现 ;

    // 创建输出混音器对象 , 可以指定一个混响效果参数 ( 该混淆参数可选 )
    const SLInterfaceID ids_engine[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean req_engine[1] = {SL_BOOLEAN_FALSE};
    result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, ids_engine, req_engine);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // 实现输出混音器
    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;



    // III . 获取混响接口 并 设置混响 ( 可能会失败 )


    // 获取环境混响接口
    // 如果环境混响效果不可用 , 该操作可能失败
    // either because the feature is not present, excessive CPU load, or
    // the required MODIFY_AUDIO_SETTINGS permission was not requested and granted
    result = (*outputMixObject)->GetInterface(outputMixObject, SL_IID_ENVIRONMENTALREVERB,
                                               &outputMixEnvironmentalReverb);
    if (SL_RESULT_SUCCESS == result) {
        result = (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(
                outputMixEnvironmentalReverb, &reverbSettings);
        (void)result;
    }




    //IV . 配置音源输入


    // 配置要播放的音频输入缓冲队列属性参数 , 缓冲区大小 , 音频格式 , 采样率 , 样本位数 , 通道数 , 样本大小端格式
    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    /*
        typedef struct SLDataFormat_PCM_ {
        SLuint32 		formatType;     //数据格式                 SL_DATAFORMAT_PCM
        SLuint32 		numChannels;    //通道数 , 左右声道 2个     2
        SLuint32 		samplesPerSec;  //采样率 44100Hz           SL_SAMPLINGRATE_44_1
        SLuint32 		bitsPerSample;  //采样位数 16位            SL_PCMSAMPLEFORMAT_FIXED_16
        SLuint32 		containerSize;  //容器大小                 SL_PCMSAMPLEFORMAT_FIXED_16
        SLuint32 		channelMask;    //通道        SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT
        SLuint32		endianness;     //小端格式                 SL_BYTEORDER_LITTLEENDIAN
    } SLDataFormat_PCM;
     */
    SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM,           //PCM 格式
                                   2,                           //两个声道
                                   SL_SAMPLINGRATE_44_1,        //采样率 44100 Hz
                                   SL_PCMSAMPLEFORMAT_FIXED_16, //采样位数 16位
                                   SL_PCMSAMPLEFORMAT_FIXED_16, //容器为 16 位
                                   SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,  //左右双声道
                                   SL_BYTEORDER_LITTLEENDIAN};  //小端格式

    // 设置音频数据源 , 配置缓冲区 ( loc_bufq ) 与 音频格式 (format_pcm)
    SLDataSource audioSrc = {&loc_bufq, &format_pcm};



    // V . 配置音频输出


    // 配置混音器 : 将 outputMixObject 混音器对象装载入 SLDataLocator_OutputMix 结构体中
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};

    // 将 SLDataLocator_OutputMix 结构体装载到 SLDataSink 中
    //  音频输出通过 loc_outmix 输出 , 实际上是通过 outputMixObject 混音器对象输出的
    SLDataSink audioSnk = {&loc_outmix, NULL};




    // VI . 创建并实现播放器


    /*
     * 创建音频播放器:
     *      如果需要效果器时 , 不支持高性能音频
     *     ( fast audio does not support when SL_IID_EFFECTSEND is required, skip it
     *          for fast audio case )
     */

    // 操作队列接口 , 如果需要 特效接口 , 添加 SL_IID_EFFECTSEND
    const SLInterfaceID ids_player[3] = {SL_IID_BUFFERQUEUE, SL_IID_VOLUME, SL_IID_EFFECTSEND,
            /*SL_IID_MUTESOLO,*/};
    const SLboolean req_player[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,
            /*SL_BOOLEAN_TRUE,*/ };


    // 创建播放器
    result = (*engineEngine)->CreateAudioPlayer(
            engineEngine,
            &bqPlayerObject,
            &audioSrc, //音频输入
            &audioSnk, //音频商户处
            bqPlayerSampleRate? 2 : 3,//
            ids_player,
            req_player);

    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // 创建播放器对象
    result = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;



    // VII . 获取播放器接口 和 缓冲队列接口


    // 获取播放器 Player 接口 : 该接口用于设置播放器状态 , 开始 暂停 停止 播放 等操作
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;

    // 获取播放器 缓冲队列 接口 : 该接口用于控制 音频 缓冲区数据 播放
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE,
                                             &bqPlayerBufferQueue);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;




    // VIII . 注册回调函数


    // 注册缓冲区队列的回调函数 , 每次播放完数据后 , 会自动回调该函数
    //      传入参数 this , 就是 bqPlayerCallback 函数中的 context 参数
    result = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, bqPlayerCallback, this);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;



    // IX . 获取效果器接口 和 音量控制接口 ( 不是必须的 )


    // 获取效果器发送接口 ( get the effect send interface )
    bqPlayerEffectSend = NULL;
    if( 0 == bqPlayerSampleRate) {
        result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_EFFECTSEND,
                                                 &bqPlayerEffectSend);
        assert(SL_RESULT_SUCCESS == result);
        (void)result;
    }

#if 0   // mute/solo is not supported for sources that are known to be mono, as this is
    // get the mute/solo interface
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_MUTESOLO, &bqPlayerMuteSolo);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;
#endif

    // 获取音量控制接口

    // 获取音量控制接口 ( get the volume interface ) [ 如果需要调节音量可以获取该接口 ]
    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME, &bqPlayerVolume);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;



    // X . 设置播放状态


    // 设置播放器正在播放状态 ( set the player's state to playing )
    result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
    assert(SL_RESULT_SUCCESS == result);
    (void)result;


    // XI. 手动调用激活回调函数

    // 手动激活 , 手动调用一次 bqPlayerCallback 回调函数
    bqPlayerCallback(bqPlayerBufferQueue, this);
```


**3 . bqPlayerCallback 回调函数 :** 

```cpp
//每当缓冲数据播放完毕后 , 会自动回调该回调函数
// this callback handler is called every time a buffer finishes playing
void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
{
    //获取 PCM 采样数据 , 将重采样的数据放到 data 中
    int data_size ; 

	//进行 FFMPEG 音频重采样 ... 大块代码参考上一篇博客 

    //开始播放
    if ( data_size > 0 ){

        //通过播放器队列接口 , 将 PCM 数据加入到该队列缓冲区后 , 就会自动播放这段音频
        //  注意 , 最后一个参数是样本字节数
        (*bq)->Enqueue(bq, audioChannel->data, data_size);
    }

}
```









>[【Android FFMPEG 开发】OpenSLES 播放音频 ( 创建引擎 | 输出混音设置 | 配置输入输出 | 创建播放器 | 获取播放/队列接口 | 回调函数 | 开始播放 | 激活回调 )](https://blog.csdn.net/shulianghan/article/details/104880199)



<br>
<br>

#### XII . OpenSLES 播放音频

---

<br> 

**1 . 音视频同步总结 :** 

 <font color=red>以音频播放的时间为基准 , 调整视频的播放速度 , 让视频与音频进行同步 ; 

 <font color=blue>先计算出音频的播放时间 ; 再计算视频的播放时间 ; 

 <font color=green>根据视频与音频之间的比较 , 如果视频比音频快 , 那么增大视频帧之间的间隔 , 降低视频帧绘制速度 ; 
如果视频比音频慢 , 那么需要丢弃部分视频帧 , 以追赶上音频的速度 ; 

<br> 

<br> 

**2 . 音视频同步代码示例 :** 

```cpp
//根据帧率 ( fps ) 计算两次图像绘制之间的间隔
//  注意单位换算 : 实际使用的是微秒单位 , 使用 av_usleep ( ) 方法时 , 需要传入微秒单位 , 后面需要乘以 10 万
double frame_delay = 1.0 / fps;


while (isPlaying){
    //从线程安全队列中获取 AVFrame * 图像
    ...
    
    //获取当前画面的相对播放时间 , 相对 : 即从播放开始到现在的时间
    //  该值大多数情况下 , 与 pts 值是相同的
    //  该值比 pts 更加精准 , 参考了更多的信息
    //  转换成秒 : 这里要注意 pts 需要转成 秒 , 需要乘以 time_base 时间单位
    //  其中 av_q2d 是将 AVRational 转为 double 类型
    double vedio_best_effort_timestamp_second = avFrame->best_effort_timestamp * av_q2d(time_base);
    
    //解码时 , 该值表示画面需要延迟多长时间在显示
    //  extra_delay = repeat_pict / (2*fps)
    //  需要使用该值 , 计算一个额外的延迟时间
    //  这里按照文档中的注释 , 计算一个额外延迟时间
    double extra_delay = avFrame->repeat_pict / ( fps * 2 );
    
    //计算总的帧间隔时间 , 这是真实的间隔时间
    double total_frame_delay = frame_delay + extra_delay;
    
    //将 total_frame_delay ( 单位 : 秒 ) , 转换成 微秒值 , 乘以 10 万
    unsigned microseconds_total_frame_delay = total_frame_delay * 1000 * 1000;
    
    if(vedio_best_effort_timestamp_second == 0 ){
    
        //如果播放的是第一帧 , 或者当前音频没有播放 , 就要正常播放
        //休眠 , 单位微秒 , 控制 FPS 帧率
        av_usleep(microseconds_total_frame_delay);
        
    }else{
    
        //如果不是第一帧 , 要开始考虑音视频同步问题了
        //获取音频的相对时间
        if(audioChannel != NULL) {
            //音频的相对播放时间 , 这个是相对于播放开始的相对播放时间
            double audio_pts_second = audioChannel->audio_pts_second;
            
            //使用视频相对时间 - 音频相对时间
            double second_delta = vedio_best_effort_timestamp_second - audio_pts_second;
            
            //将相对时间转为 微秒单位
            unsigned microseconds_delta = second_delta * 1000 * 1000;
            
            //如果 second_delta 大于 0 , 说明视频播放时间比较长 , 视频比音频快
            //如果 second_delta 小于 0 , 说明视频播放时间比较短 , 视频比音频慢
            if(second_delta > 0){
            
                //视频快处理方案 : 增加休眠时间
                //休眠 , 单位微秒 , 控制 FPS 帧率
                av_usleep(microseconds_total_frame_delay + microseconds_delta);
                
            }else if(second_delta < 0){
            
                //视频慢处理方案 :
                //  ① 方案 1 : 减小休眠时间 , 甚至不休眠
                //  ② 方案 2 : 视频帧积压太多了 , 这里需要将视频帧丢弃 ( 比方案 1 极端 )
                if(fabs(second_delta) >= 0.05){
                  
                    //丢弃解码后的视频帧
                    ...
                    
                    //终止本次循环 , 继续下一次视频帧绘制
                    continue;
if
                }else{
                    //如果音视频之间差距低于 0.05 秒 , 不操作 ( 50ms )
                }
            }
        }
    }


```


>[【Android FFMPEG 开发】FFMPEG 音视频同步 ( 音视频同步方案 | 视频帧 FPS 控制 | H.264 编码 I / P / B 帧 | PTS | 音视频同步 )](https://blog.csdn.net/shulianghan/article/details/104891200)


<br>
<br>

#### XIII . GitHub 代码地址

---

<br> 

**1 . GitHub 代码地址 :** [FFMPEG 直播示例](https://github.com/han1202012/011_FFMPEG)


**2 . 效果展示 :** <font color=blue>使用的是湖南卫视的直播源 rtmp://58.200.131.2:1935/livetv/hunantv 
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200406133653776.gif)
