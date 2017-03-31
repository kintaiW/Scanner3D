LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OPENCV_INSTALL_MODULES:=on
OPENCV_CAMERA_MODULES:=off
include /home/kintai/tools/OpenCV-android-sdk/sdk/native/jni/OpenCV.mk
LOCAL_MODULE := future
LOCAL_SRC_FILES := libfuturejni.cpp \
                    ProcessImage.cpp \
                    Director.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)

LOCAL_CPPFLAGS += -std=c++11 -DANDROID=1
LOCAL_LDLIBS += -llog

include $(BUILD_SHARED_LIBRARY)
#-D__cplusplus=201103L