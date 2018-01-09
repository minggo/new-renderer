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

#include "DepthTexture.h"
#include "BunnyData.h"
#include "../Utils.h"
#include "platform/CCPlatformConfig.h"

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
            
                void main() {
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
                uniform float near;
                uniform float far;
            
                void main() {
                    float z = texture2D(texture, uv).x;
                    float viewZ = (near * far) / ((far - near) * z - far);
                    float depth = (viewZ + near) / (near - far);
                    
                    gl_FragColor.rgb = vec3(depth);
                    gl_FragColor.a = 1.0;
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
            
                void main ()
                {
                    vec4 pos = projection * view * model * vec4(a_position, 1);
                    
                    gl_Position = pos;
                }
            )";
            
            const char* frag = R"(
#ifdef GL_ES
                precision highp float;
#endif
                varying vec3 position;
            
                // uniform vec4 color;
            
                void main ()
                {
                    gl_FragColor = vec4(1, 1, 1, 1);
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
    
    BigTriangle* bg;
    Bunny* bunny;
}

DepthTexture::DepthTexture()
: _t(0.0f)
{
    _device = gfx::DeviceGraphics::getInstance();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (!(_device->supportGLExtension("OES_depth_texture")))
        GFX_LOGE("error: the device doesn't support OES_depth_texture");
#endif
    
    gfx::Texture2D::Options options;
    options.width = utils::WINDOW_WIDTH;
    options.height = utils::WINDOW_HEIGHT;
    options.format = gfx::Texture::Format::D16;
    options.wrapS = gfx::Texture::WrapMode::CLAMP;
    options.wrapT = gfx::Texture::WrapMode::CLAMP;
    _depthTexture = new gfx::Texture2D();
    _depthTexture->init(_device, options);
    
    _frameBuffer = new gfx::FrameBuffer();
    _frameBuffer->init(_device, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _frameBuffer->setDepthBuffer(_depthTexture);
    
    bunny = new Bunny();
    bg = new BigTriangle();
}

DepthTexture::~DepthTexture()
{
    delete bunny;
    delete bg;
    
    GFX_SAFE_RELEASE(_frameBuffer);
    GFX_SAFE_RELEASE(_depthTexture);
}

void DepthTexture::tick(float dt)
{
    _t += dt;
    
    _eye.set(30.f * std::cos(_t), 20.f, 30.f * std::sin(_t));
    _center.set(0, 2.5f, 0);
    _up.set(0, 1.f, 0);
    Mat4::createLookAt(_eye, _center, _up, &_view);
    
    Mat4::createPerspective(45.f, 1.0f * utils::WINDOW_WIDTH / utils::WINDOW_HEIGHT, 0.1f, 100.f, &_projection);
    
    _device->setFrameBuffer(_frameBuffer);
    _device->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    
    _device->clear(gfx::ClearFlag::DEPTH, nullptr, 1, 0);
    
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
    // _device->setUniformVec4("color", {0.5f, 0.5f, 0.5f, 1});
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
    // _device->setUniformVec4("color", {0.5f, 0.5f, 0.5f, 1});
    _device->setProgram(bunny->program);
    _device->draw(0, bunny->indexBuffer->getCount());
    
    // Draw bg.
    _device->setFrameBuffer(nullptr);
    _device->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    Color4F clearColor(0.1f, 0.1f, 0.1f, 1.f);
    _device->clear(gfx::ClearFlag::COLOR | gfx::ClearFlag::DEPTH, &clearColor, 1, 0);
    _device->setTexture("texture", _depthTexture, 0);
    _device->setUniformf("near", 0.1f);
    _device->setUniformf("far", 100.f);
    _device->setVertexBuffer(0, bg->vertexBuffer);
    _device->setProgram(bg->program);
    _device->draw(0, bg->vertexBuffer->getCount());
}
