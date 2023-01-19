#include <jni.h>
#include <string>
#include <iostream>
#include "log.hpp"
#include <android/log.h>

using namespace std;
JavaVM *g_JavaVM = NULL;


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
    cout<<"inPCMFile:"<<endl;
    ALOGE("inPCMFile:")
    return 0;
}

static JNINativeMethod jniMethods[] = {
        {"resamplePCM", "(Ljava/lang/String;ILjava/lang/String;ILjava/lang/String;ILjava/lang/String;I)I", (void *) native_resamplePCM},
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

jint JNI_OnLoad(JavaVM *vm, void *reserved){
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


