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
        clearColor = rhs.clearColor;
        needClearColor = rhs.needClearColor;
        
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
        needClearDepth = rhs.needClearDepth;
        needClearStencil = rhs.needClearStencil;
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

void RenderPassDescriptor::setClearColor(float r, float g, float b, float a)
{
    _colorAttachments.clearColor = {r, g, b, a};
    _colorAttachments.needClearColor = true;
}

void RenderPassDescriptor::setDepthStencilAttachment(Texture* texture)
{
    CC_SAFE_RETAIN(texture);
    CC_SAFE_RELEASE(_depthStencilAttachment.texture);
    _depthStencilAttachment.texture = texture;
    
    if (texture)
        _depthStencilAttachmentSet = true;
}

void RenderPassDescriptor::setDepthClearValue(float clearValue)
{
    _depthStencilAttachment.clearDepth = clearValue;
    _depthStencilAttachment.needClearDepth = true;
}

void RenderPassDescriptor::setStencilClearValue(uint32_t clearValue)
{
    _depthStencilAttachment.clearStencil = clearValue;
    _depthStencilAttachment.needClearStencil = true;
}

bool RenderPassDescriptor::hasStencil() const
{
    return (_depthStencilAttachmentSet &&
            TextureFormat::D24S8 == _depthStencilAttachment.texture->getTextureFormat());
}

CC_BACKEND_END
