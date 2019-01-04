#include "RenderPipeline.h"
#include "Program.h"

CC_BACKEND_BEGIN

RenderPipeline::RenderPipeline(Program* program)
:_program(program)
{
    CC_SAFE_RETAIN(_program);
}

RenderPipeline::~RenderPipeline()
{
    CC_SAFE_RELEASE(_program);
}

CC_BACKEND_END
