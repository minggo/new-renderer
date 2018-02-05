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

#include "../macro.h"
#include "../types.h"
#include "CCGraphicsHandle.h"

GFX_BEGIN

class DeviceGraphics;

class IndexBuffer final : public GraphicsHandle
{
public:
    GFX_DEFINE_CREATE_METHOD_6(IndexBuffer, init, DeviceGraphics*, IndexFormat, Usage, const void*, size_t, uint32_t)

    IndexBuffer();
    virtual ~IndexBuffer();

    bool init(DeviceGraphics* device, IndexFormat format, Usage usage, const void* data, size_t dataByteLength, uint32_t numIndices);
    void update(uint32_t offset, const void* data, size_t dataByteLength);

    inline uint32_t getCount() const { return _numIndices; }
    inline void setCount(uint32_t numIndices) { _numIndices = numIndices; }

    inline IndexFormat getFormat() const { return _format; }
    inline void setFormat(IndexFormat format) { _format = format; }

    inline uint32_t getBytesPerIndex() const { return _bytesPerIndex; }
    inline void setBytesPerIndex(uint32_t bytesPerIndex) {_bytesPerIndex = bytesPerIndex; }

    inline Usage getUsage() const { return _usage; }
    inline void setUsage(Usage usage) { _usage = usage; }

    inline uint32_t getBytes() const { return _bytes; }
    inline void setBytes(uint32_t bytes) { _bytes = bytes; }

    using FetchDataCallback = std::function<uint8_t*(size_t*)>;
    void setFetchDataCallback(const FetchDataCallback& cb) { _fetchDataCallback = cb; }
    uint8_t* invokeFetchDataCallback(size_t* bytes) {
        if (_fetchDataCallback == nullptr)
        {
            *bytes = 0;
            return nullptr;
        }
        return _fetchDataCallback(bytes);
    }
    
private:
    DeviceGraphics* _device;
    IndexFormat _format;
    Usage _usage;
    uint32_t _numIndices;
    uint32_t _bytesPerIndex;
    uint32_t _bytes;

    FetchDataCallback _fetchDataCallback;

    CC_DISALLOW_COPY_ASSIGN_AND_MOVE(IndexBuffer)
};

GFX_END
