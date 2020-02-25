//
// Created by octopus on 2020/2/25.
//

#ifndef INC_011_FFMPEG_FFMPEG_H
#define INC_011_FFMPEG_FFMPEG_H


//封装对视频的操作
class FFMPEG {


public: //类中默认都是私有的, 如果共有需要指定 public

    //构造函数
    FFMPEG(const char* dataSource);

    //析构函数
    ~FFMPEG();

private:

    //保存数据源
    char* dataSource;

};


#endif //INC_011_FFMPEG_FFMPEG_H
