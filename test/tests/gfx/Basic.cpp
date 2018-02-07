/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

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

std::string test_unrollLoops(const std::string& text);

using namespace cocos2d;
using namespace cocos2d::renderer;

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


    static const char* testCode = R"(#if 3 > 0
#pragma for id in range(0, 3)
    uniform vec3 dir_light{id}_direction;
    uniform vec3 dir_light{id}_color;
#pragma endFor
#endif

#if 4 > 0
#pragma for id in range(0, 4)
    uniform vec3 point_light{id}_position;
    uniform vec3 point_light{id}_color;
    uniform float point_light{id}_range;
#pragma endFor
#endif

#if 5 > 0
#pragma for id in range(0, 5)
    uniform vec3 spot_light{id}_position;
    uniform vec3 spot_light{id}_direction;
    uniform vec3 spot_light{id}_color;
    uniform vec2 spot_light{id}_spot;
    uniform float spot_light{id}_range;
#pragma endFor
#endif)";

    const std::string correctResult = R"(#if 3 > 0

    uniform vec3 dir_light0_direction;
    uniform vec3 dir_light0_color;

    uniform vec3 dir_light1_direction;
    uniform vec3 dir_light1_color;

    uniform vec3 dir_light2_direction;
    uniform vec3 dir_light2_color;

#endif

#if 4 > 0

    uniform vec3 point_light0_position;
    uniform vec3 point_light0_color;
    uniform float point_light0_range;

    uniform vec3 point_light1_position;
    uniform vec3 point_light1_color;
    uniform float point_light1_range;

    uniform vec3 point_light2_position;
    uniform vec3 point_light2_color;
    uniform float point_light2_range;

    uniform vec3 point_light3_position;
    uniform vec3 point_light3_color;
    uniform float point_light3_range;

#endif

#if 5 > 0

    uniform vec3 spot_light0_position;
    uniform vec3 spot_light0_direction;
    uniform vec3 spot_light0_color;
    uniform vec2 spot_light0_spot;
    uniform float spot_light0_range;

    uniform vec3 spot_light1_position;
    uniform vec3 spot_light1_direction;
    uniform vec3 spot_light1_color;
    uniform vec2 spot_light1_spot;
    uniform float spot_light1_range;

    uniform vec3 spot_light2_position;
    uniform vec3 spot_light2_direction;
    uniform vec3 spot_light2_color;
    uniform vec2 spot_light2_spot;
    uniform float spot_light2_range;

    uniform vec3 spot_light3_position;
    uniform vec3 spot_light3_direction;
    uniform vec3 spot_light3_color;
    uniform vec2 spot_light3_spot;
    uniform float spot_light3_range;

    uniform vec3 spot_light4_position;
    uniform vec3 spot_light4_direction;
    uniform vec3 spot_light4_color;
    uniform vec2 spot_light4_spot;
    uniform float spot_light4_range;

#endif)";

    GFX_LOGD("%s", correctResult.c_str());

    std::string out = test_unrollLoops(testCode);
    GFX_LOGD("===>\n%s, correct: %d, out: %d", out.c_str(), (int)correctResult.length(), (int)out.length());
    assert(out == correctResult);
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
