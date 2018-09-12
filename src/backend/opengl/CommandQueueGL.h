#pragma once

#include "../CommandQueue.h"

CC_BACKEND_BEGIN

class CommandQueueGL : public CommandQueue
{
public:
    virtual CommandBuffer* createCommandBuffer() override;
};

CC_BACKEND_END
