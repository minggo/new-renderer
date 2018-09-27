#include "RenderPassMTL.h"
#include "TextureMTL.h"

CC_BACKEND_BEGIN

RenderPassMTL::RenderPassMTL(const RenderPassDescriptor& descriptor)
: RenderPass(descriptor)
{
    _renderPassDescritprMTL = [MTLRenderPassDescriptor renderPassDescriptor];
    [_renderPassDescritprMTL retain];
    
    const auto& renderPassColorAttachments = descriptor.getColorAttachments();
    int i = 0;
    for (const auto&texture : renderPassColorAttachments.textures)
    {
        if (LoadOp::CLEAR == renderPassColorAttachments.loadOp)
        {
            _renderPassDescritprMTL.colorAttachments[i].loadAction = MTLLoadActionClear;
            _renderPassDescritprMTL.colorAttachments[i].clearColor = MTLClearColorMake(renderPassColorAttachments.clearColor[0],
                                                                                       renderPassColorAttachments.clearColor[1],
                                                                                       renderPassColorAttachments.clearColor[2],
                                                                                       renderPassColorAttachments.clearColor[3]);
        }
        else
            _renderPassDescritprMTL.colorAttachments[i].loadAction = MTLLoadActionLoad;
        
        _renderPassDescritprMTL.colorAttachments[i].texture = static_cast<TextureMTL*>(texture)->getMTLTexture();
        _renderPassDescritprMTL.colorAttachments[i].storeAction = MTLStoreActionStore;
            
        ++i;
    }
}

CC_BACKEND_END
