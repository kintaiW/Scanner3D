//
// Created by kintai on 17-3-27.
//
#include <stdio.h>
#include <jni.h>

#include "ProcessImage.h"
#include "ThreadPool.h"
#include "Director.h"
#include "FutureLog.h"
//#define  LOG_TAG    "FUTURE"
//#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
//#define LOGK(x,...) LOGE("%s(%d)," x,__FUNCTION__,__LINE__,__VA_ARGS__);

//extern "C"{


void
Java_net_sourceforge_opencamera_MainActivity_futureTest
    (JNIEnv * env, jobject thiz)
{
//    string str("/mnt/sdcard/Akintai/background.jpeg");
//    int temp = readLocalImage(str);
//    LOGK("future test 20170328: %d ",6);
    ThreadPool pool(4);
    auto result = pool.enqueue([](int answer) { return answer; }, 42);
    LOGK("future test 20170329: %d ",result.get());
}

void
Java_net_sourceforge_opencamera_MainActivity_futureTest
    (JNIEnv * env, jobject thiz, jint num)
{
    Director::getInstance()->addTask(num);
}

void
Java_net_sourceforge_opencamera_MainActivity_futureTest
(JNIEnv * env, jobject thiz, jstring path)
{
    const char * str;
    str = env->GetStringUTFChars(path,NULL);
    LOGK("java to native path:%s\n",str);
    char * pc = new char[strlen(str)+1];
    strcpy(pc,str);
    Director::getInstance()->setImagePath(pc);
    Director::getInstance()->startProcess();
}

//}