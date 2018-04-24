#include <jni.h>
#include <string>
#include <android/log.h>

const char* LOG_TAG = "Native Library Example";


void JNICALL NATIVE_EXECUTE(JNIEnv*) {
    __android_log_write(ANDROID_LOG_INFO, LOG_TAG, "nativeExecute");
}


extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
    __android_log_write(ANDROID_LOG_INFO, LOG_TAG, "OnLoad");

    JNIEnv *env = nullptr;
    vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);

    jclass nativeClass = env->FindClass("nl/ivovandongen/lib/Native");

    JNINativeMethod methods[] = {
            {"execute", "()V", reinterpret_cast<void *>(&NATIVE_EXECUTE)}
    };

    if (env->RegisterNatives(nativeClass, methods, 1) < 0) {
        env->ExceptionDescribe();
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}

extern "C" JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *, void *) {
    __android_log_write(ANDROID_LOG_INFO, LOG_TAG, "OnUnLoad");
}
