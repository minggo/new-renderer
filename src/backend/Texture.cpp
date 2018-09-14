#include "Texture.h"

CC_BACKEND_BEGIN

namespace
{
    uint8_t computeBytesPerElement(TextureFormat textureFormat)
    {
        uint8_t ret = 0;
        switch (textureFormat)
        {
            case TextureFormat::R8G8B8A8:
                ret = 4;
                break;
            case TextureFormat::R8G8B8:
                ret = 3;
                break;
            case TextureFormat::A8:
                ret = 1;
                break;
            case TextureFormat::R5G5B5A1:
            case TextureFormat::R4G4B4A4:
            case TextureFormat::R5G6B5:
            case TextureFormat::D16:
                ret = 2;
                break;
            default:
                break;
        }
        return ret;
    }
}

Texture::Texture(const TextureDescriptor& descriptor)
: _width(descriptor.width)
, _height(descriptor.height)
, _textureType(descriptor.textureType)
, _textureFormat(descriptor.textureFormat)
, _bytesPerElement(computeBytesPerElement(descriptor.textureFormat))
{
}

Texture::~Texture()
{}

CC_BACKEND_END
