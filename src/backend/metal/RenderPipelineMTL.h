#pragma once

#include "../RenderPipeline.h"
#include "../RenderPipelineDescriptor.h"
#include <string>
#include <vector>
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class RenderPipelineMTL : public RenderPipeline
{
public:
    RenderPipelineMTL(id<MTLDevice> mtlDevice, const RenderPipelineDescriptor& descriptor);
    ~RenderPipelineMTL();
    
    inline id<MTLRenderPipelineState> getMTLRenderPipelineState() const { return _mtlRenderPipelineState; }
    inline id<MTLDepthStencilState> getMTLDepthStencilState() const { return _mtlDepthStencilState; }
    
    inline void* getVertexUniformBuffer() const { return _vertexUniformBuffer; }
    inline void* getFragmentUniformBuffer() const { return _fragementUniformBuffer; }
    inline const std::vector<std::string>& getVertexUniforms() const { return _activeVertexUniforms; }
    inline const std::vector<std::string>& getFragmentUniforms() const { return _activeFragmentUniforms; }
    
private:
    id<MTLRenderPipelineState> _mtlRenderPipelineState = nil;
    id<MTLDepthStencilState> _mtlDepthStencilState = nil;
    
    void* _vertexUniformBuffer = nullptr;
    std::vector<std::string> _activeVertexUniforms;
    
    void* _fragementUniformBuffer = nullptr;
    std::vector<std::string> _activeFragmentUniforms;
};

CC_BACKEND_END
