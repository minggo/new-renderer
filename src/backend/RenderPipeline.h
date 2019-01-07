#pragma once

#include "Macros.h"
#include "Types.h"

#include "base/CCRef.h"

CC_BACKEND_BEGIN
class Program;
class RenderPipeline : public cocos2d::Ref
{
public:
    virtual ~RenderPipeline();
    
    virtual Program* getProgram() const { return _program; }
    
protected:
    RenderPipeline(Program* program);
    
    Program* _program = nullptr;
};

CC_BACKEND_END
