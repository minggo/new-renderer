#pragma once

#include "Macros.h"
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include <string>
#include <vector>
#include <unordered_map>

CC_BACKEND_BEGIN

class ShaderModule;
class Texture;

class Program : public Ref
{
public:
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
    
    virtual int getUniformLocation(const std::string& uniform) = 0;
    virtual void setVertexUniform(int location, void* data, uint32_t size) = 0;
    virtual void setFragmentUniform(int location, void* data, uint32_t size) = 0;
    virtual void setTexture(const std::string& name, uint32_t index, Texture* texture);
    virtual void setTextureArray(const std::string& name, const std::vector<uint32_t>& indices, const std::vector<Texture*> textures);
    
    inline ShaderModule* getVertexShader() const { return _vertexShader; }
    inline ShaderModule* getFragmentShader() const { return _fragmentShader; }
    inline const std::unordered_map<std::string, TextureInfo>& getTextureInfos() const { return _textureInfos; }
    
protected:
    Program(ShaderModule* vs, ShaderModule* fs);
    virtual ~Program();
    
private:
    backend::ShaderModule* _vertexShader = nullptr;
    backend::ShaderModule* _fragmentShader = nullptr;
    std::unordered_map<std::string, TextureInfo> _textureInfos;
};

CC_BACKEND_END
