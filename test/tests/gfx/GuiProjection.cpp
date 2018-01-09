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

#include "GuiProjection.h"
#include "cocos2d.h"
#include "../Utils.h"

#include <vector>

using namespace cocos2d;
using namespace cocos2d::gfx;

static const uint32_t _spriteWidth = 128;
static const uint32_t _spriteHeight = 128;


GuiProjection::GuiProjection()
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

    _device = DeviceGraphics::getInstance();

    _program = new Program();
    _program->init(_device, vert, frag);
    _program->link();


    {
        auto img = new cocos2d::Image();
        bool ret = img->initWithImageFile("assets/uv_checker_02.jpg");
        assert(ret);

        cocos2d::Data data;
        data.copy(img->getData(), img->getDataLen());

        Texture::Options options;
        options.images.push_back(std::move(data));
        options.width = img->getWidth();
        options.height = img->getHeight();
        options.format = Texture::Format::RGB8;

        img->release();

        _texture = new Texture2D();
        _texture->init(_device, options);
    }

    VertexFormat vertexFmt({
        { ATTRIB_NAME_POSITION, AttribType::FLOAT32, 2},
        { ATTRIB_NAME_UV, AttribType::FLOAT32, 2},
    });

    float vertexBuf[][4] = {
        0, 0,                       0, 0,
        0, _spriteHeight,            0, 1,
        _spriteWidth, _spriteHeight,  1, 1,
        0, 0,                       0, 0,
        _spriteWidth, _spriteHeight,  1, 1,
        _spriteWidth, 0,             1, 0
    };

    _vertexBuffer = new VertexBuffer();
    _vertexBuffer->init(_device,
                        vertexFmt,
                        Usage::STATIC,
                        &vertexBuf[0][0],
                        sizeof(vertexBuf),
                        sizeof(vertexBuf)/sizeof(vertexBuf[0]));


    Mat4::createOrthographicOffCenter(0.0f, utils::WINDOW_WIDTH, 0.0f, utils::WINDOW_HEIGHT, -100.0f, 100.0f, &_projection);
    _translantion.translate(10.0f, (utils::WINDOW_HEIGHT - _spriteHeight) / 2.0f, 0.0f);

    _rotation.translate(10 + _spriteWidth * 2.0f, (utils::WINDOW_HEIGHT - _spriteHeight) / 2.0f, 0);
    _rotation.rotateZ(CC_DEGREES_TO_RADIANS(15));

    _scale.translate(10 + _spriteWidth * 4.0f, (utils::WINDOW_HEIGHT - _spriteHeight) / 2.0f, 0);
    _scale.scale(1.2f, 0.5f, 1.0f);
}

GuiProjection::~GuiProjection()
{
    GFX_SAFE_RELEASE(_vertexBuffer);
    GFX_SAFE_RELEASE(_program);
    GFX_SAFE_RELEASE(_texture);
}

void GuiProjection::tick(float dt)
{
    _device->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    Color4F color(0.1f, 0.1f, 0.1f, 1.f);
    _device->clear(ClearFlag::COLOR | ClearFlag::DEPTH, &color, 1.0, 0);


    if (_texture) {
        _device->setTexture("texture", _texture, 0);

        // translation
        _device->setCullMode(CullMode::NONE);
        _device->setVertexBuffer(0, _vertexBuffer);
        _device->setUniformf("color", 1, 0, 0, 1);
        _device->setUniformMat4("projection", _projection);
        _device->setUniformMat4("transform", _translantion);
        _device->setProgram(_program);
        _device->draw(0, _vertexBuffer->getCount());

        // rotation
        _device->setCullMode(CullMode::NONE);
        _device->setVertexBuffer(0, _vertexBuffer);
        _device->setUniformf("color", 0, 1, 0, 1);
        _device->setUniformMat4("projection", _projection);
        _device->setUniformMat4("transform", _rotation);
        _device->setProgram(_program);
        _device->draw(0, _vertexBuffer->getCount());

        // scale
        _device->setCullMode(CullMode::NONE);
        _device->setVertexBuffer(0, _vertexBuffer);
        _device->setUniformf("color", 0, 0, 1, 1);
        _device->setUniformMat4("projection", _projection);
        _device->setUniformMat4("transform", _scale);
        _device->setProgram(_program);
        _device->draw(0, _vertexBuffer->getCount());
    }
}





