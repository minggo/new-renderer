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

#include "Particle.h"
#include "../Utils.h"

#include <vector>

using namespace cocos2d;
using namespace cocos2d::gfx;

Particle::Particle()
{
    const char* vert = R"(
#ifdef GL_ES
    precision highp float;
#endif
    uniform mat4 model, view, projection;

    attribute vec2 a_quad;
    attribute vec3 a_position;
    attribute vec4 a_color;

    varying vec4 color;
    varying vec2 uv;

    void main() {
        // billboard
        vec4 pos = view * model * vec4(a_position, 1);
        pos.xy += a_quad.xy;
        pos = projection * pos;

        uv = vec2(a_quad * -0.5 + 0.5);

        gl_Position = pos;
        gl_PointSize = 2.0;
        color = a_color;
    }
    )";

    const char* frag = R"(
#ifdef GL_ES
    precision highp float;
#endif
    uniform sampler2D u_texture;

    varying vec4 color;
    varying vec2 uv;

    void main () {
        gl_FragColor = color * texture2D( u_texture, uv );
    }
    )";

    _device = DeviceGraphics::getInstance();

    Data imageData;

    const size_t BUFFER_SIZE = 128 * 128 * 3;
    uint8_t* data = (uint8_t*)malloc(BUFFER_SIZE);

    const size_t lineWidth = 128;
    const size_t lineHeight = 128;
    utils::fillRectWithColor(data, lineWidth, lineHeight, 0, 0, 128, 128, 0xD0, 0xD0, 0xD0);
    utils::fillRectWithColor(data, lineWidth, lineHeight, 0, 0, 64, 64, 0x50, 0x50, 0x50);
    utils::fillRectWithColor(data, lineWidth, lineHeight, 32, 32, 32, 32, 0xFF, 0x00, 0x00);
    utils::fillRectWithColor(data, lineWidth, lineHeight, 64, 64, 64, 64, 0x00, 0xFF, 0x00);
    utils::fillRectWithColor(data, lineWidth, lineHeight, 96, 96, 32, 32, 0x00, 0x00, 0xFF);

    imageData.fastSet(data, BUFFER_SIZE);

    Texture::Options options;
    options.images.push_back(std::move(imageData));
    options.width = options.height = 128;
    options.wrapS = Texture::WrapMode::REPEAT;
    options.wrapT = Texture::WrapMode::REPEAT;
    options.format = Texture::Format::RGB8;
    options.hasMipmap = true;

    _texture = new Texture2D();
    _texture->init(_device, options);

    _program = new Program();
    _program->init(_device, vert, frag);
    _program->link();

    VertexFormat vertexFmt({
        { "a_quad", AttribType::FLOAT32, 2 },
        { ATTRIB_NAME_POSITION, AttribType::FLOAT32, 3},
        { ATTRIB_NAME_COLOR, AttribType::FLOAT32, 4 },
    });

    _vertexBuffer = new VertexBuffer();
    _vertexBuffer->init(_device,
                         vertexFmt,
                         Usage::DYNAMIC,
                         &_vbufferArray[0][0][0],
                         sizeof(_vbufferArray),
                         maxQuadCount * 4);

    // ib
    uint16_t dst = 0;
    uint16_t* p = _ibufferArray[0];
    for (uint16_t i = 0; i < maxQuadCount; ++i) {
        uint16_t baseIndex = i * 4;
        p[dst++] = baseIndex;
        p[dst++] = baseIndex + 1;
        p[dst++] = baseIndex + 2;
        p[dst++] = baseIndex;
        p[dst++] = baseIndex + 2;
        p[dst++] = baseIndex + 3;
    }

    _indexBuffer = new IndexBuffer();
    _indexBuffer->init(_device,
                       IndexFormat::UINT16,
                       Usage::STATIC,
                       &_ibufferArray[0][0],
                       sizeof(_ibufferArray),
                       maxQuadCount * 6);

    for (size_t i = 0; i < particleCount; ++i)
    {
        _particles[i].velocity = utils::vec3Random(cocos2d::random(0.1f, 10.0f));
        _particles[i].age = 0;
        _particles[i].life = cocos2d::random(1.0f, 10.0f);
    }

    Mat4::createPerspective(60.0f, 1.0f * utils::WINDOW_WIDTH / utils::WINDOW_HEIGHT, 0.01f, 1000.0f, &_projection);
    Mat4::createLookAt(Vec3(30.0f , 20.0f, 30.0f), Vec3(0.0f, 2.5f, 0.0f), Vec3(0.0f, 1.0f, 0.f), &_view);
}

Particle::~Particle()
{
    GFX_SAFE_RELEASE(_vertexBuffer);
    GFX_SAFE_RELEASE(_indexBuffer);
    GFX_SAFE_RELEASE(_program);
    GFX_SAFE_RELEASE(_texture);
}

void Particle::tick(float dt)
{
    // update particles
    for (size_t i = 0; i < particleCount; ++i) {
        ParticleData& p = _particles[i];
        p.position = utils::vec3ScaleAndAdd(p.position, p.velocity, dt);
        p.age += dt;

        if (p.age >= p.life) {
            p.age = 0;
            p.position = Vec3::ZERO;
        }
    }

    // variables
    static const float quadVerts[][2] = {
        {-1, -1},
        {1, -1},
        {1, 1},
        {-1, 1}
    };

    float* pVbuffer = &_vbufferArray[0][0][0];
    // update vertex-buffer
    for (size_t i = 0; i < particleCount; ++i) {
        ParticleData& p = _particles[i];
        for (size_t v = 0; v < 4; ++v) {
            size_t offset = vertStride * (4 * i + v);

            // quad
            pVbuffer[offset + 0] = quadVerts[v][0];
            pVbuffer[offset + 1] = quadVerts[v][1];

            // pos
            pVbuffer[offset + 2] = p.position.x;
            pVbuffer[offset + 3] = p.position.y;
            pVbuffer[offset + 4] = p.position.z;

            // color
            pVbuffer[offset + 5] = 1;
            pVbuffer[offset + 6] = 1;
            pVbuffer[offset + 7] = 1;
            pVbuffer[offset + 8] = 1.0 - p.age / p.life;
        }
    }
    _vertexBuffer->update(0, &_vbufferArray[0][0][0], sizeof(_vbufferArray));

    _device->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    Color4F color(0.1f, 0.1f, 0.1f, 1.f);
    _device->clear(ClearFlag::COLOR | ClearFlag::DEPTH, &color, 1.0, 0);

    _device->enableBlend();;

    _device->setBlendFuncSeparate(BlendFactor::SRC_ALPHA, BlendFactor::ONE_MINUS_SRC_ALPHA, BlendFactor::ONE, BlendFactor::ONE);
    _device->setBlendEquationSeparate(BlendOp::ADD, BlendOp::ADD);

    _device->setVertexBuffer(0, _vertexBuffer);
    _device->setIndexBuffer(_indexBuffer);
    _device->setUniformMat4("model", _model);
    _device->setUniformMat4("view", _view);
    _device->setUniformMat4("projection", _projection);
    _device->setUniformVec4("color", Vec4(0.5f, 0.5f, 0.5f, 1.0f));
    _device->setTexture("u_texture", _texture, 0);
    _device->setProgram(_program);
    _device->draw(0, _indexBuffer->getCount());
}

