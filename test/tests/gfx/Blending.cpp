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
#include "math/Mat4.h"
#include "../Utils.h"

using namespace cocos2d;

namespace
{
    struct Quad
    {
        Quad()
        {
            const char* vert = R"(
            #ifdef GL_ES
                precision highp float;
            #endif
                attribute vec2 a_position;
                attribute vec2 a_uv;
                varying vec2 uv;
                uniform mat4 model, projection;
            
                void main()
                {
                    uv = a_uv;
                    gl_Position = projection * model * vec4(a_position, 0, 1);
                }
            )";
            
            const char* frag = R"(
            #ifdef GL_ES
                precision highp float;
            #endif
                varying vec2 uv;
                uniform sampler2D texture;
            
                void main()
                {
                    gl_FragColor = texture2D(texture, uv);
                }
            )";
            
            program = new gfx::Program();
            auto device = gfx::DeviceGraphics::getInstance();
            program->init(device, vert, frag);
            program->link();
            
            gfx::VertexFormat vertexFormat({
                {gfx::ATTRIB_NAME_POSITION, gfx::AttribType::FLOAT32, 2},
                {gfx::ATTRIB_NAME_UV, gfx::AttribType::FLOAT32, 2}
            });
            float vertices[] = {
                -0.5f, -0.5f,   0,   0,
                -0.5f,  0.5f,   0, 1.f,
                 0.5f,  0.5f, 1.f, 1.f,
                 0.5f, -0.5f, 1.f,   0
            };
            vertexBuffer = new gfx::VertexBuffer;
            vertexBuffer->init(device,
                               vertexFormat,
                               gfx::Usage::STATIC,
                               vertices,
                               sizeof(vertices),
                               4);
            
            uint8_t indices[] = {0, 3, 1, 1, 3, 2};
            indexBuffer = new gfx::IndexBuffer();
            indexBuffer->init(device,
                              gfx::IndexFormat::UINT8,
                              gfx::Usage::STATIC,
                              indices,
                              sizeof(indices),
                              6);
        }
        
        ~Quad()
        {
            GFX_SAFE_RELEASE(vertexBuffer);
            GFX_SAFE_RELEASE(indexBuffer);
            GFX_SAFE_RELEASE(program);
        }
        
        gfx::VertexBuffer* vertexBuffer;
        gfx::IndexBuffer* indexBuffer;
        gfx::Program* program;
    };
    
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
    
    // rotation is not used
    Mat4 createModel(const cocos2d::Vec3& t, const cocos2d::Vec3& s)
    {
        Mat4 model(Mat4::IDENTITY);
        
        model.translate(t);
        model.scale(s);
        
        return model;
    }
    
    BigTriangle *bigTriangle = nullptr;
    Quad *quad = nullptr;
}

//
// Blending implementation.
//
    
Blending::Blending()
: _dt(0.f)
{
    if (bigTriangle)
        delete bigTriangle;
    bigTriangle = new BigTriangle();
    
    if (quad)
        delete quad;
    quad = new Quad();
    
    _device = gfx::DeviceGraphics::getInstance();
    
    gfx::Texture::Options options;
    options.width = 128;
    options.height = 128;
    options.wrapS = gfx::Texture::WrapMode::REPEAT;
    options.wrapT = gfx::Texture::WrapMode::REPEAT;
    options.format = gfx::Texture::Format::RGB8;
    options.hasMipmap = true;
    options.images.push_back(utils::loadData("assets/background.png"));
    _backgroud = new gfx::Texture2D();
    _backgroud->init(_device, options);
    
    gfx::Texture2D::Options options2;
    options2.width = 128;
    options2.height = 128;
    options2.format = gfx::Texture::Format::RGBA8;
    options2.images.push_back(utils::loadData("assets/sprite0.png"));
    options2.flipY = false;
    _sprite0 = new gfx::Texture2D();
    _sprite0->init(_device, options2);
}

Blending::~Blending()
{
    delete bigTriangle;
    bigTriangle = nullptr;
    
    delete quad;
    quad = nullptr;
    
    GFX_SAFE_RELEASE(_backgroud);
    GFX_SAFE_RELEASE(_sprite0);
}

void Blending::tick(float dt)
{
    _dt += dt;
    
    Mat4::createOrthographicOffCenter(0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT, 0, 0, 1000.f, &_projection);
    _device->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    
    Color4F clearColor(0.1f, 0.1f, 0.1f, 1.f);
    _device->clear(gfx::ClearFlag::COLOR | gfx::ClearFlag::DEPTH,
                  &clearColor,
                  1,
                  0);
    
    _device->setUniformf("time", _dt);
    _device->setUniformMat4("projection", _projection.m);

    _device->setTexture("texture", _backgroud, 0);
    _device->setVertexBuffer(0, bigTriangle->vertexBuffer);
    _device->setProgram(bigTriangle->program);
    _device->draw(0, bigTriangle->vertexBuffer->getCount());

    // sprites
    
    float size = std::min(utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT) * 0.15f;
    float hsize = size * 0.5f;
    
    // no blending
    float offsetX = 5.f + hsize;
    float offsetY = 5.f + hsize;
    _device->enableBlend();
    _device->setBlendFuncSeparate(gfx::BlendFactor::ONE,
                                 gfx::BlendFactor::ZERO,
                                 gfx::BlendFactor::ONE,
                                 gfx::BlendFactor::ONE);
    _device->setBlendEquationSeparate(gfx::BlendOp::ADD, gfx::BlendOp::ADD);
    _device->setCullMode(gfx::CullMode::NONE);
    _model = std::move(createModel(cocos2d::Vec3(offsetX, offsetY, 0), cocos2d::Vec3(size, size, 0)));
    _device->setUniformMat4("model", _model);
    _device->setTexture("texture", _sprite0, 0);
    _device->setVertexBuffer(0, quad->vertexBuffer);
    _device->setIndexBuffer(quad->indexBuffer);
    _device->setProgram(quad->program);
    _device->draw(0, quad->indexBuffer->getCount());
    
    // normal
    offsetY = offsetY + 5.f + size;
    _device->enableBlend();
    _device->setBlendFuncSeparate(gfx::BlendFactor::SRC_ALPHA,
                                  gfx::BlendFactor::ONE_MINUS_SRC_ALPHA,
                                  gfx::BlendFactor::ONE,
                                  gfx::BlendFactor::ONE);
    _device->setBlendEquationSeparate(gfx::BlendOp::ADD, gfx::BlendOp::ADD);
    
    _device->setCullMode(gfx::CullMode::NONE);
    _model = std::move(createModel(cocos2d::Vec3(offsetX, offsetY, 0), cocos2d::Vec3(size, size, 0)));
    _device->setUniformMat4("model", _model);
    _device->setTexture("texture", _sprite0, 0);
    _device->setVertexBuffer(0, quad->vertexBuffer);
    _device->setIndexBuffer(quad->indexBuffer);
    _device->setProgram(quad->program);
    _device->draw(0, quad->indexBuffer->getCount());
    
    // additive
    offsetY = offsetY + 5.f + size;
    _device->enableBlend();
    _device->setBlendFuncSeparate(gfx::BlendFactor::SRC_ALPHA,
                                  gfx::BlendFactor::ONE,
                                  gfx::BlendFactor::ONE,
                                  gfx::BlendFactor::ONE);
    _device->setBlendEquationSeparate(gfx::BlendOp::ADD, gfx::BlendOp::ADD);
    
    _device->setCullMode(gfx::CullMode::NONE);
    _model = std::move(createModel(cocos2d::Vec3(offsetX, offsetY, 0), cocos2d::Vec3(size, size, 0)));
    _device->setUniformMat4("model", _model);
    _device->setTexture("texture", _sprite0, 0);
    _device->setVertexBuffer(0, quad->vertexBuffer);
    _device->setIndexBuffer(quad->indexBuffer);
    _device->setProgram(quad->program);
    _device->draw(0, quad->indexBuffer->getCount());
    
    // substract
    offsetY = offsetY + 5.f + size;
    _device->enableBlend();
    _device->setBlendFuncSeparate(gfx::BlendFactor::ZERO,
                                  gfx::BlendFactor::ONE_MINUS_SRC_COLOR,
                                  gfx::BlendFactor::ONE,
                                  gfx::BlendFactor::ONE);
    _device->setBlendEquationSeparate(gfx::BlendOp::ADD, gfx::BlendOp::ADD);
    
    _device->setCullMode(gfx::CullMode::NONE);
    _model = std::move(createModel(cocos2d::Vec3(offsetX, offsetY, 0), cocos2d::Vec3(size, size, 0)));
    _device->setUniformMat4("model", _model);
    _device->setTexture("texture", _sprite0, 0);
    _device->setVertexBuffer(0, quad->vertexBuffer);
    _device->setIndexBuffer(quad->indexBuffer);
    _device->setProgram(quad->program);
    _device->draw(0, quad->indexBuffer->getCount());
    
    // multiply
    offsetY = offsetY + 5.f + size;
    _device->enableBlend();
    _device->setBlendFuncSeparate(gfx::BlendFactor::ZERO,
                                  gfx::BlendFactor::SRC_COLOR,
                                  gfx::BlendFactor::ONE,
                                  gfx::BlendFactor::ONE);
    _device->setBlendEquationSeparate(gfx::BlendOp::ADD, gfx::BlendOp::ADD);
    
    _device->setCullMode(gfx::CullMode::NONE);
    _model = std::move(createModel(cocos2d::Vec3(offsetX, offsetY, 0), cocos2d::Vec3(size, size, 0)));
    _device->setUniformMat4("model", _model);
    _device->setTexture("texture", _sprite0, 0);
    _device->setVertexBuffer(0, quad->vertexBuffer);
    _device->setIndexBuffer(quad->indexBuffer);
    _device->setProgram(quad->program);
    _device->draw(0, quad->indexBuffer->getCount());
}

