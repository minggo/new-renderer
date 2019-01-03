#pragma once

#include "Macros.h"
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include <string>

CC_BACKEND_BEGIN

class ShaderModule;

class Program : public Ref
{
public:
    virtual int getUniformLocation(const std::string& uniform) = 0;
    
    inline ShaderModule* getVertexShader() const { return _vertexShader; }
    inline ShaderModule* getFragmentShader() const { return _fragmentShader; }
    
protected:
    Program(ShaderModule* vs, ShaderModule* fs);
    virtual ~Program();
    
private:
    backend::ShaderModule* _vertexShader = nullptr;
    backend::ShaderModule* _fragmentShader = nullptr;
};

CC_BACKEND_END
