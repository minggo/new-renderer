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

#include "DepthTextureBackend.h"
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
            
            auto device = backend::Device::getInstance();
            
            // render pipeline
            
            backend::RenderPipelineDescriptor renderPipelineDescriptor;
            auto vs = device->createShaderModule(cocos2d::backend::ShaderStage::VERTEX, vert);
            auto fs = device->createShaderModule(cocos2d::backend::ShaderStage::FRAGMENT, frag);
            renderPipelineDescriptor.program = device->createProgram(vs, fs);
            _nearLocation = renderPipelineDescriptor.program->getUniformLocation("near");
            _farLocation = renderPipelineDescriptor.program->getUniformLocation("far");
            
            backend::VertexLayout vertexLayout;
            vertexLayout.setAtrribute("a_position", 0, cocos2d::backend::VertexFormat::FLOAT_R32G32, 0);
            vertexLayout.setLayout(2 * sizeof(float), cocos2d::backend::VertexStepMode::VERTEX);
            renderPipelineDescriptor.vertexLayouts.push_back(vertexLayout);
            renderPipelineDescriptor.depthAttachmentFormat = backend::TextureFormat::D24S8;
            
            renderPipeline = device->newRenderPipeline(renderPipelineDescriptor);
            
            // vertex buffer
            float vertices[] = {-1, 4, -1, -1, 4, -1};
            vertexBuffer = device->newBuffer(sizeof(vertices),
                                             cocos2d::backend::BufferType::VERTEX,
                                             cocos2d::backend::BufferUsage::READ);
            vertexBuffer->updateData(vertices, sizeof(vertices));
        }
        
        ~BigTriangle()
        {
            CC_SAFE_RELEASE(renderPipeline);
            CC_SAFE_RELEASE(vertexBuffer);
        }
        
        inline int getNearLocation() const { return _nearLocation; }
        inline int getFarLocaiton() const { return _farLocation; }
        inline backend::Program* getProgram() { return renderPipeline->getProgram(); }
        
        backend::RenderPipeline* renderPipeline = nullptr;
        backend::Buffer* vertexBuffer = nullptr;
        
        int _nearLocation = -1;
        int _farLocation = -1;
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
            
            auto device = backend::Device::getInstance();
            
            // render pipeline
            
            backend::RenderPipelineDescriptor renderPipelineDescriptor;
            renderPipelineDescriptor.depthAttachmentFormat = backend::TextureFormat::D24S8;
            renderPipelineDescriptor.colorAttachmentsFormat[0] = backend::TextureFormat::NONE;
            auto vs = device->createShaderModule(cocos2d::backend::ShaderStage::VERTEX, vert);
            auto fs = device->createShaderModule(cocos2d::backend::ShaderStage::FRAGMENT, frag);
            renderPipelineDescriptor.program = device->createProgram(vs, fs);
            _modelLocation = renderPipelineDescriptor.program->getUniformLocation("model");
            _viewLocation = renderPipelineDescriptor.program->getUniformLocation("view");
            _projectionLocation = renderPipelineDescriptor.program->getUniformLocation("projection");

            backend::VertexLayout vertexLayout;
            vertexLayout.setLayout(3 * sizeof(float), cocos2d::backend::VertexStepMode::VERTEX);
            vertexLayout.setAtrribute("a_position", 0, cocos2d::backend::VertexFormat::FLOAT_R32G32B32, 0);
            renderPipelineDescriptor.vertexLayouts.push_back(vertexLayout);
            
            backend::DepthStencilDescriptor depthStencilDescriptor;
            depthStencilDescriptor.depthWriteEnabled = true;
            depthStencilDescriptor.depthTestEnabled = true;
            depthStencilDescriptor.depthCompareFunction = backend::CompareFunction::LESS;
            auto depthStencilState = device->createDepthStencilState(depthStencilDescriptor);
            renderPipelineDescriptor.depthStencilState = depthStencilState;
            
            renderPipeline = device->newRenderPipeline(renderPipelineDescriptor);
            renderPipeline->retain();
            
            // vertex buffer
            vertexBuffer = device->newBuffer(sizeof(bunny_positions),
                                             cocos2d::backend::BufferType::VERTEX,
                                             cocos2d::backend::BufferUsage::READ);
            vertexBuffer->updateData((void*)&bunny_positions[0][0], sizeof(bunny_positions));
            
            // index buffer
            indexBuffer = device->newBuffer(sizeof(bunny_cells),
                                            cocos2d::backend::BufferType::INDEX,
                                            cocos2d::backend::BufferUsage::READ);
            indexBuffer->updateData((void*)&bunny_cells[0], sizeof(bunny_cells));
        }
        
        ~Bunny()
        {
            CC_SAFE_RELEASE(vertexBuffer);
            CC_SAFE_RELEASE(indexBuffer);
            CC_SAFE_RELEASE(renderPipeline);
        }
        
        inline int getModelLocation() const { return _modelLocation; }
        inline int getViewLocation() const { return _viewLocation; }
        inline int getProjectionLocation() const { return _projectionLocation; }
        inline backend::Program* getProgram() { return renderPipeline->getProgram(); }
        
        backend::Buffer* vertexBuffer = nullptr;
        backend::Buffer* indexBuffer = nullptr;
        backend::RenderPipeline* renderPipeline = nullptr;
        
        int _modelLocation = -1;
        int _viewLocation = -1;
        int _projectionLocation = -1;
    };
    
    BigTriangle* bg;
    Bunny* bunny;
}

DepthTextureBackend::DepthTextureBackend()
: _t(0.0f)
{
    bunny = new Bunny();
    bg = new BigTriangle();
    auto device = backend::Device::getInstance();
    
    // depth texture
    backend::SamplerDescriptor samplerDescriptor;
    samplerDescriptor.sAddressMode = backend::SamplerAddressMode::CLAMP_TO_EDGE;
    samplerDescriptor.tAddressMode = backend::SamplerAddressMode::CLAMP_TO_EDGE;
    
    backend::TextureDescriptor textureDescriptor;
    textureDescriptor.width = utils::WINDOW_WIDTH;
    textureDescriptor.height = utils::WINDOW_HEIGHT;
    textureDescriptor.textureType = backend::TextureType::TEXTURE_2D;
    textureDescriptor.textureUsage = backend::TextureUsage::RENDER_TARGET;
    textureDescriptor.samplerDescriptor = samplerDescriptor;
    textureDescriptor.textureFormat = backend::TextureFormat::D24S8;
    _depthTexture = device->newTexture(textureDescriptor);
    bg->getProgram()->setTexture("texture", 0, _depthTexture);
    
    // render pass Bunny 1
    _renderPassBunny1.clearDepthValue = 1;
    _renderPassBunny1.needClearDepth = true;
    _renderPassBunny1.depthAttachmentTexture = _depthTexture;
    _renderPassBunny1.needDepthAttachment = true;
    _renderPassBunny1.needColorAttachment = false;
    
    // render pass 2
    _renderPassBunny2.depthAttachmentTexture = _depthTexture;
    _renderPassBunny2.needDepthAttachment = true;
    _renderPassBunny2.needColorAttachment = false;
    
    // render pass BigTriangle
    _renderPassBigTriangle.clearColorValue = {0.1f, 0.1f, 0.1f, 1};
    _renderPassBigTriangle.needClearColor = true;
    _renderPassBigTriangle.clearDepthValue = 1;
    _renderPassBigTriangle.needClearDepth = true;
    _renderPassBigTriangle.needDepthAttachment = true;
    _renderPassBigTriangle.needColorAttachment = true;
    
    _commandBuffer = device->newCommandBuffer();
}

DepthTextureBackend::~DepthTextureBackend()
{
    delete bunny;
    delete bg;
    
    CC_SAFE_RELEASE(_depthTexture);
    CC_SAFE_RELEASE(_commandBuffer);
}

void DepthTextureBackend::tick(float dt)
{
    _t += dt;
    
    _eye.set(30.f * std::cos(_t), 20.f, 30.f * std::sin(_t));
    _center.set(0, 2.5f, 0);
    _up.set(0, 1.f, 0);
    Mat4::createLookAt(_eye, _center, _up, &_view);

    Mat4::createPerspective(45.f, 1.0f * utils::WINDOW_WIDTH / utils::WINDOW_HEIGHT, 0.1f, 100.f, &_projection);
    
    _commandBuffer->beginFrame();

    // Draw bunny one.
    _commandBuffer->beginRenderPass(_renderPassBunny1);
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _commandBuffer->setRenderPipeline(bunny->renderPipeline);
    _commandBuffer->setVertexBuffer(0, bunny->vertexBuffer);
    _commandBuffer->setIndexBuffer(bunny->indexBuffer);
    
    _model = Mat4::IDENTITY;
    _model.translate(5, 0, 0);
    
    bunny->getProgram()->setVertexUniform(bunny->getModelLocation(), _model.m, sizeof(_model.m));
    bunny->getProgram()->setVertexUniform(bunny->getViewLocation(),  _view.m, sizeof(_view.m));
    bunny->getProgram()->setVertexUniform(bunny->getProjectionLocation(), _projection.m, sizeof(_projection.m));
    
    _commandBuffer->drawElements(cocos2d::backend::PrimitiveType::TRIANGLE,
                                 cocos2d::backend::IndexFormat::U_SHORT,
                                 sizeof(bunny_cells) / bunny_cells[0]);    

    // Draw bunny two.
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _commandBuffer->setRenderPipeline(bunny->renderPipeline);
    _commandBuffer->setVertexBuffer(0, bunny->vertexBuffer);
    _commandBuffer->setIndexBuffer(bunny->indexBuffer);
    
    _model = Mat4::IDENTITY;
    _model.translate(-5, 0, 0);
    bunny->getProgram()->setVertexUniform(bunny->getModelLocation(), _model.m, sizeof(_model.m));
    bunny->getProgram()->setVertexUniform(bunny->getViewLocation(), _view.m, sizeof(_view.m));
    bunny->getProgram()->setVertexUniform(bunny->getProjectionLocation(), _projection.m, sizeof(_projection.m));
    
    _commandBuffer->drawElements(cocos2d::backend::PrimitiveType::TRIANGLE,
                                 cocos2d::backend::IndexFormat::U_SHORT,
                                 sizeof(bunny_cells) / bunny_cells[0]);
    _commandBuffer->endRenderPass();
    
    // Draw bg.
    _commandBuffer->beginRenderPass(_renderPassBigTriangle);
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _commandBuffer->setRenderPipeline(bg->renderPipeline);
    _commandBuffer->setVertexBuffer(0, bg->vertexBuffer);
    
    float near = 0.1f;
    float far = 100.f;
    bg->getProgram()->setFragmentUniform(bg->getNearLocation(), &near, sizeof(float));
    bg->getProgram()->setFragmentUniform(bg->getFarLocaiton(), &far, sizeof(float));
    
    _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 6);
    _commandBuffer->endRenderPass();
    
    _commandBuffer->endFrame();
}
