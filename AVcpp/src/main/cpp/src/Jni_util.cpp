#include <malloc.h>
#include <cstring>
#include "Jni_util.hpp"

using namespace std;

const char* jstring2str(JNIEnv *env,jstring jstr){
    //使用反射String 转换
    char * c= nullptr;
    jclass clazz = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID methodId =  env->GetMethodID(clazz,"getBytes","(Ljava/lang/String;)[B");
    jbyteArray byteArray= (jbyteArray)env->CallObjectMethod(jstr,methodId,strencode);
    jsize alen = env->GetArrayLength(byteArray);
    jbyte *ba = env->GetByteArrayElements(byteArray,JNI_FALSE);
    if (alen>0){
        c = static_cast<char *>(malloc(alen + 1));
        memcpy(c,ba,alen);
        c[alen]=0;
    }
    env->ReleaseByteArrayElements(byteArray,ba,0);
    return c;
}