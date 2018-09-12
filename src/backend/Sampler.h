#pragma once

#include "Macros.h"
#include "Types.h"
#include "base/CCRef.h"

CC_BACKEND_BEGIN

struct SamplerDescriptor
{
    SamplerFilter magFilter = SamplerFilter::LINEAR;
    SamplerFilter minFilter = SamplerFilter::LINEAR;
    SamplerFilter mipmapFilter = SamplerFilter::LINEAR;
    SamplerAddressMode rAddressMode = SamplerAddressMode::REPEAT;
    SamplerAddressMode sAddressMode = SamplerAddressMode::REPEAT;
    SamplerAddressMode tAssressMode = SamplerAddressMode::REPEAT;
};

class Sampler : public cocos2d::Ref
{
protected:
    Sampler();
};

CC_BACKEND_END
