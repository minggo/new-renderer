#include "RenderPipelineGL.h"
#include "ShaderModuleGL.h"
#include "DepthStencilStateGL.h"
#include "ProgramGL.h"
#include "BlendStateGL.h"

#include <assert.h>

CC_BACKEND_BEGIN

RenderPipelineGL::RenderPipelineGL(const RenderPipelineDescriptor& descriptor)
: RenderPipeline(descriptor.program)
{
    _programGL = static_cast<ProgramGL*>(descriptor.program);
    _programGL->computeAttributeInfos(descriptor);
    CC_SAFE_RETAIN(_programGL);
    
    const auto& depthStencilState = descriptor.depthStencilState;
    CC_SAFE_RETAIN(depthStencilState);
    _depthStencilState = static_cast<DepthStencilStateGL*>(depthStencilState);
    
    const auto& blendState = descriptor.blendState;
    CC_SAFE_RETAIN(blendState);
    _blendState = static_cast<BlendStateGL*>(blendState);
}

RenderPipelineGL::~RenderPipelineGL()
{
    CC_SAFE_RELEASE(_programGL);
    CC_SAFE_RELEASE(_depthStencilState);
    CC_SAFE_RELEASE(_blendState);
}

CC_BACKEND_END
