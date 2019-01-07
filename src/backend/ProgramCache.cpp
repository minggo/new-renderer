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

backend::Program* ProgramCache::newProgram(const std::string &vertexShader, const std::string &fragmentShader)
{
    std::string shaderSource = vertexShader + fragmentShader;
    std::size_t key = std::hash<std::string>{}(shaderSource);
    const auto& iter = ProgramCache::_cachedPrograms.find(key);
    if (ProgramCache::_cachedPrograms.end() != iter)
    {
        return iter->second;
    }

    auto vertexShaderModule = backend::Device::getInstance()->createShaderModule(backend::ShaderStage::VERTEX, vertexShader);
    auto fragmentShaderModule = backend::Device::getInstance()->createShaderModule(backend::ShaderStage::FRAGMENT, fragmentShader);
    auto program = backend::Device::getInstance()->createProgram(vertexShaderModule, fragmentShaderModule);
    CC_SAFE_RETAIN(program);
    
    ProgramCache::_cachedPrograms.emplace(key, program);
    
    return program;
}

CC_BACKEND_END
