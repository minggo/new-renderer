#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
#include <vector>
#include <chrono>

#define GLFW_EXPOSE_NATIVE_COCOA
#include "glfw3/glfw3.h"
#include "glfw3/glfw3native.h"

#include "backend/metal/DeviceMTL.h"
#include "../tests/TestBase.h"
#include "../tests/Utils.h"

#include "../tests/backend/BasicBackend.h"
#include "../tests/backend/Texture2DBackend.h"
#include "../tests/backend/BunnyBackend.h"
#include "../tests/backend/DepthTextureBackend.h"
#include "../tests/backend/BlendingBackend.h"
#include "../tests/backend/MultiTexturesBackend.h"
#include "../tests/backend/StencilBackend.h"

namespace
{
    int nextIndex = 0;
    using createFunc = TestBaseI* (*)();
    std::vector<createFunc> tests;
    TestBaseI* test = nullptr;
    
    void keyCallback(GLFWwindow* window, int button, int action, int mods)
    {
        if (GLFW_RELEASE == action)
        {
            if (GLFW_MOUSE_BUTTON_RIGHT == button)
                nextIndex = (++nextIndex) % tests.size();
            else if (GLFW_MOUSE_BUTTON_LEFT == button)
                nextIndex = int((--nextIndex + tests.size()) % tests.size());
            
            delete test;
            test = tests[nextIndex]();
        }
    }
    
    void initTests()
    {
        static bool first = true;
        if (first)
        {
            tests = {
                StencilBackend::create,
                BlendingBackend::create,
                DepthTextureBackend::create,
                Texture2DBackendTest::create,
                MultiTexturesBackend::create,
                BasicBackend::create,
                BunnyBackend::create,
            };
            
            test = tests[0]();
            
            first = false;
        }
    }
}

int main(int argc, char * argv[])
{
    @autoreleasepool
    {
        if (!glfwInit())
            return -1;
        
        // Don't create gl context.
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        auto window = glfwCreateWindow(960, 640, "backend window", nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }
        
        NSView* contentView = [glfwGetCocoaWindow(window) contentView];
        [contentView setWantsLayer: YES];
        
        CGSize size;
        size.width = 960;
        size.height = 640;
        utils::WINDOW_WIDTH = 960;
        utils::WINDOW_HEIGHT = 640;
        
        CAMetalLayer* layer = [CAMetalLayer layer];
        [layer setDevice:MTLCreateSystemDefaultDevice()];
        [layer setPixelFormat:MTLPixelFormatBGRA8Unorm];
        [layer setFramebufferOnly:YES];
        [layer setDrawableSize:size];
                
        [contentView setLayer:layer];
        
        cocos2d::backend::DeviceMTL::setCAMetalLayer(layer);
        
        glfwSetMouseButtonCallback(window, keyCallback);
        
        std::chrono::steady_clock::time_point prevTime;
        std::chrono::steady_clock::time_point now;
        float dt = 0.f;
        while (!glfwWindowShouldClose(window))
        {
            prevTime = std::chrono::steady_clock::now();
            cocos2d::backend::DeviceMTL::updateDrawable();
            // Should invoke after `cocos2d::backend::DeviceMTL::updateDrawable()`.
            initTests();
            test->tick(dt);
            
            glfwPollEvents();
            
            now = std::chrono::steady_clock::now();
            dt = std::chrono::duration_cast<std::chrono::microseconds>(now - prevTime).count() / 1000000.f;
        }
        
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    return 0;
}
