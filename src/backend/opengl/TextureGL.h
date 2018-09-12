#pragma once

#include "../Texture.h"
#include "platform/CCGL.h"

CC_BACKEND_BEGIN

class TextureGL : public Texture
{
public:
    TextureGL(const TextureDescriptor& descriptor);
    ~TextureGL();
    
    // TODO: update sub data.
    virtual void updateData(uint8_t* data, uint32_t size) override;
    
    inline GLuint getHandler() const { return _texture; }
    
private:
    void toGLTypes();
    
    GLuint _texture = 0;
    
    // Used in glTexImage2D().
    GLint _internalFormat = GL_RGBA;
    GLenum _format = GL_RGBA;
    GLenum _type = GL_UNSIGNED_BYTE;
};

CC_BACKEND_END
