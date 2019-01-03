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

private:
    ShaderModuleMTL* _vertexShader = nullptr;
    ShaderModuleMTL* _fragmentShader = nullptr;
};

CC_BACKEND_END
