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
#include "BasicBackend.h"
#include "../Utils.h"

#include "backend/RenderPipelineDescriptor.h"
#include "backend/RenderPassDescriptor.h"
#include "backend/ShaderModule.h"
#include "backend/VertexLayout.h"

std::string test_unrollLoops(const std::string& text);

using namespace cocos2d;

BasicBackend::BasicBackend()
: _time(0.f)
{
#if 0
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
    
#else
    const char* vert = R"(
    #include <metal_stdlib>
    #include <simd/simd.h>
    
    using namespace metal;
    
    typedef struct
    {
        float4 position [[position]];
    } VertexData;
    
    typedef struct
    {
        // Positions in pixel space (i.e. a value of 100 indicates 100 pixels from the origin/center)
        vector_float2 position;
    } AAPLVertex;
    
    vertex VertexData
    main0(uint vertexID [[vertex_id]],
          constant AAPLVertex *vertexArray [[ buffer(0) ]])
    {
        VertexData out;
        out.position.xy = vertexArray[vertexID].position.xy;
        out.position.z = 0.0;
        out.position.w = 1.0;
        
        return out;
    }
    )";
    
    const char* frag = R"(
        #include <metal_stdlib>
        #include <simd/simd.h>
    
        using namespace metal;
    
        typedef struct
        {
            float4 position [[position]];
        } VertexData;
    
        fragment float4
        main0(VertexData in [[stage_in]])
        {
            return float4(1.0, 0.0, 0.0, 1.0);
        }
    )";
#endif
    
    auto device = cocos2d::backend::Device::getInstance();
    
    auto vs = device->createShaderModule(cocos2d::backend::ShaderStage::VERTEX, vert);
    auto fs = device->createShaderModule(cocos2d::backend::ShaderStage::FRAGMENT, frag);
    cocos2d::backend::RenderPipelineDescriptor renderPipelineDescriptor;
    renderPipelineDescriptor.setVertexShaderModule(vs);
    renderPipelineDescriptor.setFragmentShaderModule(fs);
    
    cocos2d::backend::VertexLayout vertexLayout;
    vertexLayout.setAtrribute("a_position", 0, cocos2d::backend::VertexFormat::FLOAT_R32G32, 0);
    vertexLayout.setLayout(sizeof(float) * 2, cocos2d::backend::VertexStepMode::VERTEX);
    renderPipelineDescriptor.setVertexLayout(0, vertexLayout);
    
    _renderPipeline = device->createRenderPipeline(renderPipelineDescriptor);
    _renderPipeline->retain();
    
    _commandBuffer = device->createCommandBuffer();
    _commandBuffer->retain();

    float data[] = {-1, 0, 0, -1, 1, 1};
    _vertexBuffer = device->createBuffer(sizeof(data), cocos2d::backend::BufferType::VERTEX, cocos2d::backend::BufferUsage::READ);
    _vertexBuffer->updateData((uint8_t*)data, sizeof(data));
    _vertexBuffer->retain();
    
//    cocos2d::backend::RenderPassDescriptor renderPassDescriptor;
//    renderPassDescriptor.setColorAttachmentsLoadOp(cocos2d::backend::LoadOp::CLEAR);
//    renderPassDescriptor.setColorAttachmentsClearColor(0.1f, 0.1f, 0.1f, 0.1f);
//    renderPassDescriptor.setDepthStencilAttachment(nullptr, cocos2d::backend::LoadOp::CLEAR, cocos2d::backend::LoadOp::LOAD);
//    renderPassDescriptor.setDepthStencilAttachmentClearValue(1, 0);
//    _renderPass = device->createRenderPass(renderPassDescriptor);
//    _renderPass->retain();
}

BasicBackend::~BasicBackend()
{
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_renderPipeline);
    CC_SAFE_RELEASE(_commandBuffer);
    CC_SAFE_RELEASE(_renderPass);
}

void BasicBackend::tick(float dt)
{
    _time += dt;
    float color[4] = {1.f, std::abs(std::sin(_time)), 0.f, 1.f};
    
//    _commandBuffer->beginRenderPass(_renderPass);
    _commandBuffer->beginRenderPass(nullptr);
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _commandBuffer->setRenderPipeline(_renderPipeline);
    _commandBuffer->setVertexBuffer(0, _vertexBuffer);
    _bindGroup.setUniform("color", 0, color, sizeof(color));
    _commandBuffer->setBindGroup(&_bindGroup);
    _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 3);
    _commandBuffer->endRenderPass();
}
