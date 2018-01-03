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

#include "CCTexture2D.h"
#include "CCDeviceGraphics.h"
#include "CCGFXUtils.h"

namespace {

    //TODO: OpenGL ES 2.0 < WebGL < OpenGL 3.0
    // Refer to https://yq.aliyun.com/articles/62339
//    const GLuint GL_UNPACK_FLIP_Y_WEBGL = 0x9240;
//    const GLuint GL_UNPACK_PREMULTIPLY_ALPHA_WEBGL = 0x9241;
//    const GLuint GL_UNPACK_COLORSPACE_CONVERSION_WEBGL = 0x9243;
}

GFX_BEGIN

Texture2D::Texture2D()
{

}

Texture2D::~Texture2D()
{

}

bool Texture2D::init(DeviceGraphics* device, Options& options)
{
    bool ok = Texture::init(device);
    if (ok)
    {
        _target = GL_TEXTURE_2D;
        GL_CHECK(glGenTextures(1, &_glID));
        
        if (options.images.empty())
            options.images.push_back(Data());
        
        update(options);
    }
    return ok;
}

void Texture2D::update(const Options& options)
{
    bool genMipmap = _hasMipmap;

     _width = options.width;
    _height = options.height;
    _anisotropy = options.anisotropy;
    _minFilter = options.minFilter;
    _magFilter = options.magFilter;
    _mipFilter = options.mipFilter;
    _wrapS = options.wrapS;
    _wrapT = options.wrapT;
    _format = options.format;
    _compressed = _format >= TextureFormat::RGB_DXT1 && _format <= TextureFormat::RGBA_PVRTC_4BPPV1;

    // check if generate mipmap
    _hasMipmap = options.hasMipmap;
    genMipmap = options.hasMipmap;

    if (options.images.size() > 1)
    {
        genMipmap = false; //TODO: is it true here?
        uint16_t maxLength = options.width > options.height ? options.width : options.height;
        if (maxLength >> (options.images.size() - 1) != 1) {
            GFX_LOGE("texture-2d mipmap is invalid, should have a 1x1 mipmap.");
        }
    }

    // NOTE: get pot after _width, _height has been assigned.
    bool pot = isPow2(_width) && isPow2(_height);
    if (!pot) {
        genMipmap = false;
    }

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, _glID));
    if (!options.images.empty()) {
        setMipmap(options.images, options.isFlipY, options.isPremultiplyAlpha);
    }

    setTexInfo();

    if (genMipmap) {
        GL_CHECK(glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST));
        GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
    }
    _device->restoreTexture(0);
}

void Texture2D::updateSubImage(const SubImageOption& option)
{
    const GLTextureFmt& glFmt = glTextureFmt(_format);

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, _glID));
    setSubImage(glFmt, option);
    _device->restoreTexture(0);
}

void Texture2D::updateImage(const ImageOption& option)
{
    const GLTextureFmt& glFmt = glTextureFmt(_format);

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, _glID));
    setImage(glFmt, option);
    _device->restoreTexture(0);
}

// Private methods:

void Texture2D::setSubImage(const GLTextureFmt& glFmt, const SubImageOption& option)
{
    bool flipY = option.isFlipY;
    bool premultiplyAlpha = option.isPremultiplyAlpha;
    const auto& img = option.image;

    //TODO:    GL_CHECK(glPixelStorei(GL_UNPACK_FLIP_Y_WEBGL, flipY));
//    GL_CHECK(glPixelStorei(GL_UNPACK_PREMULTIPLY_ALPHA_WEBGL, premultiplyAlpha));

    //Set the row align only when mipmapsNum == 1 and the data is uncompressed
    if (!_hasMipmap && !_compressed && glFmt.bpp > 0)
    {
        unsigned int bytesPerRow = option.width * glFmt.bpp / 8;

        if(bytesPerRow % 8 == 0)
        {
            GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 8));
        }
        else if(bytesPerRow % 4 == 0)
        {
            GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 4));
        }
        else if(bytesPerRow % 2 == 0)
        {
            GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 2));
        }
        else
        {
            GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
        }
    }
    else
    {
        GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    }

    if (_compressed)
    {
        GL_CHECK(glCompressedTexSubImage2D(GL_TEXTURE_2D,
                                   option.level,
                                   option.x,
                                   option.y,
                                   option.width,
                                   option.height,
                                   glFmt.format,
                                   (GLsizei)img.getSize(),
                                   img.getBytes()
                                   ));
    }
    else
    {
        GL_CHECK(glTexSubImage2D( GL_TEXTURE_2D,
                         option.level,
                         option.x,
                         option.y,
                         option.width,
                         option.height,
                         glFmt.format,
                         glFmt.pixelType,
                         img.getBytes()
                         ));
    }
}

void Texture2D::setImage(const GLTextureFmt& glFmt, const ImageOption& option)
{
    bool flipY = option.isFlipY;
    bool premultiplyAlpha = option.isPremultiplyAlpha;
    const auto& img = option.image;

    //TODO:    GL_CHECK(glPixelStorei(GL_UNPACK_FLIP_Y_WEBGL, flipY));
//    GL_CHECK(glPixelStorei(GL_UNPACK_PREMULTIPLY_ALPHA_WEBGL, premultiplyAlpha));

    //Set the row align only when mipmapsNum == 1 and the data is uncompressed
    if (!_hasMipmap && !_compressed && glFmt.bpp > 0)
    {
        unsigned int bytesPerRow = option.width * glFmt.bpp / 8;

        if(bytesPerRow % 8 == 0)
        {
            GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 8));
        }
        else if(bytesPerRow % 4 == 0)
        {
            GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 4));
        }
        else if(bytesPerRow % 2 == 0)
        {
            GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 2));
        }
        else
        {
            GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
        }
    }
    else
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    }

    if (_compressed) {
        GL_CHECK(glCompressedTexImage2D(
                                GL_TEXTURE_2D,
                                option.level,
                                glFmt.internalFormat,
                                option.width,
                                option.height,
                                0,
                                (GLsizei)img.getSize(),
                                img.getBytes()
                                ));
    } else {
        GL_CHECK(glTexImage2D( GL_TEXTURE_2D,
                      option.level,
                      glFmt.internalFormat,
                      option.width,
                      option.height,
                      0,
                      glFmt.format,
                      glFmt.pixelType,
                      img.getBytes()
                      ));
    }
}

void Texture2D::setMipmap(const std::vector<cocos2d::Data>& images, bool isFlipY, bool isPremultiplyAlpha)
{
    const auto& glFmt = glTextureFmt(_format);
    ImageOption options;
    options.width = _width;
    options.height = _height;
    options.isFlipY = isFlipY;
    options.isPremultiplyAlpha = isPremultiplyAlpha;
    options.level = 0;

    for (size_t i = 0, len = images.size(); i < len; ++i)
    {
        options.level = (GLint)i;
        options.width = _width >> i;
        options.height = _height >> i;
        options.image = images[i];
        setImage(glFmt, options);
    }
}

void Texture2D::setTexInfo()
{
    bool pot = isPow2(_width) && isPow2(_height);

    // WebGL1 doesn't support all wrap modes with NPOT textures
    if (!pot && (_wrapS != TextureWrapMode::CLAMP || _wrapT != TextureWrapMode::CLAMP))
    {
        GFX_LOGW("WebGL1 doesn\'t support all wrap modes with NPOT textures");
        _wrapS = TextureWrapMode::CLAMP;
        _wrapT = TextureWrapMode::CLAMP;
    }

    TextureFilter mipFilter = _hasMipmap ? _mipFilter : TextureFilter::NONE;
    if (!pot && mipFilter != TextureFilter::NONE)
    {
        GFX_LOGW("NPOT textures do not support mipmap filter");
        mipFilter = TextureFilter::NONE;
    }

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glFilter(_minFilter, mipFilter)));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glFilter(_magFilter, TextureFilter::NONE)));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)_wrapS));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)_wrapT));

    //TODO:    let ext = this._device.ext('EXT_texture_filter_anisotropic');
//    if (ext) {
//        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, ext.TEXTURE_MAX_ANISOTROPY_EXT, this._anisotropy));
//    }
}

GFX_END
