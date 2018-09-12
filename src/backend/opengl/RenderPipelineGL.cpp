#include "RenderPipelineGL.h"
#include "ShaderModuleGL.h"
#include "DepthStencilStateGL.h"
#include "Program.h"

#include <assert.h>

CC_BACKEND_BEGIN

RenderPipelineGL::RenderPipelineGL(const RenderPipelineDescriptor& descriptor)
{
    _program = new Program(descriptor);
    
    const auto& depthStencilState = descriptor.getDepthStencilState();
    CC_SAFE_RETAIN(depthStencilState);
    _depthStencilState = static_cast<DepthStencilStateGL*>(depthStencilState);
}

RenderPipelineGL::~RenderPipelineGL()
{
    CC_SAFE_RELEASE(_program);
    CC_SAFE_RELEASE(_depthStencilState);
}

CC_BACKEND_END
