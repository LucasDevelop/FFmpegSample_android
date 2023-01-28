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
    //分配packet
    packet = av_packet_alloc();
    if (!packet){
        ALOGE("alloc packet err")
        goto end;
    }
    //分配frame
    frame = av_frame_alloc();
    if (!frame) {
        ALOGE("alloc frame failed")
        goto end;
    }
    //设置frame参数
    frame->nb_samples = codecContext->frame_size;
    frame->format = codecContext->sample_fmt;
    frame->channel_layout = codecContext->channel_layout;
    frame->channels = codecContext->channels;
    //位frame分配buffer
    ret = av_frame_get_buffer(frame, 0);
    if (ret < 0) {
        print_av_err(ret, "frame get buffer err")
        goto end;
    }

    return true;
    end:
    if (packet){
        av_packet_free(&packet);
    }
    if (frame) {
        av_frame_free(&frame);
    }
    if (codecContext) {
        avcodec_free_context(&codecContext);
    }
    return false;
}

int AudioEncode::encode(AVFrame *avFrame,AVPacket *avPacket,ofstream aacFile){
    int ret = 0;
    ret= avcodec_send_frame(codecContext,frame);
    if (ret<0){
        print_av_err(ret,"send frame err")
        return ret;
    }
    // 编码和解码都是一样的，都是send 1次，然后receive多次, 直到AVERROR(EAGAIN)或者AVERROR_EOF
    while (ret>=0){
        ret = avcodec_receive_packet(codecContext,packet);
        if (ret == AVERROR(EAGAIN)||ret == AVERROR_EOF){
            return 0;
        } else if (ret < 0){
            print_av_err(ret,"receiver packet err")
            return ret;
        }
        
    }
}

bool AudioEncode::convert() {
    int ret=0;
    int64_t pts=0;
    //读取pcm数据
    ifstream pcmFile(inPcmFilePath);
    if (!pcmFile.is_open()) {
        ALOGE("open pcm file err.")
        return false;
    }
    ofstream aacFile(outAACFilePath);
    if (!aacFile.is_open()) {
        ALOGE("open aac file err")
        return false;
    }
    //计算一帧数据大小
    int frame_size = codecContext->channels * codecContext->sample_rate *
                     av_get_bytes_per_sample(codecContext->sample_fmt);
    char *pcm_buf = (char*) malloc(frame_size);
    for (;;) {
        //清空数据
        memset(pcm_buf,0,frame_size);
        pcmFile.read(pcm_buf,frame_size);
        if (pcmFile.gcount()<=0){
            ALOGD("read pcm file end.")
            break;
        }
        //确保frame可写
        ret = av_frame_make_writable(frame);
        if (ret<0){
            print_av_err(ret,"frame not writeable.")
            break;
        }
        if (frame->format==AV_SAMPLE_FMT_S16){
            ret = av_samples_fill_arrays(frame->data,frame->linesize,(uint8_t*)pcm_buf,frame->channels,frame->nb_samples,(AVSampleFormat)frame->format,0);
            if (ret<0){
                print_av_err(ret,"fill sample arrays err")
                break;
            }
        }
        //编码
        pts+=frame->nb_samples;
        frame->pts = pts; // 使用采样率作为pts的单位，具体换算成秒 pts*1/采样率
        encode();


    }
}


AudioEncode::~AudioEncode() {

}