#include "SeApi.h"
#include "Utils.h"
#include "jsb_global.h"
#include "jsb_gfx_auto.hpp"
#include "jsb_gfx_manual.hpp"
#include "jsb_conversions.hpp"

#include <memory>

#include <android/log.h>
#include <jni.h>

#define  MY_LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,MY_LOG_TAG,__VA_ARGS__)

namespace {
    enum class TouchEventType
    {
        BEGAN,
        MOVED,
        ENDED,
        CANCELLED
    };


    void onTouchEvent(TouchEventType type, int id, float x, float y)
    {
        auto se = se::ScriptEngine::getInstance();
        se->clearException();
        se::AutoHandleScope hs;

        auto global = se->getGlobalObject();
        se::Value touchUpFuncVal;
        if (global->getProperty("onTouchEvent", &touchUpFuncVal))
        {
            se::ValueArray args;
            args.push_back(se::Value((int)type));
            args.push_back(se::Value(x));
            args.push_back(se::Value(y));
            touchUpFuncVal.toObject()->call(args, nullptr);
        }
    }

    se::Value tickVal;
}

extern "C" {

    JNIEXPORT void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
    {
        utils::WINDOW_WIDTH = w;
        utils::WINDOW_HEIGHT = h;

        auto se = se::ScriptEngine::getInstance();
        se->addRegisterCallback(jsb_register_global_variables);
        se->addRegisterCallback(register_all_gfx);
        se->addRegisterCallback(jsb_register_gfx_manual);

    //    se->enableDebugger("0.0.0.0", 5678);

        se->addBeforeInitHook([](){
            JSBClassType::init();
        });

        jsb_init_file_operation_delegate();

        se->start();

        se::AutoHandleScope hs;

        char commandBuf[200] = {0};
        sprintf(commandBuf, "window.canvas = { width: %d, height: %d };", utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
        se->evalString(commandBuf);
        se->runScript("src/gfx.js");
        se->runScript("src/renderer-test/main-jsb.js");
        se->runScript("src/renderer-test/src/basic.js", &tickVal);

        se->addAfterCleanupHook([](){
            JSBClassType::destroy();
        });
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeRender(JNIEnv* env) {
        // FIXME:
        se::AutoHandleScope hs;
        float dt = 0.016f;
        se::ValueArray args;
        args.push_back(se::Value(dt));
        tickVal.toObject()->call(args, nullptr);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeOnPause() {
        
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeOnResume() {
        
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInsertText(JNIEnv* env, jobject thiz, jstring text) {
        
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeDeleteBackward(JNIEnv* env, jobject thiz) {
    }

    JNIEXPORT jstring JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeGetContentText() {
        return 0;
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesBegin(JNIEnv * env, jobject thiz, jint id, jfloat x, jfloat y) {
        onTouchEvent(TouchEventType::BEGAN, id, x, y);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesEnd(JNIEnv * env, jobject thiz, jint id, jfloat x, jfloat y) {
        onTouchEvent(TouchEventType::ENDED, id, x, y);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesMove(JNIEnv * env, jobject thiz, jintArray ids, jfloatArray xs, jfloatArray ys) {

    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeTouchesCancel(JNIEnv * env, jobject thiz, jintArray ids, jfloatArray xs, jfloatArray ys) {

    }
}

void cocos_android_app_init(JNIEnv* env) {
    LOGD("cocos_android_app_init");
}
