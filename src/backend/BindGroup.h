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
        UniformInfo(const std::string& _name, uint32_t index, void* _data, uint32_t size);
        UniformInfo();
        ~UniformInfo();
        UniformInfo& operator =(UniformInfo&& rhs);
        
        std::string name;
        uint32_t index = 0;
        void* data = nullptr;
    };
    
    struct TextureInfo
    {
        TextureInfo(const std::string& _name, uint32_t _index, Texture* _texture);
        TextureInfo();
        ~TextureInfo();
        TextureInfo& operator =(TextureInfo&& rhs);
        
        std::string name;
        uint32_t index = 0;
        Texture* texture = nullptr;
    };
    
    struct SamplerInfo
    {
        SamplerInfo(uint32_t index, Sampler* sampler);
        SamplerInfo();
        SamplerInfo(const SamplerInfo& rhs);
        ~SamplerInfo();
        SamplerInfo& operator =(SamplerInfo&& rhs);
        
        uint32_t index = 0;
        Sampler* sampler = nullptr;
    };
    
    BindGroup();
    
    void setTexture(const std::string& name, uint32_t index, Texture* texture);
    void setSampler(const uint32_t index, Sampler* sampler);
    void bindTextureSampler(Texture* texture, Sampler* sampler);
    Sampler* getBoundSampler(Texture* texture) const;
    void setUniform(const std::string& name, uint32_t index, void* data, uint32_t size);
    
    inline const std::unordered_map<std::string, UniformInfo>& getUniformInfos() const { return _uniformInfos; }
    inline const std::unordered_map<std::string, TextureInfo>& getTextureInfos() const { return _textureInfos; }
    
private:
    std::unordered_map<std::string, UniformInfo> _uniformInfos;
    std::unordered_map<std::string, TextureInfo> _textureInfos;
    
    std::vector<SamplerInfo> _samplerInfos;
    std::unordered_map<Texture*, Sampler*> _textureSamplerMap;
};

CC_BACKEND_END
