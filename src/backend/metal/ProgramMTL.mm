#include "ProgramMTL.h"
#include "ShaderModuleMTL.h"

CC_BACKEND_BEGIN

ProgramMTL::ProgramMTL(ShaderModule* vs, ShaderModule* fs)
: _vertexShader(static_cast<ShaderModuleMTL*>(vs))
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

int ProgramMTL::getVertexUniformLocation(const std::string& uniform) const
{
    const auto& uniforms = _vertexShader->getUniforms();
    return getUniformLcation(uniforms, uniform);
}

int ProgramMTL::getFragmentUniformLocation(const std::string& uniform) const
{
    const auto& uniforms = _fragmentShader->getUniforms();
    return getUniformLcation(uniforms, uniform);
}

int ProgramMTL::getUniformLcation(const std::unordered_map<std::string, int>& uniformsInfo, const std::string& uniform) const
{
    const auto& iter = uniformsInfo.find(uniform);
    if(iter != uniformsInfo.end())
        return iter->second;
    
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

void ProgramMTL::fillUniformBuffer(uint8_t* buffer, uint32_t offset, void* uniformData, uint32_t uniformSize)
{
    memcpy(buffer + offset, uniformData, uniformSize);
}

CC_BACKEND_END
