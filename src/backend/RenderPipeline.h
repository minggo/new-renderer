#pragma once

#include "Macros.h"
#include "Types.h"

#include "base/CCRef.h"

CC_BACKEND_BEGIN
class Program;
class RenderPipeline : public cocos2d::Ref
{
public:
    RenderPipeline(Program* program);
    virtual ~RenderPipeline();
    
    virtual Program* getProgram() { return _program; }
    
protected:
    Program* _program = nullptr;
};

CC_BACKEND_END
