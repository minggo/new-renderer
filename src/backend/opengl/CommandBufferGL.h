#pragma once

#include "../Macros.h"
#include "../CommandBuffer.h"

#include "platform/CCGL.h"

#include <vector>

CC_BACKEND_BEGIN

class BufferGL;
class RenderPipelineGL;
class ProgramGL;

class CommandBufferGL : public CommandBuffer
{
public:
    CommandBufferGL();
    ~CommandBufferGL();
    
    virtual void beginFrame() override;
    virtual void beginRenderPass(const RenderPassDescriptor& descriptor) override;
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) override;
    virtual void setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;
    virtual void setCullMode(CullMode mode) override;
    virtual void setVertexBuffer(uint32_t index, Buffer* buffer) override;
    virtual void setIndexBuffer(Buffer* buffer) override;
    virtual void drawArrays(PrimitiveType primitiveType, uint32_t start,  uint32_t count) override;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, uint32_t count) override;
    virtual void endRenderPass() override;
    virtual void endFrame() override;
    
private:
    struct Viewport
    {
        uint32_t x = 0;
        uint32_t y = 0;
        uint32_t w = 0;
        uint32_t h = 0;
    };
    
    void prepareDrawing() const;
    void bindVertexBuffer(ProgramGL* program) const;
    void setUniforms(ProgramGL* program) const;
    void cleanResources();
    void applyRenderPassDescriptor(const RenderPassDescriptor& descirptor);
    
    struct Viewport _viewport;
    GLint _defaultFBO = 0;
    GLuint _currentFBO = 0;
    std::vector<BufferGL*> _vertexBuffers;
    BufferGL* _indexBuffer = nullptr;
    RenderPipelineGL* _renderPipeline = nullptr;
    CullMode _cullMode = CullMode::NONE;
};

CC_BACKEND_END
