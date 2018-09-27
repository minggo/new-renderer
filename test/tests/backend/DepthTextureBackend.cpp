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
            renderPipelineDescriptor.setVertexShaderModule(vs);
            renderPipelineDescriptor.setFragmentShaderModule(fs);
            
            backend::VertexLayout vertexLayout;
            vertexLayout.setAtrribute("a_position", 0, cocos2d::backend::VertexFormat::FLOAT_R32G32, 0);
            vertexLayout.setLayout(2 * sizeof(float), cocos2d::backend::VertexStepMode::VERTEX);
            renderPipelineDescriptor.setVertexLayout(0, vertexLayout);
            
            renderPipeline = device->createRenderPipeline(renderPipelineDescriptor);
            renderPipeline->retain();
            
            // vertex buffer
            float vertices[] = {-1, 4, -1, -1, 4, -1};
            vertexBuffer = device->createBuffer(sizeof(vertices),
                                                cocos2d::backend::BufferType::VERTEX,
                                                cocos2d::backend::BufferUsage::READ);
            vertexBuffer->updateData(vertices, sizeof(vertices));
            vertexBuffer->retain();
        }
        
        ~BigTriangle()
        {
            CC_SAFE_RELEASE(renderPipeline);
            CC_SAFE_RELEASE(vertexBuffer);
        }
        
        backend::RenderPipeline* renderPipeline = nullptr;
        backend::Buffer* vertexBuffer = nullptr;
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
            auto vs = device->createShaderModule(cocos2d::backend::ShaderStage::VERTEX, vert);
            auto fs = device->createShaderModule(cocos2d::backend::ShaderStage::FRAGMENT, frag);
            renderPipelineDescriptor.setVertexShaderModule(vs);
            renderPipelineDescriptor.setFragmentShaderModule(fs);

            backend::VertexLayout vertexLayout;
            vertexLayout.setLayout(3 * sizeof(float), cocos2d::backend::VertexStepMode::VERTEX);
            vertexLayout.setAtrribute("a_position", 0, cocos2d::backend::VertexFormat::FLOAT_R32G32B32, 0);
            renderPipelineDescriptor.setVertexLayout(0, vertexLayout);
            
            backend::DepthStencilDescriptor depthStencilDescriptor;
            depthStencilDescriptor.depthWriteEnabled = true;
            depthStencilDescriptor.depthCompareFunction = backend::CompareFunction::LESS;
            auto depthStencilState = device->createDepthStencilState(depthStencilDescriptor);
            renderPipelineDescriptor.setDepthStencilState(depthStencilState);
            
            renderPipeline = device->createRenderPipeline(renderPipelineDescriptor);
            renderPipeline->retain();
            
            // vertex buffer
            vertexBuffer = device->createBuffer(sizeof(bunny_positions),
                                                cocos2d::backend::BufferType::VERTEX,
                                                cocos2d::backend::BufferUsage::READ);
            vertexBuffer->updateData((void*)&bunny_positions[0][0], sizeof(bunny_positions));
            vertexBuffer->retain();
            
            // index buffer
            indexBuffer = device->createBuffer(sizeof(bunny_cells),
                                               cocos2d::backend::BufferType::INDEX,
                                               cocos2d::backend::BufferUsage::READ);
            indexBuffer->updateData((void*)&bunny_cells[0], sizeof(bunny_cells));
            indexBuffer->retain();
        }
        
        ~Bunny()
        {
            CC_SAFE_RELEASE(vertexBuffer);
            CC_SAFE_RELEASE(indexBuffer);
            CC_SAFE_RELEASE(renderPipeline);
        }
        
        backend::Buffer* vertexBuffer = nullptr;
        backend::Buffer* indexBuffer = nullptr;
        backend::RenderPipeline* renderPipeline = nullptr;
    };
    
    BigTriangle* bg;
    Bunny* bunny;
}

DepthTextureBackend::DepthTextureBackend()
: _t(0.0f)
{
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    if (!(_device->supportGLExtension("OES_depth_texture")))
//        printf("error: the device doesn't support OES_depth_texture");
//#endif
    
    auto device = backend::Device::getInstance();
    
    // depth texture
    
    backend::SamplerDescriptor samplerDescriptor;
    samplerDescriptor.rAddressMode = backend::SamplerAddressMode::CLAMP_TO_EDGE;
    samplerDescriptor.sAddressMode = backend::SamplerAddressMode::CLAMP_TO_EDGE;
    
    backend::TextureDescriptor textureDescriptor;
    textureDescriptor.width = utils::WINDOW_WIDTH;
    textureDescriptor.height = utils::WINDOW_HEIGHT;
    textureDescriptor.textureType = backend::TextureType::TEXTURE_2D;
    textureDescriptor.samplerDescriptor = samplerDescriptor;
    textureDescriptor.textureFormat = backend::TextureFormat::D16;
    _depthTexture = device->createTexture(textureDescriptor);
    _depthTexture->retain();
    
    // render pass Bunny 1
    backend::RenderPassDescriptor renderPassDescriptorBunny1;
    renderPassDescriptorBunny1.setDepthStencilAttachment(_depthTexture,
                                                         cocos2d::backend::LoadOp::CLEAR,
                                                         cocos2d::backend::LoadOp::LOAD);
    renderPassDescriptorBunny1.setDepthStencilAttachmentClearValue(1, 0);
    _renderPassBunny1 = device->createRenderPass(renderPassDescriptorBunny1);
    _renderPassBunny1->retain();
    
    // render pass 2
    backend::RenderPassDescriptor renderPassDescriptorBunny2;
    renderPassDescriptorBunny2.setDepthStencilAttachment(_depthTexture,
                                                         cocos2d::backend::LoadOp::LOAD,
                                                         cocos2d::backend::LoadOp::LOAD);
    _renderPassBunny2 = device->createRenderPass(renderPassDescriptorBunny2);
    _renderPassBunny2->retain();
    
    // render pass BigTriangle
    backend::RenderPassDescriptor renderPassDescriptorBigTriangle;
    renderPassDescriptorBigTriangle.setColorAttachmentsClearColor(0.1f, 0.1f, 0.1f, 1);
    renderPassDescriptorBigTriangle.setColorAttachmentsLoadOp(cocos2d::backend::LoadOp::CLEAR);
    renderPassDescriptorBigTriangle.setDepthStencilAttachment(nullptr,
                                                              cocos2d::backend::LoadOp::CLEAR,
                                                              cocos2d::backend::LoadOp::LOAD);
    renderPassDescriptorBigTriangle.setDepthStencilAttachmentClearValue(1, 0);
    _renderPassBigTriangle = device->createRenderPass(renderPassDescriptorBigTriangle);
    _renderPassBigTriangle->retain();
    
    _commandBuffer = device->createCommandBuffer();
    _commandBuffer->retain();
    
    bunny = new Bunny();
    bg = new BigTriangle();
}

DepthTextureBackend::~DepthTextureBackend()
{
    delete bunny;
    delete bg;
    
    CC_SAFE_RELEASE(_depthTexture);
    CC_SAFE_RELEASE(_renderPassBunny1);
    CC_SAFE_RELEASE(_renderPassBunny2);
    CC_SAFE_RELEASE(_renderPassBigTriangle);
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

    // Draw bunny one.
    
    _commandBuffer->beginRenderPass(_renderPassBunny1);
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _commandBuffer->setRenderPipeline(bunny->renderPipeline);
    _commandBuffer->setVertexBuffer(0, bunny->vertexBuffer);
    _commandBuffer->setIndexBuffer(0, bunny->indexBuffer);
    
    _model = Mat4::IDENTITY;
    _model.translate(5, 0, 0);
    _bindGroupBunny.setUniform("model", 0, _model.m, sizeof(_model.m));
    _bindGroupBunny.setUniform("view", 1, _view.m, sizeof(_view.m));
    _bindGroupBunny.setUniform("projection", 2, _projection.m, sizeof(_projection.m));
    _commandBuffer->setBindGroup(&_bindGroupBunny);
    
    _commandBuffer->drawElements(cocos2d::backend::PrimitiveType::TRIANGLE,
                                 cocos2d::backend::IndexFormat::U_SHORT,
                                 sizeof(bunny_cells) / bunny_cells[0]);    
    _commandBuffer->endRenderPass();

    // Draw bunny two.
    _commandBuffer->beginRenderPass(_renderPassBunny2);
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _commandBuffer->setRenderPipeline(bunny->renderPipeline);
    _commandBuffer->setVertexBuffer(0, bunny->vertexBuffer);
    _commandBuffer->setIndexBuffer(0, bunny->indexBuffer);
    
    _model = Mat4::IDENTITY;
    _model.translate(-5, 0, 0);
    _bindGroupBunny.setUniform("model", 0, _model.m, sizeof(_model.m));
    _bindGroupBunny.setUniform("view", 1, _view.m, sizeof(_view.m));
    _bindGroupBunny.setUniform("projection", 2, _projection.m, sizeof(_projection.m));
    _commandBuffer->setBindGroup(&_bindGroupBunny);
    
    _commandBuffer->drawElements(cocos2d::backend::PrimitiveType::TRIANGLE,
                                 cocos2d::backend::IndexFormat::U_SHORT,
                                 sizeof(bunny_cells) / bunny_cells[0]);
    _commandBuffer->endRenderPass();
    
    // Draw bg.

    _commandBuffer->beginRenderPass(_renderPassBigTriangle);
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _commandBuffer->setRenderPipeline(bg->renderPipeline);
    _commandBuffer->setVertexBuffer(0, bg->vertexBuffer);
    
    _bindGroupBigTriangle.setTexture("texture", 0, _depthTexture);
    float near = 0.1f;
    float far = 100.f;
    _bindGroupBigTriangle.setUniform("near", 1, &near, sizeof(float));
    _bindGroupBigTriangle.setUniform("far", 2, &far, sizeof(float));
    _commandBuffer->setBindGroup(&_bindGroupBigTriangle);
    
    _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 6);
    _commandBuffer->endRenderPass();
}
