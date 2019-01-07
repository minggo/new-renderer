#pragma once

#include "Macros.h"
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include "Program.h"

#include <string>
#include <unordered_map>

CC_BACKEND_BEGIN

class ShaderModule;

class ProgramCache : public Ref
{
public:
    /** returns the shared instance */
    static ProgramCache* getInstance();
    
    /** purges the cache. It releases the retained instance. */
    static void destroyInstance();
    
    backend::Program* newProgram(const std::string& vertexShader, const std::string& fragmentShader);
    
protected:
    ProgramCache() = default;
    virtual ~ProgramCache();
    
    static std::unordered_map<std::size_t, backend::Program*> _cachedPrograms;
};

CC_BACKEND_END
