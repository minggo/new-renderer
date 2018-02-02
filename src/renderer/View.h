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

#pragma once

#include <vector>
#include "math/Vec3.h"
#include "math/Mat4.h"
#include "base/ccTypes.h"
#include "../macro.h"
#include "../types.h"

GFX_BEGIN

class Light;
class FrameBuffer;

class View : public Ref
{
public:
    View();
    
    void getForward(Vec3& out) const;
    void getPosition(Vec3& out) const;
    
    uint32_t id;
    
    // viewport
    Rect rect = {0, 0, 1.f, 1.f};
    
    // clear options
    Color4F color = {0.3f, 0.3f, 0.3f, 1.f};
    int depth = 1;
    int stencil = 1;
    uint8_t clearFlags = ClearFlag::COLOR | ClearFlag::DEPTH;
    
    // matrix
    Mat4 matView;
    Mat4 matProj;
    Mat4 matViewProj;
    Mat4 matInvViewPorj;
    
    // stages & framebuffer
    std::vector<std::string> stages;
    bool cullingByID = false;
    FrameBuffer* frameBuffer = nullptr;
    
    Light* shadowLight = nullptr;
};

GFX_END
