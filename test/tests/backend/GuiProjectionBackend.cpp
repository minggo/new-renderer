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

#include "GuiProjectionBackend.h"
#include "../Utils.h"

#include <vector>

using namespace cocos2d;

static const uint32_t _spriteWidth = 128;
static const uint32_t _spriteHeight = 128;


GuiProjectionBackend::GuiProjectionBackend()
{
    const char* vert = R"(
#ifdef GL_ES
    precision highp float;
#endif
    uniform mat4 projection;
    uniform mat4 transform;
    attribute vec2 a_position;
    attribute vec2 a_uv;
    varying vec2 v_uv;

    void main () {
        gl_Position = projection * transform * vec4(a_position, 0, 1);
        v_uv = a_uv;
    }
    )";

    const char* frag = R"(
#ifdef GL_ES
    precision highp float;
#endif
    uniform sampler2D texture;
    uniform vec4 color;
    varying vec2 v_uv;

    void main () {
        gl_FragColor = color * texture2D(texture, v_uv);
    }
    )";

    auto device = backend::Device::getInstance();
    backend::RenderPipelineDescriptor renderPipelineDescriptor;
    auto vs = device->cacheShaderModule(backend::ShaderStage::VERTEX, vert);
    auto fs = device->cacheShaderModule(backend::ShaderStage::FRAGMENT, frag);
    renderPipelineDescriptor.setVertexShaderModule(vs);
    renderPipelineDescriptor.setFragmentShaderModule(fs);
    
#define VERTEX_POSITION_SIZE 2
#define VERTEX_UV_SIZE 2
    
    uint32_t uvOffset = VERTEX_POSITION_SIZE*sizeof(float);
    uint32_t totalOffset = (VERTEX_POSITION_SIZE + VERTEX_UV_SIZE)*sizeof(float);
    backend::VertexLayout vertexLayout;
    vertexLayout.setAtrribute("a_position", 0, backend::VertexFormat::FLOAT_R32G32, 0);
    vertexLayout.setAtrribute("a_uv", 1, backend::VertexFormat::FLOAT_R32G32, uvOffset);
    vertexLayout.setLayout(totalOffset, backend::VertexStepMode::VERTEX);
    renderPipelineDescriptor.setVertexLayout(0, vertexLayout);
    
    _renderPipeline = device->cacheRenderPipeline(renderPipelineDescriptor);
    _commandBuffer = device->newCommandBuffer();
    
    auto img = new cocos2d::Image();
    bool ret = img->initWithImageFile("assets/uv_checker_02.jpg");
    assert(ret);

    cocos2d::Data data;
    data.copy(img->getData(), img->getDataLen());

    backend::TextureDescriptor textureDescriptor;
    textureDescriptor.textureFormat = backend::TextureFormat::R8G8B8;
    textureDescriptor.width = img->getWidth();
    textureDescriptor.height = img->getHeight();
    _texture = device->newTexture(textureDescriptor);
    _texture->updateData(data.getBytes());

    img->release();

    float vertexBuf[][4] = {
        0,            _spriteHeight,   0, 0,
        0,                        0,   0, 1,
        _spriteWidth,             0,   1, 1,
        0,            _spriteHeight,   0, 0,
        _spriteWidth,             0,   1, 1,
        _spriteWidth, _spriteHeight,   1, 0
    };
    uint32_t vertexBufSize = sizeof(vertexBuf);
    _vertexBufferElementCount = 6;
    _vertexBuffer = device->newBuffer(vertexBufSize, backend::BufferType::VERTEX, backend::BufferUsage::READ);
    _vertexBuffer->updateData(vertexBuf, vertexBufSize);
    
    Mat4::createOrthographicOffCenter(0.0f, utils::WINDOW_WIDTH, 0.0f, utils::WINDOW_HEIGHT, -100.0f, 100.0f, &_projection);
    _translantion.translate(10.0f, (utils::WINDOW_HEIGHT - _spriteHeight) / 2.0f, 0.0f);

    _rotation.translate(10 + _spriteWidth * 2.0f, (utils::WINDOW_HEIGHT - _spriteHeight) / 2.0f, 0);
    _rotation.rotateZ(CC_DEGREES_TO_RADIANS(15));

    _scale.translate(10 + _spriteWidth * 4.0f, (utils::WINDOW_HEIGHT - _spriteHeight) / 2.0f, 0);
    _scale.scale(1.2f, 0.5f, 1.0f);
    
    backend::RenderPassDescriptor renderPassDescriptor;
    renderPassDescriptor.setClearColor(0.1f, 0.1f, 0.1f, 1.f);
    renderPassDescriptor.setClearDepth(1);
    _renderPass = device->cacheRenderPass(renderPassDescriptor);
}

GuiProjectionBackend::~GuiProjectionBackend()
{
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_commandBuffer);
    CC_SAFE_RELEASE(_renderPipeline);
    CC_SAFE_RELEASE(_renderPass);
}

void GuiProjectionBackend::tick(float dt)
{
    _commandBuffer->beginRenderPass(_renderPass);
    _commandBuffer->setRenderPipeline(_renderPipeline);
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    
    if (_texture) {
        _bindGroup.setTexture("texture", 0, _texture);
        
        // translation
        _commandBuffer->setCullMode(backend::CullMode::NONE);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        float redColor[4] = {1, 0, 0, 1};
        _bindGroup.setUniform("color", redColor, sizeof(redColor));
        _bindGroup.setUniform("projection", _projection.m, sizeof(_projection.m));
        _bindGroup.setUniform("transform", _translantion.m, sizeof(_translantion.m));
        
        _commandBuffer->setBindGroup(&_bindGroup);
        _commandBuffer->drawArrays(backend::PrimitiveType::TRIANGLE, 0, _vertexBufferElementCount);
        
        // rotation
        _commandBuffer->setRenderPipeline(_renderPipeline);
        _commandBuffer->setCullMode(backend::CullMode::NONE);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        float greenColor[4] = {0, 1, 0, 1};
        _bindGroup.setUniform("color", greenColor, sizeof(greenColor));
        _bindGroup.setUniform("projection", _projection.m, sizeof(_projection.m));
        _bindGroup.setUniform("transform", _rotation.m, sizeof(_rotation.m));
        
        _commandBuffer->setBindGroup(&_bindGroup);
        _commandBuffer->drawArrays(backend::PrimitiveType::TRIANGLE, 0, _vertexBufferElementCount);
       

        // scale
        _commandBuffer->setRenderPipeline(_renderPipeline);
        _commandBuffer->setCullMode(backend::CullMode::NONE);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        float blueColor[4] = {0, 0, 1, 1};
        _bindGroup.setUniform("color", blueColor, sizeof(blueColor));
        _bindGroup.setUniform("projection", _projection.m, sizeof(_projection.m));
        _bindGroup.setUniform("transform", _scale.m, sizeof(_scale.m));
        
        _commandBuffer->setBindGroup(&_bindGroup);
        _commandBuffer->drawArrays(backend::PrimitiveType::TRIANGLE, 0, _vertexBufferElementCount);
    }
    
    _commandBuffer->endRenderPass();
}





