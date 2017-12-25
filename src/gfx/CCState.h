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

struct State
{
    // TODO: adjust memeber position to reduce size??
    
    State();
    const State& operator =(const State& rhs);
    State(const State&) = delete;
    State& operator =(const State&& rhs) = delete;
    State(const State &&) = delete;
    
    void reset();
    void set(const State& cpy);
    
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
    int stencilRefFront;
    unsigned int stencilMaskFront;
    StencilOp stencilFailOpFront;
    StencilOp stencilZFailOpFront;
    StencilOp stencilZPassOpFront;
    unsigned int stencilWriteMaskFront;
    StencilFunc stencilFuncBack;
    int stencilRefBack;
    unsigned int stencilMaskBack;
    StencilOp stencilFailOpBack;
    StencilOp stencilZFailOpBack;
    StencilOp stencilZPassOpBack;
    unsigned int stencilWriteMaskBack;
    
    CullMode cullMode;
    
    PrimitiveType primitiveType;
    
    int maxStream;
    std::vector<VertexBuffer*> vertexBuffers;
    std::vector<int> vertexBufferOffsets;
    IndexBuffer *indexBuffer;
    std::vector<int> textureUintes;
    Program *program;
    
private:
    void init();
};

GFX_END
