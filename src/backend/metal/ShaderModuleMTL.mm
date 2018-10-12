#include "ShaderModuleMTL.h"
#include "DeviceMTL.h"

#include "glsl_optimizer/glsl/glsl_optimizer.h"

CC_BACKEND_BEGIN

ShaderModuleMTL::ShaderModuleMTL(id<MTLDevice> mtlDevice, ShaderStage stage, const std::string& source)
: ShaderModule(stage)
{
    // Convert GLSL shader to metal shader
    //TODO: don't crreate/destroy ctx every time.
    glslopt_ctx* ctx = glslopt_initialize(kGlslTargetMetal);
    glslopt_shader_type shaderType = stage == ShaderStage::VERTEX ? kGlslOptShaderVertex : kGlslOptShaderFragment;
    glslopt_shader* glslShader = glslopt_optimize(ctx, shaderType, source.c_str(), 0);
    if (!glslShader)
    {
        NSLog(@"Can not translate GLSL shader to metal shader:");
        NSLog(@"%s", source.c_str());
        return;
    }
    
    const char* metalShader = glslopt_get_raw_output(glslShader);
    if (!metalShader)
    {
        NSLog(@"Can not get metal shader:");
        NSLog(@"%s", source.c_str());
        return;
    }
    
//    NSLog(@"%s", metalShader);
    
    parseUniform(mtlDevice, glslShader);
    parseTexture(mtlDevice, glslShader);
    
    glslopt_cleanup(ctx);
    
    NSString* shader = [NSString stringWithUTF8String:metalShader];
    NSError* error;
    id<MTLLibrary> library = [mtlDevice newLibraryWithSource:shader
                                                     options:nil
                                                       error:&error];
    if (!library)
    {
        NSLog(@"Can not compile metal shader: %@", error);
        NSLog(@"%s", metalShader);
        return;
    }
    
    _mtlFunction = [library newFunctionWithName:@"xlatMtlMain"];
    if (!_mtlFunction)
    {
        NSLog(@"metal shader is ---------------");
        NSLog(@"%s", metalShader);
        assert(false);
    }
}

ShaderModuleMTL::~ShaderModuleMTL()
{
    [_mtlFunction release];
    
    // _uniformBuffer is free by RenderPipeline
}

void ShaderModuleMTL::parseUniform(id<MTLDevice> mtlDevice, glslopt_shader* shader)
{
    const int uniformCount = glslopt_shader_get_uniform_count(shader);
    const int uniformSize = glslopt_shader_get_uniform_total_size(shader);
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
        _uniforms.push_back(parName);
    }
}

void ShaderModuleMTL::parseTexture(id<MTLDevice> mtlDevice, glslopt_shader* shader)
{
    const int textureCount = glslopt_shader_get_texture_count(shader);
    for (int i = 0; i < textureCount; ++i)
    {
        const char* parName;
        glslopt_basic_type parType;
        glslopt_precision parPrec;
        int parVecSize, parMatSize, parArrSize, location;
        glslopt_shader_get_texture_desc(shader, i, &parName, &parType, &parPrec, &parVecSize, &parMatSize, &parArrSize, &location);
        _textures.push_back(parName);
    }
}

CC_BACKEND_END
