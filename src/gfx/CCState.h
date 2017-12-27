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

#pragma once

#include <stdint.h>
#include <vector>
#include "../macro.h"
#include "../types.h"

GFX_BEGIN

class VertexBuffer;
class IndexBuffer;
class Program;
class Texture;

struct State final
{
    // TODO: adjust memeber position to reduce size??
    
    State();
    State(const State&);
    State(State &&);
    ~State();

    State& operator =(const State& rhs);
    State& operator =(State&& rhs);

    void reset();

    // blend
    bool blend;
    bool blendSepartion;
    uint32_t blendColor;
    BlendOp blendEq;
    BlendOp blendAlphaEq;
    BlendFactor blendSrc;
    BlendFactor blendDst;
    BlendFactor blendSrcAlpha;
    BlendFactor blendDstAlpha;
    
    // depth
    bool depthTest;
    bool depthWrite;
    DepthFunc depthFunc;
    
    // stencil
    bool stencilTest;
    bool stencilSeparation;
    StencilFunc stencilFuncFront;
    int32_t stencilRefFront;
    uint32_t stencilMaskFront;
    StencilOp stencilFailOpFront;
    StencilOp stencilZFailOpFront;
    StencilOp stencilZPassOpFront;
    uint32_t stencilWriteMaskFront;
    StencilFunc stencilFuncBack;
    int32_t stencilRefBack;
    uint32_t stencilMaskBack;
    StencilOp stencilFailOpBack;
    StencilOp stencilZFailOpBack;
    StencilOp stencilZPassOpBack;
    uint32_t stencilWriteMaskBack;
    
    CullMode cullMode;
    
    PrimitiveType primitiveType;
    
    int32_t maxStream;

    void setVertexBuffer(size_t index, VertexBuffer* vertBuf);
    VertexBuffer* getVertexBuffer(size_t index) const;

    void setVertexBufferOffset(size_t index, int32_t offset);
    int32_t getVertexBufferOffset(size_t index) const;

    void setIndexBuffer(IndexBuffer* indexBuf);
    IndexBuffer* getIndexBuffer() const;

    void setTexture(size_t index, Texture* texture);
    Texture* getTexture(size_t index) const;

    void setProgram(Program* program);
    Program* getProgram() const;

private:
    std::vector<VertexBuffer*> _vertexBuffers;
    std::vector<int32_t> _vertexBufferOffsets;
    IndexBuffer *_indexBuffer;
    std::vector<Texture*> _textureUnits;
    Program *_program;
};

GFX_END
