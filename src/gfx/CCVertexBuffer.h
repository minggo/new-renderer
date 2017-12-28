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
#include "../types.h"
#include "CCVertexFormat.h"
#include "CCGraphicsHandle.h"

GFX_BEGIN

class DeviceGraphics;

class VertexBuffer final : public GraphicsHandle
{
public:
    GFX_DEFINE_CREATE_METHOD_6(VertexBuffer, init,  DeviceGraphics*, const VertexFormat&, Usage, const void*, size_t, uint32_t)

    VertexBuffer();
    virtual ~VertexBuffer();

    bool init(DeviceGraphics* device, const VertexFormat& format, Usage usage, const void* data, size_t dataByteLength, uint32_t numVertices);
    void update(uint32_t offset, const void* data, size_t dataByteLength);
    inline uint32_t getCount() const { return _numVertices; }
    inline const VertexFormat& getFormat() { return _format; };

private:
    DeviceGraphics* _device;
    VertexFormat _format;
    Usage _usage;
    uint32_t _numVertices;
    uint32_t _bytes;

    CC_DISALLOW_COPY_ASSIGN_AND_MOVE(VertexBuffer)
};

GFX_END
