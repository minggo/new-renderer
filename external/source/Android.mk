LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

path := $(LOCAL_PATH)

LOCAL_MODULE := external_static

LOCAL_MODULE_FILENAME := libexternal

LOCAL_SRC_FILES := $(LOCAL_PATH)/firefox/WebGLFormats.cpp \
                   $(LOCAL_PATH)/firefox/WebGLTexelConversions.cpp \
                   $(LOCAL_PATH)/firefox/mozilla/Assertions.cpp \
                   $(LOCAL_PATH)/tinyxml2/tinyxml2.cpp \
                   $(LOCAL_PATH)/unzip/ioapi_mem.cpp \
                   $(LOCAL_PATH)/unzip/ioapi.cpp \
                   $(LOCAL_PATH)/unzip/unzip.cpp \
                   $(LOCAL_PATH)/ConvertUTF/ConvertUTF.c \
                   $(LOCAL_PATH)/ConvertUTF/ConvertUTFWrapper.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/firefox \
                    $(LOCAL_PATH)/tinydir \
                    $(LOCAL_PATH)/tinyxml2 \
                    $(LOCAL_PATH) \
                    $(LOCAL_PATH)/../android/include \
                    $(LOCAL_PATH)/../../cocos \
                    $(LOCAL_PATH)/../../cocos/platform

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/firefox \
                           $(LOCAL_PATH)/tinydir \
                           $(LOCAL_PATH)/tinyxml2 \
                           $(LOCAL_PATH)


LOCAL_CFLAGS   :=  -DUSE_FILE32API
LOCAL_CFLAGS   +=  -fexceptions

LOCAL_EXPORT_CFLAGS   := -DUSE_FILE32API


include $(BUILD_STATIC_LIBRARY)
