/****************************************************************************
 Copyright (c) 2018 Chukong Technologies

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCProgram.h"
#include "CCGFXUtils.h"

namespace {

    uint32_t _genID = 0;

    std::string logForOpenGLShader(GLuint shader)
    {
        GLint logLength = 0;

        GL_CHECK(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength));
        if (logLength < 1)
            return "";

        char *logBytes = (char*)malloc(sizeof(char) * logLength);
        GL_CHECK(glGetShaderInfoLog(shader, logLength, nullptr, logBytes));
        std::string ret(logBytes);

        free(logBytes);
        return ret;
    }

    std::string logForOpenGLProgram(GLuint program)
    {
        GLint logLength = 0;

        GL_CHECK(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength));
        if (logLength < 1)
            return "";

        char *logBytes = (char*)malloc(sizeof(char) * logLength);
        GL_CHECK(glGetProgramInfoLog(program, logLength, nullptr, logBytes));
        std::string ret(logBytes);

        free(logBytes);
        return ret;
    }

    bool _createShader(GLenum type, const std::string& src, GLuint* outShader)
    {
        assert(outShader != nullptr);
        GLuint shader = glCreateShader(type);
        const GLchar* sources[] = { src.c_str() };
        GL_CHECK(glShaderSource(shader, 1, sources, nullptr));
        GL_CHECK(glCompileShader(shader));

        GLint status;
        GL_CHECK(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));

        if (!status)
        {
            GLsizei length;
            GL_CHECK(glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &length));
            GLchar* src = (GLchar *)malloc(sizeof(GLchar) * length);

            GL_CHECK(glGetShaderSource(shader, length, nullptr, src));
            GFX_LOGE("ERROR: Failed to compile shader:\n%s", src);

            std::string shaderLog = logForOpenGLShader(shader);
            GFX_LOGE("%s", shaderLog.c_str());

            free(src);

            *outShader = 0;
            return false;
        }

        *outShader = shader;
        return true;
    }

} // namespace {

GFX_BEGIN

Program::Program()
: _device(nullptr)
, _id(0)
, _linked(false)
{

}

Program::~Program()
{
    GL_CHECK(glDeleteProgram(_glID));
}

bool Program::init(DeviceGraphics* device, const char* vertSource, const char* fragSource)
{
    assert(device);
    assert(vertSource);
    assert(fragSource);

    _device = device;
    _vertSource = vertSource;
    _fragSource = fragSource;
    _id = _genID++;
    _linked = false;
    return true;
}

void Program::link()
{
    if (_linked) {
        return;
    }

    GLuint vertShader;
    bool ok = _createShader(GL_VERTEX_SHADER, _vertSource, &vertShader);
    if (!ok)
        return;

    GLuint fragShader;
    ok = _createShader(GL_FRAGMENT_SHADER, _fragSource, &fragShader);
    if (!ok)
    {
        glDeleteShader(vertShader);
        return;
    }

    GLuint program = glCreateProgram();
    GL_CHECK(glAttachShader(program, vertShader));
    GL_CHECK(glAttachShader(program, fragShader));
    GL_CHECK(glLinkProgram(program));

    GLint status = GL_TRUE;
    GL_CHECK(glGetProgramiv(program, GL_LINK_STATUS, &status));

    if (status == GL_FALSE)
    {
        GFX_LOGE("ERROR: Failed to link program: %u", program);
        std::string programLog = logForOpenGLProgram(program);
        GFX_LOGE("%s", programLog.c_str());
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
        glDeleteProgram(program);
        return;
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    _glID = program;

    // parse attribute
    GLint numAttributes;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &numAttributes);

    if (numAttributes > 0)
    {
        GLint length;
        glGetProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);

        if (length > 0)
        {
            GLchar* attribName = (GLchar*) new char(length + 1);
            Attribute attribute;
            for (GLint i = 0; i < numAttributes; ++i) {
                // Query attribute info.
                glGetActiveAttrib(program, i, length, nullptr, &attribute.size, &attribute.type, attribName);
                attribName[length] = '\0';
                attribute.name = attribName;
                // Query the pre-assigned attribute location
                attribute.location = glGetAttribLocation(program, attribName);

                _attributes.push_back(std::move(attribute));
            }
            delete [] attribName;
        }
    }

    // Query and store uniforms from the program.
    GLint activeUniforms;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &activeUniforms);
    if (activeUniforms > 0)
    {
        GLint length;
        glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
        if (length > 0)
        {
            GLchar* uniformName = (GLchar*) new char(length + 1);

            Uniform uniform;
            for (int i = 0; i < activeUniforms; ++i)
            {
                // Query uniform info.
                GL_CHECK(glGetActiveUniform(program, i, length, nullptr, &uniform.size, &uniform.type, uniformName));
                uniformName[length] = '\0';
                bool isArray = false;
                // remove possible array '[]' from uniform name
                if (length > 3)
                {
                    char* c = strrchr(uniformName, '[');
                    if (c)
                    {
                        *c = '\0';
                        isArray = true;
                    }
                }

                uniform.name = uniformName;
                GL_CHECK(uniform.location = glGetUniformLocation(program, uniformName));

                GLenum err = glGetError();
                if (err != GL_NO_ERROR)
                {
                    GFX_LOGE("error: 0x%x  uniformName: %s", (int)err, uniformName);
                }
                assert(err == GL_NO_ERROR);

                if (!isArray)
                {
                    uniform.size = -1;
                }

                _uniforms.push_back(std::move(uniform));
            }
            
            delete [] uniformName;
        }
    }

    _linked = true;
}

GFX_END
