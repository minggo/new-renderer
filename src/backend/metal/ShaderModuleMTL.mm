#include "ShaderModuleMTL.h"
#include "DeviceMTL.h"

CC_BACKEND_BEGIN

ShaderModuleMTL::ShaderModuleMTL(id<MTLDevice> mtlDevice, ShaderStage stage, const std::string& source)
: ShaderModule(stage)
{
    NSString* shader = [NSString stringWithUTF8String:source.c_str()];
    NSError* error;
    id<MTLLibrary> library = [mtlDevice newLibraryWithSource:shader
                                                     options:nil
                                                       error:&error];
    if (!library)
    {
        NSLog(@"Can not compile shader: %@", error);
        return;
    }
    
    _mtlFunction = [library newFunctionWithName:@"main0"];
    
}

CC_BACKEND_END
