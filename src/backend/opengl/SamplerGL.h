#pragma once

#include "../Sampler.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN

class SamplerGL : public Sampler
{
public:
    SamplerGL(const SamplerDescriptor& descriptor);
    
    void apply() const;
    
private:
    GLint _magFilterGL = GL_LINEAR;
    GLint _minFilterGL = GL_LINEAR;
    GLint _rAddressModeGL = GL_REPEAT;
    GLint _sAddressModeGL = GL_REPEAT;
    GLint _tAddressModeGL = GL_REPEAT;
};

CC_BACKEND_END
