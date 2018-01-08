#include <memory>

#include <android/log.h>
#include <jni.h>

#include "../../../../tests/gfx/Basic.h"
#include "../../../../tests/gfx/Bunny.h"
#include "../../../../tests/gfx/Blending.h"
#include "../../../../tests/gfx/DepthTexture.h"
#include "../../../../tests/gfx/GuiProjection.h"
#include "../../../../tests/gfx/MultiTextures.h"
#include "../../../../tests/gfx/Particle.h"
#include "../../../../tests/gfx/PostProcess.h"
#include "../../../../tests/gfx/Stencil.h"
#include "../../../../tests/gfx/SubImage.h"
#include "../../../../tests/gfx/Texture2D.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

namespace {
    using createFunc = TestBaseI* (*)();
    std::vector<createFunc> tests;
    TestBaseI* test = nullptr;

    void initTests()
    {
        tests = {
           // Basic::create,
           // Bunny::create,
           Blending::create,
           MultiTextures::create,
           Particle::create,
           Stencil::create,
           PostProcess::create,
           DepthTexture::create,
           GuiProjection::create,
           SubImage::create,
           Texture2DTest::create,
        };
    }
}

extern "C" {

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeRender(JNIEnv* env) {
        if (!test)
            test = test = tests[0]();
        test->tick(0.016f);
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
    }
}

void cocos_android_app_init(JNIEnv* env) {
    LOGD("cocos_android_app_init");
    initTests();
}
