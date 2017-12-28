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

#include "Blending.h"
#include "gfx/CCGFX.h"
#include "math/Mat4.h"
#include "../defines.h"

using namespace cocos2d;

namespace
{
    struct BigTriangle
    {
        BigTriangle()
        {
            const char* vert = R"(
            #ifdef GL_ES
                precision highp float;
            #endif
                attribute vec2 a_position;
                varying vec2 uv;
                void main()
                {
                    uv = (a_position + 1.0) * 0.5;
                    gl_Position = vec4(a_position, 0, 1);
                }
            )";
            
            const char* frag = R"(
            #ifdef GL_ES
                precision highp float;
            #endif
                varying vec2 uv;
                uniform sampler2D texture;
                uniform float time;
            
                void main()
                {
                    vec2 offset = vec2(time * -0.01);
                    gl_FragColor = texture2D(texture, 20.0 * (uv + offset));
                }
            )";
                
            auto device = gfx::DeviceGraphics::getInstance();
            program = new gfx::Program();
            program->init(device, vert, frag);
            program->link();
                    
            gfx::VertexFormat vertexFormat({
                {gfx::ATTRIB_NAME_POSITION, gfx::AttribType::FLOAT32, 2}
            });
            float vertices[] = {
                -1, 4,
                -1, -1,
                4, -1
            };
            vertexBuffer = new gfx::VertexBuffer();
            vertexBuffer->init(device, vertexFormat, gfx::Usage::STATIC, vertices, sizeof(vertices), 3);
        }
        
        ~BigTriangle()
        {
            GFX_SAFE_RELEASE(program);
            GFX_SAFE_RELEASE(vertexBuffer);
        }
        
        gfx::Program* program;
        gfx::VertexBuffer* vertexBuffer;
    };
        
        BigTriangle *bigTriangle = nullptr;
        Mat4 projection;
        gfx::DeviceGraphics *device = nullptr;
}

//
// Blending implementation.
//
    
Blending::Blending()
: _dt(0.f)
{
    bigTriangle = new BigTriangle();
    device = gfx::DeviceGraphics::getInstance();
}

Blending::~Blending()
{
    delete bigTriangle;
    bigTriangle = nullptr;
}

void Blending::tick(float dt)
{
    _dt += dt;
    
    Mat4::createOrthographic(WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, 1000.f, &projection);
    device->setViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    Color4F clearColor(0.1f, 0.1f, 0.1f, 1.f);
    device->clear(gfx::ClearFlag::COLOR | gfx::ClearFlag::DEPTH,
                  &clearColor,
                  1,
                  0);
    
    device->setUniformf("time", _dt);
    device->setUniformMat4("projection", projection.m);
    
    device->setVertexBuffer(0, bigTriangle->vertexBuffer);
    device->setProgram(bigTriangle->program);
    device->draw(0, bigTriangle->vertexBuffer->getCount());
}

