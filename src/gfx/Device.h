//
//  Device.hpp
//  Test
//
//  Created by minggo on 12/14/17.
//  Copyright © 2017 cocos. All rights reserved.
//

#pragma once

#include <stdint.h>
#include <string>
#include "../macro.h"
#include "../types.h"

CC_BEGIN

class FrameBuffer;
class VertexBuffer;
class IndexBuffer;
class Program;
class Texture;

class Device
{
public:
    void setFrameBuffer(const FrameBuffer* fb);
    void setViewport(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    void setScissor(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    void clear(ClearFlag flags, uint32_t rgba, uint8_t depth, uint8_t stencil);
    
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
    CC_DISALLOW_COPY_ASSIGN_AND_MOVE(Device);
    
    void initStates();
    void restoreTexture(uint32_t index);
    void restoreIndexBuffer();
};

CC_END
