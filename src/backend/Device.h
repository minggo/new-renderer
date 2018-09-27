#pragma once

#include "Macros.h"
#include "Types.h"
#include "RenderPipelineDescriptor.h"
#include "RenderPassDescriptor.h"
#include "Texture.h"
#include "Sampler.h"
#include "DepthStencilState.h"
#include "BlendState.h"

#include "base/CCRef.h"

#include <string>

CC_BACKEND_BEGIN

class CommandBuffer;
class Buffer;
class ShaderModule;
class RenderPipeline;
class RenderPass;

class Device : public cocos2d::Ref
{
public:
    static Device* getInstance();
    
    virtual ~Device() = default;
    
    virtual CommandBuffer* createCommandBuffer() = 0;
    virtual Buffer* createBuffer(uint32_t size, BufferType type, BufferUsage usage) = 0;
    virtual RenderPass* createRenderPass(const RenderPassDescriptor& descriptor) = 0;
    virtual Texture* createTexture(const TextureDescriptor& descriptor) = 0;
    virtual ShaderModule* createShaderModule(ShaderStage stage, const std::string& source) = 0;
    virtual DepthStencilState* createDepthStencilState(const DepthStencilDescriptor& descriptor) = 0;
    virtual BlendState* createBlendState(const BlendDescriptor& descriptor) = 0;
    virtual RenderPipeline* createRenderPipeline(const RenderPipelineDescriptor& descriptor) = 0;
    virtual Sampler* createSampler(const SamplerDescriptor& descriptor) = 0;
    
private:
    static Device* _instance;
};

CC_BACKEND_END
