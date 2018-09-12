#include "../Device.h"
#include "RenderPipelineGL.h"
#include "BufferGL.h"
#include "ShaderModuleGL.h"
#include "CommandQueueGL.h"
#include "RenderPassGL.h"
#include "TextureGL.h"
#include "SamplerGL.h"
#include "DepthStencilStateGL.h"

CC_BACKEND_BEGIN

Device* Device::_instance = nullptr;

Device* Device::getInstance()
{
    if (!_instance)
        _instance = new (std::nothrow) Device();
    
    return _instance;
}

CommandQueue* Device::createCommandQueue()
{
    auto ret = new (std::nothrow) CommandQueueGL();
    if (ret)
        ret->autorelease();
    
    return ret;
}

Buffer* Device::createBuffer(uint32_t size, BufferType type, BufferUsage usage)
{
    auto ret = new (std::nothrow) BufferGL(size, type, usage);
    if (ret)
        ret->autorelease();
    
    return ret;
}

Texture* Device::createTexture(const TextureDescriptor& descriptor)
{
    auto ret = new (std::nothrow) TextureGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

RenderPass* Device::createRenderPass(const RenderPassDescriptor& descriptor)
{
    auto ret = new (std::nothrow) RenderPassGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

ShaderModule* Device::createShaderModule(ShaderStage stage, const std::string& source)
{
    auto ret = new (std::nothrow) ShaderModuleGL(stage, source);
    if (ret)
        ret->autorelease();
    
    return ret;
}

DepthStencilState* Device::createDepthStencilState(const DepthStencilDescriptor& descriptor)
{
    auto ret = new (std::nothrow) DepthStencilStateGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

RenderPipeline* Device::createRenderPipeline(const RenderPipelineDescriptor& descriptor)
{
    auto ret = new (std::nothrow) RenderPipelineGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

Sampler* Device::createSampler(const SamplerDescriptor &descriptor)
{
    auto ret = new (std::nothrow) SamplerGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

CC_BACKEND_END
