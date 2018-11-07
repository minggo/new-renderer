#pragma once

#include "../Device.h"
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
#import <vector>
#include <unordered_map>
CC_BACKEND_BEGIN

class DeviceMTL : public Device
{
public:
    // TODO: temple solution to get default renderpass descriptor.
    static void setCAMetalLayer(CAMetalLayer* metalLayer);
    // Invoke by engine internally at the beginning of rendering a new frame.
    static void updateDrawable();
    static CAMetalLayer* getCAMetalLayer() { return DeviceMTL::_metalLayer; }
    static id<CAMetalDrawable> getCurrentDrawable() { return DeviceMTL::_currentDrawable; }
    
    DeviceMTL();
    ~DeviceMTL();
    
    virtual CommandBuffer* newCommandBuffer() override;
    virtual Buffer* newBuffer(uint32_t size, BufferType type, BufferUsage usage) override;
    virtual RenderPass* newRenderPass(const RenderPassDescriptor& descriptor) override;
    virtual Texture* newTexture(const TextureDescriptor& descriptor) override;
    virtual RenderPass* cacheRenderPass(const RenderPassDescriptor& descriptor) override;
    virtual ShaderModule* createShaderModule(ShaderStage stage, const std::string& source) override;
    virtual ShaderModule* cacheShaderModule(ShaderStage stage, const std::string& source) override;
    virtual DepthStencilState* createDepthStencilState(const DepthStencilDescriptor& descriptor) override;
    virtual BlendState* createBlendState(const BlendDescriptor& descriptor) override;
    virtual RenderPipeline* newRenderPipeline(const RenderPipelineDescriptor& descriptor) override;
    virtual RenderPipeline* cacheRenderPipeline(const RenderPipelineDescriptor& descriptor) override;
    inline id<MTLDevice> getMTLDevice() const { return _mtlDevice; }
    inline id<MTLCommandQueue> getMTLCommandQueue() const { return _mtlCommandQueue; }
    
private:
    size_t findRenderPassInCache(const RenderPassDescriptor& descriptor);
    size_t findShaderModuleInCache(const ShaderStage& stage, const std::string& source);
    size_t findRenderPipelineInCache(const RenderPipelineDescriptor& descriptor);

private:
    static CAMetalLayer* _metalLayer;
    static id<CAMetalDrawable> _currentDrawable;
    
    id<MTLDevice> _mtlDevice = nil;
    id<MTLCommandQueue> _mtlCommandQueue = nil;
    
    std::vector<RenderPass*> _cacheRenderPass;
    std::vector<ShaderModule*> _cacheShaderModule;
    std::vector<RenderPipeline*> _cacheRenderPipeline;
};

CC_BACKEND_END
