#pragma once

#include "Macros.h"
#include "base/CCRef.h"

#include <string>
#include <unordered_map>
#include <vector>

CC_BACKEND_BEGIN

class Texture;
class Sampler;

class BindGroup : public cocos2d::Ref
{
public:
    struct UniformInfo
    {
        UniformInfo(const std::string& _name, void* _data, uint32_t _size);
        UniformInfo() = default;
        ~UniformInfo();
        UniformInfo& operator =(UniformInfo&& rhs);
        
        std::string name;
        uint32_t size = 0;
        void* data = nullptr;
    };
    
    struct TextureInfo
    {
        TextureInfo(const std::string& _name, const std::vector<uint32_t>& _indices, const std::vector<Texture*> _textures);
        TextureInfo() = default;
        ~TextureInfo();
        TextureInfo& operator =(TextureInfo&& rhs);
        
        void retainTextures();
        void releaseTextures();
        
        std::string name;
        std::vector<uint32_t> indices;
        std::vector<Texture*> textures;
    };
    
    void setTexture(const std::string& name, uint32_t index, Texture* texture);
    void setTextureArray(const std::string& name, const std::vector<uint32_t>& indices, const std::vector<Texture*> textures);
    void setVertexUniform(int location, const std::string& name, void* data, uint32_t size);
    void setFragmentUniform(int location, const std::string& name, void* data, uint32_t size);
    
    inline const std::unordered_map<int, UniformInfo>& getVertexUniformInfos() const { return _vertexUniformInfos; }
    inline const std::unordered_map<int, UniformInfo>& getFragUniformInfos() const { return _fragUniformInfos; }
    inline const std::unordered_map<std::string, TextureInfo>& getTextureInfos() const { return _textureInfos; }
    
private:
    std::unordered_map<int, UniformInfo> _vertexUniformInfos;
    std::unordered_map<int, UniformInfo> _fragUniformInfos;
    std::unordered_map<std::string, TextureInfo> _textureInfos;
};

CC_BACKEND_END
