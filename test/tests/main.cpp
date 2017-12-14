//
//  main.cpp
//  Test
//
//  Created by minggo on 12/14/17.
//  Copyright © 2017 cocos. All rights reserved.
//

#include <glfw3.h>

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
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
