#pragma once

#include "Macros.h"

#include "base/CCRef.h"

CC_BACKEND_BEGIN

class CommandBuffer;

class CommandQueue : public cocos2d::Ref
{
public:
    virtual CommandBuffer* createCommandBuffer() = 0;
};

CC_BACKEND_END
