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
#include <string>
#include <vector>
#include "../macro.h"
#include "../types.h"

// header files from cocos2d-x
#include "../files-from-cocos2dx/ccTypes.h"

GFX_BEGIN

class FrameBuffer;
class VertexBuffer;
class IndexBuffer;
class Program;
class Texture;

class Device
{
public:
    void setFrameBuffer(const FrameBuffer* fb);
    void setViewport(int x, int y, int w, int h);
    void setScissor(int x, int y, int w, int h);
    
    void clear(ClearFlag flags, Color4F *color, uint8_t depth, uint8_t stencil);
    
    void enableBlend();
    void enableDepthTest();
    void enableDepthWrite();
    void enableStencilTest();
    
    void setStencilFunc(StencilFunc func, int ref, unsigned int mask);
    void setStencilFuncFront(StencilFunc func, int ref, unsigned int mask);
    void setStencilFuncBack(StencilFunc func, int ref, unsigned int mask);
    
    void setStencilOp(StencilOp failOp, StencilOp zFailOp, StencilOp zPassOp, unsigned int writeMask);
    void setstencilOpFront(StencilOp failOp, StencilOp zFailOp, StencilOp zPassOp, unsigned int writeMask);
    void setStencilOpBack(StencilOp failOp, StencilOp zFailOp, StencilOp zPassOp, unsigned int writeMask);
    
    void setDepthTest(DepthFunc func);
    
    void setBlendColor(uint32_t rgba);
    void setBlendColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void setBlendFunc(BlendFactor src, BlendFactor dst);
    void setBlendFuncSeparate(BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha);
    void setBlendEquation(BlendOp mode);
    void setBlendEquationSeparate(BlendOp modeRGB, BlendFactor modeAlpha);
    
    void setCullMode(CullMode mode);
    
    void setVertexBuffer(int stream, VertexBuffer* buffer, int start = 0);
    void setIndexBuffer(IndexBuffer *buffer);
    void setProgram(Program *program);
    void setTexture(const std::string& name, Texture* texture, int slot);
    void setTextureArray(const std::string& name, const std::vector<Texture*>& texutres, const std::vector<int>& slots);
    //TODO
    // setUniform
    void setPrimitiveType(PrimitiveType type);
    
    void draw(int base, size_t count);
    
private:
    
    struct Capacity
    {
        int maxVextexTextures;
        int maxFragUniforms;
        int maxTextureUints;
        int maxVertexAttributes;
        int maxDrawBuffers;
        int maxColorAttatchments;
    };
    
    Device();
    CC_DISALLOW_COPY_ASSIGN_AND_MOVE(Device);
    
    void initStates();
    void initCaps();
    void restoreTexture(uint32_t index);
    void restoreIndexBuffer();
    
    int _vx;
    int _vy;
    int _vw;
    int _vh;
    
    int _sx;
    int _sy;
    int _sw;
    int _sh;
    
    Capacity _caps;
    
    FrameBuffer *_frameBuffer;
    std::vector<int> _enabledAtrributes;
    std::vector<int> _newAttributes;
    
    // TODO: State info, uniforms
    
};

GFX_END
