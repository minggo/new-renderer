#pragma once

#include "../Program.h"
#include <unordered_map>

CC_BACKEND_BEGIN

class ShaderModuleMTL;

class ProgramMTL : public Program
{
public:
    ProgramMTL(ShaderModule* vs, ShaderModule* fs);
    ~ProgramMTL();
    
    virtual int getVertexUniformLocation(const std::string& uniform) const override;
    virtual int getFragmentUniformLocation(const std::string& uniform) const override;
    virtual void setVertexUniform(int location, void* data, uint32_t size) override;
    virtual void setFragmentUniform(int location, void* data, uint32_t size) override;
    
    inline const ShaderModuleMTL* getVertexShaderModule() const { return _vertexShader; }
    inline const ShaderModuleMTL* getFragmentShaderModule() const { return _fragmentShader; }
    
private:
    void fillUniformBuffer(uint8_t* buffer, uint32_t offset, void* uniformData, uint32_t uniformSize);
    int getUniformLcation(const std::unordered_map<std::string, int>& uniformsInfo, const std::string& uniform) const;
    
    ShaderModuleMTL* _vertexShader = nullptr;
    ShaderModuleMTL* _fragmentShader = nullptr;
};

CC_BACKEND_END
