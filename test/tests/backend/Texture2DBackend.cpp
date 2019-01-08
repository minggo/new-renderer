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

#include "Texture2DBackend.h"
#include "cocos2d.h"
#include "../Utils.h"
#include "backend/Device.h"
#include "backend/ProgramCache.h"

#include <vector>

using namespace cocos2d;
using namespace cocos2d::backend;


Texture2DBackendTest::Texture2DBackendTest()
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

    auto device = cocos2d::backend::Device::getInstance();
    {
        FontDefinition fontDef;
        fontDef._dimensions = Size(512, 512);
        fontDef._alignment = TextHAlignment::CENTER;
        fontDef._vertAlignment = TextVAlignment::CENTER;
        fontDef._fontSize = 32;

        int width = 0;
        int height = 0;
        bool hasPremulplyAlpha = false;
        Data labelData = cocos2d::Device::getTextureDataForText("use canvas element as texture, filled by rgb(199,237,204)", fontDef, cocos2d::Device::TextAlign::CENTER, width, height, hasPremulplyAlpha);
        assert(!labelData.isNull());

        TextureDescriptor canvasTexDes;
        canvasTexDes.width = width;
        canvasTexDes.height = height;
        canvasTexDes.textureType = TextureType::TEXTURE_2D;
        canvasTexDes.textureFormat = TextureFormat::R8G8B8A8;
        _canvasTexture = device->newTexture(canvasTexDes);
        _canvasTexture->updateData(labelData.getBytes());
    }

    {
        auto img = new cocos2d::Image();
        bool ret = img->initWithImageFile("assets/uv_checker_01.jpg");
        assert(ret);

        cocos2d::Data data;
        data.copy(img->getData(), img->getDataLen());

        TextureDescriptor texDes;
        texDes.width = img->getWidth();
        texDes.height = img->getHeight();
        texDes.textureFormat = TextureFormat::R8G8B8;
        texDes.textureType = TextureType::TEXTURE_2D;
        _texture = device->newTexture(texDes);
        _texture->updateData(data.getBytes());

        img->release();
    }

    float vertexBuf[] = {
        -1, -1,
        1, -1,
        1, 1,
        1, 1,
        -1, 1,
        -1, -1
    };
    _vertexBuffer = device->newBuffer(sizeof(vertexBuf), cocos2d::backend::BufferType::VERTEX, cocos2d::backend::BufferUsage::READ);
    _vertexBuffer->updateData(vertexBuf, sizeof(vertexBuf));
    
    // create render pipeline
    
    RenderPipelineDescriptor renderPipelineDescriptor;
    renderPipelineDescriptor.program = device->createProgram(vert, frag);
    _transformLocation = renderPipelineDescriptor.program->getVertexUniformLocation("transform");
    _colorLocation = renderPipelineDescriptor.program->getFragmentUniformLocation("color");
    _textureLocation = renderPipelineDescriptor.program->getFragmentUniformLocation("texture");
    
    VertexLayout vertexLayout;
    vertexLayout.setAtrribute("a_position", 0, cocos2d::backend::VertexFormat::FLOAT_R32G32, 0);
    vertexLayout.setLayout(2 * sizeof(float), cocos2d::backend::VertexStepMode::VERTEX);
    renderPipelineDescriptor.vertexLayouts.push_back(vertexLayout);
    _renderPipeline = device->newRenderPipeline(renderPipelineDescriptor);

    _transform0.translate(-0.5f, 0, 0);
    _transform0.scale(0.5f);
    _transform1.translate(0.5f, 0, 0);
    _transform1.scale(0.5f);
    
    // render pass
    _renderPassDescriptor.clearColorValue = {0.1f, 0.1f, 0.1f, 0.1f};
    _renderPassDescriptor.needClearColor = true;
    _renderPassDescriptor.needColorAttachment = true;
    
    _commandBuffer = device->newCommandBuffer();
}

Texture2DBackendTest::~Texture2DBackendTest()
{
    CC_SAFE_RELEASE(_renderPipeline);
    CC_SAFE_RELEASE(_commandBuffer);
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_canvasTexture);
    CC_SAFE_RELEASE(_texture);
}

void Texture2DBackendTest::tick(float dt)
{
    _commandBuffer->beginFrame();
    float color[4] = {1.f, 0.f, 0.f, 1.f};
    _renderPipeline->getProgram()->setFragmentUniform(_colorLocation, color, sizeof(color));
    if (_canvasTexture)
    {
        _renderPassDescriptor.needClearColor = true;
        _commandBuffer->beginRenderPass(_renderPassDescriptor);
        _commandBuffer->setRenderPipeline(_renderPipeline);
        _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        _renderPipeline->getProgram()->setVertexUniform(_transformLocation, _transform0.m, sizeof(_transform0.m));
        _renderPipeline->getProgram()->setFragmentTexture(_textureLocation, 0, _canvasTexture);
        
        _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 6);
        _commandBuffer->endRenderPass();
    }
    
    if (_texture)
    {
        _renderPassDescriptor.needClearColor = false;
        _commandBuffer->beginRenderPass(_renderPassDescriptor);
        _commandBuffer->setRenderPipeline(_renderPipeline);
        _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
        _commandBuffer->setVertexBuffer(0, _vertexBuffer);
        
        _renderPipeline->getProgram()->setVertexUniform(_transformLocation, _transform1.m, sizeof(_transform1.m));
        _renderPipeline->getProgram()->setFragmentTexture(_textureLocation, 0, _texture);
        
        _commandBuffer->drawArrays(cocos2d::backend::PrimitiveType::TRIANGLE, 0, 6);
        _commandBuffer->endRenderPass();
    }
    _commandBuffer->endFrame();
}




