#include "RenderPipelineDescriptor.h"
#include "ShaderModule.h"
#include "DepthStencilState.h"

#include <assert.h>

CC_BACKEND_BEGIN

RenderPipelineDescriptor::~RenderPipelineDescriptor()
{
    CC_SAFE_RELEASE(_vertexShaderModule);
    CC_SAFE_RELEASE(_fragmentShaderModule);
    CC_SAFE_RELEASE(_depthStencilState);
}

void RenderPipelineDescriptor::setVertexShaderModule(ShaderModule* module)
{
    assert(module != nullptr);
    assert(ShaderStage::VERTEX == module->getShaderStage());
    
    if (ShaderStage::VERTEX == module->getShaderStage())
    {
        CC_SAFE_RETAIN(module);
        CC_SAFE_RELEASE(_vertexShaderModule);
        _vertexShaderModule = module;
    }
}

void RenderPipelineDescriptor::setDepthStencilState(DepthStencilState* depthStencilState)
{
    assert(depthStencilState != nullptr);
    
    CC_SAFE_RETAIN(depthStencilState);
    CC_SAFE_RELEASE(_depthStencilState);
    _depthStencilState = depthStencilState;
}

void RenderPipelineDescriptor::setFragmentShaderModule(ShaderModule* module)
{
    assert(module != nullptr);
    assert(ShaderStage::FRAGMENT == module->getShaderStage());
    
    if (ShaderStage::FRAGMENT == module->getShaderStage())
    {
        CC_SAFE_RETAIN(module);
        CC_SAFE_RELEASE(_fragmentShaderModule);
        _fragmentShaderModule = module;
    }
}

void RenderPipelineDescriptor::setVertexLayout(uint32_t index, const VertexLayout& vertexLayout)
{
    if (index >= _vertexLayouts.capacity())
        _vertexLayouts.resize(index + 1);
    
    _vertexLayouts[index] = vertexLayout;
}

CC_BACKEND_END
