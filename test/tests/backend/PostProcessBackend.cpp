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

#define _USE_MATH_DEFINES
#include <math.h>

#include "PostProcessBackend.h"
#include "BunnyData.h"
#include "../Utils.h"
#include "backend/Program.h"

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
#ifndef GL_ES
                    uv = vec2(uv.x, 1.0 - uv.y);
#endif
                    gl_Position = vec4(a_position, 0, 1);
                }
            )";
            
            const char* frag = R"(
#ifdef GL_ES
                precision highp float;
#endif
                varying vec2 uv;
                uniform sampler2D texture;
            
                float pattern(vec2 uv)
                {
                    float angle = 1.57;
                    float scale = 2.0;
                    vec2 center = vec2(0.5, 0.5);
                    vec2 size = vec2(256.0, 256.0);
                    float s = sin(angle);
                    float c = cos(angle);
                    vec2 tex = uv * size - center;
                    vec2 point = vec2(c * tex.x - s * tex.y, s * tex.x + c * tex.y) * scale;
                    
                    return (sin(point.x) * sin(point.y)) * 4.0;
                }
            
                void main()
                {
                    vec4 color = texture2D(texture, uv);
                    float p = pattern(uv);
                    
                    float average = (color.r + color.g + color.b) / 3.0;
                    gl_FragColor = vec4(vec3(average * 10.0 - 5.0 + p), color.a);
                }
            )";
            
            auto device = backend::Device::getInstance();

            backend::RenderPipelineDescriptor renderPipelineDescriptor;
            renderPipelineDescriptor.colorAttachmentsFormat[0] = backend::TextureFormat::SYSTEM_DEFAULT;
            renderPipelineDescriptor.depthAttachmentFormat = backend::TextureFormat::D24S8;
            
            auto vs = device->createShaderModule(backend::ShaderStage::VERTEX, vert);
            auto fs = device->createShaderModule(backend::ShaderStage::FRAGMENT, frag);
            renderPipelineDescriptor.program = device->createProgram(vs, fs);

            backend::VertexLayout vertexLayout;
            vertexLayout.setAtrribute("a_position", 0, backend::VertexFormat::FLOAT_R32G32, 0);
            vertexLayout.setLayout(2 * sizeof(float), backend::VertexStepMode::VERTEX);
            renderPipelineDescriptor.vertexLayouts.push_back(vertexLayout);
            _renderPipeline = device->newRenderPipeline(renderPipelineDescriptor);
            
            float vertices[] = {-1, 4, -1, -1, 4, -1};
            _vertexBuffer = device->newBuffer(sizeof(vertices),
                                              backend::BufferType::VERTEX,
                                              backend::BufferUsage::READ);
            _vertexBuffer->updateData(vertices, sizeof(vertices));
        }
        
        ~BigTriangle()
        {
            CC_SAFE_RELEASE(_vertexBuffer);
            CC_SAFE_RELEASE(_renderPipeline);
        }
        
        backend::Buffer* _vertexBuffer = nullptr;
        backend::RenderPipeline* _renderPipeline = nullptr;
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
            
            auto device = backend::Device::getInstance();
            
            backend::RenderPipelineDescriptor renderPipelineDescriptor;
            renderPipelineDescriptor.colorAttachmentsFormat[0] = backend::TextureFormat::R8G8B8A8;
            renderPipelineDescriptor.depthAttachmentFormat = backend::TextureFormat::D24S8;
            
            auto vs = device->createShaderModule(backend::ShaderStage::VERTEX, vert);
            auto fs = device->createShaderModule(backend::ShaderStage::FRAGMENT, frag);
            
            renderPipelineDescriptor.program = device->createProgram(vs, fs);
            _modelLocation = renderPipelineDescriptor.program->getUniformLocation("model");
            _viewLocation = renderPipelineDescriptor.program->getUniformLocation("view");
            _projectionLocation = renderPipelineDescriptor.program->getUniformLocation("projection");
            _colorLocation = renderPipelineDescriptor.program->getUniformLocation("color");
            
            backend::VertexLayout vertexLayout;
            vertexLayout.setAtrribute("a_position", 0, backend::VertexFormat::FLOAT_R32G32B32, 0);
            vertexLayout.setLayout(3 * sizeof(float), backend::VertexStepMode::VERTEX);
            renderPipelineDescriptor.vertexLayouts.push_back(vertexLayout);
            
            backend::DepthStencilDescriptor depthStencilDescriptor;
            depthStencilDescriptor.depthTestEnabled = true;
            depthStencilDescriptor.depthWriteEnabled = true;
            depthStencilDescriptor.depthCompareFunction = backend::CompareFunction::LESS;
            auto depthStencilState = device->createDepthStencilState(depthStencilDescriptor);
            renderPipelineDescriptor.depthStencilState = depthStencilState;
            _renderPipeline = device->newRenderPipeline(renderPipelineDescriptor);
            
            _vertexBuffer = device->newBuffer(sizeof(bunny_positions),
                                              backend::BufferType::VERTEX,
                                              backend::BufferUsage::READ);
            _vertexBuffer->updateData((void*)&bunny_positions[0][0], sizeof(bunny_positions));
            
            _indexBuffer = device->newBuffer(sizeof(bunny_cells),
                                             backend::BufferType::INDEX,
                                             backend::BufferUsage::READ);
            _indexBuffer->updateData((void*)&bunny_cells[0], sizeof(bunny_cells));
        }
        
        ~Bunny()
        {
            CC_SAFE_RELEASE(_vertexBuffer);
            CC_SAFE_RELEASE(_indexBuffer);
            CC_SAFE_RELEASE(_renderPipeline);
        }
        
        inline int getModelLocaiton() const { return _modelLocation; }
        inline int getViewLocaiton() const { return _viewLocation; }
        inline int getProjectionLocaiton() const { return _projectionLocation; }
        inline int getColorLocaiton() const { return _colorLocation; }
        
        backend::Buffer* _vertexBuffer = nullptr;
        backend::Buffer* _indexBuffer = nullptr;
        backend::RenderPipeline* _renderPipeline = nullptr;
        
        int _modelLocation = -1;
        int _viewLocation = -1;
        int _projectionLocation = -1;
        int _colorLocation = -1;
    };
    
    Bunny* bunny = nullptr;
    BigTriangle *bg = nullptr;
}

PostProcessBackend::PostProcessBackend()
: _t(0.0f)
{
    auto device = backend::Device::getInstance();
    
    backend::TextureDescriptor textureDescriptor;
    textureDescriptor.width = utils::WINDOW_WIDTH;
    textureDescriptor.height = utils::WINDOW_HEIGHT;
    textureDescriptor.textureFormat = backend::TextureFormat::R8G8B8A8;
    textureDescriptor.textureUsage = backend::TextureUsage::RENDER_TARGET;
    textureDescriptor.samplerDescriptor.sAddressMode = backend::SamplerAddressMode::CLAMP_TO_EDGE;
    textureDescriptor.samplerDescriptor.tAddressMode = backend::SamplerAddressMode::CLAMP_TO_EDGE;
    _colorTexture = device->newTexture(textureDescriptor);

    backend::TextureDescriptor textureDescriptor2;
    textureDescriptor2.width = utils::WINDOW_WIDTH;
    textureDescriptor2.height = utils::WINDOW_HEIGHT;
    textureDescriptor2.textureUsage = backend::TextureUsage::RENDER_TARGET;
    textureDescriptor2.textureFormat = backend::TextureFormat::D24S8;
    _depthTexture = device->newTexture(textureDescriptor2);
    
    _renderPassDescriptorBunny1.clearDepthValue = 1;
    _renderPassDescriptorBunny1.needClearDepth = true;
    _renderPassDescriptorBunny1.depthAttachmentTexture = _depthTexture;
    _renderPassDescriptorBunny1.needDepthAttachment = true;
    _renderPassDescriptorBunny1.clearColorValue = {0.1f, 0.1f, 0.1f, 1.f};
    _renderPassDescriptorBunny1.needClearColor = true;
    _renderPassDescriptorBunny1.needColorAttachment = true;
    _renderPassDescriptorBunny1.colorAttachmentsTexture[0] = _colorTexture;
    
    _renderPassDescriptorBunny2.needColorAttachment = true;
    _renderPassDescriptorBunny2.colorAttachmentsTexture[0] = _colorTexture;
    _renderPassDescriptorBunny2.depthAttachmentTexture = _depthTexture;
    _renderPassDescriptorBunny2.needDepthAttachment = true;
    
    _renderPassDescriptorBg.clearColorValue = {0.1f, 0.1f, 0.1f, 1.f};
    _renderPassDescriptorBg.needClearColor = true;
    _renderPassDescriptorBg.needColorAttachment = true;
    _renderPassDescriptorBg.clearDepthValue = 1;
    _renderPassDescriptorBg.needClearDepth = true;
    _renderPassDescriptorBg.needDepthAttachment = true;
    
    _commandBuffer = device->newCommandBuffer();
    
    bunny = new Bunny();
    bg = new BigTriangle();
}

PostProcessBackend::~PostProcessBackend()
{
    delete bunny;
    delete bg;

    CC_SAFE_RELEASE(_commandBuffer);
    CC_SAFE_RELEASE(_colorTexture);
    CC_SAFE_RELEASE(_depthTexture);
}

void PostProcessBackend::tick(float dt)
{
    _t += dt;
    
    _eye.set(30.f * std::cos(_t), 20.f, 30.f * std::sin(_t));
    _center.set(0, 2.5f, 0);
    _up.set(0, 1.f, 0);
    Mat4::createLookAt(_eye, _center, _up, &_view);
    
    Mat4::createPerspective(45.f, 1.0f * (utils::WINDOW_WIDTH / utils::WINDOW_HEIGHT), 0.01f, 1000.f, &_projection);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    _projection = utils::getAdjustMatrix() * _projection;
#endif
    
    _commandBuffer->beginFrame();
    
    _commandBuffer->beginRenderPass(_renderPassDescriptorBunny1);
    
    // Draw bunny one.
    _model = Mat4::IDENTITY;
    _model.translate(5, 0, 0);
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _commandBuffer->setRenderPipeline(bunny->_renderPipeline);
    _commandBuffer->setVertexBuffer(0, bunny->_vertexBuffer);
    _commandBuffer->setIndexBuffer(bunny->_indexBuffer);
    
    _bindGroup.setVertexUniform(bunny->getModelLocaiton(), "model", _model.m, sizeof(_model.m));
    _bindGroup.setVertexUniform(bunny->getViewLocaiton(), "view", _view.m, sizeof(_view.m));
    _bindGroup.setVertexUniform(bunny->getProjectionLocaiton(), "projection", _projection.m, sizeof(_projection.m));
    float color[4] = {0.1f, 0.1f, 0.1f, 1};
    _bindGroup.setFragmentUniform(bunny->getColorLocaiton(), "color", color, sizeof(color));
    _commandBuffer->setBindGroup(&_bindGroup);
    
    _commandBuffer->drawElements(backend::PrimitiveType::TRIANGLE,
                                 backend::IndexFormat::U_SHORT,
                                 sizeof(bunny_cells) / sizeof(bunny_cells[0]));
    _commandBuffer->endRenderPass();
    
    // Draw bunny two.
    _commandBuffer->beginRenderPass(_renderPassDescriptorBunny2);
    _model = Mat4::IDENTITY;
    _model.translate(-5, 0, 0);
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _commandBuffer->setRenderPipeline(bunny->_renderPipeline);
    _commandBuffer->setVertexBuffer(0, bunny->_vertexBuffer);
    _commandBuffer->setIndexBuffer(bunny->_indexBuffer);
    
    _bindGroup.setVertexUniform(bunny->getModelLocaiton(), "model", _model.m, sizeof(_model.m));
    _bindGroup.setVertexUniform(bunny->getViewLocaiton(), "view", _view.m, sizeof(_view.m));
    _bindGroup.setVertexUniform(bunny->getProjectionLocaiton(), "projection", _projection.m, sizeof(_projection.m));
    float color2[4] = {0.3f, 0.3f, 0.3f, 1};
    _bindGroup.setFragmentUniform(bunny->getColorLocaiton(), "color", color2 , sizeof(color2));
    _commandBuffer->setBindGroup(&_bindGroup);
    
    _commandBuffer->drawElements(backend::PrimitiveType::TRIANGLE,
                                 backend::IndexFormat::U_SHORT,
                                 sizeof(bunny_cells) / bunny_cells[0]);
    
    _commandBuffer->endRenderPass();
    
    // Draw bg.
    _commandBuffer->beginRenderPass(_renderPassDescriptorBg);
    
    _bindGroup.setTexture("texture", 0, _colorTexture);
    _commandBuffer->setBindGroup(&_bindGroup);
    
    _commandBuffer->setRenderPipeline(bg->_renderPipeline);
    _commandBuffer->setVertexBuffer(0, bg->_vertexBuffer);
    _commandBuffer->drawArrays(backend::PrimitiveType::TRIANGLE, 0, 3);
    
    _commandBuffer->endRenderPass();
    
    _commandBuffer->endFrame();
}
