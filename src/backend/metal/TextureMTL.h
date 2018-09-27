#pragma once

#include "../Texture.h"
#include "DeviceMTL.h"

CC_BACKEND_BEGIN

class TextureMTL : public Texture
{
public:
    TextureMTL(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor);
    ~TextureMTL();
    
    virtual void updateData(uint8_t* data) override;
    
    inline id<MTLTexture> getMTLTexture() const { return _metlTexture; }
    
private:
    id<MTLTexture> _metlTexture = nil;
    uint32_t _bytesPerRow = 0;
};

CC_BACKEND_END
