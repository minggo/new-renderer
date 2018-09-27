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

#include "BlendingBackend.h"
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
            
            auto device = backend::Device::getInstance();
            
            backend::RenderPipelineDescriptor renderPipelineDescriptor;
            auto vs = device->createShaderModule(cocos2d::backend::ShaderStage::VERTEX, vert);
            auto fs = device->createShaderModule(cocos2d::backend::ShaderStage::FRAGMENT, frag);
            renderPipelineDescriptor.setVertexShaderModule(vs);
            renderPipelineDescriptor.setFragmentShaderModule(fs);
            
            backend::VertexLayout vertexLayout;
            vertexLayout.setAtrribute("a_position", 0, cocos2d::backend::VertexFormat::FLOAT_R32G32, 0);
            vertexLayout.setAtrribute("a_uv", 1, cocos2d::backend::VertexFormat::FLOAT_R32G32, 2 * sizeof(float));
            vertexLayout.setLayout(4 * sizeof(float), cocos2d::backend::VertexStepMode::VERTEX);
            renderPipelineDescriptor.setVertexLayout(0, vertexLayout);
            
            backend::BlendDescriptor blendDescriptorNoBlending;
            blendDescriptorNoBlending.blendEnabled = true;
            blendDescriptorNoBlending.rgbBlendOperation = backend::BlendOperation::ADD;
            blendDescriptorNoBlending.alphaBlendOperation = backend::BlendOperation::ADD;
            blendDescriptorNoBlending.sourceRGBBlendFactor = backend::BlendFactor::ONE;
            blendDescriptorNoBlending.destinationRGBBlendFactor = backend::BlendFactor::ZERO;
            blendDescriptorNoBlending.sourceAlphaBlendFactor = backend::BlendFactor::ONE;
            blendDescriptorNoBlending.destinationAlphaBlendFactor = backend::BlendFactor::ZERO;
            auto blendStateNoBlending = device->createBlendState(blendDescriptorNoBlending);
            renderPipelineDescriptor.setBlendState(blendStateNoBlending);
            renderPipelineNoBlending = device->createRenderPipeline(renderPipelineDescriptor);
            renderPipelineNoBlending->retain();

            backend::BlendDescriptor blendDescriptorNormal;
            blendDescriptorNormal.blendEnabled = true;
            blendDescriptorNormal.rgbBlendOperation = backend::BlendOperation::ADD;
            blendDescriptorNormal.alphaBlendOperation = backend::BlendOperation::ADD;
            blendDescriptorNormal.sourceRGBBlendFactor = backend::BlendFactor::SRC_ALPHA;
            blendDescriptorNormal.destinationRGBBlendFactor = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
            blendDescriptorNormal.sourceAlphaBlendFactor = backend::BlendFactor::ONE;
            blendDescriptorNormal.destinationRGBBlendFactor = backend::BlendFactor::ONE;
            auto blendStateNormal = device->createBlendState(blendDescriptorNormal);
            renderPipelineDescriptor.setBlendState(blendStateNormal);
            renderPipelineNormal = device->createRenderPipeline(renderPipelineDescriptor);
            renderPipelineNormal->retain();
            
            backend::BlendDescriptor blendDescriptorAddtive;
            blendDescriptorAddtive.blendEnabled = true;
            blendDescriptorAddtive.rgbBlendOperation = backend::BlendOperation::ADD;
            blendDescriptorAddtive.alphaBlendOperation = backend::BlendOperation::ADD;
            blendDescriptorAddtive.sourceRGBBlendFactor = backend::BlendFactor::SRC_ALPHA;
            blendDescriptorAddtive.destinationRGBBlendFactor = backend::BlendFactor::ONE;
            blendDescriptorAddtive.sourceAlphaBlendFactor = backend::BlendFactor::ONE;
            blendDescriptorAddtive.destinationAlphaBlendFactor = backend::BlendFactor::ONE;
            auto blendStateAddtive = device->createBlendState(blendDescriptorAddtive);
            renderPipelineDescriptor.setBlendState(blendStateAddtive);
            renderPipelineAddtive = device->createRenderPipeline(renderPipelineDescriptor);
            renderPipelineAddtive->retain();
            
            backend::BlendDescriptor blendDescriptorSubstract;
            blendDescriptorSubstract.blendEnabled = true;
            blendDescriptorSubstract.rgbBlendOperation = backend::BlendOperation::ADD;
            blendDescriptorSubstract.alphaBlendOperation = backend::BlendOperation::ADD;
            blendDescriptorSubstract.sourceRGBBlendFactor = backend::BlendFactor::ZERO;
            blendDescriptorSubstract.destinationRGBBlendFactor = backend::BlendFactor::ONE_MINUS_SRC_COLOR;
            blendDescriptorSubstract.sourceAlphaBlendFactor = backend::BlendFactor::ONE;
            blendDescriptorSubstract.destinationAlphaBlendFactor = backend::BlendFactor::ONE;
            auto blendStateSubstract = device->createBlendState(blendDescriptorSubstract);
            renderPipelineDescriptor.setBlendState(blendStateSubstract);
            renderPipelineSubstract = device->createRenderPipeline(renderPipelineDescriptor);
            renderPipelineSubstract->retain();
            
            backend::BlendDescriptor blendDescriptorMultiply;
            blendDescriptorMultiply.blendEnabled = true;
            blendDescriptorMultiply.rgbBlendOperation = backend::BlendOperation::ADD;
            blendDescriptorMultiply.alphaBlendOperation = backend::BlendOperation::ADD;
            blendDescriptorMultiply.sourceRGBBlendFactor = backend::BlendFactor::ZERO;
            blendDescriptorMultiply.destinationRGBBlendFactor = backend::BlendFactor::SRC_COLOR;
            blendDescriptorMultiply.sourceAlphaBlendFactor = backend::BlendFactor::ONE;
            blendDescriptorMultiply.destinationAlphaBlendFactor = backend::BlendFactor::ONE;
            auto blendStateMultiply = device->createBlendState(blendDescriptorMultiply);
            renderPipelineDescriptor.setBlendState(blendStateMultiply);
            renderPipelineMultiply = device->createRenderPipeline(renderPipelineDescriptor);
            renderPipelineMultiply->retain();
            
            float vertices[] = {
                -0.5f, -0.5f,   0,   0,
                -0.5f,  0.5f,   0, 1.f,
                 0.5f,  0.5f, 1.f, 1.f,
                 0.5f, -0.5f, 1.f,   0
            };
            vertexBuffer = device->createBuffer(sizeof(vertices),
                                                cocos2d::backend::BufferType::VERTEX,
                                                cocos2d::backend::BufferUsage::READ);
            vertexBuffer->retain();
            vertexBuffer->updateData(vertices, sizeof(vertices));
            
            uint8_t indices[] = {0, 3, 1, 1, 3, 2};
            indexBuffer = device->createBuffer(sizeof(indices),
                                               cocos2d::backend::BufferType::INDEX,
                                               cocos2d::backend::BufferUsage::READ);
            indexBuffer->updateData(indices, sizeof(indices));
            indexBuffer->retain();
        }
        
        ~Quad()
        {
            CC_SAFE_RELEASE(renderPipelineNoBlending);
            CC_SAFE_RELEASE(renderPipelineNormal);
            CC_SAFE_RELEASE(renderPipelineAddtive);
            CC_SAFE_RELEASE(renderPipelineSubstract);
            CC_SAFE_RELEASE(renderPipelineMultiply);
            CC_SAFE_RELEASE(vertexBuffer);
            CC_SAFE_RELEASE(indexBuffer);
        }

        backend::RenderPipeline* renderPipelineNoBlending = nullptr;
        backend::RenderPipeline* renderPipelineNormal = nullptr;
        backend::RenderPipeline* renderPipelineAddtive = nullptr;
        backend::RenderPipeline* renderPipelineSubstract = nullptr;
        backend::RenderPipeline* renderPipelineMultiply = nullptr;
        backend::Buffer* vertexBuffer = nullptr;
        backend::Buffer* indexBuffer = nullptr;
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
            
            auto device = backend::Device::getInstance();
            
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
            
            float vertices[] = {
                -1, 4,
                -1, -1,
                4, -1
            };
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
    
BlendingBackend::BlendingBackend()
: _dt(0.f)
{
    delete bigTriangle;
    bigTriangle = new BigTriangle();
    
    delete quad;
    quad = new Quad();
    
    auto device = backend::Device::getInstance();
    
    backend::TextureDescriptor textureDescriptorBackgroud;
    textureDescriptorBackgroud.width = 128;
    textureDescriptorBackgroud.height = 128;
    textureDescriptorBackgroud.samplerDescriptor.rAddressMode = backend::SamplerAddressMode::REPEAT;
    textureDescriptorBackgroud.samplerDescriptor.sAddressMode = backend::SamplerAddressMode::REPEAT;
    textureDescriptorBackgroud.samplerDescriptor.mipmapFilter = backend::SamplerFilter::LINEAR;
    textureDescriptorBackgroud.textureFormat = backend::TextureFormat::R8G8B8;
    _backgroud = device->createTexture(textureDescriptorBackgroud);
    _backgroud->updateData(utils::loadData("assets/background.png").getBytes());
    _backgroud->retain();
    
    backend::TextureDescriptor textureDescriptorSprite0;
    textureDescriptorSprite0.width = 128;
    textureDescriptorSprite0.height = 128;
    textureDescriptorSprite0.textureFormat = backend::TextureFormat::R8G8B8A8;
    _sprite0 = device->createTexture(textureDescriptorSprite0);
    _sprite0->updateData(utils::loadData("assets/sprite0.png").getBytes());
    _sprite0->retain();
    
    _commandBuffer = device->createCommandBuffer();
    _commandBuffer->retain();
    
    backend::RenderPassDescriptor renderPassDescriptorBigTriangl;
    renderPassDescriptorBigTriangl.setColorAttachmentsClearColor(0.1f, 0.1f, 0.1f, 1.f);
    renderPassDescriptorBigTriangl.setDepthStencilAttachment(nullptr,
                                                             cocos2d::backend::LoadOp::CLEAR,
                                                             cocos2d::backend::LoadOp::LOAD);
    renderPassDescriptorBigTriangl.setDepthStencilAttachmentClearValue(1, 0);
    _renderPassBigTriangle = device->createRenderPass(renderPassDescriptorBigTriangl);
    _renderPassBigTriangle->retain();
}

BlendingBackend::~BlendingBackend()
{
    delete bigTriangle;
    delete quad;
    
    CC_SAFE_RELEASE(_backgroud);
    CC_SAFE_RELEASE(_sprite0);
    CC_SAFE_RELEASE(_commandBuffer);
    CC_SAFE_RELEASE(_renderPassBigTriangle);
}

void BlendingBackend::tick(float dt)
{
    _dt += dt;
    
    Mat4::createOrthographicOffCenter(0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT, 0, 0, 1000.f, &_projection);
    
    _commandBuffer->beginRenderPass(_renderPassBigTriangle);
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _commandBuffer->setRenderPipeline(bigTriangle->renderPipeline);
    
    _bindGroupBigTriangle.setUniform("time", 0, &_dt, sizeof(_dt));
    _bindGroupBigTriangle.setUniform("projection", 1, _projection.m, sizeof(_projection.m));
    _bindGroupBigTriangle.setTexture("texture", 0, _backgroud);
    _commandBuffer->setBindGroup(&_bindGroupBigTriangle);
    
    _commandBuffer->setVertexBuffer(0, bigTriangle->vertexBuffer);
    _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 3);
    _commandBuffer->endRenderPass();
    

    // sprites
    
    float size = std::min(utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT) * 0.15f;
    float hsize = size * 0.5f;

    // no blending
    _commandBuffer->beginRenderPass(nullptr);
    _commandBuffer->setRenderPipeline(quad->renderPipelineNoBlending);
    
    float offsetX = 5.f + hsize;
    float offsetY = 5.f + hsize;
    _model = std::move(createModel(cocos2d::Vec3(offsetX, offsetY, 0), cocos2d::Vec3(size, size, 0)));
    _bindGroup.setUniform("model", 0, _model.m, sizeof(_model.m));
    _bindGroup.setUniform("projection", 1, _projection.m, sizeof(_projection.m));
    _bindGroup.setTexture("texture", 0, _sprite0);
    _commandBuffer->setBindGroup(&_bindGroup);
    
    _commandBuffer->setVertexBuffer(0, quad->vertexBuffer);
    _commandBuffer->setIndexBuffer(0, quad->indexBuffer);
    _commandBuffer->drawElements(cocos2d::backend::PrimitiveType::TRIANGLE,
                                 cocos2d::backend::IndexFormat::U_BYTE,
                                 6);
    _commandBuffer->endRenderPass();

    // normal
    _commandBuffer->beginRenderPass(nullptr);
    _commandBuffer->setRenderPipeline(quad->renderPipelineNormal);
    
    offsetY = offsetY + 5.f + size;
    _model = std::move(createModel(cocos2d::Vec3(offsetX, offsetY, 0), cocos2d::Vec3(size, size, 0)));
    _bindGroup.setUniform("model", 0, _model.m, sizeof(_model.m));
    _bindGroup.setUniform("projection", 1, _projection.m, sizeof(_projection.m));
    _bindGroup.setTexture("texture", 0, _sprite0);
    _commandBuffer->setBindGroup(&_bindGroup);
    
    _commandBuffer->setVertexBuffer(0, quad->vertexBuffer);
    _commandBuffer->setIndexBuffer(0, quad->indexBuffer);
    _commandBuffer->drawElements(cocos2d::backend::PrimitiveType::TRIANGLE,
                                 cocos2d::backend::IndexFormat::U_BYTE,
                                 6);
    _commandBuffer->endRenderPass();

    // additive
    _commandBuffer->beginRenderPass(nullptr);
    _commandBuffer->setRenderPipeline(quad->renderPipelineAddtive);
    
    offsetY = offsetY + 5.f + size;
    _model = std::move(createModel(cocos2d::Vec3(offsetX, offsetY, 0), cocos2d::Vec3(size, size, 0)));
    _bindGroup.setUniform("model", 0, _model.m, sizeof(_model.m));
    _bindGroup.setUniform("projection", 1, _projection.m, sizeof(_projection.m));
    _bindGroup.setTexture("texture", 0, _sprite0);
    _commandBuffer->setBindGroup(&_bindGroup);
    
    _commandBuffer->setVertexBuffer(0, quad->vertexBuffer);
    _commandBuffer->setIndexBuffer(0, quad->indexBuffer);
    _commandBuffer->drawElements(cocos2d::backend::PrimitiveType::TRIANGLE,
                                 cocos2d::backend::IndexFormat::U_BYTE,
                                 6);
    _commandBuffer->endRenderPass();

    // substract

    _commandBuffer->beginRenderPass(nullptr);
    _commandBuffer->setRenderPipeline(quad->renderPipelineSubstract);
    
    offsetY = offsetY + 5.f + size;
    _model = std::move(createModel(cocos2d::Vec3(offsetX, offsetY, 0), cocos2d::Vec3(size, size, 0)));
    _bindGroup.setUniform("model", 0, _model.m, sizeof(_model.m));
    _bindGroup.setUniform("projection", 1, _projection.m, sizeof(_projection.m));
    _bindGroup.setTexture("texture", 0, _sprite0);
    _commandBuffer->setBindGroup(&_bindGroup);
    
    _commandBuffer->setVertexBuffer(0, quad->vertexBuffer);
    _commandBuffer->setIndexBuffer(0, quad->indexBuffer);
    _commandBuffer->drawElements(cocos2d::backend::PrimitiveType::TRIANGLE,
                                 cocos2d::backend::IndexFormat::U_BYTE,
                                 6);
    _commandBuffer->endRenderPass();

    // multiply
    _commandBuffer->beginRenderPass(nullptr);
    _commandBuffer->setRenderPipeline(quad->renderPipelineMultiply);
    
    offsetY = offsetY + 5.f + size;
    _model = std::move(createModel(cocos2d::Vec3(offsetX, offsetY, 0), cocos2d::Vec3(size, size, 0)));
    _bindGroup.setUniform("model", 0, _model.m, sizeof(_model.m));
    _bindGroup.setUniform("projection", 1, _projection.m, sizeof(_projection.m));
    _bindGroup.setTexture("texture", 0, _sprite0);
    _commandBuffer->setBindGroup(&_bindGroup);
    
    _commandBuffer->setVertexBuffer(0, quad->vertexBuffer);
    _commandBuffer->setIndexBuffer(0, quad->indexBuffer);
    _commandBuffer->drawElements(cocos2d::backend::PrimitiveType::TRIANGLE,
                                 cocos2d::backend::IndexFormat::U_BYTE,
                                 6);
    _commandBuffer->endRenderPass();
}

