LOCAL_PATH := $(call my-dir)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := uv_static
LOCAL_MODULE_FILENAME := libuv
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libuv.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include/uv
include $(PREBUILT_STATIC_LIBRARY)


