#pragma once

#include "../Device.h"
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

CC_BACKEND_BEGIN

class DeviceMTL : public Device
{
public:
    // TODO: temple solution to get default renderpass descriptor.
    static void setCAMetalLayer(CAMetalLayer* metalLayer);
    static MTLRenderPassDescriptor* getDefaultMTLRenderPassDescriptor();
    // Invoke by engine internally at the beginning of rendering a new frame.
    static void updateDrawable();
    static CAMetalLayer* getCAMetalLayer() { return DeviceMTL::_metalLayer; }
    static id<CAMetalDrawable> getCurrentDrawable() { return DeviceMTL::_currentDrawable; }
    
    DeviceMTL();
    ~DeviceMTL();
    
    virtual CommandBuffer* createCommandBuffer() override;
    virtual Buffer* createBuffer(uint32_t size, BufferType type, BufferUsage usage) override;
    virtual RenderPass* createRenderPass(const RenderPassDescriptor& descriptor) override;
    virtual Texture* createTexture(const TextureDescriptor& descriptor) override;
    virtual ShaderModule* createShaderModule(ShaderStage stage, const std::string& source) override;
    virtual DepthStencilState* createDepthStencilState(const DepthStencilDescriptor& descriptor) override;
    virtual BlendState* createBlendState(const BlendDescriptor& descriptor) override;
    virtual RenderPipeline* createRenderPipeline(const RenderPipelineDescriptor& descriptor) override;
    virtual Sampler* createSampler(const SamplerDescriptor& descriptor) override;
    
private:
    static CAMetalLayer* _metalLayer;
    static id<CAMetalDrawable> _currentDrawable;
    static MTLRenderPassDescriptor* _defaultRenderPassDescriptor;
    
    id<MTLDevice> _mtlDevice = nil;
};

CC_BACKEND_END
