#include <jni.h>
#include <string>
#include <android/log.h>

#include "native-lib.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ioutils_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ioutils_MainActivity_methodOne(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_ioutils_MainActivity_methodTwo(
        JNIEnv *env,
        jobject /* this */) {
    return 3;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_ioutils_MainActivity_methodThree(
        JNIEnv *env,
        jobject object, jint val) {

    return val;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ioutils_MainActivity_methodFour(
        JNIEnv *env,
        jobject object, jstring val) {
    TRACED("[%s][%d]:\n", __func__, __LINE__);
    return val;
}