#pragma once

#include "../Macros.h"
#include "../Types.h"
#include "../RenderPipelineDescriptor.h"
#include "base/CCRef.h"
#include "platform/CCGL.h"
#include "../Program.h"

#include <string>
#include <unordered_map>

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
    std::shared_ptr<uint8_t> buffer = nullptr;
};


class ProgramGL : public Program
{
public:
    typedef std::vector<AttributeInfo> VertexAttributeArray;
    
    ProgramGL(ShaderModule* vs, ShaderModule* fs);
    ~ProgramGL();
    
    virtual void setVertexUniform(int location, void* data, uint32_t size) override;
    virtual void setFragmentUniform(int location, void* data, uint32_t size) override;
    virtual int getVertexUniformLocation(const std::string& uniform) const override;
    virtual int getFragmentUniformLocation(const std::string& uniform) const override;
    
    inline const std::vector<VertexAttributeArray>& getAttributeInfos() const { return _attributeInfos; }
    inline const std::unordered_map<int, UniformInfo>& getUniformInfos() const { return _uniformInfos; }
    inline GLuint getHandler() const { return _program; }
    void computeAttributeInfos(const RenderPipelineDescriptor& descriptor);
    
private:
    void createProgram();
    bool getAttributeLocation(const std::string& attributeName, uint32_t& location);
    void computeUniformInfos();
    void setUniform(int location, void* data, uint32_t size);
    void setUniform(bool isArray, GLuint location, uint32_t size, GLenum uniformType, void* data) const;
    
    GLuint _program = 0;
    ShaderModuleGL* _vertexShaderModule = nullptr;
    ShaderModuleGL* _fragmentShaderModule = nullptr;
    
    std::vector<VertexAttributeArray> _attributeInfos;
    std::unordered_map<int, UniformInfo> _uniformInfos;
};

CC_BACKEND_END
