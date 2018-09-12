#include "SamplerGL.h"

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

SamplerGL::SamplerGL(const SamplerDescriptor& descriptor)
{
    _magFilterGL = toGLMagFilter(descriptor.magFilter);
    _minFilterGL = toGLMinFilter(descriptor.minFilter, descriptor.mipmapFilter);
    
    _rAddressModeGL = toGLAddressMode(descriptor.rAddressMode);
    _sAddressModeGL = toGLAddressMode(descriptor.sAddressMode);
    _tAddressModeGL = toGLAddressMode(descriptor.tAssressMode);
}

void SamplerGL::apply() const
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilterGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, _rAddressModeGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _sAddressModeGL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _tAddressModeGL);
}

CC_BACKEND_END
