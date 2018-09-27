#include "DeviceMTL.h"
#include "CommandBufferMTL.h"
#include "BufferMTL.h"
#include "RenderPipelineMTL.h"
#include "ShaderModuleMTL.h"

CC_BACKEND_BEGIN

CAMetalLayer* DeviceMTL::_metalLayer = nil;
id<CAMetalDrawable> DeviceMTL::_currentDrawable = nil;

Device* Device::getInstance()
{
    if (!_instance)
        _instance = new (std::nothrow) DeviceMTL();

    return _instance;
}

void DeviceMTL::setCAMetalLayer(CAMetalLayer* metalLayer)
{
    DeviceMTL::_metalLayer = metalLayer;
}

void DeviceMTL::updateDrawable()
{
    if (DeviceMTL::_currentDrawable)
        [DeviceMTL::_currentDrawable release];
    
    DeviceMTL::_currentDrawable = [DeviceMTL::_metalLayer nextDrawable];
    [DeviceMTL::_currentDrawable retain];
}

MTLRenderPassDescriptor* DeviceMTL::getDefaultMTLRenderPassDescriptor()
{
    MTLRenderPassDescriptor* descriptor = [MTLRenderPassDescriptor renderPassDescriptor];
    descriptor.colorAttachments[0].texture = DeviceMTL::_currentDrawable.texture;
    descriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
    descriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
    descriptor.depthAttachment.loadAction = MTLLoadActionClear;
    descriptor.stencilAttachment.loadAction = MTLLoadActionClear;
    return descriptor;
}

DeviceMTL::DeviceMTL()
{
    _mtlDevice = DeviceMTL::_metalLayer.device;
}

DeviceMTL::~DeviceMTL()
{
}

CommandBuffer* DeviceMTL::createCommandBuffer()
{
    auto ret = new (std::nothrow) CommandBufferMTL(_mtlDevice);
    if (ret)
        ret->autorelease();
    
    return ret;
}

Buffer* DeviceMTL::createBuffer(uint32_t size, BufferType type, BufferUsage usage)
{
    auto ret = new (std::nothrow) BufferMTL(_mtlDevice, size, type, usage);
    if (ret)
        ret->autorelease();
    
    return ret;
}

Texture* DeviceMTL::createTexture(const TextureDescriptor& descriptor)
{
    return nullptr;
}

RenderPass* DeviceMTL::createRenderPass(const RenderPassDescriptor& descriptor)
{
    return nullptr;
}

ShaderModule* DeviceMTL::createShaderModule(ShaderStage stage, const std::string& source)
{
    auto ret = new (std::nothrow) ShaderModuleMTL(_mtlDevice, stage, source);
    if (ret)
        ret->autorelease();
    
    return ret;
}

DepthStencilState* DeviceMTL::createDepthStencilState(const DepthStencilDescriptor& descriptor)
{
    return nullptr;
}

BlendState* DeviceMTL::createBlendState(const BlendDescriptor& descriptor)
{
    return nullptr;
}

RenderPipeline* DeviceMTL::createRenderPipeline(const RenderPipelineDescriptor& descriptor)
{
    auto ret = new (std::nothrow) RenderPipelineMTL(_mtlDevice, descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

Sampler* DeviceMTL::createSampler(const SamplerDescriptor &descriptor)
{
    return nullptr;
}

CC_BACKEND_END
