#include "TextureGL.h"

#include "ccMacros.h"

CC_BACKEND_BEGIN

namespace
{
    GLint toGLMagFilter(SamplerFilter magFilter)
    {
        GLint ret = GL_LINEAR;
        switch (magFilter)
        {
            case SamplerFilter::LINEAR:
                ret = GL_LINEAR;
                break;
            case SamplerFilter::NEAREST:
                ret = GL_NEAREST;
                break;
            default:
                break;
        }
        return ret;
    }
    
    GLint toGLMinFilter(SamplerFilter minFilter, SamplerFilter mipmapFilter)
    {
        GLint ret = GL_LINEAR;
        switch (minFilter)
        {
            case SamplerFilter::LINEAR:
                switch (mipmapFilter)
                {
                    case SamplerFilter::LINEAR:
                        ret = GL_LINEAR_MIPMAP_LINEAR;
                        break;
                    case SamplerFilter::NEAREST:
                        ret = GL_LINEAR_MIPMAP_NEAREST;
                        break;
                    case SamplerFilter::NONE:
                    default:
                        break;
                }
                break;
            case SamplerFilter::NEAREST:
                switch (mipmapFilter)
                {
                    case SamplerFilter::LINEAR:
                        ret = GL_NEAREST_MIPMAP_LINEAR;
                        break;
                    case SamplerFilter::NEAREST:
                        ret = GL_NEAREST_MIPMAP_NEAREST;
                        break;
                    case SamplerFilter::NONE:
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        return ret;
    }
    
    GLint toGLAddressMode(SamplerAddressMode addressMode)
    {
        GLint ret = GL_REPEAT;
        switch (addressMode)
        {
            case SamplerAddressMode::REPEAT:
                ret = GL_REPEAT;
                break;
            case SamplerAddressMode::MIRROR_REPEAT:
                ret = GL_MIRRORED_REPEAT;
                break;
            case SamplerAddressMode::CLAMP_TO_EDGE:
                ret = GL_CLAMP_TO_EDGE;
                break;
            default:
                break;
        }
        return ret;
    }
}

TextureGL::TextureGL(const TextureDescriptor& descriptor) : Texture(descriptor)
{
    glGenTextures(1, &_texture);
    toGLTypes();
    
    _magFilterGL = toGLMagFilter(descriptor.samplerDescriptor.magFilter);
    _minFilterGL = toGLMinFilter(descriptor.samplerDescriptor.minFilter,
                                 descriptor.samplerDescriptor.mipmapFilter);
    
    _sAddressModeGL = toGLAddressMode(descriptor.samplerDescriptor.sAddressMode);
    _tAddressModeGL = toGLAddressMode(descriptor.samplerDescriptor.tAddressMode);
    
    // Update data here because `updateData()` may not be invoked later,
    // for example, a texture is used as depth buffer.
    uint8_t* data = (uint8_t*)malloc(_width * _height * _bytesPerElement);
    updateData(data);
    free(data);
}

TextureGL::~TextureGL()
{
    if (_texture)
        glDeleteTextures(1, &_texture);
}

void TextureGL::updateData(uint8_t* data)
{
    // TODO: support texture cube, and compressed data.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 _internalFormat,
                 _width,
                 _height,
                 0,
                 _format,
                 _type,
                 data);
    CHECK_GL_ERROR_DEBUG();
    
    generateMipmpas();
    CHECK_GL_ERROR_DEBUG();
}

void TextureGL::apply(int index) const
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _sAddressModeGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _tAddressModeGL);
}

void TextureGL::generateMipmpas() const
{
    if (TextureFormat::D16 != _textureFormat)
        glGenerateMipmap(GL_TEXTURE_2D);
}

void TextureGL::toGLTypes()
{
    switch (_textureFormat)
    {
        case TextureFormat::R8G8B8A8:
            _internalFormat = GL_RGBA;
            _format = GL_RGBA;
            _type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::R8G8B8:
            _internalFormat = GL_RGB;
            _format = GL_RGB;
            _type = GL_UNSIGNED_BYTE;
            break;
//        case TextureFormat::R5G5B5A1:
//            _internalFormat = GL_RGBA;
//            _format = GL_RGBA;
//            _type = GL_UNSIGNED_SHORT_5_5_5_1;
//            break;
//        case TextureFormat::R4G4B4A4:
//            _internalFormat = GL_RGBA;
//            _format = GL_RGBA;
//            _type = GL_UNSIGNED_SHORT_4_4_4_4;
//            break;
//        case TextureFormat::R5G6B5:
//            _internalFormat = GL_RGB;
//            _format = GL_RGB;
//            _type = GL_UNSIGNED_SHORT_5_6_5;
//            break;
        case TextureFormat::A8:
            _internalFormat = GL_ALPHA;
            _format = GL_ALPHA;
            _type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::D16:
            _format = GL_DEPTH_COMPONENT;
            _internalFormat = GL_DEPTH_COMPONENT;
            _type = GL_UNSIGNED_INT;
        case TextureFormat::D24S8:
            _format = GL_DEPTH_STENCIL_OES;
            _internalFormat = GL_DEPTH_STENCIL_OES;
            _type = GL_UNSIGNED_INT_24_8_OES;
            break;
        default:
            break;
    }
}

CC_BACKEND_END
