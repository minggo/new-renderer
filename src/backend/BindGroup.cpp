#include "BindGroup.h"
#include "Texture.h"
#include "Sampler.h"

CC_BACKEND_BEGIN

BindGroup::UniformInfo::UniformInfo(const std::string& _name, void* _data, uint32_t _size)
: name(_name)
, size(_size)
{
    data = malloc(size);
    if (data)
        memcpy(data, _data, size);
}

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
        size = rhs.size;
        
        data = rhs.data;
        rhs.data = nullptr;
    }
    
    return *this;
}

BindGroup::TextureInfo::TextureInfo(const std::string& _name, const std::vector<uint32_t>& _indices, const std::vector<Texture*> _textures)
: name(_name)
, indices(_indices)
, textures(_textures)
{
    retainTextures();
}

BindGroup::TextureInfo::~TextureInfo()
{
    releaseTextures();
}

BindGroup::TextureInfo& BindGroup::TextureInfo::operator=(TextureInfo&& rhs)
{
    if (this != &rhs)
    {
        name = rhs.name;
        indices = rhs.indices;
        
        rhs.retainTextures();
        releaseTextures();
        textures = rhs.textures;
        rhs.textures.clear();
    }
    return *this;
}

void BindGroup::TextureInfo::retainTextures()
{
    for (auto& texture : textures)
        CC_SAFE_RETAIN(texture);
}

void BindGroup::TextureInfo::releaseTextures()
{
    for (auto& texture : textures)
        CC_SAFE_RELEASE(texture);
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

void BindGroup::setTexture(const std::string &name, uint32_t index, Texture *texture)
{
    TextureInfo textureInfo(name, {index}, {texture});
    _textureInfos[name] = std::move(textureInfo);
}

void BindGroup::setTextureArray(const std::string& name, const std::vector<uint32_t>& indices, const std::vector<Texture*> textures)
{
    assert(indices.size() == textures.size());
    
    TextureInfo textureInfo(name, indices, textures);
    _textureInfos[name] = std::move(textureInfo);
}

void BindGroup::setUniform(const std::string& name, void* data, uint32_t size)
{
    UniformInfo uniform(name, data, size);
    _uniformInfos[name] = std::move(uniform);
}

CC_BACKEND_END
