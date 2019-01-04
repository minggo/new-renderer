#pragma once

#include "../ShaderModule.h"
#include <string>
#include <vector>
#include <memory>
#import <Metal/Metal.h>
#include <unordered_map>

struct glslopt_shader;

CC_BACKEND_BEGIN

class ShaderModuleMTL : public ShaderModule
{
public:
    ShaderModuleMTL(id<MTLDevice> mtlDevice, ShaderStage stage, const std::string& source);
    ~ShaderModuleMTL();
    
    inline id<MTLFunction> getMTLFunction() const { return _mtlFunction; }
    inline const std::shared_ptr<uint8_t>& getUniformBuffer() const { return _uniformBuffer; }
    inline const std::unordered_map<std::string, int>& getUniforms() const { return _uniforms; }
    inline const std::vector<std::string>& getTextures() const { return _textures; }
    inline uint32_t getUniformBufferSize() const { return _uniformBufferSize; }
    
private:
    void parseUniform(id<MTLDevice> mtlDevice, glslopt_shader* shader);
    void parseTexture(id<MTLDevice> mtlDevice, glslopt_shader* shader);
    
    id<MTLFunction> _mtlFunction = nil;
    
    std::shared_ptr<uint8_t> _uniformBuffer = nullptr;
    std::unordered_map<std::string, int> _uniforms;
    uint32_t _uniformBufferSize = 0;
    
    // Texture index is the same as vector index.
    std::vector<std::string> _textures;
};

CC_BACKEND_END
