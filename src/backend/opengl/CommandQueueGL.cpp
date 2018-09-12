#include "CommandQueueGL.h"
#include "CommandBufferGL.h"

#include <new>

CC_BACKEND_BEGIN

CommandBuffer* CommandQueueGL::createCommandBuffer()
{
    auto ret = new (std::nothrow) CommandBufferGL();
    if (ret)
        ret->autorelease();
    
    return ret;
}

CC_BACKEND_END
