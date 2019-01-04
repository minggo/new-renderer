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

void ProgramMTL::setVertexUniform(int location, void* data, uint32_t size)
{
    if(location < 0)
        return;
    
    const auto& vertexUniformBuffer = _vertexShader->getUniformBuffer();
    fillUniformBuffer(vertexUniformBuffer.get(), location, data, size);
}

void ProgramMTL::setFragmentUniform(int location, void* data, uint32_t size)
{
    if(location < 0)
        return;
    
    const auto& fragUniformBuffer = _fragmentShader->getUniformBuffer();
    fillUniformBuffer(fragUniformBuffer.get(), location, data, size);
}

void ProgramMTL::fillUniformBuffer(uint8_t* buffer, uint32_t offset, void* uniformData, uint32_t uniformSize) const
{
    memcpy(buffer + offset, uniformData, uniformSize);
}
CC_BACKEND_END
