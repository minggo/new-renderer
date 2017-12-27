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

#include "CCRenderTarget.h"
#include "CCRenderBuffer.h"
#include "CCTexture2D.h"

GFX_BEGIN

RenderTarget::RenderTarget()
: _tex(nullptr)
, _rb(nullptr)
{

}

RenderTarget::~RenderTarget()
{
    GFX_SAFE_RELEASE(_tex);
    GFX_SAFE_RELEASE(_rb);
}

bool RenderTarget::initWithTexture(Texture2D* tex)
{
    _tex = tex;
    GFX_SAFE_RETAIN(_tex);
    return true;
}

bool RenderTarget::initWithRenderBuffer(RenderBuffer* rb)
{
    _rb = rb;
    GFX_SAFE_RETAIN(_rb);
    return true;
}

GLuint RenderTarget::getHandle() const
{
    if (_tex != nullptr)
        return _tex->getHandle();

    if (_rb != nullptr)
        return _rb->getHandle();

    return 0;
}

GFX_END
