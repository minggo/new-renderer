#include "Texture.h"

CC_BACKEND_BEGIN

Texture::Texture(const TextureDescriptor& descriptor)
: _width(descriptor.width)
, _height(descriptor.height)
, _textureType(descriptor.textureType)
, _textureFormat(descriptor.textureFormat)
{
}

Texture::~Texture()
{}

void Texture::computeBytesPerElement()
{
    switch (_textureFormat)
    {
        case TextureFormat::R8G8B8A8:
            _bytesPerElement = 4;
            break;
        case TextureFormat::R8G8B8:
            _bytesPerElement = 3;
            break;
        case TextureFormat::A8:
            _bytesPerElement = 1;
            break;
        case TextureFormat::R5G5B5A1:
        case TextureFormat::R4G4B4A4:
        case TextureFormat::R5G6B5:
            _bytesPerElement = 2;
            break;
        default:
            break;
    }
}

CC_BACKEND_END
