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

#include "StencilBackend.h"
#include "cocos2d.h"
#include "../Utils.h"
#include "backend/Program.h"

#include <vector>

using namespace cocos2d;

StencilBackend::StencilBackend()
{
    const char* vert = R"(
#ifdef GL_ES
    precision highp float;
#endif
    uniform mat4 transform;
    attribute vec2 a_position;
    varying vec2 v_texcoord;
    void main () {
        gl_Position = transform * vec4(a_position, 0, 1);
        v_texcoord = a_position * 0.5 + 0.5;
        v_texcoord = vec2(v_texcoord.x, 1.0 - v_texcoord.y);
    }
    )";

    const char* frag = R"(
#ifdef GL_ES
    precision highp float;
#endif
    uniform sampler2D texture;
    uniform vec4 color;
    varying vec2 v_texcoord;
    void main () {
        gl_FragColor = texture2D(texture, v_texcoord);
    }
    )";

    auto device = backend::Device::getInstance();
    
    FontDefinition fontDef;
    fontDef._dimensions = Size(512, 512);
    fontDef._alignment = TextHAlignment::CENTER;
    fontDef._vertAlignment = TextVAlignment::CENTER;
    fontDef._fontSize = 64;
    int width = 0;
    int height = 0;
    bool hasPremulplyAlpha = false;
    Data labelData = Device::getTextureDataForText("Stencil Element", fontDef, Device::TextAlign::CENTER, width, height, hasPremulplyAlpha);
    assert(!labelData.isNull());
    backend::TextureDescriptor textureDescriptor;
    textureDescriptor.width = width;
    textureDescriptor.height = height;
    textureDescriptor.textureFormat = backend::TextureFormat::R8G8B8A8;
    _canvasTexture = device->newTexture(textureDescriptor);
    _canvasTexture->updateData(labelData.getBytes());

    auto img = new cocos2d::Image();
    bool ret = img->initWithImageFile("assets/uv_checker_02.jpg");
    assert(ret);
    backend::TextureDescriptor textureDescriptor2;
    textureDescriptor2.width = img->getWidth();
    textureDescriptor2.height = img->getHeight();
    textureDescriptor2.textureFormat = backend::TextureFormat::R8G8B8;
    _texture = device->newTexture(textureDescriptor2);
    _texture->updateData(img->getData());
    img->release();
    
    backend::RenderPipelineDescriptor renderPipelineDescriptor;
    renderPipelineDescriptor.stencilAttachmentFormat = backend::TextureFormat::D24S8;
    renderPipelineDescriptor.colorAttachmentsFormat[0] = backend::TextureFormat::SYSTEM_DEFAULT;
    auto vs = device->createShaderModule(cocos2d::backend::ShaderStage::VERTEX, vert);
    auto fs = device->createShaderModule(cocos2d::backend::ShaderStage::FRAGMENT, frag);
    renderPipelineDescriptor.program = device->createProgram(vs, fs);
    _transformLocation = renderPipelineDescriptor.program->getVertexUniformLocation("transform");
    _colorLocation = renderPipelineDescriptor.program->getFragmentUniformLocation("color");
    _textureLocation = renderPipelineDescriptor.program->getFragmentUniformLocation("texture");

    backend::VertexLayout vertexLayout;
    vertexLayout.setAtrribute("a_position", 0, cocos2d::backend::VertexFormat::FLOAT_R32G32, 0);
    vertexLayout.setLayout(2 * sizeof(float), cocos2d::backend::VertexStepMode::VERTEX);
    renderPipelineDescriptor.vertexLayouts.push_back(vertexLayout);
    _renderPipeline = device->newRenderPipeline(renderPipelineDescriptor);
    
    backend::DepthStencilDescriptor depthStencilDescriptor;
    depthStencilDescriptor.stencilTestEnabled = true;
    depthStencilDescriptor.backFaceStencil.stencilCompareFunction = backend::CompareFunction::NEVER;
    depthStencilDescriptor.backFaceStencil.readMask = 0xFF;
    depthStencilDescriptor.backFaceStencil.writeMask = 0xFF;
    depthStencilDescriptor.backFaceStencil.stencilFailureOperation = backend::StencilOperation::REPLACE;
    depthStencilDescriptor.backFaceStencil.depthFailureOperation = backend::StencilOperation::KEEP;
    depthStencilDescriptor.backFaceStencil.depthStencilPassOperation = backend::StencilOperation::KEEP;
    depthStencilDescriptor.frontFaceStencil = depthStencilDescriptor.backFaceStencil;
    auto depthStencilState = device->createDepthStencilState(depthStencilDescriptor);
    renderPipelineDescriptor.depthStencilState = depthStencilState;
    _renderPipelineCavasTexture = device->newRenderPipeline(renderPipelineDescriptor);
    
    depthStencilDescriptor.backFaceStencil.stencilCompareFunction = backend::CompareFunction::EQUAL;
    depthStencilDescriptor.backFaceStencil.stencilFailureOperation = backend::StencilOperation::KEEP;
    depthStencilDescriptor.frontFaceStencil = depthStencilDescriptor.backFaceStencil;
    depthStencilState = device->createDepthStencilState(depthStencilDescriptor);
    renderPipelineDescriptor.depthStencilState = depthStencilState;
    _renderPipelineTextureBackAndFront = device->newRenderPipeline(renderPipelineDescriptor);
    
    depthStencilDescriptor.frontFaceStencil.stencilCompareFunction = backend::CompareFunction::ALWAYS;
    depthStencilState = device->createDepthStencilState(depthStencilDescriptor);
    renderPipelineDescriptor.depthStencilState = depthStencilState;
    _renderPipelineTextureBack = device->newRenderPipeline(renderPipelineDescriptor);
    
    depthStencilDescriptor.frontFaceStencil.stencilCompareFunction = backend::CompareFunction::EQUAL;
    depthStencilDescriptor.backFaceStencil.stencilCompareFunction = backend::CompareFunction::ALWAYS;
    depthStencilState = device->createDepthStencilState(depthStencilDescriptor);
    renderPipelineDescriptor.depthStencilState = depthStencilState;
    _renderPipelineTextureFront = device->newRenderPipeline(renderPipelineDescriptor);
    
    _renderPassDescriptor.clearColorValue = {1.0f, 0.1f, 0.1f, 1.f};
    _renderPassDescriptor.needClearColor = true;
    _renderPassDescriptor.needColorAttachment = true;
    _renderPassDescriptor.needStencilAttachment = true;

    float vertexBuf[][2] = {
        {-1, -1},
        {1, -1},
        {1, 1},
        {1, 1},
        {-1, -1},
        {-1, 1}
    };
    _vertexBuffer = device->newBuffer(sizeof(vertexBuf), cocos2d::backend::BufferType::VERTEX, cocos2d::backend::BufferUsage::READ);
    _vertexBuffer->updateData(vertexBuf, sizeof(vertexBuf));
    
    _commandBuffer = device->newCommandBuffer();

    _transform0.scale(0.5f);
    _transform0.rotateZ(utils::PI / 4);

    _transform1.scale(0.5f, 0.5f, 0.25f);
}

StencilBackend::~StencilBackend()
{
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_canvasTexture);
    CC_SAFE_RELEASE(_renderPipeline);
    CC_SAFE_RELEASE(_commandBuffer);
    CC_SAFE_RELEASE(_renderPipelineCavasTexture);
    CC_SAFE_RELEASE(_renderPipelineTextureBackAndFront);
    CC_SAFE_RELEASE(_renderPipelineTextureBack);
    CC_SAFE_RELEASE(_renderPipelineTextureFront);
}

void StencilBackend::tick(float dt)
{
    _commandBuffer->beginFrame();
    
    float color[4] = {1, 0, 0, 1};
    
    // draw stencil and image
    if (_canvasTexture)
    {
        _renderPassDescriptor.needClearColor = true;
        _commandBuffer->beginRenderPass(_renderPassDescriptor);
        _commandBuffer->setViewport(utils::WINDOW_WIDTH / 6, utils::WINDOW_HEIGHT / 2, utils::WINDOW_WIDTH / 3, utils::WINDOW_HEIGHT / 2);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        _commandBuffer->setCullMode(backend::CullMode::NONE);
        _commandBuffer->setRenderPipeline(_renderPipeline);
        
        
        _renderPipeline->getProgram()->setFragmentUniform(_colorLocation, color, sizeof(color));
        _renderPipeline->getProgram()->setVertexUniform(_transformLocation, _transform0.m, sizeof(_transform0.m));
        _renderPipeline->getProgram()->setFragmentTexture(_textureLocation, 0, _canvasTexture);
        
        _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 6);
        
        _commandBuffer->endRenderPass();
    }
    
    if (_texture)
    {
        _renderPassDescriptor.needClearColor = false;
        _renderPassDescriptor.needClearStencil = false;
        _commandBuffer->beginRenderPass(_renderPassDescriptor);

        _commandBuffer->setViewport(utils::WINDOW_WIDTH / 2, utils::WINDOW_HEIGHT / 2, utils::WINDOW_WIDTH / 3, utils::WINDOW_HEIGHT / 2);
        _commandBuffer->setRenderPipeline(_renderPipeline);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        _commandBuffer->setCullMode(backend::CullMode::NONE);

        _renderPipeline->getProgram()->setFragmentTexture(_textureLocation, 0, _texture);
        _renderPipeline->getProgram()->setVertexUniform(_transformLocation, _transform1.m, sizeof(_transform1.m));
        
        _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 6);
        _commandBuffer->endRenderPass();
    }
    
    // back and front
    
    if (_canvasTexture)
    {
        _commandBuffer->beginRenderPass(_renderPassDescriptor);

        _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH / 3, utils::WINDOW_HEIGHT / 2);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        _commandBuffer->setCullMode(backend::CullMode::NONE);
        _commandBuffer->setStencilReferenceValue(0x1);
        _commandBuffer->setRenderPipeline(_renderPipelineCavasTexture);

        _renderPipeline->getProgram()->setVertexUniform(_transformLocation, _transform0.m, sizeof(_transform0.m));
        _renderPipeline->getProgram()->setFragmentTexture(_textureLocation, 0, _canvasTexture);
        _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 6);
        _commandBuffer->endRenderPass();
    }
    if (_texture)
    {
        _commandBuffer->beginRenderPass(_renderPassDescriptor);
        _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH / 3, utils::WINDOW_HEIGHT / 2);
        _commandBuffer->setStencilReferenceValue(0x1);
        _commandBuffer->setRenderPipeline(_renderPipelineTextureBackAndFront);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        _commandBuffer->setCullMode(backend::CullMode::NONE);

        _renderPipeline->getProgram()->setFragmentTexture(_textureLocation, 0, _texture);
        _renderPipeline->getProgram()->setVertexUniform(_transformLocation, _transform1.m, sizeof(_transform1.m));
       
        _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 6);
        _commandBuffer->endRenderPass();
    }

    // back

    if (_canvasTexture)
    {
        _commandBuffer->beginRenderPass(_renderPassDescriptor);
        _commandBuffer->setViewport(utils::WINDOW_WIDTH / 3, 0, utils::WINDOW_WIDTH / 3, utils::WINDOW_HEIGHT / 2);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        _commandBuffer->setCullMode(backend::CullMode::NONE);
        _commandBuffer->setStencilReferenceValue(0x1);
        _commandBuffer->setRenderPipeline(_renderPipelineCavasTexture);

        _renderPipeline->getProgram()->setVertexUniform(_transformLocation, _transform0.m, sizeof(_transform0.m));
        _renderPipeline->getProgram()->setFragmentTexture(_textureLocation, 0, _canvasTexture);
        _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 6);
        _commandBuffer->endRenderPass();
    }
    if (_texture)
    {
        _commandBuffer->beginRenderPass(_renderPassDescriptor);
        _commandBuffer->setViewport(utils::WINDOW_WIDTH / 3, 0, utils::WINDOW_WIDTH / 3, utils::WINDOW_HEIGHT / 2);
        _commandBuffer->setRenderPipeline(_renderPipelineTextureBack);
        _commandBuffer->setStencilReferenceValue(0x1);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        _commandBuffer->setCullMode(backend::CullMode::NONE);

        _renderPipeline->getProgram()->setFragmentTexture(_textureLocation, 0, _texture);
        _renderPipeline->getProgram()->setVertexUniform(_transformLocation, _transform1.m, sizeof(_transform1.m));
        
        _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 6);
        _commandBuffer->endRenderPass();
    }

    // front
    if (_canvasTexture)
    {
        _commandBuffer->beginRenderPass(_renderPassDescriptor);
        _commandBuffer->setViewport(utils::WINDOW_WIDTH * 2 / 3, 0, utils::WINDOW_WIDTH / 3, utils::WINDOW_HEIGHT / 2);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        _commandBuffer->setCullMode(backend::CullMode::NONE);
        _commandBuffer->setStencilReferenceValue(0x1);
        _commandBuffer->setRenderPipeline(_renderPipelineCavasTexture);

        _renderPipeline->getProgram()->setVertexUniform(_transformLocation, _transform0.m, sizeof(_transform0.m));
        _renderPipeline->getProgram()->setFragmentTexture(_textureLocation, 0, _canvasTexture);
        _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 6);
        _commandBuffer->endRenderPass();
    }
    if (_texture)
    {
        _commandBuffer->beginRenderPass(_renderPassDescriptor);
        _commandBuffer->setViewport(utils::WINDOW_WIDTH * 2 / 3, 0, utils::WINDOW_WIDTH / 3, utils::WINDOW_HEIGHT / 2);
        _commandBuffer->setRenderPipeline(_renderPipelineTextureFront);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        _commandBuffer->setStencilReferenceValue(0x1);
        _commandBuffer->setCullMode(backend::CullMode::NONE);

        _renderPipeline->getProgram()->setFragmentTexture(_textureLocation, 0, _texture);
        _renderPipeline->getProgram()->setVertexUniform(_transformLocation, _transform1.m, sizeof(_transform1.m));

        _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 6);
        _commandBuffer->endRenderPass();
    }
    
    _commandBuffer->endFrame();
}
