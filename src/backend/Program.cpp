#include "Program.h"
#include "ShaderModule.h"
#include "Texture.h"

CC_BACKEND_BEGIN

Program::Program(ShaderModule* vs, ShaderModule* fs)
: _vertexShader(vs)
, _fragmentShader(fs)
{
    CC_SAFE_RETAIN(_vertexShader);
    CC_SAFE_RETAIN(_fragmentShader);
}

Program::~Program()
{
    CC_SAFE_RELEASE(_vertexShader);
    CC_SAFE_RELEASE(_fragmentShader);
    _textureInfos.clear();
}

Program::TextureInfo::TextureInfo(const std::string& _name, const std::vector<uint32_t>& _indices, const std::vector<Texture*> _textures)
: name(_name)
, indices(_indices)
, textures(_textures)
{
    retainTextures();
}

Program::TextureInfo::~TextureInfo()
{
    releaseTextures();
}

Program::TextureInfo& Program::TextureInfo::operator=(TextureInfo&& rhs)
{
    if (this != &rhs)
    {
        name = rhs.name;
        indices = rhs.indices;
        
        rhs.retainTextures();
        releaseTextures();
        textures = rhs.textures;
        
        //release the textures before cleaning the vertor
        rhs.releaseTextures();
        rhs.textures.clear();
    }
    return *this;
}

void Program::TextureInfo::retainTextures()
{
    for (auto& texture : textures)
        CC_SAFE_RETAIN(texture);
}

void Program::TextureInfo::releaseTextures()
{
    for (auto& texture : textures)
        CC_SAFE_RELEASE(texture);
}

void Program::setTexture(const std::string &name, uint32_t index, Texture *texture)
{
    TextureInfo textureInfo(name, {index}, {texture});
    _textureInfos[name] = std::move(textureInfo);
}

void Program::setTextureArray(const std::string& name, const std::vector<uint32_t>& indices, const std::vector<Texture*> textures)
{
    assert(indices.size() == textures.size());
    
    TextureInfo textureInfo(name, indices, textures);
    _textureInfos[name] = std::move(textureInfo);
}

CC_BACKEND_END
