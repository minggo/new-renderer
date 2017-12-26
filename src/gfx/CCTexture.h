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

#include <vector>

GFX_BEGIN

class DeviceGraphics;
class Image;

class Texture : public GraphicsHandle
{
protected:
    struct InitOptions
    {
        std::vector<Image*> images;
        bool hasMipmap;
        uint16_t width;
        uint16_t height;
        
    };

    Texture();
    virtual ~Texture();

    bool init(DeviceGraphics* device);
    inline GLuint getTarget() const { return _target; }

protected:
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
