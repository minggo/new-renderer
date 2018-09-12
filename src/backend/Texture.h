#pragma once

#include "Types.h"

#include "base/CCRef.h"

CC_BACKEND_BEGIN

struct TextureDescriptor
{
    TextureType textureType = TextureType::TEXTURE_2D;
    TextureFormat textureFormat = TextureFormat::R8G8B8;
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t depth = 0;
};

class Texture : public cocos2d::Ref
{
public:
    virtual void updateData(uint8_t* data, uint32_t size) = 0;
    
protected:
    Texture(const TextureDescriptor& descriptor);
    virtual ~Texture();
    
    void computeBytesPerElement();
    
    uint32_t _width = 0;
    uint32_t _height = 0;
    // The bytes of all components.
    uint32_t _bytesPerElement = 0;
    TextureType _textureType = TextureType::TEXTURE_2D;
    TextureFormat _textureFormat = TextureFormat::R8G8B8;
};

CC_BACKEND_END
