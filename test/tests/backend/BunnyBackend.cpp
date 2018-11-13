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
#include "BunnyBackend.h"
#include "BunnyData.h"
#include "../Utils.h"
#include "backend/Device.h"
#include "backend/VertexLayout.h"

using namespace cocos2d;

BunnyBackend::BunnyBackend()
: _time(0.0f)
{
    const char* vert = R"(
#ifdef GL_ES
    precision highp float;
#endif
    attribute vec3 a_position;
    uniform mat4 model, view, projection;
    varying vec3 position;

    void main () {
        vec4 pos = projection * view * model * vec4(a_position, 1);
        position = a_position.xyz;
        gl_Position = pos;
    }
    )";

    const char* frag = R"(
#ifdef GL_ES
    precision highp float;
#endif
    uniform vec4 color;
    varying vec3 position;

    void main () {
        gl_FragColor = color * vec4(position, 1);
    }
    )";
    
    auto device = cocos2d::backend::Device::getInstance();
    
    // create renderpipeline

    cocos2d::backend::RenderPipelineDescriptor renderPipelineDescriptor;
    
    cocos2d::backend::VertexLayout vertexLayout;
    vertexLayout.setLayout(3 * sizeof(float), cocos2d::backend::VertexStepMode::VERTEX);
    vertexLayout.setAtrribute("a_position", 0, cocos2d::backend::VertexFormat::FLOAT_R32G32B32, 0);
    renderPipelineDescriptor.setVertexLayout(0, vertexLayout);
    
    // depth/stencil state
    cocos2d::backend::DepthStencilDescriptor depthStencilDescriptor;
    depthStencilDescriptor.depthWriteEnabled = true;
    depthStencilDescriptor.depthCompareFunction = cocos2d::backend::CompareFunction::LESS;
    auto depthStencilState = device->createDepthStencilState(depthStencilDescriptor);
    renderPipelineDescriptor.setDepthStencilState(depthStencilState);
 
    auto vs = device->createShaderModule(cocos2d::backend::ShaderStage::VERTEX, vert);
    auto fs = device->createShaderModule(cocos2d::backend::ShaderStage::FRAGMENT, frag);
    renderPipelineDescriptor.setVertexShaderModule(vs);
    renderPipelineDescriptor.setFragmentShaderModule(fs);
 
    _renderPipeline = device->newRenderPipeline(renderPipelineDescriptor);
    
    // render pass
    cocos2d::backend::RenderPassDescriptor renderPassDescriptor;
    renderPassDescriptor.setClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    renderPassDescriptor.setClearDepth(1.f);
    _renderPass = device->newRenderPass(renderPassDescriptor);
    
    // bind group
    _bindGroup.setUniform("model", _model.m, sizeof(_model.m));
    Mat4::createPerspective(60.0f, 1.0f * utils::WINDOW_WIDTH / utils::WINDOW_HEIGHT, 0.01f, 1000.0f, &_projection);
    _bindGroup.setUniform("projection", _projection.m, sizeof(_projection.m));
    float color[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    _bindGroup.setUniform("color", color, sizeof(color));

    // vertex buffer
    _vertexBuffer = device->newBuffer(sizeof(bunny_positions),
                                      cocos2d::backend::BufferType::VERTEX,
                                      cocos2d::backend::BufferUsage::READ);
    _vertexBuffer->updateData((void*)&bunny_positions[0][0], sizeof(bunny_positions));

    // index buffer
    _indexBuffer = device->newBuffer(sizeof(bunny_cells),
                                     cocos2d::backend::BufferType::INDEX,
                                     cocos2d::backend::BufferUsage::READ);
    _indexBuffer->updateData((void*)&bunny_cells[0], sizeof(bunny_cells));
    
    _commandBuffer = device->newCommandBuffer();
}

BunnyBackend::~BunnyBackend()
{
    CC_SAFE_RELEASE(_commandBuffer);
    CC_SAFE_RELEASE(_renderPass);
    CC_SAFE_RELEASE(_indexBuffer);
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_renderPipeline);
}

void BunnyBackend::tick(float dt)
{
    _time += dt;
    Mat4::createLookAt(Vec3(30.0f * std::cos(_time), 20.0f, 30.0f * std::sin(_time)), Vec3(0.0f, 2.5f, 0.0f), Vec3(0.0f, 1.0f, 0.f), &_view);
    _bindGroup.setUniform("view", _view.m, sizeof(_view.m));
    
    _commandBuffer->beginRenderPass(_renderPass);
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _commandBuffer->setRenderPipeline(_renderPipeline);
    _commandBuffer->setVertexBuffer(0, _vertexBuffer);
    _commandBuffer->setIndexBuffer(_indexBuffer);
    _commandBuffer->setBindGroup(&_bindGroup);
    _commandBuffer->drawElements(cocos2d::backend::PrimitiveType::TRIANGLE,
                                 cocos2d::backend::IndexFormat::U_SHORT,
                                 sizeof(bunny_cells) / sizeof(bunny_cells[0]));
    _commandBuffer->endRenderPass();
}

