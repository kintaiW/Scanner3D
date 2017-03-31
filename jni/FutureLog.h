//
// Created by kintai on 17-3-30.
//

#ifndef OPENCAMERA_CODE_FUTURELOG_H
#define OPENCAMERA_CODE_FUTURELOG_H

#define LOG_TAG "Scanner3D"

#ifdef ANDROID
#include <android/log.h>
#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGK(x,...) LOGE("%s(%d)," x,__FUNCTION__,__LINE__,__VA_ARGS__)
#else
#include <stdio.h>
#define LOGK(x,...) fprintf(stdout,"%s(%d)," x,__FUNCTION__,__LINE__,__VA_ARGS__);//? no check
#endif

#endif //OPENCAMERA_CODE_FUTURELOG_H
