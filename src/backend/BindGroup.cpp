#include "BindGroup.h"
#include "Texture.h"
#include "Sampler.h"

CC_BACKEND_BEGIN

BindGroup::UniformInfo::UniformInfo(const std::string& _name, uint32_t _index, void* _data, uint32_t size)
: name(_name)
, index(_index)
{
    data = malloc(size);
    if (data)
        memcpy(data, _data, size);
}

BindGroup::UniformInfo::UniformInfo()
{}

BindGroup::UniformInfo::~UniformInfo()
{
    if (data)
        free(data);
}

BindGroup::UniformInfo& BindGroup::UniformInfo::operator=(UniformInfo&& rhs)
{
    if (this != &rhs)
    {
        name = rhs.name;
        index = rhs.index;
        
        data = rhs.data;
        rhs.data = nullptr;
    }
    
    return *this;
}

BindGroup::TextureInfo::TextureInfo(const std::string& _name, uint32_t _index, Texture* _texture)
: name(_name)
, index(_index)
, texture(_texture)
{
    CC_SAFE_RETAIN(texture);
}

BindGroup::TextureInfo::TextureInfo()
{}

BindGroup::TextureInfo::~TextureInfo()
{
    CC_SAFE_RELEASE(texture);
}

BindGroup::TextureInfo& BindGroup::TextureInfo::operator=(TextureInfo&& rhs)
{
    if (this != &rhs)
    {
        name = rhs.name;
        index = rhs.index;
        
        CC_SAFE_RETAIN(rhs.texture);
        CC_SAFE_RELEASE(texture);
        texture = rhs.texture;
        rhs.texture = nullptr;
    }
    return *this;
}

BindGroup::SamplerInfo::SamplerInfo(uint32_t _index, Sampler* _sampler)
: index(_index)
, sampler(_sampler)
{
    CC_SAFE_RETAIN(sampler);
}

BindGroup::SamplerInfo::SamplerInfo()
{}

BindGroup::SamplerInfo::~SamplerInfo()
{
    CC_SAFE_RELEASE(sampler);
}

BindGroup::SamplerInfo& BindGroup::SamplerInfo::operator=(SamplerInfo &&rhs)
{
    if (this != &rhs)
    {
        index = rhs.index;
        
        sampler = rhs.sampler;
        rhs.sampler = nullptr;
    }
    return *this;
}

BindGroup::SamplerInfo::SamplerInfo(const SamplerInfo& rhs)
: index(rhs.index)
{
    if (this != &rhs)
    {
        CC_SAFE_RETAIN(rhs.sampler);
        CC_SAFE_RELEASE(sampler);
        sampler = rhs.sampler;
    }
}

BindGroup::BindGroup()
{
    _samplerInfos.reserve(5);
}

void BindGroup::setSampler(const uint32_t index, Sampler* sampler)
{
    if (index >= _samplerInfos.size())
        _samplerInfos.resize(index + 1);

    SamplerInfo samplerInfo(index, sampler);
    _samplerInfos[index] = std::move(samplerInfo);
}

void BindGroup::bindTextureSampler(Texture* texture, Sampler* sampler)
{
    _textureSamplerMap[texture] = sampler;
}

Sampler* BindGroup::getBoundSampler(Texture* texture) const
{
    if (_textureSamplerMap.end() != _textureSamplerMap.find(texture))
        return _textureSamplerMap.at(texture);
    else
        return nullptr;
}

void BindGroup::setTexture(const std::string &name, uint32_t index, Texture *texture)
{
    TextureInfo textureInfo(name, index, texture);
    _textureInfos[name] = std::move(textureInfo);
}

void BindGroup::setUniform(const std::string& name, uint32_t index, void* data, uint32_t size)
{
    UniformInfo uniform(name, index, data, size);
    _uniformInfos[name] = std::move(uniform);
}

CC_BACKEND_END
