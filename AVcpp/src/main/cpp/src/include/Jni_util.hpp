#ifndef JNI_UTIL_HPP
#define JNI_UTIL_HPP
#include <jni.h>
#include <string>
using  namespace std;

string string2str(JNIEnv *env,jstring jstr);

#endif