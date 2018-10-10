#include "RenderPassMTL.h"
#include "TextureMTL.h"
#include "DeviceMTL.h"

CC_BACKEND_BEGIN

RenderPassMTL::RenderPassMTL(id<MTLDevice> mtlDevice, const RenderPassDescriptor& descriptor)
: RenderPass(descriptor)
{
    if (_colorAttachmentsSet || _depthStencilAttachmentSet)
    {
        _renderPassDescritprMTL = [MTLRenderPassDescriptor renderPassDescriptor];
        [_renderPassDescritprMTL retain];
        _newRenderPassDescriptorMTL = true;
        
        // Set color attachments.
        if (_colorAttachmentsSet)
        {
            const auto& renderPassColorAttachments = descriptor.getColorAttachments();
            int i = 0;
            for (const auto&texture : renderPassColorAttachments.textures)
            {
                if (!texture)
                    continue;
                
                if (renderPassColorAttachments.needClearColor)
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
        
        // Set depth&stencil attachment.
        const auto& renderPassDepthStencilAttachment = descriptor.getDepthStencilAttachment();
        if (_depthStencilAttachmentSet)
        {
            _renderPassDescritprMTL.depthAttachment.texture = static_cast<TextureMTL*>(renderPassDepthStencilAttachment.texture)->getMTLTexture();
            _renderPassDescritprMTL.stencilAttachment.texture = static_cast<TextureMTL*>(renderPassDepthStencilAttachment.texture)->getMTLTexture();
        }
    }
    else
        _renderPassDescritprMTL = DeviceMTL::getDefaultMTLRenderPassDescriptor();
    
    // Set depth clear value
    const auto& renderPassDepthStencilAttachment = descriptor.getDepthStencilAttachment();
    if (renderPassDepthStencilAttachment.needClearDepth)
    {
        _renderPassDescritprMTL.depthAttachment.loadAction = MTLLoadActionClear;
        _renderPassDescritprMTL.depthAttachment.clearDepth = renderPassDepthStencilAttachment.clearDepth;
    }
    else
        _renderPassDescritprMTL.depthAttachment.loadAction = MTLLoadActionLoad;
    
    // Set stencil clear value.
    if (renderPassDepthStencilAttachment.needClearStencil)
    {
        _renderPassDescritprMTL.stencilAttachment.loadAction = MTLLoadActionClear;
        _renderPassDescritprMTL.stencilAttachment.clearStencil = renderPassDepthStencilAttachment.clearStencil;
    }
    else
        _renderPassDescritprMTL.stencilAttachment.loadAction = MTLLoadActionLoad;
}

RenderPassMTL::~RenderPassMTL()
{
    if (_newRenderPassDescriptorMTL)
        [_renderPassDescritprMTL release];
}

CC_BACKEND_END
