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


//        Texture::Options options;
//        options.width = width;
//        options.height = height;
//        options.images.push_back(std::move(labelData));
//        _canvasTexture = new renderer::Texture2D();
//        _canvasTexture->init(_device, options);
    backend::TextureDescriptor textureDescriptor;
    textureDescriptor.width = width;
    textureDescriptor.height = height;
    textureDescriptor.textureFormat = backend::TextureFormat::R8G8B8A8;
    _canvasTexture = device->createTexture(textureDescriptor);
    _canvasTexture->retain();

    auto img = new cocos2d::Image();
    bool ret = img->initWithImageFile("assets/uv_checker_02.jpg");
    assert(ret);


//    Texture::Options options;
//    options.images.push_back(std::move(data));
//    options.width = img->getWidth();
//    options.height = img->getHeight();
//    options.format = Texture::Format::RGB8;
    backend::TextureDescriptor textureDescriptor2;
    textureDescriptor2.width = img->getWidth();
    textureDescriptor2.height = img->getHeight();
    textureDescriptor2.textureFormat = backend::TextureFormat::R8G8B8;
    _texture = device->createTexture(textureDescriptor2);
    _texture->retain();

    img->release();
    
    backend::RenderPipelineDescriptor renderPipelineDescriptor;
    auto vs = device->createShaderModule(cocos2d::backend::ShaderStage::VERTEX, vert);
    auto fs = device->createShaderModule(cocos2d::backend::ShaderStage::FRAGMENT, frag);
    renderPipelineDescriptor.setVertexShaderModule(vs);
    renderPipelineDescriptor.setFragmentShaderModule(fs);
    
    backend::VertexLayout vertexLayout;
    vertexLayout.setAtrribute("a_position", 0, cocos2d::backend::VertexFormat::FLOAT_R32G32, 0);
    vertexLayout.setLayout(2 * sizeof(float), cocos2d::backend::VertexStepMode::VERTEX);
    renderPipelineDescriptor.setVertexLayout(0, vertexLayout);
    
    _renderPipeline = device->createRenderPipeline(renderPipelineDescriptor);
    _renderPipeline->retain();
    
    backend::RenderPassDescriptor renderPassDescriptor;
    renderPassDescriptor.setColorAttachmentsClearColor(1.0f, 0.1f, 0.1f, 1.f);
    renderPassDescriptor.setDepthStencilAttachment(nullptr, cocos2d::backend::LoadOp::CLEAR, cocos2d::backend::LoadOp::LOAD);
    renderPassDescriptor.setDepthStencilAttachmentClearValue(1, 0);
    _renderPass = device->createRenderPass(renderPassDescriptor);
    _renderPass->retain();


//    VertexFormat vertexFmt({
//        { ATTRIB_NAME_POSITION, AttribType::FLOAT32, 2},
//    });

    float vertexBuf[][2] = {
        {-1, -1},
        {1, -1},
        {1, 1},
        {1, 1},
        {-1, -1},
        {-1, 1}
    };
//
//    _vertexBuffer = new VertexBuffer();
//    _vertexBuffer->init(_device,
//                        vertexFmt,
//                        Usage::DYNAMIC,
//                        &vertexBuf[0][0],
//                        sizeof(vertexBuf),
//                        sizeof(vertexBuf)/sizeof(vertexBuf[0]));
    _vertexBuffer = device->createBuffer(sizeof(vertexBuf), cocos2d::backend::BufferType::VERTEX, cocos2d::backend::BufferUsage::READ);
    _vertexBuffer->updateData(_vertexBuffer, sizeof(vertexBuf));
    _vertexBuffer->retain();

    _transform0.scale(0.5f);
    _transform0.rotateZ(utils::PI / 4);

    _transform1.scale(0.5f, 0.5f, 0.25f);
}

StencilBackend::~StencilBackend()
{
    RENDERER_SAFE_RELEASE(_vertexBuffer);
    RENDERER_SAFE_RELEASE(_program);
    RENDERER_SAFE_RELEASE(_texture);
    RENDERER_SAFE_RELEASE(_canvasTexture);
}

void StencilBackend::tick(float dt)
{
    _device->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    Color4F color(1.f, 0.1f, 0.1f, 1.f);
    _device->clear(ClearFlag::COLOR | ClearFlag::DEPTH, &color, 1.0, 0);

    // draw stencil and image
    _device->setViewport(utils::WINDOW_WIDTH / 6, utils::WINDOW_HEIGHT / 2, utils::WINDOW_WIDTH / 3, utils::WINDOW_HEIGHT / 2);
    if (_canvasTexture) {
        _device->setVertexBuffer(0, _vertexBuffer);
        _device->setUniformf("color", 1, 0, 0, 1);
        _device->setTexture("texture", _canvasTexture, 0);
        _device->setUniformMat4("transform", _transform0);
        _device->setProgram(_program);
        _device->setCullMode(renderer::CullMode::NONE);
        _device->draw(0, _vertexBuffer->getCount());
    }

    _device->setViewport(utils::WINDOW_WIDTH / 2, utils::WINDOW_HEIGHT / 2, utils::WINDOW_WIDTH / 3, utils::WINDOW_HEIGHT / 2);
    if (_texture) {
        _device->setVertexBuffer(0, _vertexBuffer);
        _device->setUniformf("color", 1, 0, 0, 1);
        _device->setTexture("texture", _texture, 0);
        _device->setUniformMat4("transform", _transform1);
        _device->setProgram(_program);
        _device->setCullMode(renderer::CullMode::NONE);
        _device->draw(0, _vertexBuffer->getCount());
    }

    // back and front
    _device->setViewport(0, 0, utils::WINDOW_WIDTH / 3, utils::WINDOW_HEIGHT / 2);
    if (_canvasTexture) {
        _device->setVertexBuffer(0, _vertexBuffer);
        _device->setUniformf("color", 1, 0, 0, 1);
        _device->setTexture("texture", _canvasTexture, 0);
        _device->setUniformMat4("transform", _transform0);
        _device->setProgram(_program);
        _device->setCullMode(renderer::CullMode::NONE);
        _device->enableStencilTest();
        _device->setStencilFunc(StencilFunc::NEVER, 0x1, 0xFF);
        _device->setStencilOp(StencilOp::REPLACE, StencilOp::KEEP, StencilOp::KEEP, 0xFF);
        _device->draw(0, _vertexBuffer->getCount());
    }
    if (_texture) {
        _device->setVertexBuffer(0, _vertexBuffer);
        _device->setUniformf("color", 1, 0, 0, 1);
        _device->setTexture("texture", _texture, 0);
        _device->setUniformMat4("transform", _transform1);
        _device->setProgram(_program);
        _device->setCullMode(renderer::CullMode::NONE);
        _device->enableStencilTest();
        _device->setStencilFunc(StencilFunc::EQUAL, 0x1, 0xFF);
        _device->setStencilOp(StencilOp::KEEP, StencilOp::KEEP, StencilOp::KEEP, 0xFF);
        _device->draw(0, _vertexBuffer->getCount());
    }

    // back
    _device->setViewport(utils::WINDOW_WIDTH / 3, 0, utils::WINDOW_WIDTH / 3, utils::WINDOW_HEIGHT / 2);
    if (_canvasTexture) {
        _device->setVertexBuffer(0, _vertexBuffer);
        _device->setUniformf("color", 1, 0, 0, 1);
        _device->setTexture("texture", _canvasTexture, 0);
        _device->setUniformMat4("transform", _transform0);
        _device->setProgram(_program);
        _device->setCullMode(renderer::CullMode::NONE);
        _device->enableStencilTest();
        _device->setStencilFunc(StencilFunc::NEVER, 0x1, 0xFF);
        _device->setStencilOp(StencilOp::REPLACE, StencilOp::KEEP, StencilOp::KEEP, 0xFF);
        _device->draw(0, _vertexBuffer->getCount());
    }
    if (_texture) {
        _device->setVertexBuffer(0, _vertexBuffer);
        _device->setUniformf("color", 1, 0, 0, 1);
        _device->setTexture("texture", _texture, 0);
        _device->setUniformMat4("transform", _transform1);
        _device->setProgram(_program);
        _device->setCullMode(renderer::CullMode::NONE);
        _device->enableStencilTest();
        _device->setStencilFuncBack(StencilFunc::EQUAL, 0x1, 0xFF);
        _device->setStencilFuncFront(StencilFunc::ALWAYS, 0x1, 0xFF);
        _device->setStencilOpBack(StencilOp::KEEP, StencilOp::KEEP, StencilOp::KEEP, 0xFF);
        _device->draw(0, _vertexBuffer->getCount());
    }

    // front
    _device->setViewport(utils::WINDOW_WIDTH * 2 / 3, 0, utils::WINDOW_WIDTH / 3, utils::WINDOW_HEIGHT / 2);
    if (_canvasTexture) {
        _device->setVertexBuffer(0, _vertexBuffer);
        _device->setUniformf("color", 1, 0, 0, 1);
        _device->setTexture("texture", _canvasTexture, 0);
        _device->setUniformMat4("transform", _transform0);
        _device->setProgram(_program);
        _device->setCullMode(renderer::CullMode::NONE);
        _device->enableStencilTest();
        _device->setStencilFunc(StencilFunc::NEVER, 0x1, 0xFF);
        _device->setStencilOp(StencilOp::REPLACE, StencilOp::KEEP, StencilOp::KEEP, 0xFF);
        _device->draw(0, _vertexBuffer->getCount());
    }
    if (_texture) {
        _device->setVertexBuffer(0, _vertexBuffer);
        _device->setUniformf("color", 1, 0, 0, 1);
        _device->setTexture("texture", _texture, 0);
        _device->setUniformMat4("transform", _transform1);
        _device->setProgram(_program);
        _device->setCullMode(renderer::CullMode::NONE);
        _device->enableStencilTest();
        _device->setStencilFuncFront(StencilFunc::EQUAL, 0x1, 0xFF);
        _device->setStencilFuncBack(StencilFunc::ALWAYS, 0x1, 0xFF);
        _device->setStencilOpFront(StencilOp::KEEP, StencilOp::KEEP, StencilOp::KEEP, 0xFF);
        _device->draw(0, _vertexBuffer->getCount());
    }
}


