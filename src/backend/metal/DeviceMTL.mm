#include "DeviceMTL.h"
#include "CommandBufferMTL.h"
#include "BufferMTL.h"
#include "RenderPipelineMTL.h"
#include "ShaderModuleMTL.h"
#include "RenderPassMTL.h"
#include "DepthStencilStateMTL.h"
#include "TextureMTL.h"
#include "BlendStateMTL.h"
#include "Utils.h"


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
    Utils::createDefaultRenderPassDescriptor();
}

void DeviceMTL::updateDrawable()
{
    if (DeviceMTL::_currentDrawable)
        [DeviceMTL::_currentDrawable release];
    
    DeviceMTL::_currentDrawable = [DeviceMTL::_metalLayer nextDrawable];
    [DeviceMTL::_currentDrawable retain];
    
    Utils::updateDefaultRenderPassDescriptor(DeviceMTL::_currentDrawable.texture);
}

DeviceMTL::DeviceMTL()
{
    _mtlDevice = DeviceMTL::_metalLayer.device;
    _mtlCommandQueue = [_mtlDevice newCommandQueue];
}

DeviceMTL::~DeviceMTL()
{
    for(auto& renderPass : _cachedRenderPass)
        CC_SAFE_RELEASE(renderPass);
    _cachedRenderPass.clear();
    
    for(auto& renderPipeline : _cachedRenderPipeline)
        CC_SAFE_RELEASE(renderPipeline);
    _cachedRenderPipeline.clear();
    
    for(auto& shaderModule : _cachedShaderModule)
        CC_SAFE_RELEASE(shaderModule);
    _cachedShaderModule.clear();
}

CommandBuffer* DeviceMTL::newCommandBuffer()
{
    return new (std::nothrow) CommandBufferMTL(this);
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
    auto posIndex = findRenderPassInCache(descriptor);
    if(posIndex != -1)
    {
        _cachedRenderPass[posIndex]->retain();
        return _cachedRenderPass[posIndex];
    }
    else
    {
        auto renderPass = new (std::nothrow) RenderPassMTL(_mtlDevice, descriptor);
        renderPass->retain();
        _cachedRenderPass.push_back(renderPass);
        return renderPass;
    }
}

size_t DeviceMTL::findRenderPassInCache(const RenderPassDescriptor& descriptor)
{
    for(std::vector<RenderPass*>::const_iterator iter = _cachedRenderPass.begin(); iter != _cachedRenderPass.end(); iter++)
    {
        bool bFound = (*iter)->Find(descriptor);
        if(bFound)
        {
            return iter - _cachedRenderPass.begin();
        }
    }

    return -1;
}

ShaderModule* DeviceMTL::createShaderModule(ShaderStage stage, const std::string& source)
{
    auto posIndex = findShaderModuleInCache(stage, source);
    if (posIndex != -1)
    {
        _cachedShaderModule[posIndex]->retain();
        return _cachedShaderModule[posIndex];
    }

    auto shaderModule = new (std::nothrow) ShaderModuleMTL(_mtlDevice, stage, source);
    shaderModule->retain();
    _cachedShaderModule.push_back(shaderModule);
    return shaderModule;
}

size_t DeviceMTL::findShaderModuleInCache(const ShaderStage& stage, const std::string& source)
{
    for(std::vector<ShaderModule*>::const_iterator iter = _cachedShaderModule.begin(); iter != _cachedShaderModule.end(); iter++)
    {
        ShaderModuleMTL* shader = static_cast<ShaderModuleMTL*>(*iter);
        if(shader->getShaderStage() != stage)
            continue;
        bool bFound = shader->Find(source);
        if(bFound)
        {
            return iter - _cachedShaderModule.begin();
        }
    }
    return -1;
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
    auto ret = new (std::nothrow) BlendStateMTL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

RenderPipeline* DeviceMTL::newRenderPipeline(const RenderPipelineDescriptor& descriptor)
{
    auto posIndex = findRenderPipelineInCache(descriptor);
    if (posIndex != -1)
    {
        _cachedRenderPipeline[posIndex]->retain();
        return _cachedRenderPipeline[posIndex];
    }
    else
    {
        auto renderPipeline = new (std::nothrow) RenderPipelineMTL(_mtlDevice, descriptor);
        renderPipeline->retain();
        _cachedRenderPipeline.push_back(renderPipeline);
        return renderPipeline;
    }
}

size_t DeviceMTL::findRenderPipelineInCache(const RenderPipelineDescriptor& descriptor)
{
    for(std::vector<RenderPipeline*>::const_iterator iter = _cachedRenderPipeline.begin(); iter != _cachedRenderPipeline.end(); iter++)
    {
        RenderPipelineMTL* renderPipeline = static_cast<RenderPipelineMTL*>(*iter);
        if(renderPipeline->getHash() == renderPipeline->createHash(descriptor))
        {
            return iter - _cachedRenderPipeline.begin();
        }
    }
    return -1;
}

CC_BACKEND_END
