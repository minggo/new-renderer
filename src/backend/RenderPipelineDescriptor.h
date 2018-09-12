#pragma once

#include "Macros.h"
#include "Types.h"
#include "VertexLayout.h"

#include <vector>

CC_BACKEND_BEGIN

class ShaderModule;
class DepthStencilState;

class RenderPipelineDescriptor
{
public:
    ~RenderPipelineDescriptor();
    
    void setVertexShaderModule(ShaderModule* module);
    void setFragmentShaderModule(ShaderModule* module);
    void setVertexLayout(uint32_t index, const VertexLayout& vertexLayout);
    void setDepthStencilState(DepthStencilState* depthStencilState);
    //    void setColorAttatchmentBlendState(uint32_t attachmentSlot, BlendState* descriptor);
//    void setDepthStencilAttatmentFormat(PixelFormat format);
    
    inline ShaderModule* getVertexShaderModule() const { return _vertexShaderModule; }
    inline ShaderModule* getFragmentShaderModule() const { return _fragmentShaderModule; }
    inline const std::vector<VertexLayout>& getVertexLayouts() const { return _vertexLayouts; }
    inline DepthStencilState* getDepthStencilState() const { return _depthStencilState; }
    
private:
    ShaderModule* _vertexShaderModule = nullptr;
    ShaderModule* _fragmentShaderModule = nullptr;
    std::vector<VertexLayout> _vertexLayouts;
    DepthStencilState* _depthStencilState = nullptr;
};

CC_BACKEND_END
