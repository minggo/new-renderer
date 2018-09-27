#include "DeviceGL.h"
#include "RenderPipelineGL.h"
#include "BufferGL.h"
#include "ShaderModuleGL.h"
#include "CommandBufferGL.h"
#include "RenderPassGL.h"
#include "TextureGL.h"
#include "SamplerGL.h"
#include "DepthStencilStateGL.h"
#include "BlendStateGL.h"

CC_BACKEND_BEGIN

Device* Device::getInstance()
{
    if (!_instance)
        _instance = new (std::nothrow) DeviceGL();
    
    return _instance;
}

CommandBuffer* DeviceGL::createCommandBuffer()
{
    auto ret = new (std::nothrow) CommandBufferGL();
    if (ret)
        ret->autorelease();
    
    return ret;
}

Buffer* DeviceGL::createBuffer(uint32_t size, BufferType type, BufferUsage usage)
{
    auto ret = new (std::nothrow) BufferGL(size, type, usage);
    if (ret)
        ret->autorelease();
    
    return ret;
}

Texture* DeviceGL::createTexture(const TextureDescriptor& descriptor)
{
    auto ret = new (std::nothrow) TextureGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

RenderPass* DeviceGL::createRenderPass(const RenderPassDescriptor& descriptor)
{
    auto ret = new (std::nothrow) RenderPassGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

ShaderModule* DeviceGL::createShaderModule(ShaderStage stage, const std::string& source)
{
    auto ret = new (std::nothrow) ShaderModuleGL(stage, source);
    if (ret)
        ret->autorelease();
    
    return ret;
}

DepthStencilState* DeviceGL::createDepthStencilState(const DepthStencilDescriptor& descriptor)
{
    auto ret = new (std::nothrow) DepthStencilStateGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

BlendState* DeviceGL::createBlendState(const BlendDescriptor& descriptor)
{
    auto ret = new (std::nothrow) BlendStateGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

RenderPipeline* DeviceGL::createRenderPipeline(const RenderPipelineDescriptor& descriptor)
{
    auto ret = new (std::nothrow) RenderPipelineGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

Sampler* DeviceGL::createSampler(const SamplerDescriptor &descriptor)
{
    auto ret = new (std::nothrow) SamplerGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

CC_BACKEND_END
