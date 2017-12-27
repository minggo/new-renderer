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

#include "CCState.h"

#include "CCVertexBuffer.h"
#include "CCIndexBuffer.h"
#include "CCTexture2D.h"
#include "CCProgram.h"

GFX_BEGIN

namespace {
    const State __defaultState;
}

State::State()
// blend
: blend(false)
, blendSepartion(false)
, blendColor(0xFFFFFFFF)
, blendEq(BlendOp::ADD)
, blendAlphaEq(BlendOp::ADD)
, blendSrc(BlendFactor::ONE)
, blendDst(BlendFactor::ZERO)
, blendSrcAlpha(BlendFactor::ONE)
, blendDstAlpha(BlendFactor::ZERO)
// depth
, depthTest(false)
, depthWrite(false)
, depthFunc(DepthFunc::LESS)
// stencil
, stencilTest(false)
, stencilSeparation(false)
, stencilFuncFront(StencilFunc::ALWAYS)
, stencilRefFront(0)
, stencilMaskFront(0xFF)
, stencilFailOpFront(StencilOp::KEEP)
, stencilZFailOpFront(StencilOp::KEEP)
, stencilZPassOpFront(StencilOp::KEEP)
, stencilWriteMaskFront(0xFF)
, stencilFuncBack(StencilFunc::ALWAYS)
, stencilRefBack(0)
, stencilMaskBack(0xFF)
, stencilFailOpBack(StencilOp::KEEP)
, stencilZFailOpBack(StencilOp::KEEP)
, stencilZPassOpBack(StencilOp::KEEP)
, stencilWriteMaskBack(0xFF)
// cull-mode
, cullMode(CullMode::BACK)

// primitive-type
, primitiveType(PrimitiveType::TRIANGLES)

// bindings
, maxStream(-1)
, _indexBuffer(nullptr)
, _program(nullptr)
{
}

State::State(const State& o)
{
    *this = o;
}

State::State(State&& o)
{
    *this = std::move(o);
}

State::~State()
{
    for (auto vertexBuf : _vertexBuffers)
    {
        GFX_SAFE_RELEASE(vertexBuf);
    }

    GFX_SAFE_RELEASE(_indexBuffer);

    for (auto texture : _textureUnits)
    {
        GFX_SAFE_RELEASE(texture);
    }

    GFX_SAFE_RELEASE(_program);
}

State& State::operator=(const State& o)
{
    // blend
    blend = o.blend;
    blendSepartion = o.blendSepartion;
    blendColor = o.blendColor;
    blendEq = o.blendEq;
    blendAlphaEq = o.blendAlphaEq;
    blendSrc = o.blendSrc;
    blendDst = o.blendDst;
    blendSrcAlpha = o.blendSrcAlpha;
    blendDstAlpha = o.blendDstAlpha;
    // depth
    depthTest = o.depthTest;
    depthWrite = o.depthWrite;
    depthFunc = o.depthFunc;
    // stencil
    stencilTest = o.stencilTest;
    stencilSeparation = o.stencilSeparation;
    stencilFuncFront = o.stencilFuncFront;
    stencilRefFront = o.stencilRefFront;
    stencilMaskFront = o.stencilMaskFront;
    stencilFailOpFront = o.stencilFailOpFront;
    stencilZFailOpFront = o.stencilZFailOpFront;
    stencilZPassOpFront = o.stencilZPassOpFront;
    stencilWriteMaskFront = o.stencilWriteMaskFront;
    stencilFuncBack = o.stencilFuncBack;
    stencilRefBack = o.stencilRefBack;
    stencilMaskBack = o.stencilMaskBack;
    stencilFailOpBack = o.stencilFailOpBack;
    stencilZFailOpBack = o.stencilZFailOpBack;
    stencilZPassOpBack = o.stencilZPassOpBack;
    stencilWriteMaskBack = o.stencilWriteMaskBack;
    // cull-mode
    cullMode = o.cullMode;

    // primitive-type
    primitiveType = o.primitiveType;

    // bindings
    maxStream = o.maxStream;

    _vertexBufferOffsets = o._vertexBufferOffsets;

    for (auto vertexBuf : _vertexBuffers)
    {
        GFX_SAFE_RELEASE(vertexBuf);
    }

    if (o._vertexBuffers.empty())
    {
        _vertexBuffers.clear();
    }
    else
    {
        _vertexBuffers.resize(o._vertexBuffers.size());

        for (size_t i = 0, len = o._vertexBuffers.size(); i < len; ++i)
        {
            _vertexBuffers[i] = o._vertexBuffers[i];
            GFX_SAFE_RETAIN(_vertexBuffers[i]);
        }
    }

    GFX_SAFE_RETAIN(o._indexBuffer);
    GFX_SAFE_RELEASE(_indexBuffer);
    _indexBuffer = o._indexBuffer;

    for (auto texture : _textureUnits)
    {
        GFX_SAFE_RELEASE(texture);
    }

    if (o._textureUnits.empty())
    {
        _textureUnits.clear();
    }
    else
    {
        _textureUnits.resize(o._textureUnits.size());
        for (size_t i = 0, len = o._textureUnits.size(); i < len; ++i)
        {
            _textureUnits[i] = o._textureUnits[i];
            GFX_SAFE_RETAIN(_textureUnits[i]);
        }
    }

    GFX_SAFE_RETAIN(o._program);
    GFX_SAFE_RELEASE(_program);
    _program = o._program;

    return *this;
}

State& State::operator=(State&& o)
{
    // blend
    blend = o.blend;
    blendSepartion = o.blendSepartion;
    blendColor = o.blendColor;
    blendEq = o.blendEq;
    blendAlphaEq = o.blendAlphaEq;
    blendSrc = o.blendSrc;
    blendDst = o.blendDst;
    blendSrcAlpha = o.blendSrcAlpha;
    blendDstAlpha = o.blendDstAlpha;
    // depth
    depthTest = o.depthTest;
    depthWrite = o.depthWrite;
    depthFunc = o.depthFunc;
    // stencil
    stencilTest = o.stencilTest;
    stencilSeparation = o.stencilSeparation;
    stencilFuncFront = o.stencilFuncFront;
    stencilRefFront = o.stencilRefFront;
    stencilMaskFront = o.stencilMaskFront;
    stencilFailOpFront = o.stencilFailOpFront;
    stencilZFailOpFront = o.stencilZFailOpFront;
    stencilZPassOpFront = o.stencilZPassOpFront;
    stencilWriteMaskFront = o.stencilWriteMaskFront;
    stencilFuncBack = o.stencilFuncBack;
    stencilRefBack = o.stencilRefBack;
    stencilMaskBack = o.stencilMaskBack;
    stencilFailOpBack = o.stencilFailOpBack;
    stencilZFailOpBack = o.stencilZFailOpBack;
    stencilZPassOpBack = o.stencilZPassOpBack;
    stencilWriteMaskBack = o.stencilWriteMaskBack;
    // cull-mode
    cullMode = o.cullMode;

    // primitive-type
    primitiveType = o.primitiveType;

    // bindings
    maxStream = o.maxStream;

    _vertexBufferOffsets = std::move(o._vertexBufferOffsets);
    _vertexBuffers = std::move(o._vertexBuffers);

    _indexBuffer = o._indexBuffer;
    o._indexBuffer = nullptr;

    _textureUnits = std::move(o._textureUnits);
    _program = o._program;
    o._program = nullptr;

    return *this;
}

void State::reset()
{
    *this = __defaultState;
}

void State::setVertexBuffer(size_t index, VertexBuffer* vertBuf)
{
    assert(vertBuf != nullptr);
    if (index >= _vertexBuffers.size())
    {
        _vertexBuffers.resize(index + 1);
    }

    VertexBuffer* oldBuf = _vertexBuffers[index];
    if (oldBuf != vertBuf)
    {
        oldBuf->release();
        _vertexBuffers[index] = vertBuf;
        vertBuf->retain();
    }
}

VertexBuffer* State::getVertexBuffer(size_t index) const
{
    assert(index < _vertexBuffers.size());
    return _vertexBuffers[index];
}

void State::setVertexBufferOffset(size_t index, int32_t offset)
{
    if (index >= _vertexBufferOffsets.size())
    {
        _vertexBufferOffsets.resize(index + 1);
    }

    _vertexBufferOffsets[index] = offset;
}

int32_t State::getVertexBufferOffset(size_t index) const
{
    assert(index < _vertexBufferOffsets.size());
    return _vertexBufferOffsets[index];
}

void State::setIndexBuffer(IndexBuffer* indexBuf)
{
    assert(indexBuf != nullptr);
    if (_indexBuffer != indexBuf)
    {
        _indexBuffer->release();
        _indexBuffer = indexBuf;
        indexBuf->retain();
    }
}

IndexBuffer* State::getIndexBuffer() const
{
    return _indexBuffer;
}

void State::setTexture(size_t index, Texture* texture)
{
    assert(texture != nullptr);
    if (index >= _textureUnits.size())
    {
        _textureUnits.resize(index + 1);
    }

    Texture* oldTexture = _textureUnits[index];
    if (oldTexture != texture)
    {
        oldTexture->release();
        _textureUnits[index] = texture;
        texture->retain();
    }
}

Texture* State::getTexture(size_t index) const
{
    assert(index < _textureUnits.size());
    return _textureUnits[index];
}

void State::setProgram(Program* program)
{
    assert(program != nullptr);
    if (_program != program)
    {
        _program->release();
        _program = program;
        program->retain();
    }
}

Program* State::getProgram() const
{
    return _program;
}

GFX_END
