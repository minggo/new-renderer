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

#include "CCIndexBuffer.h"
#include "CCDevice.h"

CC_BEGIN

IndexBuffer::IndexBuffer(Device* device, IndexFormat format, Usage usage, void* data, size_t dataByteLength, uint32_t numIndices)
: _device(device)
, _format(format)
, _usage(usage)
, _numIndices(numIndices)
, _bytesPerIndex(0)
{
    // calculate bytes
    if (format == IndexFormat::UINT8)
    {
        _bytesPerIndex = 1;
    }
    else if (format == IndexFormat::UINT16)
    {
        _bytesPerIndex = 2;
    }
    else if (format == IndexFormat::UINT32)
    {
        _bytesPerIndex = 4;
    }

    _bytes = _bytesPerIndex * numIndices;

    // update
    glGenBuffers(1, &_glID);
    update(0, data, dataByteLength);

    // stats
    //TODO:    device._stats.ib += _bytes;
}

IndexBuffer::~IndexBuffer()
{
    if (_glID == -1)
    {
        GFX_LOGE("The buffer already destroyed");
        return;
    }

    glDeleteBuffers(1, &_glID);
    //TODO:    _device._stats.ib -= _bytes;
    _glID = -1;
}

void IndexBuffer::update(uint32_t offset, void* data, size_t dataByteLength)
{
    if (_glID == -1) {
        GFX_LOGE("The buffer is destroyed");
        return;
    }

    if (data && dataByteLength + offset > _bytes) {
        GFX_LOGE("Failed to update data, bytes exceed.");
        return;
    }

    GLenum glUsage = (GLenum)_usage;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _glID);
    if (!data)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _bytes, nullptr, glUsage);
    }
    else
    {
        if (offset > 0)
        {
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (GLintptr)offset, (GLsizeiptr)dataByteLength, (const GLvoid*)data);
        }
        else
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)dataByteLength, data, glUsage);
        }
    }
    _device->restoreIndexBuffer();
}

CC_END
