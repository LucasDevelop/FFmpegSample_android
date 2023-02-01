#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <android/log.h>

extern "C" {
#include "libavutil/avutil.h"
}

#define A_TAG "ffmpeg_native"
#define ALOGD(...) \
        __android_log_print(ANDROID_LOG_DEBUG,A_TAG,__VA_ARGS__);

#define ALOGE(...) \
        __android_log_print(ANDROID_LOG_ERROR,A_TAG,__VA_ARGS__);

#define print_av_err(ret,msg) \
        char errInfo[1024]; \
        av_strerror(ret,errInfo,sizeof(errInfo)); \
        ALOGE("%s,code:%d,msg:%s",msg,ret,errInfo)
//        cout<<msg<<",err:"<<errInfo<<endl;

#endif