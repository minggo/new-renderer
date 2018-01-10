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

#include <vector>
#include "Basic.h"
#include "../Utils.h"

using namespace cocos2d;
using namespace cocos2d::gfx;

Basic::Basic()
: _time(0.f)
{
    const char* vert = R"(
        #ifdef GL_ES
        precision highp float;
        #endif
        attribute vec2 a_position;
        void main()
        {
            gl_Position = vec4(a_position, 0, 1);
        }
    )";
    
    const char* frag = R"(
        #ifdef GL_ES
        precision highp float;
        #endif
        uniform vec4 color;
        void main()
        {
            gl_FragColor = color;
        }
    )";
    
    _device = DeviceGraphics::getInstance();
    _program = new Program();
    _program->init(_device, vert, frag);
    _program->link();
    
    VertexFormat vertexFmt({
        {ATTRIB_NAME_POSITION, AttribType::FLOAT32, 2}
    });
    
    float data[] = {-1, 0, 0, -1, 1, 1};
    _vertexBuffer = new VertexBuffer();
    _vertexBuffer->init(_device,
                        vertexFmt,
                        Usage::STATIC,
                        data,
                        sizeof(data),
                        3);
}

Basic::~Basic()
{
    GFX_SAFE_RELEASE(_vertexBuffer);
    GFX_SAFE_RELEASE(_program);
}

void Basic::tick(float dt)
{
    _time += dt;
    
    _device->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    Color4F color(0.1f, 0.1f, 0.1f, 1.f);
    _device->clear(ClearFlag::COLOR | ClearFlag::DEPTH, &color, 1, 0);
    _device->setVertexBuffer(0, _vertexBuffer);
    _device->setUniformf("color", 1.f, std::abs(std::sin(_time)), 0.f, 1.f);
    _device->setProgram(_program);
    _device->draw(0, _vertexBuffer->getCount());
}
