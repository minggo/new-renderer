#include "TextureGL.h"

#include "ccMacros.h"

CC_BACKEND_BEGIN

TextureGL::TextureGL(const TextureDescriptor& descriptor) : Texture(descriptor)
{
    glGenTextures(1, &_texture);
    toGLTypes();
}

TextureGL::~TextureGL()
{
    if (_texture)
        glDeleteTextures(1, &_texture);
}

void TextureGL::updateData(uint8_t* data, uint32_t size)
{
    // TODO: support texture cube, and compressed data.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 _internalFormat,
                 _width,
                 _height,
                 0,
                 _format,
                 _type,
                 data);
    glGenerateMipmap(GL_TEXTURE_2D);
    CHECK_GL_ERROR_DEBUG();
}

void TextureGL::toGLTypes()
{
    switch (_textureFormat)
    {
        case TextureFormat::R8G8B8A8:
            _internalFormat = GL_RGBA;
            _format = GL_RGBA;
            _type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::R8G8B8:
            _internalFormat = GL_RGB;
            _format = GL_RGB;
            _type = GL_UNSIGNED_BYTE;
            break;
        case TextureFormat::R5G5B5A1:
            _internalFormat = GL_RGBA;
            _format = GL_RGBA;
            _type = GL_UNSIGNED_SHORT_5_5_5_1;
            break;
        case TextureFormat::R4G4B4A4:
            _internalFormat = GL_RGBA;
            _format = GL_RGBA;
            _type = GL_UNSIGNED_SHORT_4_4_4_4;
            break;
        case TextureFormat::R5G6B5:
            _internalFormat = GL_RGB;
            _format = GL_RGB;
            _type = GL_UNSIGNED_SHORT_5_6_5;
            break;
        case TextureFormat::A8:
            _internalFormat = GL_ALPHA;
            _format = GL_ALPHA;
            _type = GL_UNSIGNED_BYTE;
            break;
        default:
            break;
    }
}

CC_BACKEND_END
