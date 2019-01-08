#include "Program.h"
#include "ShaderModule.h"
#include "Texture.h"

CC_BACKEND_BEGIN

Program::Program(const std::string& vertexShader, const std::string& fragmentShader)
{
    std::string shaderSource = vertexShader + fragmentShader;
    _key = std::hash<std::string>{}(shaderSource);
}

Program::~Program()
{
    _vertexTextureInfos.clear();
    _fragmentTextureInfos.clear();
}

Program::TextureInfo::~TextureInfo()
{
    releaseTextures();
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

void Program::setVertexTexture(int location, uint32_t slot, Texture* texture)
{
    setTexture(location, slot, texture, _vertexTextureInfos);
}

void Program::setFragmentTexture(int location, uint32_t slot, Texture* texture)
{
    setTexture(location, slot, texture, _fragmentTextureInfos);
}

void Program::setVertexTextureArray(int location, const std::vector<uint32_t>& slots, const std::vector<Texture*> textures)
{
    setTextureArray(location, slots, textures, _vertexTextureInfos);
}

void Program::setFragmentTextureArray(int location, const std::vector<uint32_t>& slots, const std::vector<Texture*> textures)
{
    setTextureArray(location, slots, textures, _fragmentTextureInfos);
}

void Program::setTexture(int location, uint32_t slot, Texture* texture, std::unordered_map<int, TextureInfo>& textureInfo)
{
    if(location < 0)
        return;

    TextureInfo info;
    info.location = location;
    info.slot = {slot};
    info.textures = {texture};
    info.retainTextures();
    textureInfo[location] = info;
}

void Program::setTextureArray(int location, const std::vector<uint32_t>& slots, const std::vector<Texture*> textures, std::unordered_map<int, TextureInfo>& textureInfo)
{
    assert(slots.size() == textures.size());
    TextureInfo info;
    info.location = location;
    info.slot = slots;
    info.textures = textures;
    info.retainTextures();
    textureInfo[location] = info;
}

CC_BACKEND_END
