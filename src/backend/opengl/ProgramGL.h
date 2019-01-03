#pragma once

#include "../Macros.h"
#include "../Types.h"
#include "../RenderPipelineDescriptor.h"
#include "base/CCRef.h"
#include "platform/CCGL.h"
#include "../Program.h"

#include <string>

CC_BACKEND_BEGIN

class ShaderModuleGL;

struct AttributeInfo
{
    uint32_t location = 0;
    uint32_t size = 0;
    GLenum type = GL_BYTE;
    GLsizei stride = 0;
    uint32_t offset = 0;
};

struct UniformInfo
{
    std::string name;
    GLsizei size = 0;
    GLuint location = 0;
    GLenum type = GL_FLOAT;
    bool isArray = false;
};


class ProgramGL : public Program
{
public:
    typedef std::vector<AttributeInfo> VertexAttributeArray;
    
    ProgramGL(ShaderModule* vs, ShaderModule* fs);
    
    ProgramGL(const RenderPipelineDescriptor& descriptor);
    ~ProgramGL();
    
    inline const std::vector<VertexAttributeArray>& getAttributeInfos() const { return _attributeInfos; }
    inline const std::vector<UniformInfo>& getUniformInfos() const { return _uniformInfos; }
    inline GLuint getHandler() const { return _program; }
    void computeAttributeInfos(const RenderPipelineDescriptor& descriptor);
    virtual int getUniformLocation(const std::string& uniform) override;
private:
    void compileProgram();
//    void computeAttributeInfos(const RenderPipelineDescriptor& descriptor);
    bool getAttributeLocation(const std::string& attributeName, uint32_t& location);
    void computeUniformInfos();
    
    GLuint _program = 0;
    ShaderModuleGL* _vertexShaderModule = nullptr;
    ShaderModuleGL* _fragmentShaderModule = nullptr;
    
    std::vector<VertexAttributeArray> _attributeInfos;
    std::vector<UniformInfo> _uniformInfos;
};

CC_BACKEND_END
