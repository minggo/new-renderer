//
//  Device.hpp
//  Test
//
//  Created by minggo on 12/14/17.
//  Copyright © 2017 cocos. All rights reserved.
//

#pragma once

#include <stdint.h>
#include "../macro.h"
#include "../types.h"

CC_BEGIN

class FrameBuffer;

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
    
private:
    CC_DISALLOW_COPY_ASSIGN_AND_MOVE(Device);
    
    void initStates();
    void restoreTexture(uint32_t index);
    void restoreIndexBuffer();
};

CC_END


