#include "DeviceMTL.h"
#include "CommandBufferMTL.h"
#include "BufferMTL.h"
#include "RenderPipelineMTL.h"
#include "ShaderModuleMTL.h"
#include "RenderPassMTL.h"

CC_BACKEND_BEGIN

CAMetalLayer* DeviceMTL::_metalLayer = nil;
id<CAMetalDrawable> DeviceMTL::_currentDrawable = nil;
MTLRenderPassDescriptor* DeviceMTL::_defaultRenderPassDescriptor = nil;

Device* Device::getInstance()
{
    if (!_instance)
        _instance = new (std::nothrow) DeviceMTL();

    return _instance;
}

void DeviceMTL::setCAMetalLayer(CAMetalLayer* metalLayer)
{
    DeviceMTL::_metalLayer = metalLayer;
    
    DeviceMTL::_defaultRenderPassDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
    DeviceMTL::_defaultRenderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
    DeviceMTL::_defaultRenderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
    DeviceMTL::_defaultRenderPassDescriptor.depthAttachment.loadAction = MTLLoadActionClear;
    DeviceMTL::_defaultRenderPassDescriptor.stencilAttachment.loadAction = MTLLoadActionClear;
    [DeviceMTL::_defaultRenderPassDescriptor retain];
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
    DeviceMTL::_defaultRenderPassDescriptor.colorAttachments[0].texture = DeviceMTL::_currentDrawable.texture;
    return DeviceMTL::_defaultRenderPassDescriptor;
}

DeviceMTL::DeviceMTL()
{
    _mtlDevice = DeviceMTL::_metalLayer.device;
    
}

DeviceMTL::~DeviceMTL()
{
}

CommandBuffer* DeviceMTL::newCommandBuffer()
{
    return new (std::nothrow) CommandBufferMTL(_mtlDevice);
}

Buffer* DeviceMTL::newBuffer(uint32_t size, BufferType type, BufferUsage usage)
{
    return new (std::nothrow) BufferMTL(_mtlDevice, size, type, usage);
}

Texture* DeviceMTL::newTexture(const TextureDescriptor& descriptor)
{
    return nullptr;
}

RenderPass* DeviceMTL::newRenderPass(const RenderPassDescriptor& descriptor)
{
    return new (std::nothrow) RenderPassMTL(descriptor);
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

RenderPipeline* DeviceMTL::newRenderPipeline(const RenderPipelineDescriptor& descriptor)
{
    return new (std::nothrow) RenderPipelineMTL(_mtlDevice, descriptor);
}

Sampler* DeviceMTL::createSampler(const SamplerDescriptor &descriptor)
{
    return nullptr;
}

CC_BACKEND_END
