#include "DeviceGL.h"
#include "RenderPipelineGL.h"
#include "BufferGL.h"
#include "ShaderModuleGL.h"
#include "CommandBufferGL.h"
#include "TextureGL.h"
#include "DepthStencilStateGL.h"
#include "BlendStateGL.h"
#include "ProgramGL.h"

CC_BACKEND_BEGIN

Device* Device::getInstance()
{
    if (!_instance)
        _instance = new (std::nothrow) DeviceGL();
    
    if(_instance)
    {
        ProgramCache::getInstance();
    }
    
    return _instance;
}

DeviceGL::~DeviceGL()
{
    ProgramCache::destroyInstance();
}

CommandBuffer* DeviceGL::newCommandBuffer()
{
    return new (std::nothrow) CommandBufferGL();
}

Buffer* DeviceGL::newBuffer(uint32_t size, BufferType type, BufferUsage usage)
{
    return new (std::nothrow) BufferGL(size, type, usage);
}

Texture* DeviceGL::newTexture(const TextureDescriptor& descriptor)
{
    return new (std::nothrow) TextureGL(descriptor);
}

DepthStencilState* DeviceGL::createDepthStencilState(const DepthStencilDescriptor& descriptor)
{
    auto ret = new (std::nothrow) DepthStencilStateGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

BlendState* DeviceGL::createBlendState(const BlendDescriptor& descriptor)
{
    auto ret = new (std::nothrow) BlendStateGL(descriptor);
    if (ret)
        ret->autorelease();
    
    return ret;
}

RenderPipeline* DeviceGL::newRenderPipeline(const RenderPipelineDescriptor& descriptor)
{
    return new (std::nothrow) RenderPipelineGL(descriptor);
}

Program* DeviceGL::createProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    auto program = ProgramCache::getInstance()->getProgram(vertexShader, fragmentShader);
    if(!program)
    {
        program = new (std::nothrow) ProgramGL(vertexShader, fragmentShader);
        if (program)
        {
            program->autorelease();
            ProgramCache::getInstance()->addProgram(program);
        }
    }
    return program;
}

CC_BACKEND_END
