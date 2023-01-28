#ifndef AUDIO_ENCODE_HPP
#define AUDIO_ENCODE_HPP

#include "log.hpp"
#include <fstream>

using namespace std;
extern "C" {
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
}

class AudioEncode {
private:
    AVCodecID codecId;
    AVCodec *codec;
    AVCodecContext *codecContext = nullptr;
    AVFrame *frame= nullptr;
    AVPacket *packet= nullptr;
    int encode(AVFrame *avFrame,AVPacket *avPacket,ofstream aacFile);
public:
    const char *inPcmFilePath = nullptr;
    AVSampleFormat inSampleFmt;
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