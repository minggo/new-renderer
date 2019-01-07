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

#include "SubImageBackend.h"
#include "cocos2d.h"
#include "../Utils.h"

#include <vector>

using namespace cocos2d;

SubImageBackend::SubImageBackend()
{
    const char* vert = R"(
#ifdef GL_ES
    precision highp float;
#endif
    attribute vec2 a_position;
    varying vec2 v_texcoord;
    void main () {
        gl_Position = vec4(a_position, 0, 1);
        v_texcoord = a_position * 0.5 + 0.5;
    }
    )";

    const char* frag = R"(
#ifdef GL_ES
    precision highp float;
#endif
    uniform sampler2D texture;
    varying vec2 v_texcoord;
    void main () {
        gl_FragColor = texture2D(texture, v_texcoord);
    }
    )";

    auto device = backend::Device::getInstance();
    
    backend::RenderPipelineDescriptor renderPipelineDescriptor;
    renderPipelineDescriptor.program = backend::ProgramCache::getInstance()->newProgram(vert, frag);
    _textureLocation = renderPipelineDescriptor.program->getFragmentUniformLocation("texture");
    
    backend::VertexLayout vertexLayout;
    vertexLayout.setAtrribute("a_position", 0, backend::VertexFormat::FLOAT_R32G32, 0);
    vertexLayout.setLayout(2 * sizeof(float), backend::VertexStepMode::VERTEX);
    renderPipelineDescriptor.vertexLayouts.push_back(vertexLayout);
    _renderPipeline = device->newRenderPipeline(renderPipelineDescriptor);

    backend::TextureDescriptor textureDescriptor;
    textureDescriptor.width = 128;
    textureDescriptor.height = 128;
    textureDescriptor.textureFormat = backend::TextureFormat::R8G8B8;
    textureDescriptor.samplerDescriptor.sAddressMode = backend::SamplerAddressMode::CLAMP_TO_EDGE;
    textureDescriptor.samplerDescriptor.tAddressMode = backend::SamplerAddressMode::CLAMP_TO_EDGE;
    textureDescriptor.samplerDescriptor.minFilter = backend::SamplerFilter::NEAREST;
    textureDescriptor.samplerDescriptor.magFilter = backend::SamplerFilter::NEAREST;
    _texture = device->newTexture(textureDescriptor);

    _commandBuffer = device->newCommandBuffer();
    
    _renderPassDescriptor.needClearColor = true;
    
    float vertexBuf[][2] = {
        {-1, -1},
        {1, -1},
        {1, 1},
        {1, 1},
        {-1, 1},
        {-1, -1}
    };
    _vertexBuffer = device->newBuffer(sizeof(vertexBuf), backend::BufferType::VERTEX, backend::BufferUsage::READ);
    _vertexBuffer->updateData(vertexBuf, sizeof(vertexBuf));

    _dataSize = _texture->getWidth() * _texture->getHeight() * 3;
    _data = (uint8_t*)malloc(_dataSize);
    memset(_data, 0, _dataSize);
    _updatePixelIndex = 0;
}

SubImageBackend::~SubImageBackend()
{
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_commandBuffer);
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_renderPipeline);
    free(_data);
}

void SubImageBackend::tick(float dt)
{
    _commandBuffer->beginFrame();
    
    _commandBuffer->beginRenderPass(_renderPassDescriptor);
    _commandBuffer->setRenderPipeline(_renderPipeline);
    
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);

    for (size_t i = 0; i < _updatePixelIndex; ++i) {
        _data[3 * i] =  cocos2d::random(0, 255);
        _data[3 * i + 1] = cocos2d::random(0, 255);
        _data[3 * i + 2] = cocos2d::random(0, 255);
    }
    _texture->updateSubData(0,
                            0,
                            _texture->getWidth(),
                            _texture->getHeight(),
                            _data);


    _commandBuffer->setVertexBuffer(0, _vertexBuffer);
    _renderPipeline->getProgram()->setFragmentTexture(_textureLocation, 0, _texture);
    
    _commandBuffer->drawArrays(backend::PrimitiveType::TRIANGLE, 0, 6);
    _commandBuffer->endRenderPass();

    if (_updatePixelIndex < _texture->getWidth() * _texture->getHeight() ) {
        _updatePixelIndex += 1;
    }
    
    _commandBuffer->endFrame();
}



