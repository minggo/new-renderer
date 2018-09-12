#include "RenderPassDescriptor.h"
#include "Texture.h"

CC_BACKEND_BEGIN

RenderPassColorAttachments::~RenderPassColorAttachments()
{
    releaseTextures();
}

RenderPassColorAttachments& RenderPassColorAttachments::operator=(const RenderPassColorAttachments& rhs)
{
    if (this != &rhs)
    {
        loadOp = rhs.loadOp;
        clearColor = rhs.clearColor;
        
        rhs.retainTextures();
        releaseTextures();
        textures = rhs.textures;
    }
    return *this;
}

void RenderPassColorAttachments::setTexture(uint32_t attachment, Texture* texture)
{
    if (attachment >= textures.size())
        textures.resize(attachment + 1);
    
    CC_SAFE_RETAIN(texture);
    CC_SAFE_RELEASE(textures[attachment]);
    textures[attachment] = texture;
}

void RenderPassColorAttachments::releaseTextures() const
{
    for (const auto& texture: textures)
        CC_SAFE_RELEASE(texture);
}

void RenderPassColorAttachments::retainTextures() const
{
    for (const auto& texture: textures)
        CC_SAFE_RETAIN(texture);
}

RenderPassDepthStencilAttachment& RenderPassDepthStencilAttachment::operator=(const RenderPassDepthStencilAttachment& rhs)
{
    if (this != &rhs)
    {
        depthLoadOp = rhs.depthLoadOp;
        stencilLoadOp = rhs.stencilLoadOp;
        clearDepth = rhs.clearDepth;
        clearStencil = rhs.clearStencil;
        
        CC_SAFE_RETAIN(rhs.texture);
        CC_SAFE_RELEASE(texture);
        texture = rhs.texture;
    }
    return *this;
}

RenderPassDepthStencilAttachment::~RenderPassDepthStencilAttachment()
{
    CC_SAFE_RELEASE(texture);
}

void RenderPassDescriptor::setColorAttachment(uint32_t attachment, Texture* texture)
{
    _colorAttachments.setTexture(attachment, texture);
    
    if (texture)
        _colorAttachmentsSet = true;
}

void RenderPassDescriptor::setColorAttachmentsClearColor(float r, float g, float b, float a)
{
    _colorAttachments.clearColor = {r, g, b, a};
}

void RenderPassDescriptor::setColorAttachmentsLoadOp(LoadOp loadOp)
{
    _colorAttachments.loadOp = loadOp;
}

void RenderPassDescriptor::setDepthStencilAttachment(Texture* texture, LoadOp depthLoadOp, LoadOp stencilLoadOp)
{
    CC_SAFE_RETAIN(texture);
    CC_SAFE_RELEASE(_depthStencilAttachment.texture);
    _depthStencilAttachment.texture = texture;
    
    _depthStencilAttachment.stencilLoadOp = stencilLoadOp;
    _depthStencilAttachment.depthLoadOp = depthLoadOp;
    
    if (texture)
        _depthStencilAttachmentSet = true;
}

void RenderPassDescriptor::setDepthStencilAttachmentClearValue(float clearDepth, float clearStencil)
{
    _depthStencilAttachment.clearDepth = clearDepth;
    _depthStencilAttachment.clearStencil = clearStencil;
}

CC_BACKEND_END
