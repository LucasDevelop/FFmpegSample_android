#ifndef AUDIO_ENCODE_HPP
#define AUDIO_ENCODE_HPP

#include "log.hpp"

extern "C" {
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
}

class AudioEncode {
private:
    AVCodecID codecId;
    AVCodec *codec;
    AVCodecContext *codecContext = nullptr;
public:
    const char *inPcmFilePath = nullptr;
    AVSampleFormat inSampleFmt = nullptr;
    int inSampleRate = 0;
    //声道枚举格式
    int inChannels;

    const char *outAACFilePath = nullptr;

    AudioEncode();

    bool initCodec();

    bool convert();

    ~AudioEncode();
};

#endif