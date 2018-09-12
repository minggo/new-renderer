#include "RenderPass.h"

CC_BACKEND_BEGIN

RenderPass::RenderPass(const RenderPassDescriptor& descriptor)
: _depthStencilAttachmentSet(descriptor._depthStencilAttachmentSet)
, _depthStencilAttachment(descriptor._depthStencilAttachment)
, _colorAttachmentsSet(descriptor._colorAttachmentsSet)
, _colorAttachments(descriptor._colorAttachments)
{
}

RenderPass::~RenderPass()
{}

CC_BACKEND_END
