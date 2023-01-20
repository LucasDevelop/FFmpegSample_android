#include "audio_encode.hpp"

AudioEncode::AudioEncode() {

}

//初始化编码器
//https://blog.51cto.com/u_4296776/5370091
//https://blog.csdn.net/qq_35651984/article/details/105682925
bool AudioEncode::initCodec() {
    int ret = 0;
    //查找编码器
    codecId = AV_CODEC_ID_AAC;
    codec = avcodec_find_encoder(codecId);
    if (!codec) {
        ALOGE("未找到编码器")
        return false;
    }
    //创建编码器上下文
    codecContext = avcodec_alloc_context3(codec);
    if (!codecContext) {
        ALOGE("创建编码器失败")
        return false;
    }
    //设置编码器参数 AV_CH_LAYOUT_STEREO
    codecContext->channel_layout = inChannels;
    codecContext->sample_rate = inSampleRate;
    codecContext->sample_fmt = inSampleFmt;
    codecContext->channels = av_get_channel_layout_nb_channels(inChannels);
    //码率=声道数*采样率*位深度
    codecContext->bit_rate =
            codecContext->channels * inSampleRate * av_get_bytes_per_sample(inSampleFmt);
    codecContext->profile = FF_PROFILE_AAC_LOW;
    //关联编码器
    ret = avcodec_open2(codecContext, codec, nullptr);
    if (ret < 0) {
        print_av_err(ret, "初始化编码器失败")
        goto end;
    }

    return true;
    end:
    return false;
}

bool AudioEncode::convert() {

}


AudioEncode::~AudioEncode() {

}