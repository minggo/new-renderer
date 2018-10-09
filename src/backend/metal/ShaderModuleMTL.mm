#include "ShaderModuleMTL.h"
#include "DeviceMTL.h"

#include "glsl_optimizer/glsl/glsl_optimizer.h"

CC_BACKEND_BEGIN

namespace
{
    void printUniforms(glslopt_shader* shader)
    {
        static const char* kGlslTypeNames[kGlslTypeCount] = {
            "float",
            "int",
            "bool",
            "2d",
            "3d",
            "cube",
            "2dshadow",
            "2darray",
            "other",
        };
        
        static const char* kGlslPrecNames[kGlslPrecCount] = {
            "high",
            "medium",
            "low",
        };
        
        char buffer[1000];
        std::string textOpt;
        const int uniformCount = glslopt_shader_get_uniform_count (shader);
        const int uniformSize = glslopt_shader_get_uniform_total_size (shader);
        if (uniformCount > 0)
        {
            sprintf(buffer, "// uniforms: %i (total size: %i)\n", uniformCount, uniformSize);
            textOpt += buffer;
        }
        for (int i = 0; i < uniformCount; ++i)
        {
            const char* parName;
            glslopt_basic_type parType;
            glslopt_precision parPrec;
            int parVecSize, parMatSize, parArrSize, location;
            glslopt_shader_get_uniform_desc(shader, i, &parName, &parType, &parPrec, &parVecSize, &parMatSize, &parArrSize, &location);
            if (location >= 0)
                sprintf(buffer, "//  #%i: %s (%s %s) %ix%i [%i] loc %i\n", i, parName, kGlslPrecNames[parPrec], kGlslTypeNames[parType], parVecSize, parMatSize, parArrSize, location);
            else
                sprintf(buffer, "//  #%i: %s (%s %s) %ix%i [%i]\n", i, parName, kGlslPrecNames[parPrec], kGlslTypeNames[parType], parVecSize, parMatSize, parArrSize);
            textOpt += buffer;
        }
        
        NSLog(@"\n%s", textOpt.c_str());
    }
}

ShaderModuleMTL::ShaderModuleMTL(id<MTLDevice> mtlDevice, ShaderStage stage, const std::string& source)
: ShaderModule(stage)
{
    // Convert GLSL shader to metal shader
    //TODO: don't crreate/destroy ctx every time.
    glslopt_ctx* ctx = glslopt_initialize(kGlslTargetMetal);
    glslopt_shader_type shaderType = stage == ShaderStage::VERTEX ? kGlslOptShaderVertex : kGlslOptShaderFragment;
    glslopt_shader* glslShader = glslopt_optimize(ctx, shaderType, source.c_str(), 0);
    const char* metalShader = glslopt_get_raw_output(glslShader);
    parseUniform(mtlDevice, glslShader);
    
    glslopt_cleanup(ctx);
    
    NSString* shader = [NSString stringWithUTF8String:metalShader];
    NSError* error;
    id<MTLLibrary> library = [mtlDevice newLibraryWithSource:shader
                                                     options:nil
                                                       error:&error];
    if (!library)
    {
        NSLog(@"Can not compile shader: %@", error);
        return;
    }
    
    _mtlFunction = [library newFunctionWithName:@"xlatMtlMain"];
}

ShaderModuleMTL::~ShaderModuleMTL()
{
    [_mtlFunction release];
    
    // _uniformBuffer is free by RenderPipeline
}

void ShaderModuleMTL::parseUniform(id<MTLDevice> mtlDevice, glslopt_shader* shader)
{
    const int uniformCount = glslopt_shader_get_uniform_count (shader);
    const int uniformSize = glslopt_shader_get_uniform_total_size (shader);
    if (uniformSize > 0)
    {
        _uniformBuffer = malloc(uniformSize);
    }
    for (int i = 0; i < uniformCount; ++i)
    {
        const char* parName;
        glslopt_basic_type parType;
        glslopt_precision parPrec;
        int parVecSize, parMatSize, parArrSize, location;
        glslopt_shader_get_uniform_desc(shader, i, &parName, &parType, &parPrec, &parVecSize, &parMatSize, &parArrSize, &location);
        _activeUniforms.push_back(parName);
    }
}

CC_BACKEND_END
