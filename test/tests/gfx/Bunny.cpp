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

#include <vector>
#include "Bunny.h"
#include "BunnyData.h"
#include "../Utils.h"

using namespace cocos2d;
using namespace cocos2d::gfx;

Bunny::Bunny()
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

    _device = DeviceGraphics::getInstance();
    _program = new Program();
    _program->init(_device, vert, frag);
    _program->link();

    VertexFormat vertexFmt({
        {ATTRIB_NAME_POSITION, AttribType::FLOAT32, 3}
    });

    _vertexBuffer = new VertexBuffer();
    _vertexBuffer->init(_device,
                        vertexFmt,
                        Usage::STATIC,
                        &bunny_positions[0][0],
                        sizeof(bunny_positions),
                        sizeof(bunny_positions) / sizeof(bunny_positions[0]));

    _indexBuffer = new IndexBuffer();
    _indexBuffer->init(_device,
                       IndexFormat::UINT16,
                       Usage::STATIC,
                       &bunny_cells[0],
                       sizeof(bunny_cells),
                       sizeof(bunny_cells) / sizeof(bunny_cells[0]));

    Mat4::createPerspective(60.0f, 1.0f * utils::WINDOW_WIDTH / utils::WINDOW_HEIGHT, 0.01f, 1000.0f, &_projection);
}

Bunny::~Bunny()
{
    GFX_SAFE_RELEASE(_vertexBuffer);
    GFX_SAFE_RELEASE(_indexBuffer);
    GFX_SAFE_RELEASE(_program);
}

void Bunny::tick(float dt)
{
    _time += dt;
    Mat4::createLookAt(Vec3(30.0f * std::cos(_time), 20.0f, 30.0f * std::sin(_time)), Vec3(0.0f, 2.5f, 0.0f), Vec3(0.0f, 1.0f, 0.f), &_view);

    _device->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    Color4F color(0.1f, 0.1f, 0.1f, 1.f);
    _device->clear(ClearFlag::COLOR | ClearFlag::DEPTH, &color, 1.0, 0);

    _device->enableDepthTest();
    _device->enableDepthWrite();

    _device->setVertexBuffer(0, _vertexBuffer);
    _device->setIndexBuffer(_indexBuffer);
    _device->setUniformMat4("model", _model);
    _device->setUniformMat4("view", _view);
    _device->setUniformMat4("projection", _projection);
    _device->setUniformVec4("color", Vec4(0.5f, 0.5f, 0.5f, 1.0f));
    _device->setProgram(_program);
    _device->draw(0, _indexBuffer->getCount());
}

