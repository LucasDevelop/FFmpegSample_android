#include "Jni_util.hpp"


string string2str(JNIEnv *env,jstring jstr){
    //使用反射String 转换
    jclass clazz = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID methodId =  env->GetMethodID(clazz,"getBytes","(Ljava/lang/String;)[B");
    jbyteArray byteArray= (jbyteArray)env->CallObjectMethod(jstr,methodId,strencode);

}