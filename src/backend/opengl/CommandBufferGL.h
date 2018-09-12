#pragma once

#include "../Macros.h"
#include "../CommandBuffer.h"

#include "platform/CCGL.h"

#include <vector>

CC_BACKEND_BEGIN

class BufferGL;
class RenderPipelineGL;

class CommandBufferGL : public CommandBuffer
{
public:
    CommandBufferGL();
    ~CommandBufferGL();
    
    virtual void beginRenderPass(RenderPass* renderPass) override;
    virtual void setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;
    virtual void setStencilReferenceValue(uint32_t value) override;
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) override;
    virtual void setVertexBuffer(uint32_t index, Buffer* buffer) override;
    virtual void setBindGroup(BindGroup* bindGroup) override;
    virtual void setIndexBuffer(uint32_t index, Buffer* buffer) override;
    virtual void drawArrays(PrimitiveType primitiveType, uint32_t start,  uint32_t count) override;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, uint32_t count) override;
    virtual void endRenderPass() override;
    
private:
    struct Viewport
    {
        uint32_t x = 0;
        uint32_t y = 0;
        uint32_t w = 0;
        uint32_t h = 0;
    };
    
    void prepareDrawing() const;
    void setUniform(bool isArray, GLuint location, uint32_t size, GLenum uniformType, void* data) const;
    
    GLint _defaultFBO = 0;
    std::vector<BufferGL*> _vertexBuffers;
    BindGroup* _bindGroup = nullptr;
    BufferGL* _indexBuffer = nullptr;
    RenderPipelineGL* _renderPipeline = nullptr;
    struct Viewport _viewport;
    uint32_t _stencilReferenceValueFront = 0;
    uint32_t _stencilReferenceValueBack = 0;
};

CC_BACKEND_END
