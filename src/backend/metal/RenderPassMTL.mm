#include "RenderPassMTL.h"
#include "TextureMTL.h"
#include "DeviceMTL.h"
#include "Utils.h"

CC_BACKEND_BEGIN

RenderPassMTL::RenderPassMTL(id<MTLDevice> mtlDevice, const RenderPassDescriptor& descriptor)
: RenderPass(descriptor)
{
    if (_colorAttachmentsSet || _depthStencilAttachmentSet)
        _renderPassDescritprMTL = [MTLRenderPassDescriptor renderPassDescriptor];
    else
        _renderPassDescritprMTL = Utils::getDefaultRenderPassDescriptor();
    [_renderPassDescritprMTL retain];
    
    setColorAttachments(descriptor);
    setDepthStencilAttachment(descriptor);
}

RenderPassMTL::~RenderPassMTL()
{
    if (!_colorAttachmentsSet && !_depthStencilAttachmentSet)
        [_renderPassDescritprMTL release];
}

MTLRenderPassDescriptor* RenderPassMTL::getMTLRenderPassDescriptor()
{
    if (!_colorAttachmentsSet && !_depthStencilAttachmentSet)
    {
        const auto& defaultRenderPassDescriptor = Utils::getDefaultRenderPassDescriptor();
        if (!_colorAttachmentsSet)
            _renderPassDescritprMTL.colorAttachments[0].texture = defaultRenderPassDescriptor.colorAttachments[0].texture;
        if (!_depthStencilAttachmentSet)
            _renderPassDescritprMTL.depthAttachment.texture = defaultRenderPassDescriptor.depthAttachment.texture;
    }
    
    return _renderPassDescritprMTL;
}

void RenderPassMTL::setColorAttachments(const RenderPassDescriptor& descriptor)
{
    const auto& renderPassColorAttachments = descriptor.getColorAttachments();
    if (_colorAttachmentsSet)
    {
        int i = 0;
        for (const auto& texture : renderPassColorAttachments.textures)
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
    else
    {
        _renderPassDescritprMTL.colorAttachments[0].texture = Utils::getTempColorAttachmentTexture();
        if (renderPassColorAttachments.needClearColor)
        {
            _renderPassDescritprMTL.colorAttachments[0].loadAction = MTLLoadActionClear;
            _renderPassDescritprMTL.colorAttachments[0].clearColor = MTLClearColorMake(renderPassColorAttachments.clearColor[0],
                                                                                       renderPassColorAttachments.clearColor[1],
                                                                                       renderPassColorAttachments.clearColor[2],
                                                                                       renderPassColorAttachments.clearColor[3]);
        }
    }
}

void RenderPassMTL::setDepthStencilAttachment(const RenderPassDescriptor &descriptor)
{
    // Set depth/stencil attachment.
    const auto& renderPassDepthStencilAttachment = descriptor.getDepthStencilAttachment();
    if (_depthStencilAttachmentSet)
    {
        const auto& textureMTL = static_cast<TextureMTL*>(renderPassDepthStencilAttachment.texture);
        _renderPassDescritprMTL.depthAttachment.texture = textureMTL->getMTLTexture();
        _renderPassDescritprMTL.stencilAttachment.texture = textureMTL->getMTLTexture();
    }
    
    // Set depth clear value.
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

CC_BACKEND_END
