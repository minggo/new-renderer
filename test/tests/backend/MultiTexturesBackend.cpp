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

#include "MultiTexturesBackend.h"
#include "base/ccTypes.h"
#include "../Utils.h"

using namespace cocos2d;

MultiTexturesBackend::MultiTexturesBackend()
{
    // program
    const char* vert = R"(
#ifdef GL_ES
        precision highp float;
#endif
        uniform mat4 transform;
        attribute vec2 a_position;
        varying vec2 v_texcoord;
        void main ()
        {
            gl_Position = transform * vec4(a_position, 0, 1);
            v_texcoord = a_position * 0.5 + 0.5;
        }
    )";
    
    const char* frag = R"(
#ifdef GL_ES
        precision highp float;
#endif
        uniform sampler2D texture[2];
        uniform vec4 color;
        varying vec2 v_texcoord;
        void main ()
        {
            gl_FragColor = texture2D(texture[0], v_texcoord) * v_texcoord.x + texture2D(texture[1], v_texcoord) * (1.0 - v_texcoord.x);
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
    
    _renderPipeline = device->newRenderPipeline(renderPipelineDescriptor);

    float vertices[] = {-1, -1, 1, -1, 1, 1, 1, 1, -1, 1, -1, -1};
    _vertexBuffer = device->newBuffer(sizeof(vertices),
                                         cocos2d::backend::BufferType::VERTEX,
                                         cocos2d::backend::BufferUsage::READ);
    _vertexBuffer->updateData(vertices, sizeof(vertices));
    
    // textures

    backend::TextureDescriptor textureDescriptor1;
    textureDescriptor1.width = 1024;
    textureDescriptor1.height = 1024;
    textureDescriptor1.textureFormat = backend::TextureFormat::R8G8B8;
    _texture1 = device->newTexture(textureDescriptor1);
    _texture1->updateData(utils::loadData("assets/uv_checker_01.jpg").getBytes());
    
    int dataSize = 512 * 512 * 3;
    uint8_t data[dataSize];
    for (int i = 0; i < dataSize; i += 3)
    {
        data[i] = 199;
        data[i + 1] = 237;
        data[i + 2] = 204;
    }
    backend::TextureDescriptor textureDescriptor2;
    textureDescriptor2.width = 512;
    textureDescriptor2.height = 512;
    textureDescriptor2.textureFormat = backend::TextureFormat::R8G8B8;
    _background = device->newTexture(textureDescriptor2);
    _background->updateData(data);
    
    _transform = cocos2d::Mat4::IDENTITY;
    _transform.translate(0, 0, 0);
    _transform.scale(0.5, 0.5, 0.5);
    
    _commandBuffer = device->newCommandBuffer();
    
    backend::RenderPassDescriptor renderPassDescriptor;
    renderPassDescriptor.setClearColor(0.1f, 0.1f, 0.1f, 1.f);
    renderPassDescriptor.setDepthClearValue(1);
    _renderPass = device->newRenderPass(renderPassDescriptor);
}

MultiTexturesBackend::~MultiTexturesBackend()
{
    CC_SAFE_RELEASE(_renderPipeline);
    CC_SAFE_RELEASE(_commandBuffer);
    CC_SAFE_RELEASE(_texture1);
    CC_SAFE_RELEASE(_background);
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_renderPass);
}

void MultiTexturesBackend::tick(float dt)
{
    _commandBuffer->beginRenderPass(_renderPass);
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    _commandBuffer->setRenderPipeline(_renderPipeline);
    _commandBuffer->setVertexBuffer(0, _vertexBuffer);
    
    float color[4] = {1.f, 0, 0, 1.f};
    _bindGroup.setUniform("color", color, sizeof(color));
    _bindGroup.setUniform("transform", _transform.m, sizeof(_transform.m));
    _bindGroup.setTextureArray("texture", {6, 7}, {_background, _texture1});
    _commandBuffer->setBindGroup(&_bindGroup);
    
    _commandBuffer->setVertexBuffer(0, _vertexBuffer);
    _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 6);
}
