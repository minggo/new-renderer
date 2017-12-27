/****************************************************************************
 Copyright (c) 2018 Chukong Technologies
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCDeviceGraphics.h"
#include "CCVertexBuffer.h"
#include "CCIndexBuffer.h"
#include "CCFrameBuffer.h"
#include "CCGraphicsHandle.h"
#include "CCTexture2D.h"
#include "CCRenderTarget.h"

GFX_BEGIN

namespace
{
    template <typename T>
    void attach(GLenum location, const T* renderTarget)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, location, GL_RENDERBUFFER, renderTarget->getHandle());
    }
    
    void attachColorBuffer(GLenum location, const RenderTarget* texture)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, location, GL_TEXTURE_2D, texture->getHandle(), 0);
    }
    
//    enum class UniformType
//    {
//        INT,
//        INT_VEC2,
//        INT_VEC3,
//        INT_VEC4,
//
//        FLOAT,
//        FLOAT_VEC2,
//        FLOAT_VEC3,
//        FLOAT_VEC4,
//        FLOAT_MAT2,
//        FLOAT_MAT3,
//        FLOAT_MAT4,
//
//        MAT2,
//        MAT3,
//        MAT4,
//
//        COUNT
//    };
    
//    void glSetUniform(const
}

void DeviceGraphics::setFrameBuffer(const FrameBuffer* fb)
{
    if (fb == _frameBuffer)
        return;
    
    _frameBuffer = const_cast<FrameBuffer*>(fb);
    GFX_SAFE_RETAIN(_frameBuffer);
    
    if (nullptr == fb)
    {
        glBindBuffer(GL_FRAMEBUFFER, 0);
        return;
    }
    
    glBindBuffer(GL_FRAMEBUFFER, fb->getHandle());
    
    int i = 0;
    const auto& colorBuffers = fb->getColorBuffers();
    for (const auto& colorBuffer : colorBuffers)
        attachColorBuffer(GL_COLOR_ATTACHMENT0 + i, colorBuffer);
    for (i = static_cast<int>(colorBuffers.size()); i < _caps.maxColorAttatchments; ++i)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, 0, 0);
    
    if (_frameBuffer->getStencilBuffer())
        attach(GL_STENCIL_ATTACHMENT, _frameBuffer->getStencilBuffer());
    
    if (_frameBuffer->getDepthStencilBuffer())
        attach(GL_DEPTH_STENCIL_ATTACHMENT, _frameBuffer->getDepthStencilBuffer());
}

void DeviceGraphics::setViewport(int x, int y, int w, int h)
{
    if (_vx != x ||
        _vy != y ||
        _vw != w ||
        _vh != h)
    {
        _vx = x;
        _vy = y;
        _vw = w;
        _vh = h;
        glViewport(_vx, _vy, _vw, _vh);
    }
}

void DeviceGraphics::setScissor(int x, int y, int w, int h)
{
    if (_sx != x ||
        _sy != y ||
        _sw != w ||
        _sh != h)
    {
        _sx = x;
        _sy = y;
        _sw = w;
        _sh = h;
        glScissor(_sx, _sy, _sw, _sh);
    }
}

void DeviceGraphics::clear(ClearFlag flags, Color4F *color, uint8_t depth, uint8_t stencil)
{
    if (flags & ClearFlag::COLOR)
        glClearColor(color->r, color->g, color->b, color->a);
    
    if (flags & ClearFlag::DEPTH)
    {
        glClearDepth(depth);
        
        glEnable(GL_DEPTH_TEST);
        glDepthMask(true);
        glDepthFunc(GL_ALWAYS);
    }
    
    if (flags & ClearFlag::STENCIL)
        glClearStencil(stencil);
    
    glClear(flags);
    
    // Restore depth related state.
    if (flags & ClearFlag::DEPTH)
    {
        if (!_currentState.depthTest)
            glDisable(GL_DEPTH_TEST);
        else
        {
            if (!_currentState.depthWrite)
                glDepthMask(false);
            if (_currentState.depthFunc != DepthFunc::ALWAYS)
                glDepthFunc(static_cast<GLenum>(_currentState.depthFunc));
        }
    }
}

void DeviceGraphics::enableBlend()
{
    _nextState.blend = true;
}

void DeviceGraphics::enableDepthTest()
{
    _nextState.depthTest = true;
}

void DeviceGraphics::enableDepthWrite()
{
    _nextState.depthWrite = true;
}

void DeviceGraphics::enableStencilTest()
{
    _nextState.stencilTest = true;
}

void DeviceGraphics::setStencilFunc(StencilFunc func, int ref, unsigned int mask)
{
    _nextState.stencilSeparation = false;
    _nextState.stencilFuncFront = _nextState.stencilFuncBack = func;
    _nextState.stencilRefFront = _nextState.stencilRefBack = ref;
    _nextState.stencilMaskFront = _nextState.stencilMaskBack = mask;
}

void DeviceGraphics::setStencilFuncFront(StencilFunc func, int ref, unsigned int mask)
{
    _nextState.stencilSeparation = true;
    _nextState.stencilFuncFront = func;
    _nextState.stencilRefFront = ref;
    _nextState.stencilMaskFront = mask;
}

void DeviceGraphics::setStencilFuncBack(StencilFunc func, int ref, unsigned int mask)
{
    _nextState.stencilSeparation = true;
    _nextState.stencilFuncBack = func;
    _nextState.stencilRefBack = ref;
    _nextState.stencilMaskBack = mask;
}

void DeviceGraphics::setStencilOp(StencilOp failOp, StencilOp zFailOp, StencilOp zPassOp, unsigned int writeMask)
{
    _nextState.stencilFailOpFront = _nextState.stencilFailOpBack = failOp;
    _nextState.stencilZFailOpFront = _nextState.stencilZFailOpBack = zFailOp;
    _nextState.stencilZPassOpFront = _nextState.stencilZPassOpBack = zPassOp;
    _nextState.stencilWriteMaskFront = _nextState.stencilWriteMaskBack = writeMask;
}

void DeviceGraphics::setstencilOpFront(StencilOp failOp, StencilOp zFailOp, StencilOp zPassOp, unsigned int writeMask)
{
    _nextState.stencilSeparation = true;
    _nextState.stencilFailOpFront = failOp;
    _nextState.stencilZFailOpFront = zFailOp;
    _nextState.stencilZPassOpFront = zPassOp;
    _nextState.stencilWriteMaskFront = writeMask;
}

void DeviceGraphics::setStencilOpBack(StencilOp failOp, StencilOp zFailOp, StencilOp zPassOp, unsigned int writeMask)
{
    _nextState.stencilSeparation = true;
    _nextState.stencilFailOpBack = failOp;
    _nextState.stencilZFailOpBack = zFailOp;
    _nextState.stencilZPassOpBack = zPassOp;
    _nextState.stencilWriteMaskBack = writeMask;
}

void DeviceGraphics::setDepthFunc(DepthFunc func)
{
    _nextState.depthFunc = func;
}

void DeviceGraphics::setBlendColor(uint32_t rgba)
{
    _nextState.blendColor = rgba;
}

void DeviceGraphics::setBlendColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    _nextState.blendColor = (r << 24) | (g << 16) | (b << 8) | a;
}

void DeviceGraphics::setBlendFunc(BlendFactor src, BlendFactor dst)
{
    _nextState.blendSepartion = false;
    _nextState.blendSrc = src;
    _nextState.blendDst = dst;
}

void DeviceGraphics::setBlendFuncSeparate(BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha)
{
    _nextState.blendSepartion = true;
    _nextState.blendSrc = srcRGB;
    _nextState.blendDst = dstRGB;
    _nextState.blendSrcAlpha = srcAlpha;
    _nextState.blendDstAlpha = dstAlpha;
}

void DeviceGraphics::setBlendEquation(BlendOp mode)
{
    _nextState.blendSepartion = false;
    _nextState.blendEq = mode;
}

void DeviceGraphics::setBlendEquationSeparate(BlendOp modeRGB, BlendOp modeAlpha)
{
    _nextState.blendSepartion = true;
    _nextState.blendEq = modeRGB;
    _nextState.blendAlphaEq = modeAlpha;
}

void DeviceGraphics::setCullMode(CullMode mode)
{
    _nextState.cullMode = mode;
}

void DeviceGraphics::setVertexBuffer(int stream, VertexBuffer* buffer, int start /*= 0*/)
{
    //Is this function should be private, and only to be invoked by renderer?
    // If so, then don't have to do reference count.
    
    _nextState.vertexBuffers.reserve(stream + 1);
    
    auto currentBuffer = _nextState.vertexBuffers[stream];
    if (currentBuffer != buffer)
    {
        GFX_SAFE_RELEASE(currentBuffer);
        _nextState.vertexBuffers[stream] = buffer;
        GFX_SAFE_RETAIN(buffer);
    }
    
    _nextState.vertexBufferOffsets.reserve(stream + 1);
    _nextState.vertexBufferOffsets[stream] = start;
}

void DeviceGraphics::setIndexBuffer(IndexBuffer *buffer)
{
    //Is this function should be private, and only to be invoked by renderer?
    // If so, then don't have to do reference count.
    
    if (_nextState.indexBuffer == buffer)
        return;
    
    GFX_SAFE_RELEASE(_nextState.indexBuffer);
    _nextState.indexBuffer = buffer;
    GFX_SAFE_RETAIN(buffer);
}

void DeviceGraphics::setProgram(Program *program)
{
    //TODO
}

void DeviceGraphics::setTexture(const std::string& name, Texture* texture, int slot)
{
    if (slot >= _caps.maxTextureUints)
    {
        // TODO: add log
        return;
    }
    
    // textureUintes's capacity is reserved as _caps.maxTextureUints in DeviceGraphics's constructore.
    GFX_SAFE_RELEASE(_nextState.textureUintes[slot]);
    _nextState.textureUintes[slot] = texture;
    GFX_SAFE_RETAIN(texture);
    
    setUniform(name, slot);
}

void DeviceGraphics::setTextureArray(const std::string& name, const std::vector<Texture*>& texutres, const std::vector<int>& slots)
{
    auto len = texutres.size();
    if (len >= _caps.maxTextureUints)
    {
        //TODO: add log
        return;
    }
    for (size_t i = 0; i < len; ++i)
    {
        auto slot = slots[i];
        GFX_SAFE_RELEASE(_nextState.textureUintes[slot]);
        _nextState.textureUintes[slot] = texutres[i];
        GFX_SAFE_RETAIN(texutres[i]);
    }
    
    setUniformiv(name, slots.size(), slots.data());
}

void DeviceGraphics::setPrimitiveType(PrimitiveType type)
{
    _nextState.primitiveType = type;
}

void DeviceGraphics::draw(int base, size_t count)
{
    
}

void DeviceGraphics::setUniformCommon(const std::string& name, const void* v, Uniform::Type type, size_t bytes)
{
    if (_uniforms.find(name) == _uniforms.end())
    {
        Uniform uniform(v, type, bytes);
        _uniforms[name] = std::move(uniform);
    }
    else
    {
        auto& uniform = _uniforms[name];
        uniform.dirty = true;
        uniform.setValue(v, bytes);
        uniform.type = type;
    }
}

void DeviceGraphics::setUniform(const std::string& name, int i1)
{
    setUniformCommon(name, &i1, Uniform::Type::INT, sizeof(int));
}

void DeviceGraphics::setUniform(const std::string& name, int i1, int i2)
{
    int tempValue[] = {i1, i2};
    setUniformCommon(name, tempValue, Uniform::Type::INT_VEC2, 2 * sizeof(int));
}

void DeviceGraphics::setUniform(const std::string& name, int i1, int i2, int i3)
{
    int tempValue[] = {i1, i2, i3};
    setUniformCommon(name, tempValue, Uniform::Type::INT_VEC3, 3 * sizeof(int));
}

void DeviceGraphics::setUniform(const std::string& name, int i1, int i2, int i3, int i4)
{
    int tempValue[] = {i1, i2, i3, i4};
    setUniformCommon(name, tempValue, Uniform::Type::INT_VEC4, 4 * sizeof(int));
}

void DeviceGraphics::setUniformiv(const std::string& name, size_t count, const int* value)
{
    setUniformCommon(name, value, Uniform::Type::INT_ARRAY, count * sizeof(int));

}

void DeviceGraphics::setUniform(const std::string& name, float f1)
{
    setUniformCommon(name, &f1, Uniform::Type::FLOAT, sizeof(float));
}

void DeviceGraphics::setUniform(const std::string& name, float f1, float f2)
{
    float tempValue[] = {f1, f2};
    setUniformCommon(name, tempValue, Uniform::Type::FLOAT_VEC2, 2 * sizeof(float));
}

void DeviceGraphics::setUniform(const std::string& name, float f1, float f2, float f3)
{
    float tempValue[] = {f1, f2, f3};
    setUniformCommon(name, tempValue, Uniform::Type::FLOAT_VEC3, 3 * sizeof(float));
}

void DeviceGraphics::setUniform(const std::string& name, float f1, float f2, float f3, float f4)
{
    float tempValue[] = {f1, f2, f3, f4};
    setUniformCommon(name, tempValue, Uniform::Type::FLOAT_VEC4, 4 * sizeof(float));
}

void DeviceGraphics::setUniformfv(const std::string& name, size_t count, const float* value)
{
    setUniformCommon(name, value, Uniform::Type::FLOAT_ARRAY, count * sizeof(float));
}

void DeviceGraphics::setUniform(const std::string& name, const cocos2d::Vec2& value)
{
    setUniform(name, value.x, value.y);
}

void DeviceGraphics::setUniform(const std::string& name, const cocos2d::Vec3& value)
{
    setUniform(name, value.x, value.y, value.z);
}

void DeviceGraphics::setUniform(const std::string& name, const cocos2d::Vec4& value)
{
    setUniform(name, value.x, value.y, value.z, value.w);
}

void DeviceGraphics::setUniformMat2(const std::string& name, float* value)
{
    setUniformfv(name, 4, value);
}

void DeviceGraphics::setUniformMat3(const std::string& name, float* value)
{
    setUniformfv(name, 9, value);
}

void DeviceGraphics::setUniformMat4(const std::string& name, float* value)
{
    setUniformfv(name, 16, value);
}

void DeviceGraphics::setUniformMat(const std::string& name, const cocos2d::Mat4& value)
{
    setUniformfv(name, 16, value.m);
}

//
// Priviate funcitons.
//

DeviceGraphics::DeviceGraphics()
: _vx(0)
, _vy(0)
, _vw(0)
, _vh(0)
, _sx(0)
, _sy(0)
, _sw(0)
, _sh(0)
, _frameBuffer(nullptr)
{
    // initExtensions?
    
    initCaps();
    initStates();
    
    _nextState.textureUintes.reserve(_caps.maxTextureUints);
}

DeviceGraphics::~DeviceGraphics()
{
    GFX_SAFE_RELEASE(_frameBuffer);
}

void DeviceGraphics::initCaps()
{
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &_caps.maxVextexTextures);
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_caps.maxVertexAttributes);
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &_caps.maxFragUniforms);
    glGetIntegerv(GL_MAX_TEXTURE_UNITS, &_caps.maxTextureUints);
    
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &_caps.maxDrawBuffers);
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &_caps.maxColorAttatchments);
}

void DeviceGraphics::initStates()
{
    glDisable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);
    glBlendEquation(GL_FUNC_ADD);
    glBlendColor(1, 1, 1, 1);
    
    glColorMask(true, true, true, true);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(false);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glDepthRange(0, 1);
    
    glDisable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 0, 0xff);
    glStencilMask(0xff);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    
    glClearDepth(1);
    glClearColor(0, 0, 0, 0);
    glClearStencil(0);
    
    glDisable(GL_SCISSOR_TEST);
}

void DeviceGraphics::restoreTexture(uint32_t index)
{
    
}

void DeviceGraphics::restoreIndexBuffer()
{
    auto ib = _currentState.indexBuffer;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib ? ib->getHandle(): 0);
}

//
// Uniform
//
namespace
{
    void initializeUniform(const void* src, void* dst, size_t bytes)
    {
        dst = malloc(bytes);
        memcpy(dst, src, bytes);
    }
}

DeviceGraphics::Uniform::Uniform()
: dirty(true)
, value(nullptr)
, type(Type::UNKNOWN)
{}

DeviceGraphics::Uniform::Uniform(const void* v, Type t, size_t bytes)
: type(t)
{
    setValue(v, bytes);
}

DeviceGraphics::Uniform::Uniform(Uniform&& h)
{
    if (this == &h)
        return;
    
    value = h.value;
    h.value = nullptr;
    
    dirty = h.dirty;
    type = h.type;
}

DeviceGraphics::Uniform::~Uniform()
{
    if (value)
    {
        free(value);
        value = nullptr;
    }
}

DeviceGraphics::Uniform& DeviceGraphics::Uniform::operator=(Uniform&& h)
{
    if (this == &h)
        return *this;
    
    dirty = h.dirty;
    type = h.type;
    
    value = h.value;
    h.value = nullptr;
    
    return *this;
}

void DeviceGraphics::Uniform::setValue(const void* v, size_t bytes)
{
    if (value)
        free(value);
    
    initializeUniform(v, value, bytes);
}

GFX_END
