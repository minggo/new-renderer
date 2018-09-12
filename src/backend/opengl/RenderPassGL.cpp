#include "RenderPassGL.h"
#include "TextureGL.h"
#include "ccMacros.h"

CC_BACKEND_BEGIN

RenderPassGL::RenderPassGL(const RenderPassDescriptor& descriptor) : RenderPass(descriptor)
{

    
    if (_depthStencilAttachmentSet || _colorAttachmentsSet)
        glGenFramebuffers(1, &_frameBuffer);
}

void RenderPassGL::apply(GLuint defaultFrameBuffer) const
{
    if (_frameBuffer)
    {
        // depth and stencil buffer
        glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
        if (_depthStencilAttachmentSet && _depthStencilAttachment.texture)
        {
            auto textureGL = static_cast<TextureGL*>(_depthStencilAttachment.texture);
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_DEPTH_ATTACHMENT,
                                   GL_TEXTURE_2D,
                                   textureGL->getHandler(),
                                   0);
            
            //TODO: check if has stencil
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_STENCIL_ATTACHMENT,
                                   GL_TEXTURE_2D,
                                   textureGL->getHandler(),
                                   0);
        }
        
        // color buffer
        if (_colorAttachmentsSet)
        {
            int i = 0;
            for (const auto& texture : _colorAttachments.textures)
            {
                if (texture)
                {
                    // TODO: support texture cube
                    auto textureGL = static_cast<TextureGL*>(texture);
                    glFramebufferTexture2D(GL_FRAMEBUFFER,
                                           GL_COLOR_ATTACHMENT0 + i,
                                           GL_TEXTURE_2D,
                                           textureGL->getHandler(),
                                           0);
                }
                ++i;
            }
        }
    }
    else
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFrameBuffer);
    
    CHECK_GL_ERROR_DEBUG();
        
    // set clear color, depth and stencil
    GLbitfield mask = 0;
    if (LoadOp::CLEAR == _colorAttachments.loadOp)
    {
        mask |= GL_COLOR_BUFFER_BIT;
        const auto& clearColor = _colorAttachments.clearColor;
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    GLboolean oldDepthWrite = GL_FALSE;
    GLboolean oldDepthTest = GL_FALSE;
    GLfloat oldDepthClearValue = 0.f;
    GLint oldDepthFunc = GL_LESS;
    if (LoadOp::CLEAR == _depthStencilAttachment.depthLoadOp)
    {
        glGetBooleanv(GL_DEPTH_WRITEMASK, &oldDepthWrite);
        glGetBooleanv(GL_DEPTH_TEST, &oldDepthTest);
        glGetFloatv(GL_DEPTH_CLEAR_VALUE, &oldDepthClearValue);
        glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFunc);
        
        mask |= GL_DEPTH_BUFFER_BIT;
        glClearDepth(_depthStencilAttachment.clearDepth);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_ALWAYS);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    if (LoadOp::CLEAR == _depthStencilAttachment.stencilLoadOp)
    {
        mask |= GL_STENCIL_BUFFER_BIT;
        glClearStencil(_depthStencilAttachment.clearStencil);
    }
    glClear(mask);
    
    CHECK_GL_ERROR_DEBUG();
    
    // restore depth test
    if (LoadOp::CLEAR == _depthStencilAttachment.depthLoadOp)
    {
        if (!oldDepthTest)
            glDisable(GL_DEPTH_TEST);
        
        glDepthMask(oldDepthWrite);
        glDepthFunc(oldDepthFunc);
        glClearDepth(oldDepthClearValue);
    }
    
    CHECK_GL_ERROR_DEBUG();
}

CC_BACKEND_END
