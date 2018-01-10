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

#define _USE_MATH_DEFINES
#include <math.h>

#include "PostProcess.h"
#include "BunnyData.h"
#include "../Utils.h"

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
            
                float angle = 1.57;
                float scale = 2.0;
                vec2 center = vec2(0.5, 0.5);
                vec2 size = vec2(256, 256);
            
                float pattern()
                {
                    float s = sin(angle);
                    float c = cos(angle);
                    vec2 tex = uv * size - center;
                    vec2 point = vec2(c * tex.x - s * tex.y, s * tex.x + c * tex.y) * scale;
                    
                    return (sin(point.x) * sin(point.y)) * 4.0;
                }
            
                void main()
                {
                    vec4 color = texture2D(texture, uv);
                    float p = pattern();
                    
                    float average = (color.r + color.g + color.b) / 3.0;
                    gl_FragColor = vec4(vec3(average * 10.0 - 5.0 + p), color.a);
                }
            )";
            
            auto device = gfx::DeviceGraphics::getInstance();
            program = new gfx::Program();
            program->init(device, vert, frag);
            program->link();
            
            gfx::VertexFormat vertexFormat({
                {gfx::ATTRIB_NAME_POSITION, gfx::AttribType::FLOAT32, 2}
            });
            float vertices[] = {-1, 4, -1, -1, 4, -1};
            vertexBuffer = new gfx::VertexBuffer();
            vertexBuffer->init(device,
                               vertexFormat,
                               gfx::Usage::STATIC,
                               vertices,
                               sizeof(vertices),
                               3);
        }
        
        ~BigTriangle()
        {
            GFX_SAFE_RELEASE(program);
            GFX_SAFE_RELEASE(vertexBuffer);
        }
        
        gfx::Program* program;
        gfx::VertexBuffer* vertexBuffer;
    };
    
    struct Bunny
    {
        Bunny()
        {
            const char* vert = R"(
#ifdef GL_ES
                precision highp float;
#endif
                attribute vec3 a_position;
                uniform mat4 model, view, projection;
            
                varying vec3 position;
            
                void main ()
                {
                    vec4 pos = projection * view * model * vec4(a_position, 1);
                    position = a_position;
                    
                    gl_Position = pos;
                }
            )";
            
            const char* frag = R"(
#ifdef GL_ES
                precision highp float;
#endif
                varying vec3 position;
            
                uniform vec4 color;
            
                void main ()
                {
                    gl_FragColor = color * vec4(position, 1);
                }
            )";
            
            auto device = gfx::DeviceGraphics::getInstance();
            
            program = new gfx::Program();
            program->init(device, vert, frag);
            program->link();
            
            gfx::VertexFormat vertexFormat({
                {gfx::ATTRIB_NAME_POSITION, gfx::AttribType::FLOAT32, 3}
            });
            vertexBuffer = new gfx::VertexBuffer();
            vertexBuffer->init(device,
                               vertexFormat,
                               gfx::Usage::STATIC,
                               &bunny_positions[0][0],
                               sizeof(bunny_positions),
                               sizeof(bunny_positions) / sizeof(bunny_positions[0]));
            
            indexBuffer = new gfx::IndexBuffer();
            indexBuffer->init(device,
                              gfx::IndexFormat::UINT16,
                              gfx::Usage::STATIC,
                              &bunny_cells[0],
                              sizeof(bunny_cells),
                              sizeof(bunny_cells) / bunny_cells[0]);
        }
        
        ~Bunny()
        {
            GFX_SAFE_RELEASE(program);
            GFX_SAFE_RELEASE(vertexBuffer);
            GFX_SAFE_RELEASE(indexBuffer);
        }
        
        gfx::Program* program;
        gfx::VertexBuffer* vertexBuffer;
        gfx::IndexBuffer* indexBuffer;
    };
    
    Bunny* bunny = nullptr;
    BigTriangle *bg = nullptr;
}

PostProcess::PostProcess()
: _t(0.0f)
{
    _device = gfx::DeviceGraphics::getInstance();
    
    gfx::Texture2D::Options options;
    options.width = utils::WINDOW_WIDTH;
    options.height = utils::WINDOW_HEIGHT;
    options.format = gfx::Texture::Format::RGBA8;
    options.wrapS = gfx::Texture::WrapMode::CLAMP;
    options.wrapT = gfx::Texture::WrapMode::CLAMP;
    _colorTexture = new gfx::Texture2D();
    _colorTexture->init(_device, options);
    
    _frameBuffer = new gfx::FrameBuffer();
    _frameBuffer->init(_device, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);

    _frameBuffer->setColorBuffer(_colorTexture, 0);
    
    auto depthBuffer = new gfx::RenderBuffer();
    depthBuffer->init(_device, gfx::RenderBuffer::Format::D16, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _frameBuffer->setDepthBuffer(depthBuffer);
    depthBuffer->release();
    
    bunny = new Bunny();
    bg = new BigTriangle();
}

PostProcess::~PostProcess()
{
    delete bunny;
    delete bg;

    GFX_SAFE_RELEASE(_frameBuffer);
    GFX_SAFE_RELEASE(_colorTexture);
}

void PostProcess::tick(float dt)
{
    _t += dt;
    
    _eye.set(30.f * std::cos(_t), 20.f, 30.f * std::sin(_t));
    _center.set(0, 2.5f, 0);
    _up.set(0, 1.f, 0);
    Mat4::createLookAt(_eye, _center, _up, &_view);
    
    Mat4::createPerspective(45.f, 1.0f * (utils::WINDOW_WIDTH / utils::WINDOW_HEIGHT), 0.01f, 1000.f, &_projection);
    
    _device->setFrameBuffer(_frameBuffer);
    _device->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    
    Color4F clearColor(0.1f, 0.1f, 0.1f, 1.f);
    _device->clear(gfx::ClearFlag::COLOR | gfx::ClearFlag::DEPTH, &clearColor, 1, 0);
    
    // Draw bunny one.
    _model = Mat4::IDENTITY;
    _model.translate(5, 0, 0);
    _device->enableDepthTest();
    _device->enableDepthWrite();
    _device->setVertexBuffer(0, bunny->vertexBuffer);
    _device->setIndexBuffer(bunny->indexBuffer);
    _device->setUniformMat4("model", _model);
    _device->setUniformMat4("view", _view);
    _device->setUniformMat4("projection", _projection);
    _device->setUniformVec4("color", {0.1f, 0.1f, 0.1f, 1});
    _device->setProgram(bunny->program);
    _device->draw(0, bunny->indexBuffer->getCount());
    
    // Draw bunny two.
    _model = Mat4::IDENTITY;
    _model.translate(-5, 0, 0);
    _device->enableDepthTest();
    _device->enableDepthWrite();
    _device->setVertexBuffer(0, bunny->vertexBuffer);
    _device->setIndexBuffer(bunny->indexBuffer);
    _device->setUniformMat4("model", _model);
    _device->setUniformMat4("view", _view);
    _device->setUniformMat4("projection", _projection);
    _device->setUniformVec4("color", {0.3f, 0.3f, 0.3f, 1});
    _device->setProgram(bunny->program);
    _device->draw(0, bunny->indexBuffer->getCount());
    
    // Draw bg.
    _device->setFrameBuffer(nullptr);
    _device->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _device->clear(gfx::ClearFlag::COLOR | gfx::ClearFlag::DEPTH, &clearColor, 1, 0);
    _device->setTexture("texture", _colorTexture, 0);
    _device->setVertexBuffer(0, bg->vertexBuffer);
    _device->setProgram(bg->program);
    _device->draw(0, bg->vertexBuffer->getCount());
}
