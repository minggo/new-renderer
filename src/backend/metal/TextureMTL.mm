#include "TextureMTL.h"

CC_BACKEND_BEGIN

namespace
{
    MTLPixelFormat toMTLPixelFormat(TextureFormat textureFormat)
    {
        MTLPixelFormat ret = MTLPixelFormatRGBA8Unorm;
        switch (textureFormat)
        {
            case TextureFormat::R8G8B8A8:
                ret = MTLPixelFormatRGBA8Unorm;
                break;
            // Should transfer the data to match pixel format when updating data.
            case TextureFormat::R8G8B8:
                ret = MTLPixelFormatRGBA8Unorm;
                break;
            case TextureFormat::A8:
                ret = MTLPixelFormatA8Unorm;
                break;
            case TextureFormat::D16:
                ret = MTLPixelFormatDepth16Unorm;
                break;
            default:
                break;
        }
        return ret;
    }
}

TextureMTL::TextureMTL(id<MTLDevice> mtlDevice, const TextureDescriptor& descriptor)
: Texture(descriptor)
{
    MTLTextureDescriptor* textureDescriptor = [[MTLTextureDescriptor alloc] init];
    textureDescriptor.width = descriptor.width;
    textureDescriptor.height = descriptor.height;
    textureDescriptor.pixelFormat = toMTLPixelFormat(descriptor.textureFormat);
    _metlTexture = [mtlDevice newTextureWithDescriptor:textureDescriptor];
    [textureDescriptor release];
    
    _bytesPerRow = _bytesPerElement * descriptor.width * descriptor.height;
}

TextureMTL::~TextureMTL()
{
    [_metlTexture release];
}

void TextureMTL::updateData(uint8_t* data)
{
    MTLRegion region =
    {
        { 0, 0, 0 },                               // MTLOrigin
        {_metlTexture.width, _metlTexture.height, 1} // MTLSize
    };
    [_metlTexture replaceRegion:region
                   mipmapLevel:0
                     withBytes:data
                   bytesPerRow:_bytesPerRow];
}

CC_BACKEND_END
