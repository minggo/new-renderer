#pragma once

#include "../Program.h"

CC_BACKEND_BEGIN

class ShaderModuleMTL;

class ProgramMTL : public Program
{
public:
    ProgramMTL(ShaderModule* vs, ShaderModule* fs);
    virtual ~ProgramMTL();
    virtual int getUniformLocation(const std::string& uniform) override;
    virtual void setVertexUniform(int location, void* data, uint32_t size) override;
    virtual void setFragmentUniform(int location, void* data, uint32_t size) override;
    
    void fillUniformBuffer(uint8_t* buffer, uint32_t offset, void* uniformData, uint32_t uniformSize) const;
    
private:
    ShaderModuleMTL* _vertexShader = nullptr;
    ShaderModuleMTL* _fragmentShader = nullptr;
};

CC_BACKEND_END
