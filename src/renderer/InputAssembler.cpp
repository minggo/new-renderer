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

#include "InputAssembler.h"
#include "gfx/CCVertexBuffer.h"
#include "gfx/CCIndexBuffer.h"

GFX_BEGIN

InputAssembler::InputAssembler()
{
}

InputAssembler::~InputAssembler()
{
    GFX_SAFE_RELEASE(_vertexBuffer);
    GFX_SAFE_RELEASE(_indexBuffer);
}

bool InputAssembler::init(VertexBuffer* vb,
                          IndexBuffer* ib,
                          PrimitiveType pt/* = PrimitiveType::TRIANGLES*/)
{
    setVertexBuffer(vb);
    setIndexBuffer(ib);
    _primitiveType = pt;
    return true;
}

void InputAssembler::setVertexBuffer(VertexBuffer* vb)
{
    GFX_SAFE_RELEASE(_vertexBuffer);
    _vertexBuffer = vb;
    GFX_SAFE_RETAIN(_vertexBuffer);
}

void InputAssembler::setIndexBuffer(IndexBuffer* ib)
{
    GFX_SAFE_RELEASE(_indexBuffer);
    _indexBuffer = ib;
    GFX_SAFE_RETAIN(_indexBuffer);
}

uint32_t InputAssembler::getPrimitiveCount() const
{
    if (-1 != _count)
        return _count;
    
    if (_indexBuffer)
        return _indexBuffer->getCount();
    
    assert(_vertexBuffer);
    return _vertexBuffer->getCount();
}

GFX_END
