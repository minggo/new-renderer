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

#include "../macro.h"
#include "types.h"

GFX_BEGIN

class DeviceGraphics;

class RenderBuffer
{
public:
    // render-buffer format
    enum class Format : uint32_t
    {
        RGBA4 = GL_RGBA4,
        RGB5_A1 = GL_RGB5_A1,
        RGB565 = GL_RGB565,
        D16 = GL_DEPTH_COMPONENT16,
        S8 = GL_STENCIL_INDEX8,
        D24S8 = GL_DEPTH_STENCIL
    };

    RenderBuffer(DeviceGraphics* device, Format format, uint16_t width, uint16_t height);
    ~RenderBuffer();

private:
    DeviceGraphics* _device;
    Format _format;
    uint16_t _width;
    uint16_t _height;
    GLuint _glID;
};

GFX_END
