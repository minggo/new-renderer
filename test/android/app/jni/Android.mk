LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

path := $(LOCAL_PATH)

LOCAL_MODULE := MyGame

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../tests/Utils.cpp \
                   $(LOCAL_PATH)/../../../tests/gfx/Basic.cpp \
                   $(LOCAL_PATH)/../../../tests/gfx/Blending.cpp \
                   $(LOCAL_PATH)/../../../tests/gfx/Bunny.cpp \
                   $(LOCAL_PATH)/../../../tests/gfx/DepthTexture.cpp \
                   $(LOCAL_PATH)/../../../tests/gfx/GuiProjection.cpp \
                   $(LOCAL_PATH)/../../../tests/gfx/MultiTextures.cpp \
                   $(LOCAL_PATH)/../../../tests/gfx/Particle.cpp \
                   $(LOCAL_PATH)/../../../tests/gfx/PostProcess.cpp \
                   $(LOCAL_PATH)/../../../tests/gfx/Stencil.cpp \
                   $(LOCAL_PATH)/../../../tests/gfx/SubImage.cpp \
                   $(LOCAL_PATH)/../../../tests/gfx/Texture2D.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../tests \
                    $(LOCAL_PATH)/../../../tests/gfx


LOCAL_STATIC_LIBRARIES := newrenderer

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(path)/../../../..)
$(call import-module, src)
