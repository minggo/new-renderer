#include "../Device.h"

CC_BACKEND_BEGIN

class DeviceGL : public Device
{
public:
    virtual CommandBuffer* createCommandBuffer() override;
    virtual Buffer* createBuffer(uint32_t size, BufferType type, BufferUsage usage) override;
    virtual RenderPass* createRenderPass(const RenderPassDescriptor& descriptor) override;
    virtual Texture* createTexture(const TextureDescriptor& descriptor) override;
    virtual ShaderModule* createShaderModule(ShaderStage stage, const std::string& source) override;
    virtual DepthStencilState* createDepthStencilState(const DepthStencilDescriptor& descriptor) override;
    virtual BlendState* createBlendState(const BlendDescriptor& descriptor) override;
    virtual RenderPipeline* createRenderPipeline(const RenderPipelineDescriptor& descriptor) override;
    virtual Sampler* createSampler(const SamplerDescriptor& descriptor) override;
};

CC_BACKEND_END
