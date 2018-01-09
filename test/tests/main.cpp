/****************************************************************************
 Copyright (c) 2018 Chukong Technologies
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "glfw3/glfw3.h"
#include <chrono>
#include "TestBase.h"
#include "defines.h"
#include "gfx/Basic.h"
#include "gfx/Bunny.h"
#include "gfx/Blending.h"
#include "gfx/MultiTextures.h"
#include "gfx/Particle.h"
#include "gfx/Stencil.h"
#include "gfx/PostProcess.h"
#include "gfx/DepthTexture.h"
#include "gfx/SubImage.h"
#include "gfx/Texture2D.h"
#include "gfx/GuiProjection.h"
#include "Utils.h"

namespace
{
    int nextIndex = 0;
    using createFunc = TestBaseI* (*)();
    std::vector<createFunc> tests;
    TestBaseI* test = nullptr;
    
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (GLFW_RELEASE == action)
        {
            if (GLFW_KEY_RIGHT == key)
                nextIndex = (++nextIndex) % tests.size();
            else if (GLFW_KEY_LEFT == key)
                nextIndex = int((--nextIndex + tests.size()) % tests.size());

            delete test;
            test = tests[nextIndex]();
        }
    }
    
    void initTests()
    {
        tests = {
            Basic::create,
            Bunny::create,
            Blending::create,
            MultiTextures::create,
            Particle::create,
            Stencil::create,
            PostProcess::create,
            DepthTexture::create,
            SubImage::create,
            Texture2DTest::create,
            GuiProjection::create,
        };
        
        test = tests[0]();
    }
}

int main(int argc, char** argv)
{
    if (!glfwInit())
        return -1;
    
    
    utils::WINDOW_WIDTH = 960;
    utils::WINDOW_HEIGHT = 640;
    auto window = glfwCreateWindow(utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT, "New Renderer Test", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwSetKeyCallback(window, keyCallback);
    glfwMakeContextCurrent(window);
    
    initTests();

    std::chrono::steady_clock::time_point prevTime;
    std::chrono::steady_clock::time_point now;
    float dt = 0.f;
    while (!glfwWindowShouldClose(window))
    {
        prevTime = std::chrono::steady_clock::now();
        test->tick(dt);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        now = std::chrono::steady_clock::now();
        dt = std::chrono::duration_cast<std::chrono::microseconds>(now - prevTime).count() / 1000000.f;
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    delete test;
    
    return 0;
}
