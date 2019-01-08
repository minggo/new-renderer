#include "ProgramGL.h"
#include "ShaderModuleGL.h"
#include "ccMacros.h"
#include "TextureGL.h"
#include <string>
#include <vector>
#include <memory>

CC_BACKEND_BEGIN

namespace
{
    GLenum toGLAttributeType(VertexFormat vertexFormat)
    {
        GLenum ret = GL_INT;
        switch (vertexFormat)
        {
            case VertexFormat::FLOAT_R32G32B32A32:
            case VertexFormat::FLOAT_R32G32B32:
            case VertexFormat::FLOAT_R32G32:
            case VertexFormat::FLOAT_R32:
                ret = GL_FLOAT;
                break;
            case VertexFormat::INT_R32G32B32A32:
            case VertexFormat::INT_R32G32B32:
            case VertexFormat::INT_R32G32:
            case VertexFormat::INT_R32:
                ret = GL_INT;
                break;
            default:
                break;
        }
        return ret;
    }
    
    GLsizei getGLAttributeSize(VertexFormat vertexFormat)
    {
        GLsizei ret = 0;
        switch (vertexFormat)
        {
            case VertexFormat::FLOAT_R32G32B32A32:
            case VertexFormat::INT_R32G32B32A32:
                ret = 4;
                break;
            case VertexFormat::FLOAT_R32G32B32:
            case VertexFormat::INT_R32G32B32:
                ret = 3;
                break;
            case VertexFormat::FLOAT_R32G32:
            case VertexFormat::INT_R32G32:
                ret = 2;
                break;
            case VertexFormat::FLOAT_R32:
            case VertexFormat::INT_R32:
                ret = 1;
                break;
            default:
                break;
        }
        return ret;
    }
    
    GLsizei getUniformSize(GLenum size)
    {
        GLsizei ret = 0;
        switch (size)
        {
            case GL_BOOL:
            case GL_BYTE:
            case GL_UNSIGNED_BYTE:
                ret = sizeof(GLbyte);
                break;
            case GL_BOOL_VEC2:
            case GL_SHORT:
            case GL_UNSIGNED_SHORT:
                ret = sizeof(GLshort);
                break;
            case GL_BOOL_VEC3:
                ret = sizeof(GLboolean);
                break;
            case GL_BOOL_VEC4:
            case GL_INT:
            case GL_UNSIGNED_INT:
            case GL_FLOAT:
                ret = sizeof(GLfloat);
                break;
            case GL_FLOAT_VEC2:
            case GL_INT_VEC2:
                ret = sizeof(GLfloat) * 2;
                break;
            case GL_FLOAT_VEC3:
            case GL_INT_VEC3:
                ret = sizeof(GLfloat) * 3;
                break;
            case GL_FLOAT_MAT2:
            case GL_FLOAT_VEC4:
            case GL_INT_VEC4:
                ret = sizeof(GLfloat) * 4;
                break;
            case GL_FLOAT_MAT3:
                ret = sizeof(GLfloat) * 9;
                break;
            case GL_FLOAT_MAT4:
                ret = sizeof(GLfloat) * 16;
                break;
            default:
                break;
        }
        return ret;
    }
}

ProgramGL::ProgramGL(const std::string& vertexShader, const std::string& fragmentShader)
: Program(vertexShader, fragmentShader)
{
    _vertexShaderModule = new (std::nothrow) ShaderModuleGL(backend::ShaderStage::VERTEX, vertexShader);
    _fragmentShaderModule = new (std::nothrow) ShaderModuleGL(backend::ShaderStage::FRAGMENT, fragmentShader);
    
    createProgram();
    computeUniformInfos();
}

ProgramGL::~ProgramGL()
{
    CC_SAFE_RELEASE(_vertexShaderModule);
    CC_SAFE_RELEASE(_fragmentShaderModule);
    if (_program)
        glDeleteProgram(_program);
}

void ProgramGL::createProgram()
{
    if (_vertexShaderModule == nullptr || _fragmentShaderModule == nullptr)
        return;
    
    auto vertShader = _vertexShaderModule->getShader();
    auto fragShader = _fragmentShaderModule->getShader();
    
    assert (vertShader != 0 && fragShader != 0);
    if (vertShader == 0 || fragShader == 0)
        return;
    
    _program = glCreateProgram();
    if (!_program)
        return;
    
    glAttachShader(_program, vertShader);
    glAttachShader(_program, fragShader);
    glLinkProgram(_program);
    
    GLint status = 0;
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (GL_FALSE == status)
    {
        printf("cocos2d: ERROR: %s: failed to link program ", __FUNCTION__);
        glDeleteProgram(_program);
        _program = 0;
    }
}

void ProgramGL::computeAttributeInfos(const RenderPipelineDescriptor& descriptor)
{
    const auto& vertexLayouts = descriptor.vertexLayouts;
    for (const auto& vertexLayout : vertexLayouts)
    {
        if (! vertexLayout.isValid())
            continue;
        
        VertexAttributeArray vertexAttributeArray;
        
        const auto& attributes = vertexLayout.getAttributes();
        for (const auto& attribute : attributes)
        {
            AttributeInfo attributeInfo;
            
            if (!getAttributeLocation(attribute.name, attributeInfo.location))
                continue;
            
            attributeInfo.stride = vertexLayout.getStride();
            attributeInfo.offset = attribute.offset;
            attributeInfo.type = toGLAttributeType(attribute.format);
            attributeInfo.size = getGLAttributeSize(attribute.format);
            
            vertexAttributeArray.push_back(attributeInfo);
        }
        
        _attributeInfos.push_back(std::move(vertexAttributeArray));
    }
}

bool ProgramGL::getAttributeLocation(const std::string& attributeName, uint32_t& location)
{
    GLint loc = glGetAttribLocation(_program, attributeName.c_str());
    if (-1 == loc)
    {
        printf("Cocos2d: %s: can not find vertex attribute of %s", __FUNCTION__, attributeName.c_str());
        return false;
    }
    
    location = GLuint(loc);
    return true;
}

void ProgramGL::computeUniformInfos()
{
    if (!_program)
    return;
    
    GLint numOfUniforms = 0;
    glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &numOfUniforms);
    if (!numOfUniforms)
    return;
    
#define MAX_UNIFORM_NAME_LENGTH 256
    UniformInfo uniform;
    GLint length = 0;
    GLchar* uniformName = (GLchar*)malloc(MAX_UNIFORM_NAME_LENGTH + 1);
    for (int i = 0; i < numOfUniforms; ++i)
    {
        glGetActiveUniform(_program, i, MAX_UNIFORM_NAME_LENGTH, &length, &uniform.size, &uniform.type, uniformName);
        uniformName[length] = '\0';
        
        if (length > 3)
        {
            char* c = strrchr(uniformName, '[');
            if (c)
            {
                *c = '\0';
                uniform.isArray = true;
            }
        }
        
        if (uniform.size > 0)
        {
            auto bufferSize = uniform.size * getUniformSize(uniform.type);
            std::shared_ptr<uint8_t> sp(new uint8_t[bufferSize], [](uint8_t *p) { delete[] p; });
            uniform.buffer = sp;
        }
        
        uniform.name = uniformName;
        uniform.location = glGetUniformLocation(_program, uniformName);
        _uniformInfos[uniform.location] = uniform;
    }
    free(uniformName);
}

int ProgramGL::getVertexUniformLocation(const std::string& uniform) const
{
    return glGetUniformLocation(_program, uniform.c_str());
}

int ProgramGL::getFragmentUniformLocation(const std::string& uniform) const
{
    return glGetUniformLocation(_program, uniform.c_str());
}

void ProgramGL::setVertexUniform(int location, void* data, uint32_t size)
{
    setUniform(location, data, size);
}

void ProgramGL::setFragmentUniform(int location, void* data, uint32_t size)
{
    setUniform(location, data, size);
}

void ProgramGL::setUniform(int location, void* data, uint32_t size)
{
    if(location < 0)
        return;
    
    glUseProgram(_program);
    const auto& uniform = _uniformInfos[location];
    memcpy(uniform.buffer.get(), data, size);
    setUniform(uniform.isArray, uniform.location, uniform.size, uniform.type, uniform.buffer.get());
}

#define DEF_TO_INT(pointer, index)     (*((GLint*)(pointer) + index))
#define DEF_TO_FLOAT(pointer, index)   (*((GLfloat*)(pointer) + index))
void ProgramGL::setUniform(bool isArray, GLuint location, uint32_t size, GLenum uniformType, void* data) const
{
    GLsizei count = size;
    switch (uniformType)
    {
        case GL_INT:
        case GL_BOOL:
        case GL_SAMPLER_2D:
        case GL_SAMPLER_CUBE:
            if (isArray)
                glUniform1iv(location, count, (GLint*)data);
            else
            {
                glUniform1i(location, DEF_TO_INT(data, 0));
                cocos2d::log("TextureID = %d\n", DEF_TO_INT(data, 0));
            }
            break;
        case GL_INT_VEC2:
        case GL_BOOL_VEC2:
            if (isArray)
                glUniform2iv(location, count, (GLint*)data);
            else
                glUniform2i(location, DEF_TO_INT(data, 0), DEF_TO_INT(data, 1));
            break;
        case GL_INT_VEC3:
        case GL_BOOL_VEC3:
            if (isArray)
                glUniform3iv(location, count, (GLint*)data);
            else
                glUniform3i(location,
                            DEF_TO_INT(data, 0),
                            DEF_TO_INT(data, 1),
                            DEF_TO_INT(data, 2));
            break;
        case GL_INT_VEC4:
        case GL_BOOL_VEC4:
            if (isArray)
                glUniform4iv(location, count, (GLint*)data);
            else
                glUniform4i(location,
                            DEF_TO_INT(data, 0),
                            DEF_TO_INT(data, 1),
                            DEF_TO_INT(data, 2),
                            DEF_TO_INT(data, 4));
            break;
        case GL_FLOAT:
            if (isArray)
                glUniform1fv(location, count, (GLfloat*)data);
            else
                glUniform1f(location, DEF_TO_FLOAT(data, 0));
            break;
        case GL_FLOAT_VEC2:
            if (isArray)
                glUniform2fv(location, count, (GLfloat*)data);
            else
                glUniform2f(location, DEF_TO_FLOAT(data, 0), DEF_TO_FLOAT(data, 1));
            break;
        case GL_FLOAT_VEC3:
            if (isArray)
                glUniform3fv(location, count, (GLfloat*)data);
            else
                glUniform3f(location,
                            DEF_TO_FLOAT(data, 0),
                            DEF_TO_FLOAT(data, 1),
                            DEF_TO_FLOAT(data, 2));
            break;
        case GL_FLOAT_VEC4:
            if (isArray)
                glUniform4fv(location, count, (GLfloat*)data);
            else
                glUniform4f(location,
                            DEF_TO_FLOAT(data, 0),
                            DEF_TO_FLOAT(data, 1),
                            DEF_TO_FLOAT(data, 2),
                            DEF_TO_FLOAT(data, 3));
            break;
        case GL_FLOAT_MAT2:
            glUniformMatrix2fv(location, count, GL_FALSE, (GLfloat*)data);
            break;
        case GL_FLOAT_MAT3:
            glUniformMatrix3fv(location, count, GL_FALSE, (GLfloat*)data);
            break;
        case GL_FLOAT_MAT4:
            glUniformMatrix4fv(location, count, GL_FALSE, (GLfloat*)data);
            break;
            break;
            
        default:
            break;
    }
}


CC_BACKEND_END
