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
    inline const std::vector<std::string>& getVertexUniforms() const { return _vertexUniforms; }
    inline const std::vector<std::string>& getFragmentUniforms() const { return _fragmentUniforms; }
    inline const std::vector<std::string>& getVertexTextures() const { return _vertexTextures; }
    inline const std::vector<std::string>& getFragmentTextures() const { return _fragmentTextures; }
    
private:
    id<MTLRenderPipelineState> _mtlRenderPipelineState = nil;
    id<MTLDepthStencilState> _mtlDepthStencilState = nil;
    
    void* _vertexUniformBuffer = nullptr;
    std::vector<std::string> _vertexUniforms;
    std::vector<std::string> _vertexTextures;
    
    void* _fragementUniformBuffer = nullptr;
    std::vector<std::string> _fragmentUniforms;
    std::vector<std::string> _fragmentTextures;
};

CC_BACKEND_END
