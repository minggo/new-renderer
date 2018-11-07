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
#include "math/HashAlgorithm.h"


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
    for(auto& renderPass : _cacheRenderPass)
        CC_SAFE_RELEASE(renderPass);
    _cacheRenderPass.clear();
    
    for(auto& renderPipeline : _cacheRenderPipeline)
        CC_SAFE_RELEASE(renderPipeline);
    _cacheRenderPipeline.clear();
    
    for(auto& shaderModule : _cacheShaderModule)
        CC_SAFE_RELEASE(shaderModule);
    _cacheShaderModule.clear();
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
    return new (std::nothrow) RenderPassMTL(_mtlDevice, descriptor);
}

size_t DeviceMTL::findRenderPassInCache(const RenderPassDescriptor& descriptor)
{
    for(std::vector<RenderPass*>::const_iterator iter = _cacheRenderPass.begin(); iter != _cacheRenderPass.end(); iter++)
    {
        bool bFound = (*iter)->Find(descriptor);
        if(bFound)
        {
            return iter - _cacheRenderPass.begin();
        }
    }

    return -1;
}

RenderPass* DeviceMTL::cacheRenderPass(const RenderPassDescriptor& descriptor)
{
    auto posIndex = findRenderPassInCache(descriptor);
    if(posIndex != -1)
    {
        _cacheRenderPass[posIndex]->retain();
        return _cacheRenderPass[posIndex];
    }
    else
    {
        RenderPass* renderPass = newRenderPass(descriptor);
        renderPass->retain();
        _cacheRenderPass.push_back(renderPass);
        return renderPass;
    }
}

ShaderModule* DeviceMTL::createShaderModule(ShaderStage stage, const std::string& source)
{
    auto ret = new (std::nothrow) ShaderModuleMTL(_mtlDevice, stage, source);
    if (ret)
        ret->autorelease();
    
    return ret;
}

size_t DeviceMTL::findShaderModuleInCache(const ShaderStage& stage, const std::string& source)
{
    for(std::vector<ShaderModule*>::const_iterator iter = _cacheShaderModule.begin(); iter != _cacheShaderModule.end(); iter++)
    {
        ShaderModuleMTL* shader = static_cast<ShaderModuleMTL*>(*iter);
        if(shader->getShaderStage() != stage)
            continue;
        bool bFound = shader->Find(source);
        if(bFound)
        {
            return iter - _cacheShaderModule.begin();
        }
    }
    return -1;
}

ShaderModule* DeviceMTL::cacheShaderModule(ShaderStage stage, const std::string& source)
{
    auto posIndex = findShaderModuleInCache(stage, source);
    if (posIndex != -1)
    {
        _cacheShaderModule[posIndex]->retain();
        return _cacheShaderModule[posIndex];
    }
    else
    {
        ShaderModule* shaderModule = createShaderModule(stage, source);
        shaderModule->retain();
        _cacheShaderModule.push_back(shaderModule);
        return shaderModule;
    }
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
    return new (std::nothrow) RenderPipelineMTL(_mtlDevice, descriptor);
}

size_t DeviceMTL::findRenderPipelineInCache(const RenderPipelineDescriptor& descriptor)
{
    for(std::vector<RenderPipeline*>::const_iterator iter = _cacheRenderPipeline.begin(); iter != _cacheRenderPipeline.end(); iter++)
    {
        RenderPipelineMTL* renderPipeline = static_cast<RenderPipelineMTL*>(*iter);
        if(renderPipeline->getHash() == renderPipeline->createHash(descriptor))
        {
            return iter - _cacheRenderPipeline.begin();
        }
    }
    return -1;
}

RenderPipeline* DeviceMTL::cacheRenderPipeline(const RenderPipelineDescriptor& descriptor)
{
    auto posIndex = findRenderPipelineInCache(descriptor);
    if (posIndex != -1)
    {
        _cacheRenderPipeline[posIndex]->retain();
        return _cacheRenderPipeline[posIndex];
    }
    else
    {
        RenderPipeline* renderPipeline = newRenderPipeline(descriptor);
        renderPipeline->retain();
        _cacheRenderPipeline.push_back(renderPipeline);
//        _cacheRenderPipeline[_cacheRenderPipeline.size()] = renderPipeline;
//        _cacheRenderPipelineDescriptor.push_back(descriptor._hash);
        
        return renderPipeline;
    }

}
CC_BACKEND_END
