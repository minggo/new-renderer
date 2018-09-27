//
//  main.cpp
//  shader-compiler
//
//  Created by minggo on 9/19/18.
//  Copyright © 2018 cocos. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include "shaderc/shaderc.hpp"
#include "spirv_cross/spirv_msl.hpp"

void compileShader(shaderc_shader_kind kind, const std::string& source)
{
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;
    
    auto result = compiler.CompileGlslToSpv(source, kind, "myshader?", options);
    if (result.GetCompilationStatus() != shaderc_compilation_status_success)
    {
        std::cerr << result.GetErrorMessage();
        return;
    }
    
    const uint32_t* resultBegin = result.cbegin();
    const uint32_t* resultEnd = result.cend();
    ptrdiff_t resultSize = resultEnd - resultBegin;
    
    std::vector<uint32_t> spirv;
    spirv.assign(resultBegin, resultBegin + static_cast<uint32_t>(resultSize));
    
    spirv_cross::CompilerMSL compilerMSL(spirv);
    auto shaderMetal = compilerMSL.compile();
    printf("%s\n", shaderMetal.c_str());
}

int main(int argc, const char * argv[])
{
    compileShader(shaderc_glsl_vertex_shader, R"(
                  #version 450
                  
                  
                  layout(location = 0) in vec4 pos;
                  layout(binding = 0) uniform sampler2D u_texture0;
                  layout(location = 0) out vec4 outColor;
                  void main() {
                      //gl_Position = pos;
                      outColor = texture(u_texture0, vec2(0,0));
                  })"
    );
    
    return 0;
}
