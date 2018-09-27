#pragma once

#include "../ShaderModule.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class ShaderModuleMTL : public ShaderModule
{
public:
    ShaderModuleMTL(id<MTLDevice> mtlDevice, ShaderStage stage, const std::string& source);
    
    inline id<MTLFunction> getMTLFunction() const { return _mtlFunction; }
    
private:
    id<MTLFunction> _mtlFunction = nil;
};

CC_BACKEND_END
