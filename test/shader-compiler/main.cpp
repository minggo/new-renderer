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
    
                  layout(set = 0, location = 0) in vec4 v_texcoord;
                  layout(set =0, location = 1) in vec4 v_color;
                  layout(set = 1, location = 2) in vec4 v_tex;
                  
//                  layout(binding = 0) uniform sampler u_sampler;
                  layout(binding = 0) uniform sampler u_texture_sampler;
                  layout(binding = 1) uniform texture2D u_texture;
                  
                  layout(binding = 2) uniform UniformBlock
                  {
                      vec4 color2;
                  };
                  
                  layout(location = 0) out vec4 frag_color;
                  void main() {
                      frag_color = texture(sampler2D(u_texture, u_sample_texture), v_texcoord.xy + v_tex.xy);
                      frag_color = frag_color + color2 + v_color;
                  })"
    );
    
    return 0;
}
