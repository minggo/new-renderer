#pragma once

#include "../Sampler.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN

class SamplerGL : public Sampler
{
public:
    SamplerGL(const SamplerDescriptor& descriptor);
};

CC_BACKEND_END
