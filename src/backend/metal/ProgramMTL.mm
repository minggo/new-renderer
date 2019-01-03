#include "ProgramMTL.h"
#include "ShaderModuleMTL.h"

CC_BACKEND_BEGIN

ProgramMTL::ProgramMTL(ShaderModule* vs, ShaderModule* fs)
: Program(vs, fs)
, _vertexShader(static_cast<ShaderModuleMTL*>(vs))
, _fragmentShader(static_cast<ShaderModuleMTL*>(fs))
{
    CC_SAFE_RETAIN(_vertexShader);
    CC_SAFE_RETAIN(_fragmentShader);
}

ProgramMTL::~ProgramMTL()
{
    CC_SAFE_RELEASE(_vertexShader);
    CC_SAFE_RELEASE(_fragmentShader);
}

int ProgramMTL::getUniformLocation(const std::string& uniform)
{
    const auto& vsUniforms = _vertexShader->getUniforms();
    const auto& fsUniforms = _fragmentShader->getUniforms();
    const auto& vsIter = vsUniforms.find(uniform);
    if(vsIter != vsUniforms.end())
        return vsIter->second;
    
    const auto& fsIter = fsUniforms.find(uniform);
    if(fsIter != fsUniforms.end())
        return fsIter->second;
    
    return -1;
}

CC_BACKEND_END
