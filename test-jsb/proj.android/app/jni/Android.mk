LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

path := $(LOCAL_PATH)

LOCAL_MODULE := MyGame

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../../test/tests/Utils.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/auto/jsb_gfx_auto.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/manual/jsb_classtype.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/manual/jsb_conversions.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/manual/jsb_gfx_manual.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/manual/jsb_global.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/config.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/HandleObject.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/MappingUtils.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/RefCounter.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/Value.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/State.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/Class.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/Object.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/ObjectWrap.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/SHA1.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/ScriptEngine.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/Utils.cpp \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/env.cc \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/inspector_agent.cc \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/inspector_io.cc \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/inspector_socket.cc \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/inspector_socket_server.cc \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/node.cc \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/node_debug_options.cc \
                   $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper/v8/util.cc \
                   $(LOCAL_PATH)/../../../../external/source/xxtea/xxtea.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../.. \
                    $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/jswrapper \
                    $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/auto \
                    $(LOCAL_PATH)/../../../../cocos/scripting/js-bindings/manual \
                    $(LOCAL_PATH)/../../../../test/tests


LOCAL_STATIC_LIBRARIES := newrenderer v8_static uv_static

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(path)/../../../..)
$(call import-module, src)
$(call import-add-path, $(path)/../../../../external/android/libs)
$(call import-module, v8)
$(call import-module, uv)
