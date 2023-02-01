#include <jni.h>
#include <string>
#include <iostream>
#include "log.hpp"
#include "Jni_util.hpp"
#include "audio_resample.hpp"
#include "video_record.hpp"
#include "audio_encode.hpp"

extern "C"{
#include "libavformat/avformat.h"
}

using namespace std;
JavaVM *g_JavaVM = NULL;


//重采样
JNIEXPORT jint JNICALL
native_resamplePCM(JNIEnv *env, jobject thiz,
                   jstring inPCMFile,
                   jint inSampleRate,
                   jstring inSampleFmt,
                   jint inChannels,
                   jstring outPCMFile,
                   jint outSampleRate,
                   jstring outSampleFmt,
                   jint outChannels) {
    if (inChannels!=1&&inChannels!=2)return 1;
    if (outChannels!=1&&outChannels!=2)return 1;
    AudioResample resample;
    resample.in_pcm_file_path = jstring2str(env, inPCMFile);
    resample.in_sample_fmt = av_get_sample_fmt(jstring2str(env, inSampleFmt));
    resample.in_sample_rate = inSampleRate;
    resample.in_channels = inChannels == 1 ? AV_CH_LAYOUT_MONO : AV_CH_LAYOUT_STEREO;

    resample.out_pcm_file_path = jstring2str(env, outPCMFile);
    resample.out_sample_fmt = av_get_sample_fmt(jstring2str(env, outSampleFmt));
    resample.out_sample_rate = outSampleRate;
    resample.out_channels = outChannels == 1 ? AV_CH_LAYOUT_MONO : AV_CH_LAYOUT_STEREO;

    resample.init_codec();
    resample.convert();
    return 0;
}

//pcm转AAC
JNIEXPORT jint JNICALL
native_pcm2aac(JNIEnv *env, jobject thiz,
               jstring inPCMFile,
               jint inSampleRate,
               jstring inSampleFmt,
               jint inChannels,
               jstring outAACFilePath){
    AudioEncode audioEncode;
    audioEncode.inPcmFilePath = jstring2str(env,inPCMFile);
    audioEncode.outAACFilePath = jstring2str(env,outAACFilePath);
    audioEncode.inSampleFmt = AV_SAMPLE_FMT_FLT;
    audioEncode.inChannelLayout = inChannels==1 ? AV_CH_LAYOUT_MONO : AV_CH_LAYOUT_STEREO;
    audioEncode.inSampleRate = inSampleRate;
    if (audioEncode.initCodec()){
        audioEncode.convert();
    }
}

//视频录制
JNIEXPORT void JNICALL
native_record_video(JNIEnv *env, jobject thiz){
    VideoRecord videoRecord;
    videoRecord.initDevice();
}

static JNINativeMethod jniMethods[] = {
        {"resamplePCM", "(Ljava/lang/String;ILjava/lang/String;ILjava/lang/String;ILjava/lang/String;I)I", (void *) native_resamplePCM},
        {"pcm2aac", "(Ljava/lang/String;ILjava/lang/String;ILjava/lang/String;)I", (void *) native_pcm2aac},
        {"recordVideo", "()V", (void *) native_record_video},
};

static int registerNativeMethods(JNIEnv *env, const char *className,
                                 JNINativeMethod *gMethods, int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = JNI_ERR;
    g_JavaVM = vm;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }
    if (registerNativeMethods(env, "com/lucas/avcpp/AvCpp",
                              jniMethods,
                              sizeof(jniMethods) / sizeof(jniMethods[0])) == JNI_FALSE) {
        return JNI_ERR;
    }
    return JNI_VERSION_1_4;
}


