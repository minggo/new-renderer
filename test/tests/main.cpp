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
#include "gfx/Basic.h"

namespace
{
    std::chrono::steady_clock::time_point prevTime;
    std::chrono::steady_clock::time_point now;
    float dt = 0.f;
    
    TestBaseI* test = nullptr;
    void setup()
    {
        test = new Basic();
    }
}

int main(int argc, char** argv)
{
    if (!glfwInit())
        return -1;
    
    auto window = glfwCreateWindow(960, 640, "New Renderer Test", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    setup();
    
    while (!glfwWindowShouldClose(window))
    {
        //glClear(GL_COLOR_BUFFER_BIT);
        
        prevTime = std::chrono::steady_clock::now();
        test->tick(dt);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        now = std::chrono::steady_clock::now();
        dt = std::chrono::duration_cast<std::chrono::seconds>(now - prevTime).count();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    delete test;
    
    return 0;
}
