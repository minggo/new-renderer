/****************************************************************************
 Copyright (c) 2018 Chukong Technologies

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

#include "SubImage.h"
#include "cocos2d.h"
#include "../Utils.h"

#include <vector>

using namespace cocos2d;
using namespace cocos2d::gfx;


SubImage::SubImage()
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

    _device = DeviceGraphics::getInstance();

     _program = new Program();
    _program->init(_device, vert, frag);
    _program->link();

    Texture::Options options;
    options.width = 128;
    options.height = 128;
    options.wrapS = Texture::WrapMode::CLAMP;
    options.wrapT = Texture::WrapMode::CLAMP;
    options.minFilter = Texture::Filter::NEAREST;
    options.magFilter = Texture::Filter::NEAREST;
    options.format = Texture::Format::RGB8;
    options.hasMipmap = false;
    options.flipY = false;

    _texture = new Texture2D();
    _texture->init(_device, options);

    VertexFormat vertexFmt({
        { ATTRIB_NAME_POSITION, AttribType::FLOAT32, 2},
    });

    float vertexBuf[][2] = {
        {-1, -1},
        {1, -1},
        {1, 1},
        {1, 1},
        {-1, 1},
        {-1, -1}
    };

    _vertexBuffer = new VertexBuffer();
    _vertexBuffer->init(_device,
                        vertexFmt,
                        Usage::STATIC,
                        &vertexBuf[0][0],
                        sizeof(vertexBuf),
                        sizeof(vertexBuf)/sizeof(vertexBuf[0]));

    _dataSize = _texture->getWidth() * _texture->getHeight() * 3;
    _data = (uint8_t*)malloc(_dataSize);
    memset(_data, 0, _dataSize);
    _updatePixelIndex = 0;
}

SubImage::~SubImage()
{
    GFX_SAFE_RELEASE(_vertexBuffer);
    GFX_SAFE_RELEASE(_program);
    GFX_SAFE_RELEASE(_texture);
    free(_data);
}

void SubImage::tick(float dt)
{
    _device->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    Color4F color(1.f, 0.1f, 0.1f, 1.f);
    _device->clear(ClearFlag::COLOR | ClearFlag::DEPTH, &color, 1.0, 0);

    for (size_t i = 0; i < _updatePixelIndex; ++i) {
        _data[3 * i] =  cocos2d::random(0, 255);
        _data[3 * i + 1] = cocos2d::random(0, 255);
        _data[3 * i + 2] = cocos2d::random(0, 255);
    }

    Texture::SubImageOption opts;
    opts.x = 0;
    opts.y = 0;
    opts.width = _texture->getWidth();
    opts.height = _texture->getHeight();
    opts.level = 0;
    opts.flipY = false;
    opts.image.copy(_data, _dataSize);

    _texture->updateSubImage(opts);

    _device->setVertexBuffer(0, _vertexBuffer);
    _device->setUniformf("color", 1, 0, 0, 1);
    _device->setTexture("texture", _texture, 0);
    _device->setUniformMat4("transform", _transform0);
    _device->setProgram(_program);
    _device->draw(0, _vertexBuffer->getCount());

    if (_updatePixelIndex < _texture->getWidth() * _texture->getHeight() ) {
        _updatePixelIndex += 1;
    }
}



