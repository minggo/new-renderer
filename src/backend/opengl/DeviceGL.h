#include "../Device.h"

CC_BACKEND_BEGIN

class DeviceGL : public Device
{
public:
    ~DeviceGL();
    
    virtual CommandBuffer* newCommandBuffer() override;
    virtual Buffer* newBuffer(uint32_t size, BufferType type, BufferUsage usage) override;
    virtual Texture* newTexture(const TextureDescriptor& descriptor) override;
    virtual DepthStencilState* createDepthStencilState(const DepthStencilDescriptor& descriptor) override;
    virtual BlendState* createBlendState(const BlendDescriptor& descriptor) override;
    virtual RenderPipeline* newRenderPipeline(const RenderPipelineDescriptor& descriptor) override;
    virtual Program* createProgram(const std::string& vertexShader, const std::string& fragmentShader) override;
};

CC_BACKEND_END
