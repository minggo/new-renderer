#pragma once

#include "Macros.h"
#include "Types.h"

#include <array>
#include <vector>

CC_BACKEND_BEGIN

class Texture;
class RenderPass;

struct RenderPassColorAttachments
{
    ~RenderPassColorAttachments();
    RenderPassColorAttachments& operator=(const RenderPassColorAttachments& rhs);
    void setTexture(uint32_t attachment, Texture* texture);
    
    std::vector<Texture*> textures;
    std::array<float, 4> clearColor = {0.f, 0.f, 0.f, 0.f};
    LoadOp loadOp = LoadOp::CLEAR;
    
private:
    void releaseTextures() const;
    void retainTextures() const;
};

struct RenderPassDepthStencilAttachment
{
    RenderPassDepthStencilAttachment& operator = (const RenderPassDepthStencilAttachment& rhs);
    ~RenderPassDepthStencilAttachment();
    
    LoadOp depthLoadOp = LoadOp::CLEAR;
    LoadOp stencilLoadOp = LoadOp::CLEAR;
    float clearDepth = 1.f;
    uint32_t clearStencil = 0;
    Texture *texture = nullptr;
};

class RenderPassDescriptor
{
public:
    void setColorAttachment(uint32_t attachment, Texture* texture);
    void setColorAttachmentsClearColor(float r, float g, float b, float a);
    void setColorAttachmentsLoadOp(LoadOp loadOp);
    void setDepthStencilAttachment(Texture* texture, LoadOp depthLoadOp, LoadOp stencilLoadOp);
    void setDepthStencilAttachmentClearValue(float clearDepth, float clearStencil);
    
    inline const RenderPassDepthStencilAttachment& getDepthStencilAttachment() const { return _depthStencilAttachment; }
    inline const RenderPassColorAttachments& getColorAttachments() const { return _colorAttachments; }
    
private:
    bool _colorAttachmentsSet = false;
    RenderPassColorAttachments _colorAttachments;
    
    bool _depthStencilAttachmentSet = false;
    struct RenderPassDepthStencilAttachment _depthStencilAttachment;
    
    friend class RenderPass;
};

CC_BACKEND_END
