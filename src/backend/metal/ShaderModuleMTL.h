#pragma once

#include "../ShaderModule.h"
#include <string>
#include <vector>
#import <Metal/Metal.h>

struct glslopt_shader;

CC_BACKEND_BEGIN

class ShaderModuleMTL : public ShaderModule
{
public:
    ShaderModuleMTL(id<MTLDevice> mtlDevice, ShaderStage stage, const std::string& source);
    ~ShaderModuleMTL();
    
    inline id<MTLFunction> getMTLFunction() const { return _mtlFunction; }
    inline void* getUniformBuffer() const { return _uniformBuffer; }
    inline const std::vector<std::string>& getActiveUniforms() const { return _activeUniforms; }
    
private:
    void parseUniform(id<MTLDevice> mtlDevice, glslopt_shader* shader);
    
    id<MTLFunction> _mtlFunction = nil;
    
    // Buffer for uniforms.
    void* _uniformBuffer = nullptr;
    std::vector<std::string> _activeUniforms;
};

CC_BACKEND_END
