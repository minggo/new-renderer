#include "CommandBuffer.h"

CC_BACKEND_BEGIN

void CommandBuffer::setStencilReferenceValue(uint32_t value)
{
    _stencilReferenceValueBack = _stencilReferenceValueFront = value;
}

CC_BACKEND_END
