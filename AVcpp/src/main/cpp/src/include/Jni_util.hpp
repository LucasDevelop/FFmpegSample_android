#ifndef JNI_UTIL_HPP
#define JNI_UTIL_HPP
#include <jni.h>
#include <string>
using  namespace std;

const char* jstring2str(JNIEnv *env,jstring jstr);

#endif