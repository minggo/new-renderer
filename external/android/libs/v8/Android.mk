LOCAL_PATH := $(call my-dir)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_builtins_generators
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_builtins_generators.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_builtins_setup
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_builtins_setup.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_libbase
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_libbase.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_libplatform
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_libplatform.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_libsampler
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_libsampler.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_nosnapshot
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_nosnapshot.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_inspector
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libinspector.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := v8_static
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_base.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include/v8

LOCAL_WHOLE_STATIC_LIBRARIES += v8_builtins_generators v8_builtins_setup v8_libbase v8_libplatform v8_libsampler v8_nosnapshot v8_inspector

include $(PREBUILT_STATIC_LIBRARY)



