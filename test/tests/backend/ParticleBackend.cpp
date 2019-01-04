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

#include "ParticleBackend.h"
#include "../Utils.h"

#include <vector>

using namespace cocos2d;

ParticleBackend::ParticleBackend()
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
    
    auto device = backend::Device::getInstance();
    
    backend::RenderPipelineDescriptor renderPipelineDescriptor;
    auto vs = device->createShaderModule(backend::ShaderStage::VERTEX, vert);
    auto fs = device->createShaderModule(backend::ShaderStage::FRAGMENT, frag);
    renderPipelineDescriptor.program = device->createProgram(vs, fs);
    _modelLocation = renderPipelineDescriptor.program->getUniformLocation("model");
    _viewLocation = renderPipelineDescriptor.program->getUniformLocation("view");
    _projectionLocation = renderPipelineDescriptor.program->getUniformLocation("projection");
    
#define VERTEX_QUAD_SIZE 2
#define VERTEX_POS_SIZE 3
#define VERTEX_COLOR_SIZE 4
    
    uint32_t positionOffset = VERTEX_QUAD_SIZE*sizeof(float);
    uint32_t colorOffset = (VERTEX_POS_SIZE+VERTEX_QUAD_SIZE)*sizeof(float);
    uint32_t totalSize = (VERTEX_POS_SIZE+VERTEX_QUAD_SIZE+VERTEX_COLOR_SIZE)*sizeof(float);
    backend::VertexLayout vertexLayout;
    vertexLayout.setAtrribute("a_quad", 0, backend::VertexFormat::FLOAT_R32G32, 0);
    vertexLayout.setAtrribute("a_position", 1, backend::VertexFormat::FLOAT_R32G32B32, positionOffset);
    vertexLayout.setAtrribute("a_color", 2, backend::VertexFormat::FLOAT_R32G32B32A32, colorOffset);
    vertexLayout.setLayout(totalSize, backend::VertexStepMode::VERTEX);
    renderPipelineDescriptor.vertexLayouts.push_back(vertexLayout);
    
    backend::BlendDescriptor blendDescriptorNormal;
    blendDescriptorNormal.blendEnabled = true;
    blendDescriptorNormal.rgbBlendOperation = backend::BlendOperation::ADD;
    blendDescriptorNormal.alphaBlendOperation = backend::BlendOperation::ADD;
    blendDescriptorNormal.sourceRGBBlendFactor = backend::BlendFactor::SRC_ALPHA;
    blendDescriptorNormal.destinationRGBBlendFactor = backend::BlendFactor::ONE_MINUS_SRC_ALPHA;
    blendDescriptorNormal.sourceAlphaBlendFactor = backend::BlendFactor::ONE;
    blendDescriptorNormal.destinationRGBBlendFactor = backend::BlendFactor::ONE;
    auto blendStateNormal = device->createBlendState(blendDescriptorNormal);
    renderPipelineDescriptor.blendState = blendStateNormal;
    _renderPipelineWithBlend = device->newRenderPipeline(renderPipelineDescriptor);
    
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
    
    backend::TextureDescriptor textureDescriptor;
    textureDescriptor.width = 128;
    textureDescriptor.height = 128;
    textureDescriptor.textureFormat = backend::TextureFormat::R8G8B8;
    textureDescriptor.samplerDescriptor.sAddressMode = backend::SamplerAddressMode::REPEAT;
    textureDescriptor.samplerDescriptor.tAddressMode = backend::SamplerAddressMode::REPEAT;
    textureDescriptor.samplerDescriptor.mipmapEnabled = true;
    _texture = device->newTexture(textureDescriptor);
    _texture->updateData(imageData.getBytes());
    _renderPipelineWithBlend->getProgram()->setTexture("u_texture", 0, _texture);
    
    _commandBuffer = device->newCommandBuffer();
    _vertexBuffer = device->newBuffer(sizeof(_vbufferArray), backend::BufferType::VERTEX, backend::BufferUsage::READ);
    
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
    _indexCount = dst;
    
    _indexBuffer = device->newBuffer(sizeof(_ibufferArray), backend::BufferType::INDEX, backend::BufferUsage::READ);
    _indexBuffer->updateData(_ibufferArray, sizeof(_ibufferArray));

    for (size_t i = 0; i < particleCount; ++i)
    {
        _particles[i].velocity = utils::vec3Random(cocos2d::random(0.1f, 10.0f));
        _particles[i].age = 0;
        _particles[i].life = cocos2d::random(1.0f, 10.0f);
    }

    Mat4::createPerspective(60.0f, 1.0f * utils::WINDOW_WIDTH / utils::WINDOW_HEIGHT, 0.01f, 1000.0f, &_projection);
    Mat4::createLookAt(Vec3(30.0f , 20.0f, 30.0f), Vec3(0.0f, 2.5f, 0.0f), Vec3(0.0f, 1.0f, 0.f), &_view);
    
    _renderPassDescriptor.clearColorValue = {0.1f, 0.1f, 0.1f, 1.f};
    _renderPassDescriptor.needClearColor = true;
    _renderPassDescriptor.needColorAttachment = true;
}

ParticleBackend::~ParticleBackend()
{
    CC_SAFE_RELEASE(_vertexBuffer);
    CC_SAFE_RELEASE(_indexBuffer);
    CC_SAFE_RELEASE(_commandBuffer);
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_renderPipelineWithBlend);
}

void ParticleBackend::tick(float dt)
{
    _commandBuffer->beginFrame();
    _commandBuffer->beginRenderPass(_renderPassDescriptor);
    _commandBuffer->setRenderPipeline(_renderPipelineWithBlend);
    _commandBuffer->setViewport(0, 0, utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT);
    
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
    _vertexBuffer->updateData(_vbufferArray, sizeof(_vbufferArray));
    auto program = _renderPipelineWithBlend->getProgram();
    program->setVertexUniform(_modelLocation, _model.m, sizeof(_model.m));
    program->setVertexUniform(_viewLocation, _view.m, sizeof(_view.m));
    program->setVertexUniform(_projectionLocation, _projection.m, sizeof(_projection.m));
    
    _commandBuffer->setVertexBuffer(0, _vertexBuffer);
    _commandBuffer->setIndexBuffer(_indexBuffer);
    
    _commandBuffer->drawElements(backend::PrimitiveType::TRIANGLE, backend::IndexFormat::U_SHORT, _indexCount);
    _commandBuffer->endRenderPass();
    _commandBuffer->endFrame();
}

