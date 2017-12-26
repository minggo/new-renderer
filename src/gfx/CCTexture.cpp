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

#include "CCTexture.h"

GFX_BEGIN

Texture::Texture()
: _device(nullptr)
, _anisotropy(1)
, _target(INVALID)
, _wrapS(TextureWrapMode::REPEAT)
, _wrapT(TextureWrapMode::REPEAT)
, _width(4)
, _height(4)
, _minFilter(TextureFilter::LINEAR)
, _magFilter(TextureFilter::LINEAR)
, _mipFilter(TextureFilter::LINEAR)
, _format(TextureFormat::RGBA8)
, _hasMipmap(false)
, _compressed(false)
{

}

Texture::~Texture()
{
    if (_glID == INVALID) {
        GFX_LOGE("Invalid texture: %p", this);
        return;
    }

    glDeleteTextures(1, &_glID);

    //TODO:    this._device._stats.tex -= this.bytes;
}

bool Texture::init(DeviceGraphics* device)
{
    _device = device;
    _width = 4;
    _height = 4;
    _hasMipmap = false;
    _compressed = false;

    _anisotropy = 1;
    _minFilter = TextureFilter::LINEAR;
    _magFilter = TextureFilter::LINEAR;
    _mipFilter = TextureFilter::LINEAR;
    _wrapS = TextureWrapMode::REPEAT;
    _wrapT = TextureWrapMode::REPEAT;
    // wrapR available in webgl2
    // _wrapR = TextureWrapMode::REPEAT;
    _format = TextureFormat::RGBA8;

    _target = -1;
    return true;
}

GFX_END

