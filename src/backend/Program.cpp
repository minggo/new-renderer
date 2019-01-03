#include "Program.h"
#include "ShaderModule.h"

CC_BACKEND_BEGIN

Program::Program(ShaderModule* vs, ShaderModule* fs)
: _vertexShader(vs)
, _fragmentShader(fs)
{
    CC_SAFE_RETAIN(_vertexShader);
    CC_SAFE_RETAIN(_fragmentShader);
}

Program::~Program()
{
    CC_SAFE_RELEASE(_vertexShader);
    CC_SAFE_RELEASE(_fragmentShader);
}

CC_BACKEND_END
