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

#include "MultiTextures.h"
#include "base/ccTypes.h"
#include "../Utils.h"

using namespace cocos2d;

MultiTextures::MultiTextures()
{
    _device = renderer::DeviceGraphics::getInstance();
    
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
    _program = new renderer::Program();
    _program->init(_device, vert, frag);
    _program->link();
    
    // vertex buffer
    renderer::VertexFormat vertexFormat({
        {renderer::ATTRIB_NAME_POSITION, renderer::AttribType::FLOAT32, 2}
    });
    float vertices[] = {-1, -1, 1, -1, 1, 1, 1, 1, -1, 1, -1, -1};
    _vertexBuffer = new renderer::VertexBuffer();
    _vertexBuffer->init(_device,
                        vertexFormat,
                        renderer::Usage::STATIC,
                        vertices,
                        sizeof(vertices),
                        6);
    
    // textures
    renderer::Texture::Options options1;
    options1.width = 1024;
    options1.height = 1024;
    options1.format = renderer::Texture::Format::RGB8;
    options1.images.push_back(utils::loadData("assets/uv_checker_01.jpg"));
    _texture1 = new renderer::Texture2D();
    _texture1->init(_device, options1);
    
    renderer::Texture::Options options2;
    options2.width = 512;
    options2.height = 512;
    options2.format = renderer::Texture::Format::RGB8;
    
    int dataSize = 512 * 512 * 3;
    uint8_t data[dataSize];
    for (int i = 0; i < dataSize; i += 3)
    {
        data[i] = 199;
        data[i + 1] = 237;
        data[i + 2] = 204;
    }
    cocos2d::Data dataD;
    dataD.copy(data, dataSize);
    options2.images.push_back(dataD);
    _background = new renderer::Texture2D();
    _background->init(_device, options2);
    
    _transform = cocos2d::Mat4::IDENTITY;
    _transform.translate(0, 0, 0);
    _transform.scale(0.5, 0.5, 0.5);
}

MultiTextures::~MultiTextures()
{
    RENDERER_SAFE_RELEASE(_vertexBuffer);
    RENDERER_SAFE_RELEASE(_program);
    RENDERER_SAFE_RELEASE(_background);
    RENDERER_SAFE_RELEASE(_texture1);
}

void MultiTextures::tick(float dt)
{
    _device->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    
    Color4F clearColor(0.1f, 0.1f, 0.1f, 1.f);
    _device->clear(renderer::ClearFlag::DEPTH | renderer::ClearFlag::COLOR, &clearColor, 1, 0);
    
    _device->setVertexBuffer(0, _vertexBuffer);
    _device->setUniformf("color", 1.f, 0, 0, 1.f);
    _device->setTextureArray("texture", {_background, _texture1}, {6, 7});
    _device->setUniformMat4("transform", _transform);
    _device->setProgram(_program);
    _device->draw(0, _vertexBuffer->getCount());
}
