LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dx_static

LOCAL_MODULE_FILENAME := libcocos2d

LOCAL_SRC_FILES := $(LOCAL_PATH)/base/CCConfiguration.cpp \
                   $(LOCAL_PATH)/base/CCConsole.cpp \
                   $(LOCAL_PATH)/base/CCData.cpp \
                   $(LOCAL_PATH)/base/ccRandom.cpp \
                   $(LOCAL_PATH)/base/CCRef.cpp \
                   $(LOCAL_PATH)/base/ccTypes.cpp \
                   $(LOCAL_PATH)/base/CCValue.cpp \
                   $(LOCAL_PATH)/base/etc1.cpp \
                   $(LOCAL_PATH)/base/pvr.cpp \
                   $(LOCAL_PATH)/base/TGAlib.cpp \
                   $(LOCAL_PATH)/base/ZipUtils.cpp \
                   $(LOCAL_PATH)/math/CCAffineTransform.cpp \
                   $(LOCAL_PATH)/math/CCGeometry.cpp \
                   $(LOCAL_PATH)/math/CCVertex.cpp \
                   $(LOCAL_PATH)/math/Mat4.cpp \
                   $(LOCAL_PATH)/math/MathUtil.cpp \
                   $(LOCAL_PATH)/math/Quaternion.cpp \
                   $(LOCAL_PATH)/math/TransformUtils.cpp \
                   $(LOCAL_PATH)/math/Vec2.cpp \
                   $(LOCAL_PATH)/math/Vec3.cpp \
                   $(LOCAL_PATH)/math/Vec4.cpp \
                   $(LOCAL_PATH)/platform/CCFileUtils.cpp \
                   $(LOCAL_PATH)/platform/CCImage.cpp \
                   $(LOCAL_PATH)/platform/CCSAXParser.cpp \
                   $(LOCAL_PATH)/platform/android/CCFileUtils-android.cpp \
                   $(LOCAL_PATH)/platform/android/javaactivity-android.cpp \
                   $(LOCAL_PATH)/platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.cpp \
                   $(LOCAL_PATH)/platform/android/jni/JniHelper.cpp \
                   $(LOCAL_PATH)/platform/android/CCDevice-android.cpp
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/platform \
                    $(LOCAL_PATH)/../../external/android/include

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_STATIC_LIBRARIES := cocos_jpeg_static cocos_png_static external_static cocos_zlib_static
LOCAL_WHOLE_STATIC_LIBRARIES := cpufeatures

LOCAL_EXPORT_LDLIBS := -landroid -llog

include $(BUILD_STATIC_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../external/android/libs)
$(call import-module, png)
$(call import-module, jpeg)
$(call import-module, zlib)
$(call import-add-path, $(path)/../external)
$(call import-module, source)
$(call import-module,android/cpufeatures)