LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := main

#SDK_ROOT points to folder with SDL and oxygine-framework
LOCAL_SRC_FILES := ../../../../../..//SDL/src/main/android/SDL_android_main.c

SRC := ../../../src
LOCAL_SRC_FILES += $(SRC)/example.cpp $(SRC)/main.cpp $(SRC)/test.cpp


LOCAL_STATIC_LIBRARIES := oxygine-facebook_static  oxygine-framework_static
LOCAL_SHARED_LIBRARIES := SDL2

include $(BUILD_SHARED_LIBRARY)


#import from NDK_MODULE_PATH defined in build.cmd
$(call import-module, oxygine-framework)
$(call import-module, oxygine-facebook) 