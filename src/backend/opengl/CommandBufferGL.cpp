#include "CommandBufferGL.h"
#include "BufferGL.h"
#include "RenderPipelineGL.h"
#include "TextureGL.h"
#include "DepthStencilStateGL.h"
#include "ProgramGL.h"
#include "BlendStateGL.h"
#include "ccMacros.h"

CC_BACKEND_BEGIN

namespace
{
    GLenum toGLPrimitiveType(PrimitiveType primitiveType)
    {
        GLenum ret = GL_TRIANGLES;
        switch (primitiveType)
        {
            case PrimitiveType::POINT:
                ret = GL_POINTS;
                break;
            case PrimitiveType::LINE:
                ret = GL_LINES;
                break;
            case PrimitiveType::LINE_STRIP:
                ret = GL_LINE_STRIP;
                break;
            case PrimitiveType::TRIANGLE:
                ret = GL_TRIANGLES;
                break;
            case PrimitiveType::TRIANGLE_STRIP:
                ret = GL_TRIANGLE_STRIP;
                break;
            default:
                break;
        }
        return ret;
    }
    
    GLenum toGLIndexType(IndexFormat indexType)
    {
        GLenum ret = GL_BYTE;
        switch (indexType)
        {
            case IndexFormat::U_INT:
                ret = GL_UNSIGNED_INT;
                break;
            case IndexFormat::U_SHORT:
                ret = GL_UNSIGNED_SHORT;
                break;
            default:
                break;
        }
        return ret;
    }
    
    GLenum toGLCullMode(CullMode mode)
    {
        if (CullMode::BACK == mode)
            return GL_BACK;
        else
            return GL_FRONT;
    }
}

CommandBufferGL::CommandBufferGL()
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_defaultFBO);
}

CommandBufferGL::~CommandBufferGL()
{
    cleanResources();
}

void CommandBufferGL::beginFrame()
{
}

void CommandBufferGL::beginRenderPass(const RenderPassDescriptor& descirptor)
{
    applyRenderPassDescriptor(descirptor);
}

void CommandBufferGL::applyRenderPassDescriptor(const RenderPassDescriptor& descirptor)
{
    bool useColorAttachmentExternal = descirptor.needColorAttachment && descirptor.colorAttachmentsTexture[0];
    bool useDepthAttachmentExternal = descirptor.needDepthAttachment && descirptor.depthAttachmentTexture;
    bool useStencilAttachmentExternal = descirptor.needStencilAttachment && descirptor.stencilAttachmentTexture;
    if (useColorAttachmentExternal || useDepthAttachmentExternal || useStencilAttachmentExternal)
    {
        glGenFramebuffers(1, &_currentFBO);
    }
    else
    {
        _currentFBO = _defaultFBO;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, _currentFBO);
    
    if (useDepthAttachmentExternal)
    {
        auto depthTexture = static_cast<TextureGL*>(descirptor.depthAttachmentTexture);
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               GL_DEPTH_ATTACHMENT,
                               GL_TEXTURE_2D,
                               depthTexture->getHandler(),
                               0);
        CHECK_GL_ERROR_DEBUG();
    }
        
    if (useStencilAttachmentExternal)
    {
        auto stencilTexture = static_cast<TextureGL*>(descirptor.depthAttachmentTexture);
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               GL_STENCIL_ATTACHMENT,
                               GL_TEXTURE_2D,
                               stencilTexture->getHandler(),
                               0);
        CHECK_GL_ERROR_DEBUG();
    }
    
    if (descirptor.needColorAttachment)
    {
        int i = 0;
        for (const auto& texture : descirptor.colorAttachmentsTexture)
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
            CHECK_GL_ERROR_DEBUG();
            ++i;
        }
    }
    else
    {
        // If not draw buffer is needed, should invoke this line explicitly, or it will cause
        // GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER and GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER error.
        // https://stackoverflow.com/questions/28313782/porting-opengl-es-framebuffer-to-opengl
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
#endif
    }
    CHECK_GL_ERROR_DEBUG();
    
    // set clear color, depth and stencil
    GLbitfield mask = 0;
    if (descirptor.needClearColor)
    {
        mask |= GL_COLOR_BUFFER_BIT;
        const auto& clearColor = descirptor.clearColorValue;
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    GLboolean oldDepthWrite = GL_FALSE;
    GLboolean oldDepthTest = GL_FALSE;
    GLfloat oldDepthClearValue = 0.f;
    GLint oldDepthFunc = GL_LESS;
    if (descirptor.needClearDepth)
    {
        glGetBooleanv(GL_DEPTH_WRITEMASK, &oldDepthWrite);
        glGetBooleanv(GL_DEPTH_TEST, &oldDepthTest);
        glGetFloatv(GL_DEPTH_CLEAR_VALUE, &oldDepthClearValue);
        glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFunc);
        
        mask |= GL_DEPTH_BUFFER_BIT;
        glClearDepth(descirptor.clearDepthValue);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_ALWAYS);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    if (descirptor.needClearStencil)
    {
        mask |= GL_STENCIL_BUFFER_BIT;
        glClearStencil(descirptor.clearStencilValue);
    }
    glClear(mask);
    
    CHECK_GL_ERROR_DEBUG();
    
    // restore depth test
    if (descirptor.needClearDepth)
    {
        if (!oldDepthTest)
            glDisable(GL_DEPTH_TEST);
        
        glDepthMask(oldDepthWrite);
        glDepthFunc(oldDepthFunc);
        glClearDepth(oldDepthClearValue);
    }
    
    CHECK_GL_ERROR_DEBUG();
}

void CommandBufferGL::setRenderPipeline(RenderPipeline* renderPipeline)
{
    assert(renderPipeline != nullptr);
    if (renderPipeline == nullptr)
        return;
    
    RenderPipelineGL* rp = static_cast<RenderPipelineGL*>(renderPipeline);
    rp->retain();
    CC_SAFE_RELEASE(_renderPipeline);
    _renderPipeline = rp;
}

void CommandBufferGL::setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    _viewport.x = x;
    _viewport.y = y;
    _viewport.w = w;
    _viewport.h = h;
}

void CommandBufferGL::setCullMode(CullMode mode)
{
    _cullMode = mode;
}

void CommandBufferGL::setIndexBuffer(Buffer* buffer)
{
    assert(buffer != nullptr);
    if (buffer == nullptr)
        return;
    
    buffer->retain();
    CC_SAFE_RELEASE(_indexBuffer);
    _indexBuffer = static_cast<BufferGL*>(buffer);
}

void CommandBufferGL::setVertexBuffer(uint32_t index, Buffer* buffer)
{
    assert(buffer != nullptr);
    if (buffer == nullptr)
        return;
    
    buffer->retain();
    
    if (index >= _vertexBuffers.size())
        _vertexBuffers.resize(index + 1);

    CC_SAFE_RELEASE(_vertexBuffers[index]);
    _vertexBuffers[index] = static_cast<BufferGL*>(buffer);
}

void CommandBufferGL::drawArrays(PrimitiveType primitiveType, uint32_t start,  uint32_t count)
{
    prepareDrawing();
    glDrawArrays(toGLPrimitiveType(primitiveType), start, count);
    
    cleanResources();
}

void CommandBufferGL::drawElements(PrimitiveType primitiveType, IndexFormat indexType, uint32_t count)
{
    prepareDrawing();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer->getHandler());
    glDrawElements(toGLPrimitiveType(primitiveType), count, toGLIndexType(indexType), (GLvoid*)0);
    
    cleanResources();
}

void CommandBufferGL::endRenderPass()
{
}

void CommandBufferGL::endFrame()
{
}

void CommandBufferGL::prepareDrawing() const
{
    glViewport(_viewport.x, _viewport.y, _viewport.w, _viewport.h);
    
    const auto& program = _renderPipeline->getGLProgram();
    glUseProgram(program->getHandler());
    
    bindVertexBuffer(program);
    setUniforms(program);

    // Set depth/stencil state.
    if (_renderPipeline->getDepthStencilState())
        _renderPipeline->getDepthStencilState()->apply(_stencilReferenceValueFront,
                                                       _stencilReferenceValueBack);
    else
        DepthStencilStateGL::reset();
    
    // Set blend state.
    if (_renderPipeline->getBlendState())
        _renderPipeline->getBlendState()->apply();
    else
        BlendStateGL::reset();
    
    // Set cull mode.
    if (CullMode::NONE == _cullMode)
    {
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glEnable(GL_CULL_FACE);
        glCullFace(toGLCullMode(_cullMode));
    }
}

void CommandBufferGL::bindVertexBuffer(const ProgramGL *program) const
{
    // Bind vertex buffers and set the attributes.
    int i = 0;
    const auto& attributeInfos = program->getAttributeInfos();
    for (const auto& vertexBuffer : _vertexBuffers)
    {
        if (! vertexBuffer)
            continue;
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getHandler());
        
        const auto& attributeInfo = attributeInfos[i];
        for (const auto& attribute : attributeInfo)
        {
            glEnableVertexAttribArray(attribute.location);
            glVertexAttribPointer(attribute.location,
                                  attribute.size,
                                  attribute.type,
                                  GL_FALSE,
                                  attribute.stride,
                                  (GLvoid*)attribute.offset);
        }
        
        ++i;
    }
}

void CommandBufferGL::setUniforms(const ProgramGL* program) const
{
    if (program)
    {
        const auto& texutreInfos = program->getFragmentTextureInfos();
        const auto& activeUniformInfos = program->getUniformInfos();

        // Bind textures.
        for(const auto& textureInfo : texutreInfos)
        {
            int location = textureInfo.first;
            const auto& activeUniform = activeUniformInfos.at(location);
            assert(location == activeUniform.location);
            
            const auto& textures = textureInfo.second.textures;
            const auto& indices = textureInfo.second.slot;
            
            int i = 0;
            for (const auto& texture: textures)
            {
                static_cast<TextureGL*>(texture)->apply(indices[i]);
                ++i;
            }
            
            switch (activeUniform.type) {
                case GL_SAMPLER_2D:
                case GL_SAMPLER_CUBE:
                    if (activeUniform.isArray)
                        glUniform1iv(activeUniform.location, activeUniform.size, (GLint*)indices.data());
                    else
                        glUniform1i(activeUniform.location, *((GLint*)(indices.data())));
                    break;
                default:
                    break;
            }
        }
    }
}

void CommandBufferGL::cleanResources()
{
    CC_SAFE_RELEASE_NULL(_indexBuffer);
    CC_SAFE_RELEASE_NULL(_renderPipeline);
      
    for (const auto& vertexBuffer : _vertexBuffers)
        CC_SAFE_RELEASE(vertexBuffer);
    
    _vertexBuffers.clear();
}

CC_BACKEND_END
