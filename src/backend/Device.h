#pragma once

#include "Macros.h"
#include "Types.h"
#include "RenderPipelineDescriptor.h"
#include "RenderPassDescriptor.h"
#include "Texture.h"
#include "Sampler.h"
#include "DepthStencilState.h"

#include "base/CCRef.h"

#include <string>

CC_BACKEND_BEGIN

class CommandQueue;
class Buffer;
class ShaderModule;
class RenderPipeline;
class RenderPass;

class Device : public cocos2d::Ref
{
public:
    static Device* getInstance();
    
    CommandQueue* createCommandQueue();
    Buffer* createBuffer(uint32_t size, BufferType type, BufferUsage usage);
    RenderPass* createRenderPass(const RenderPassDescriptor& descriptor);
    Texture* createTexture(const TextureDescriptor& descriptor);
    ShaderModule* createShaderModule(ShaderStage stage, const std::string& source);
    DepthStencilState* createDepthStencilState(const DepthStencilDescriptor& descriptor);
    RenderPipeline* createRenderPipeline(const RenderPipelineDescriptor& descriptor);
    Sampler* createSampler(const SamplerDescriptor& descriptor);
    
private:
    static Device* _instance;
};

CC_BACKEND_END
