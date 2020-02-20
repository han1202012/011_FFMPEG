# I . 指定 CMake 最低版本
cmake_minimum_required(VERSION 3.4.1)

# II . 设置函数库编译
add_library( # 参数 1 : 设置生成的动态库名称
        native-lib

        # 参数 2 : 设置生成的函数库类型 : ① 静态库 STATIC ② 动态库 SHARED
        SHARED

        # 参数 3 : 配置要编译的源文件
        native-lib.cpp)

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
        avcodec
        avfilter
        avformat
        avutil
        swresample
        swscale

        # 日志库
        ${log-lib})