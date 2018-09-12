#pragma once

#include "Types.h"
#include "RenderPassDescriptor.h"
#include "base/CCRef.h"

CC_BACKEND_BEGIN

class RenderPass : public cocos2d::Ref
{
public:
    bool hasDepthStencilAttachment() const { return _depthStencilAttachmentSet; }
    bool hasColorAttachments() const { return _colorAttachmentsSet; }
    
protected:
    RenderPass(const RenderPassDescriptor& descriptor);
    virtual ~RenderPass();
    
    bool _depthStencilAttachmentSet = false;
    RenderPassDepthStencilAttachment _depthStencilAttachment;
    
    bool _colorAttachmentsSet = false;
    RenderPassColorAttachments _colorAttachments;
};

CC_BACKEND_END
