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

#include "CCGraphicsHandle.h"
#include "base/CCData.h"

#include <vector>

GFX_BEGIN

class DeviceGraphics;

class Texture : public GraphicsHandle
{
protected:
    struct Options
    {
        Options()
        : anisotropy(1)
        , width(4)
        , height(4)
        , wrapS(TextureWrapMode::REPEAT)
        , wrapT(TextureWrapMode::REPEAT)
        , minFilter(TextureFilter::LINEAR)
        , magFilter(TextureFilter::LINEAR)
        , mipFilter(TextureFilter::LINEAR)
        , format(TextureFormat::RGBA8)
        , hasMipmap(false)
        , isFlipY(false)
        , isPremultiplyAlpha(false)
        {}

        std::vector<cocos2d::Data> images;
        int32_t anisotropy;
        uint16_t width;
        uint16_t height;

        TextureWrapMode wrapS;
        TextureWrapMode wrapT;

        TextureFilter minFilter;
        TextureFilter magFilter;
        TextureFilter mipFilter;
        TextureFormat format;
        bool hasMipmap;
        bool isFlipY;
        bool isPremultiplyAlpha;
    };

    struct ImageOption
    {
        ImageOption()
        : anisotropy(1)
        , level(0)
        , width(4)
        , height(4)
        , wrapS(TextureWrapMode::REPEAT)
        , wrapT(TextureWrapMode::REPEAT)
        , minFilter(TextureFilter::LINEAR)
        , magFilter(TextureFilter::LINEAR)
        , mipFilter(TextureFilter::LINEAR)
        , format(TextureFormat::RGBA8)
        , hasMipmap(false)
        , isFlipY(false)
        , isPremultiplyAlpha(false)
        {}

        cocos2d::Data image;
        int32_t anisotropy;
        int32_t level;
        uint16_t width;
        uint16_t height;

        TextureWrapMode wrapS;
        TextureWrapMode wrapT;

        TextureFilter minFilter;
        TextureFilter magFilter;
        TextureFilter mipFilter;
        TextureFormat format;
        bool hasMipmap;
        bool isFlipY;
        bool isPremultiplyAlpha;
    };

    struct SubImageOption
    {
        SubImageOption()
        : anisotropy(1)
        , level(0)
        , x(0)
        , y(0)
        , width(4)
        , height(4)
        , wrapS(TextureWrapMode::REPEAT)
        , wrapT(TextureWrapMode::REPEAT)
        , minFilter(TextureFilter::LINEAR)
        , magFilter(TextureFilter::LINEAR)
        , mipFilter(TextureFilter::LINEAR)
        , format(TextureFormat::RGBA8)
        , hasMipmap(false)
        , isFlipY(false)
        , isPremultiplyAlpha(false)
        {}

        cocos2d::Data image;
        int32_t anisotropy;
        int32_t level;
        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;

        TextureWrapMode wrapS;
        TextureWrapMode wrapT;

        TextureFilter minFilter;
        TextureFilter magFilter;
        TextureFilter mipFilter;
        TextureFormat format;
        bool hasMipmap;
        bool isFlipY;
        bool isPremultiplyAlpha;
    };

    Texture();
    virtual ~Texture();

    bool init(DeviceGraphics* device);
    inline GLuint getTarget() const { return _target; }

protected:

    static GLenum glFilter(TextureFilter filter, TextureFilter mipFilter = TextureFilter::NONE);

    struct GLTextureFmt
    {
        GLenum format;
        GLenum internalFormat;
        GLenum pixelType;
        uint8_t bpp;
    };
    static const GLTextureFmt& glTextureFmt(TextureFormat fmt);

    static bool isPow2(int32_t v) {
        return !(v & (v - 1)) && (!!v);
    }

    static GLTextureFmt _textureFmt[];

    DeviceGraphics* _device;
    GLint _anisotropy;
    GLuint _target;
    
    TextureWrapMode _wrapS;
    TextureWrapMode _wrapT;
    uint16_t _width;
    uint16_t _height;

    TextureFilter _minFilter;
    TextureFilter _magFilter;
    TextureFilter _mipFilter;
    TextureFormat _format;

    bool _hasMipmap;
    bool _compressed;
};

GFX_END
