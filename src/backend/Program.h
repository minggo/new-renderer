#pragma once

#include "Macros.h"
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include <string>
#include <vector>

CC_BACKEND_BEGIN

class ShaderModule;
class Texture;

class Program : public Ref
{
public:
    struct TextureInfo
    {
        ~TextureInfo();

        void retainTextures();
        void releaseTextures();

        int location = 0;
        std::vector<uint32_t> slot;
        std::vector<Texture*> textures;
    };
    
    virtual int getVertexUniformLocation(const std::string& uniform) const = 0;
    virtual int getFragmentUniformLocation(const std::string& uniform) const = 0;
    virtual void setVertexUniform(int location, void* data, uint32_t size) = 0;
    virtual void setFragmentUniform(int location, void* data, uint32_t size) = 0;
    virtual void setVertexTexture(int location, uint32_t slot, Texture* texture);
    virtual void setFragmentTexture(int location, uint32_t slot, Texture* texture);
    virtual void setVertexTextureArray(int location, const std::vector<uint32_t>& slots, const std::vector<Texture*> textures);
    virtual void setFragmentTextureArray(int location, const std::vector<uint32_t>& slots, const std::vector<Texture*> textures);
    
    inline const std::vector<TextureInfo>& getVertexTextureInfos() const { return _vertexTextureInfos; }
    inline const std::vector<TextureInfo>& getFragmentTextureInfos() const { return _fragTextureInfos; }
    
protected:
    Program() = default;
    virtual ~Program();
    
    void setTexture(int location, uint32_t slot, Texture* texture, std::vector<TextureInfo>& textureInfo);
    void setTextureArray(int location, const std::vector<uint32_t>& slots, const std::vector<Texture*> textures, std::vector<TextureInfo>& textureInfo);
    
    std::vector<TextureInfo> _vertexTextureInfos;
    std::vector<TextureInfo> _fragTextureInfos;
};

CC_BACKEND_END
