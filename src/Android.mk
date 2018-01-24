LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

path := $(LOCAL_PATH)

LOCAL_MODULE := newrenderer

LOCAL_MODULE_FILENAME := libnewrenderer

LOCAL_SRC_FILES := $(LOCAL_PATH)/types.cpp \
                   $(LOCAL_PATH)/gfx/CCDeviceGraphics-gl.cpp \
                   $(LOCAL_PATH)/gfx/CCFrameBuffer.cpp \
                   $(LOCAL_PATH)/gfx/CCGFX.cpp \
                   $(LOCAL_PATH)/gfx/CCGFXUtils.cpp \
                   $(LOCAL_PATH)/gfx/CCGraphicsHandle.cpp \
                   $(LOCAL_PATH)/gfx/CCIndexBuffer.cpp \
                   $(LOCAL_PATH)/gfx/CCProgram.cpp \
                   $(LOCAL_PATH)/gfx/CCRenderBuffer.cpp \
                   $(LOCAL_PATH)/gfx/CCRenderTarget.cpp \
                   $(LOCAL_PATH)/gfx/CCState.cpp \
                   $(LOCAL_PATH)/gfx/CCTexture.cpp \
                   $(LOCAL_PATH)/gfx/CCTexture2D.cpp \
                   $(LOCAL_PATH)/gfx/CCVertexBuffer.cpp \
                   $(LOCAL_PATH)/gfx/CCVertexFormat.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/gfx

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/gfx

LOCAL_EXPORT_LDLIBS := -lGLESv2

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_STATIC_LIBRARY)

$(call import-add-path, $(path))
$(call import-module, ../cocos)
