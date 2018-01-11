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
#include "defines.h"

#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "cocos/scripting/js-bindings/auto/jsb_gfx_auto.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_global.h"
#include "cocos/scripting/js-bindings/manual/jsb_classtype.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_gfx_manual.hpp"

#include "Utils.h"

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (GLFW_RELEASE == action)
    {
        auto se = se::ScriptEngine::getInstance();
        se->clearException();
        se::AutoHandleScope hs;

        auto global = se->getGlobalObject();
        se::Value keyUpFuncVal;
        if (global->getProperty("onKeyUp", &keyUpFuncVal))
        {
            se::ValueArray args;
            args.push_back(se::Value(key));
            keyUpFuncVal.toObject()->call(args, nullptr);
        }
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
    
    auto se = se::ScriptEngine::getInstance();
    se->addRegisterCallback(jsb_register_global_variables);
    se->addRegisterCallback(register_all_gfx);
    se->addRegisterCallback(jsb_register_gfx_manual);

    se->enableDebugger("0.0.0.0", 5678);

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
    se::Value tickVal;
    se->runScript("src/main.js", &tickVal);

    std::chrono::steady_clock::time_point prevTime;
    std::chrono::steady_clock::time_point now;
    float dt = 0.f;
    while (!glfwWindowShouldClose(window))
    {
        prevTime = std::chrono::steady_clock::now();
        se::ValueArray args;
        args.push_back(se::Value(dt));
        tickVal.toObject()->call(args, nullptr);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        now = std::chrono::steady_clock::now();
        dt = std::chrono::duration_cast<std::chrono::microseconds>(now - prevTime).count() / 1000000.f;
    }

    se->addAfterCleanupHook([](){
        JSBClassType::destroy();
    });

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
