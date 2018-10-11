#include "DeviceMTL.h"
#include "CommandBufferMTL.h"
#include "BufferMTL.h"
#include "RenderPipelineMTL.h"
#include "ShaderModuleMTL.h"
#include "RenderPassMTL.h"
#include "DepthStencilStateMTL.h"
#include "TextureMTL.h"

#define DEFAULT_DEPTH_STENCIL_PIXEL_FORMAT MTLPixelFormatDepth24Unorm_Stencil8

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
    
    if (DeviceMTL::_defaultRenderPassDescriptor)
        [DeviceMTL::_defaultRenderPassDescriptor release];
    
    DeviceMTL::_defaultRenderPassDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
    DeviceMTL::_defaultRenderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionLoad;
    DeviceMTL::_defaultRenderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
    
    // Set default depth and stencil texture.
    auto defaultDepthStencilTexture = DeviceMTL::createDepthStencilTexture(metalLayer.device,
                                                                           metalLayer.drawableSize.width,
                                                                           metalLayer.drawableSize.height);
    DeviceMTL::_defaultRenderPassDescriptor.depthAttachment.texture = defaultDepthStencilTexture;
    DeviceMTL::_defaultRenderPassDescriptor.stencilAttachment.texture = defaultDepthStencilTexture;
    
    DeviceMTL::_defaultRenderPassDescriptor.depthAttachment.loadAction = MTLLoadActionLoad;
    DeviceMTL::_defaultRenderPassDescriptor.stencilAttachment.loadAction = MTLLoadActionLoad;
    [DeviceMTL::_defaultRenderPassDescriptor retain];
}

void DeviceMTL::updateDrawable()
{
    if (DeviceMTL::_currentDrawable)
        [DeviceMTL::_currentDrawable release];
    
    DeviceMTL::_currentDrawable = [DeviceMTL::_metalLayer nextDrawable];
    [DeviceMTL::_currentDrawable retain];
    
    DeviceMTL::_defaultRenderPassDescriptor.colorAttachments[0].texture = DeviceMTL::_currentDrawable.texture;
}

MTLRenderPassDescriptor* DeviceMTL::getDefaultMTLRenderPassDescriptor()
{
    return DeviceMTL::_defaultRenderPassDescriptor;
}

MTLPixelFormat DeviceMTL::getDefaultDepthStencilPixelFormat()
{
    return DEFAULT_DEPTH_STENCIL_PIXEL_FORMAT;
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
    return new (std::nothrow) TextureMTL(_mtlDevice, descriptor);
}

RenderPass* DeviceMTL::newRenderPass(const RenderPassDescriptor& descriptor)
{
    return new (std::nothrow) RenderPassMTL(_mtlDevice, descriptor);
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
    auto ret = new (std::nothrow) DepthStencilStateMTL(_mtlDevice, descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
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

id<MTLTexture> DeviceMTL::createDepthStencilTexture(id<MTLDevice> mtlDevice, uint32_t width, uint32_t height)
{
    MTLTextureDescriptor* textureDescriptor = [[MTLTextureDescriptor alloc] init];
    textureDescriptor.width = width;
    textureDescriptor.height = height;
    textureDescriptor.pixelFormat = DEFAULT_DEPTH_STENCIL_PIXEL_FORMAT;
    textureDescriptor.resourceOptions = MTLResourceStorageModePrivate;
    textureDescriptor.usage = MTLTextureUsageRenderTarget;
    auto ret = [mtlDevice newTextureWithDescriptor:textureDescriptor];
    [textureDescriptor release];
    
    return ret;
}

CC_BACKEND_END
