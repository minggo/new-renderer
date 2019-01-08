#include "ProgramCache.h"
#include "Program.h"
#include "Device.h"
#include "ShaderModule.h"

CC_BACKEND_BEGIN

std::unordered_map<std::size_t, backend::Program*>  ProgramCache::_cachedPrograms;
static ProgramCache *_sharedProgramCache = nullptr;

ProgramCache* ProgramCache::getInstance()
{
    if(!_sharedProgramCache)
    {
        _sharedProgramCache = new (std::nothrow) ProgramCache();
        if(!_sharedProgramCache)
        {
            CC_SAFE_RELEASE(_sharedProgramCache);
        }
    }
    return _sharedProgramCache;
}

void ProgramCache::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_sharedProgramCache);
}

ProgramCache::~ProgramCache()
{
    for(auto& program : _cachedPrograms)
    {
        CC_SAFE_RELEASE(program.second);
    }
    CCLOGINFO("deallocing ProgramCache: %p", this);
}

backend::Program* ProgramCache::getProgram(const std::string& vertexShader, const std::string& fragmentShader) const
{
    std::string shaderSource = vertexShader + fragmentShader;
    auto key = std::hash<std::string>{}(shaderSource);
    const auto& iter = ProgramCache::_cachedPrograms.find(key);
    if (ProgramCache::_cachedPrograms.end() != iter)
    {
        return iter->second;
    }
    
    return nullptr;
}

void ProgramCache::addProgram(backend::Program* program)
{
    CC_SAFE_RETAIN(program);
    ProgramCache::_cachedPrograms.emplace(program->getKey(), program);
}

void ProgramCache::removeProgram(backend::Program* program)
{
    if (!program)
    {
        return;
    }
    
    for (auto it = _cachedPrograms.cbegin(); it != _cachedPrograms.cend();)
    {
        if (it->second == program)
        {
            it->second->release();
            it = _cachedPrograms.erase(it);
            break;
        }
        else
            ++it;
    }
}

void ProgramCache::removeAllProgram()
{
    for (auto& program : _cachedPrograms) {
        program.second->release();
    }
    _cachedPrograms.clear();
}

CC_BACKEND_END
