#include "ProgramGL.h"
#include "ShaderModuleGL.h"
#include "ccMacros.h"

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
}

ProgramGL::ProgramGL(ShaderModule* vs, ShaderModule* fs)
:Program(vs, fs)
{
    _vertexShaderModule = (static_cast<ShaderModuleGL*>(vs));
    _fragmentShaderModule = (static_cast<ShaderModuleGL*>(fs));
    CC_SAFE_RETAIN(_vertexShaderModule);
    CC_SAFE_RETAIN(_fragmentShaderModule);
    
    compileProgram();
    computeUniformInfos();
}

ProgramGL::~ProgramGL()
{
    CC_SAFE_RELEASE(_vertexShaderModule);
    CC_SAFE_RELEASE(_fragmentShaderModule);
    if (_program)
        glDeleteProgram(_program);
}

void ProgramGL::compileProgram()
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
        
        uniform.name = uniformName;
        uniform.location = glGetUniformLocation(_program, uniformName);
        
        _uniformInfos.push_back(uniform);
    }
    free(uniformName);
}

int ProgramGL::getUniformLocation(const std::string& uniform)
{
    return glGetUniformLocation(_program, uniform.c_str());
}

CC_BACKEND_END
