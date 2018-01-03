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
#include "CCProgram.h"
#include "CCGFXUtils.h"

GFX_BEGIN

namespace {
    template <typename T>
    void attach(GLenum location, const T* renderTarget)
    {
        GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, location, GL_RENDERBUFFER, renderTarget->getHandle()));
    }
    
    void attachColorBuffer(GLenum location, const RenderTarget* texture)
    {
        GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, location, GL_TEXTURE_2D, texture->getHandle(), 0));
    }
} // namespace {

DeviceGraphics* DeviceGraphics::getInstance()
{
    static DeviceGraphics* __instance = nullptr;
    if (__instance == nullptr)
        __instance = new (std::nothrow) DeviceGraphics();

    return __instance;
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

void DeviceGraphics::clear(uint8_t flags, Color4F *color, double depth, int32_t stencil)
{
    GLbitfield mask = 0;
    if (flags & ClearFlag::COLOR)
    {
        mask |= GL_COLOR_BUFFER_BIT;
        glClearColor(color->r, color->g, color->b, color->a);
    }
    
    if (flags & ClearFlag::DEPTH)
    {
        mask |= GL_DEPTH_BUFFER_BIT;
        glClearDepth(depth);
        
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_ALWAYS);
    }
    
    if (flags & ClearFlag::STENCIL)
    {
        mask |= GL_STENCIL_BUFFER_BIT;
        glClearStencil(stencil);
    }
    
    glClear(mask);
    
    // Restore depth related state.
    if (flags & ClearFlag::DEPTH)
    {
        if (!_currentState.depthTest)
            glDisable(GL_DEPTH_TEST);
        else
        {
            if (!_currentState.depthWrite)
                glDepthMask(GL_FALSE);
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
    _nextState.setVertexBuffer(stream, buffer);
    _nextState.setVertexBufferOffset(stream, start);

    if (_nextState.maxStream < stream) {
        _nextState.maxStream = stream;
    }
}

void DeviceGraphics::setIndexBuffer(IndexBuffer *buffer)
{
    _nextState.setIndexBuffer(buffer);
}

void DeviceGraphics::setProgram(Program *program)
{
    _nextState.setProgram(program);
}

void DeviceGraphics::setTexture(const std::string& name, Texture* texture, int slot)
{
    if (slot >= _caps.maxTextureUints)
    {
        // TODO: add log
        return;
    }
    
    _nextState.setTexture(slot, texture);
    setUniformi(name, slot);
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
        _nextState.setTexture(slot, texutres[i]);
    }
    
    setUniformiv(name, slots.size(), slots.data());
}

void DeviceGraphics::setPrimitiveType(PrimitiveType type)
{
    _nextState.primitiveType = type;
}

void DeviceGraphics::draw(size_t base, GLsizei count)
{
    commitBlendStates();
    commitDepthStates();
    commitStencilStates();
    commitCullMode();
    commitVertexBuffer();
    
    auto nextIndexBuffer = _nextState.getIndexBuffer();
    if (_currentState.getIndexBuffer() != nextIndexBuffer)
    {
        GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nextIndexBuffer ? nextIndexBuffer->getHandle() : 0));
    }
    
    //commit program
    bool programDirty = false;
    if (_currentState.getProgram() != _nextState.getProgram())
    {
        if (_nextState.getProgram()->isLinked())
        {
            GL_CHECK(glUseProgram(_nextState.getProgram()->getHandle()));
        }
        else
        {
            //TODO: log
        }
        programDirty = true;
    }
    
    commitTextures();
    
    //commit uniforms
    const auto& uniformsInfo = _nextState.getProgram()->getUniforms();
    auto uniformsLen = uniformsInfo.size();
    for (int i = 0; i < uniformsLen; ++i)
    {
        const auto& uniformInfo = uniformsInfo[i];
        auto iter = _uniforms.find(uniformInfo.name);
        if (_uniforms.end() == iter)
            continue;
        
        auto& uniform = iter->second;
        if (!programDirty && !uniform.dirty)
            continue;
        
        uniform.dirty = false;
        
        setUniformToGL(uniformInfo.location, uniform);
    }
    
    // draw primitives
    if (nextIndexBuffer)
        GL_CHECK(glDrawElements(ENUM_CLASS_TO_GLENUM(_nextState.primitiveType),
                       count,
                       ENUM_CLASS_TO_GLENUM(nextIndexBuffer->getFormat()),
                       (GLvoid *)(base * nextIndexBuffer->getBytesPerIndex())));
    else
        GL_CHECK(glDrawArrays(ENUM_CLASS_TO_GLENUM(_nextState.primitiveType), (GLint)base, count));
    
    _currentState = std::move(_nextState);
}

void DeviceGraphics::setUniformCommon(const std::string& name, const void* v, Uniform::Type type, size_t bytes)
{
    setUniformCommon(name, v, type, bytes, 1);
}

void DeviceGraphics::setUniformCommon(const std::string& name, const void* v, Uniform::Type type, size_t bytes, size_t count)
{
    auto iter = _uniforms.find(name);
    if (iter == _uniforms.end())
    {
        Uniform uniform(v, type, bytes, count);
        _uniforms[name] = std::move(uniform);
    }
    else
    {
        auto& uniform = iter->second;
        uniform.dirty = true;
        uniform.setValue(v, bytes);
        uniform.type = type;
        uniform.count = count;
    }
}

void DeviceGraphics::setUniformi(const std::string& name, int i1)
{
    setUniformCommon(name, &i1, Uniform::Type::INT, sizeof(int));
}

void DeviceGraphics::setUniformi(const std::string& name, int i1, int i2)
{
    int tempValue[] = {i1, i2};
    setUniformCommon(name, tempValue, Uniform::Type::INT2, 2 * sizeof(int));
}

void DeviceGraphics::setUniformi(const std::string& name, int i1, int i2, int i3)
{
    int tempValue[] = {i1, i2, i3};
    setUniformCommon(name, tempValue, Uniform::Type::INT3, 3 * sizeof(int));
}

void DeviceGraphics::setUniformi(const std::string& name, int i1, int i2, int i3, int i4)
{
    int tempValue[] = {i1, i2, i3, i4};
    setUniformCommon(name, tempValue, Uniform::Type::INT4, 4 * sizeof(int));
}

void DeviceGraphics::setUniformiv(const std::string& name, size_t count, const int* value)
{
    setUniformCommon(name, value, Uniform::Type::INT_ARRAY, count * sizeof(int), count);
}

void DeviceGraphics::setUniformf(const std::string& name, float f1)
{
    setUniformCommon(name, &f1, Uniform::Type::FLOAT, sizeof(float));
}

void DeviceGraphics::setUniformf(const std::string& name, float f1, float f2)
{
    float tempValue[] = {f1, f2};
    setUniformCommon(name, tempValue, Uniform::Type::FLOAT2, 2 * sizeof(float));
}

void DeviceGraphics::setUniformf(const std::string& name, float f1, float f2, float f3)
{
    float tempValue[] = {f1, f2, f3};
    setUniformCommon(name, tempValue, Uniform::Type::FLOAT3, 3 * sizeof(float));
}

void DeviceGraphics::setUniformf(const std::string& name, float f1, float f2, float f3, float f4)
{
    float tempValue[] = {f1, f2, f3, f4};
    setUniformCommon(name, tempValue, Uniform::Type::FLOAT4, 4 * sizeof(float));
}

void DeviceGraphics::setUniformfv(const std::string& name, size_t count, const float* value)
{
    setUniformCommon(name, value, Uniform::Type::FLOAT_ARRAY, count * sizeof(float), count);
}

void DeviceGraphics::setUniformVec2(const std::string& name, const cocos2d::Vec2& value)
{
    setUniformf(name, value.x, value.y);
}

void DeviceGraphics::setUniformVec3(const std::string& name, const cocos2d::Vec3& value)
{
    setUniformf(name, value.x, value.y, value.z);
}

void DeviceGraphics::setUniformVec4(const std::string& name, const cocos2d::Vec4& value)
{
    setUniformf(name, value.x, value.y, value.z, value.w);
}

void DeviceGraphics::setUniformMat2(const std::string& name, float* value)
{
    setUniformCommon(name, value, Uniform::Type::MAT2, 4 * sizeof(float));
}

void DeviceGraphics::setUniformMat3(const std::string& name, float* value)
{
    setUniformCommon(name, value, Uniform::Type::MAT3, 9 * sizeof(float));
}

void DeviceGraphics::setUniformMat4(const std::string& name, float* value)
{
    setUniformCommon(name, value, Uniform::Type::MAT4, 16 * sizeof(float));
}

void DeviceGraphics::setUniformMat4(const std::string& name, const cocos2d::Mat4& value)
{
    setUniformCommon(name, value.m, Uniform::Type::MAT4, 16 * sizeof(float));
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
    
    _newAttributes.resize(_caps.maxVertexAttributes);
    _enabledAtrributes.resize(_caps.maxVertexAttributes);
    
    // Make sure _currentState and _nextState have enough sapce for textures.
    _currentState.setTexture(_caps.maxTextureUints, nullptr);
    _nextState.setTexture(_caps.maxTextureUints, nullptr);
}

DeviceGraphics::~DeviceGraphics()
{
    GFX_SAFE_RELEASE(_frameBuffer);
}

void DeviceGraphics::initCaps()
{
    GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &_caps.maxVextexTextures));
    GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_caps.maxVertexAttributes));
    GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &_caps.maxFragUniforms));
    GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &_caps.maxFragUniforms));
    GL_CHECK(glGetIntegerv(GL_MAX_TEXTURE_UNITS, &_caps.maxTextureUints));
    GL_CHECK(glGetIntegerv(GL_MAX_DRAW_BUFFERS, &_caps.maxDrawBuffers));
    GL_CHECK(glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &_caps.maxColorAttatchments));
}

void DeviceGraphics::initStates()
{
    GL_CHECK(glDisable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_ONE, GL_ZERO));
    GL_CHECK(glBlendEquation(GL_FUNC_ADD));
    GL_CHECK(glBlendColor(1, 1, 1, 1));
    
    GL_CHECK(glColorMask(true, true, true, true));
    
    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glCullFace(GL_BACK));
    
    GL_CHECK(glDisable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LESS));
    GL_CHECK(glDepthMask(GL_FALSE));
    GL_CHECK(glDisable(GL_POLYGON_OFFSET_FILL));
    GL_CHECK(glDepthRange(0, 1));
    
    GL_CHECK(glDisable(GL_STENCIL_TEST));
    GL_CHECK(glStencilFunc(GL_ALWAYS, 0, 0xff));
    GL_CHECK(glStencilMask(0xff));
    GL_CHECK(glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP));
    
    GL_CHECK(glClearDepth(1));
    GL_CHECK(glClearColor(0, 0, 0, 0));
    GL_CHECK(glClearStencil(0));
    
    GL_CHECK(glDisable(GL_SCISSOR_TEST));
}

void DeviceGraphics::restoreTexture(uint32_t index)
{
    auto texture = _currentState.getTexture(index);
    if (texture)
    {
        GL_CHECK(glBindTexture(texture->getTarget(), texture->getHandle()));
    }
    else
    {
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
    }
}

void DeviceGraphics::restoreIndexBuffer()
{
    auto ib = _currentState.getIndexBuffer();
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib ? ib->getHandle(): 0));
}

void DeviceGraphics::commitBlendStates()
{
    if (_currentState.blend != _nextState.blend)
    {
        if (!_nextState.blend)
        {
            glDisable(GL_BLEND);
            return;
        }

        glEnable(GL_BLEND);
        
        if (_nextState.blendSrc == BlendFactor::CONSTANT_COLOR ||
            _nextState.blendSrc == BlendFactor::ONE_MINUS_CONSTANT_COLOR ||
            _nextState.blendDst == BlendFactor::CONSTANT_COLOR ||
            _nextState.blendDst == BlendFactor::ONE_MINUS_CONSTANT_COLOR)
        {
            GL_CHECK(glBlendColor((_nextState.blendColor >> 24) / 255.f,
                         (_nextState.blendColor >> 16 & 0xff) / 255.f,
                         (_nextState.blendColor >> 8 & 0xff) / 255.f,
                         (_nextState.blendColor & 0xff) / 255.f));
            
        }
        
        if (_nextState.blendSepartion)
        {
            GL_CHECK(glBlendFuncSeparate(ENUM_CLASS_TO_GLENUM(_nextState.blendSrc),
                                ENUM_CLASS_TO_GLENUM(_nextState.blendDst),
                                ENUM_CLASS_TO_GLENUM(_nextState.blendSrcAlpha),
                                ENUM_CLASS_TO_GLENUM(_nextState.blendDstAlpha)));
            GL_CHECK(glBlendEquationSeparate(ENUM_CLASS_TO_GLENUM(_nextState.blendEq),
                                    ENUM_CLASS_TO_GLENUM(_nextState.blendAlphaEq)));
        }
        else
        {
            GL_CHECK(glBlendFunc(ENUM_CLASS_TO_GLENUM(_nextState.blendSrc),
                        ENUM_CLASS_TO_GLENUM(_nextState.blendDst)));
            GL_CHECK(glBlendEquation(ENUM_CLASS_TO_GLENUM(_nextState.blendEq)));
        }
        
        return;
    }
    
    if (_nextState.blend == false)
        return;
    
    if (_currentState.blendColor != _nextState.blendColor)
        glBlendColor((_nextState.blendColor >> 24) / 255.f,
                     (_nextState.blendColor >> 16 & 0xff) / 255.f,
                     (_nextState.blendColor >> 8 & 0xff) / 255.f,
                     (_nextState.blendColor & 0xff) / 255.f);
    
    if (_currentState.blendSepartion != _nextState.blendSepartion)
    {
        if (_nextState.blendSepartion)
        {
            GL_CHECK(glBlendFuncSeparate(ENUM_CLASS_TO_GLENUM(_nextState.blendSrc),
                                ENUM_CLASS_TO_GLENUM(_nextState.blendDst),
                                ENUM_CLASS_TO_GLENUM(_nextState.blendSrcAlpha),
                                ENUM_CLASS_TO_GLENUM(_nextState.blendDstAlpha)));
            GL_CHECK(glBlendEquationSeparate(ENUM_CLASS_TO_GLENUM(_nextState.blendEq),
                                    ENUM_CLASS_TO_GLENUM(_nextState.blendAlphaEq)));
        }
        else
        {
            GL_CHECK(glBlendFunc(ENUM_CLASS_TO_GLENUM(_nextState.blendSrc),
                        ENUM_CLASS_TO_GLENUM(_nextState.blendDst)));
            GL_CHECK(glBlendEquation(ENUM_CLASS_TO_GLENUM(_nextState.blendEq)));
        }
        
        return;
    }
    
    if (_nextState.blendSepartion)
    {
        if (_currentState.blendSrc != _nextState.blendSrc ||
            _currentState.blendDst != _nextState.blendDst ||
            _currentState.blendSrcAlpha != _nextState.blendSrcAlpha ||
            _currentState.blendDstAlpha != _nextState.blendDstAlpha)
        {
            GL_CHECK(glBlendFuncSeparate(ENUM_CLASS_TO_GLENUM(_nextState.blendSrc),
                                ENUM_CLASS_TO_GLENUM(_nextState.blendDst),
                                ENUM_CLASS_TO_GLENUM(_nextState.blendSrcAlpha),
                                ENUM_CLASS_TO_GLENUM(_nextState.blendDstAlpha)));
        }
    }
    
    if (_currentState.blendEq != _nextState.blendEq ||
        _currentState.blendAlphaEq != _nextState.blendAlphaEq)
    {
        GL_CHECK(glBlendEquationSeparate(ENUM_CLASS_TO_GLENUM(_nextState.blendEq),
                                ENUM_CLASS_TO_GLENUM(_nextState.blendAlphaEq)));
    }
    else
    {
        if (_currentState.blendSrc != _nextState.blendSrc ||
            _currentState.blendDst != _nextState.blendDst)
        {
            GL_CHECK(glBlendFunc(ENUM_CLASS_TO_GLENUM(_nextState.blendSrc),
                        ENUM_CLASS_TO_GLENUM(_nextState.blendDst)));
        }
        
        if (_currentState.blendEq != _nextState.blendEq)
        {
            GL_CHECK(glBlendEquation(ENUM_CLASS_TO_GLENUM(_nextState.blendEq)));
        }
    }
}

void DeviceGraphics::commitDepthStates()
{
    if (_currentState.depthTest != _nextState.depthTest)
    {
        if (!_nextState.depthTest)
        {
            glDisable(GL_DEPTH_TEST);
            return;
        }
        
        glEnable(GL_DEPTH_TEST);
        GL_CHECK(glDepthFunc(ENUM_CLASS_TO_GLENUM(_nextState.depthFunc)));
        GL_CHECK(glDepthMask(_nextState.depthWrite ? GL_TRUE : GL_FALSE));
        
        return;
    }
    
    if (_currentState.depthWrite != _nextState.depthWrite)
    {
        GL_CHECK(glDepthMask(_nextState.depthWrite ? GL_TRUE : GL_FALSE));
    }
    
    if (!_nextState.depthTest)
    {
        if (_nextState.depthWrite)
        {
            _nextState.depthTest = true;
            _nextState.depthFunc = DepthFunc::ALWAYS;
            
            GL_CHECK(glEnable(GL_DEPTH_TEST));
            GL_CHECK(glDepthFunc(ENUM_CLASS_TO_GLENUM(_nextState.depthFunc)));
        }
        
        return;
    }
    
    if (_currentState.depthFunc != _nextState.depthFunc)
        GL_CHECK(glDepthFunc(ENUM_CLASS_TO_GLENUM(_nextState.depthFunc)));
}

void DeviceGraphics::commitStencilStates()
{
    if (_currentState.stencilTest != _nextState.stencilTest)
    {
        if (!_nextState.stencilTest)
        {
            glDisable(GL_STENCIL_TEST);
            return;
        }
        
        glEnable(GL_STENCIL_TEST);
        
        if (_nextState.stencilSeparation)
        {
            glStencilFuncSeparate(GL_FRONT,
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilFuncFront),
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilRefFront),
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilMaskFront));
            glStencilMaskSeparate(GL_FRONT, ENUM_CLASS_TO_GLENUM(_nextState.stencilWriteMaskFront));
            glStencilOpSeparate(GL_FRONT,
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilFailOpFront),
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilZFailOpFront),
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilZPassOpFront));
            glStencilFuncSeparate(GL_BACK,
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilFuncBack),
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilRefBack),
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilMaskBack));
            glStencilMaskSeparate(GL_BACK, ENUM_CLASS_TO_GLENUM(_nextState.stencilWriteMaskBack));
            glStencilOpSeparate(GL_BACK,
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilFailOpBack),
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilZFailOpBack),
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilZPassOpBack));
        }
        else
        {
            glStencilFunc(ENUM_CLASS_TO_GLENUM(_nextState.stencilFuncFront),
                          ENUM_CLASS_TO_GLENUM(_nextState.stencilRefFront),
                          ENUM_CLASS_TO_GLENUM(_nextState.stencilMaskFront));
            glStencilMask(ENUM_CLASS_TO_GLENUM(_nextState.stencilWriteMaskFront));
            glStencilOp(ENUM_CLASS_TO_GLENUM(_nextState.stencilFuncFront),
                        ENUM_CLASS_TO_GLENUM(_nextState.stencilZFailOpFront),
                        ENUM_CLASS_TO_GLENUM(_nextState.stencilZPassOpFront));
        }
        
        return;
    }
    
    if (!_nextState.stencilTest)
        return;
    
    if (_currentState.stencilSeparation != _nextState.stencilSeparation)
    {
        if (_nextState.stencilSeparation)
        {
            // front
            glStencilFuncSeparate(GL_FRONT,
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilFuncFront),
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilRefFront),
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilMaskFront));
            glStencilMaskSeparate(GL_FRONT, ENUM_CLASS_TO_GLENUM(_nextState.stencilWriteMaskFront));
            glStencilOpSeparate(GL_FRONT,
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilFailOpFront),
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilZFailOpFront),
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilZPassOpFront));
            
            // back
            glStencilFuncSeparate(GL_BACK,
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilFuncBack),
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilRefBack),
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilMaskBack));
            glStencilMaskSeparate(GL_BACK, ENUM_CLASS_TO_GLENUM(_nextState.stencilWriteMaskBack));
            glStencilOpSeparate(GL_BACK,
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilFailOpBack),
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilZFailOpBack),
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilZPassOpBack));
        }
        else
        {
            glStencilFunc(ENUM_CLASS_TO_GLENUM(_nextState.stencilFuncFront),
                          ENUM_CLASS_TO_GLENUM(_nextState.stencilRefFront),
                          ENUM_CLASS_TO_GLENUM(_nextState.stencilMaskFront));
            glStencilMask(ENUM_CLASS_TO_GLENUM(_nextState.stencilWriteMaskFront));
            glStencilOp(ENUM_CLASS_TO_GLENUM(_nextState.stencilFuncFront),
                        ENUM_CLASS_TO_GLENUM(_nextState.stencilZFailOpFront),
                        ENUM_CLASS_TO_GLENUM(_nextState.stencilZPassOpFront));
        }
        
        return;
    }
    
    if (_nextState.stencilSeparation)
    {
        // font
        if (_currentState.stencilFuncFront != _nextState.stencilFuncFront ||
            _currentState.stencilRefFront != _nextState.stencilRefFront ||
            _currentState.stencilMaskFront != _nextState.stencilMaskFront)
        {
            GL_CHECK(glStencilFuncSeparate(GL_FRONT,
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilFuncFront),
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilRefFront),
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilMaskFront)));
        }
        if (_currentState.stencilWriteMaskFront != _nextState.stencilWriteMaskFront)
            GL_CHECK(glStencilMaskSeparate(GL_FRONT, ENUM_CLASS_TO_GLENUM(_nextState.stencilWriteMaskFront)));
        if (_currentState.stencilFailOpFront != _nextState.stencilFailOpFront ||
            _currentState.stencilZFailOpFront != _nextState.stencilZFailOpFront ||
            _currentState.stencilZPassOpFront != _nextState.stencilZPassOpFront)
        {
            GL_CHECK(glStencilOpSeparate(GL_FRONT,
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilFailOpFront),
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilZFailOpFront),
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilZPassOpFront)));
        }
        
        // back
        if (_currentState.stencilFuncBack != _nextState.stencilFuncBack ||
            _currentState.stencilRefBack != _nextState.stencilRefBack ||
            _currentState.stencilMaskBack != _nextState.stencilMaskBack)
        {
            GL_CHECK(glStencilFuncSeparate(GL_BACK,
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilFuncBack),
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilRefBack),
                                  ENUM_CLASS_TO_GLENUM(_nextState.stencilMaskBack)));
        }
        if (_currentState.stencilWriteMaskBack != _nextState.stencilWriteMaskBack)
            GL_CHECK(glStencilMaskSeparate(GL_BACK, ENUM_CLASS_TO_GLENUM(_nextState.stencilWriteMaskBack)));
        if (_currentState.stencilFailOpBack != _nextState.stencilFailOpBack ||
            _currentState.stencilZFailOpBack != _nextState.stencilZFailOpBack ||
            _currentState.stencilZPassOpBack != _nextState.stencilZPassOpBack)
        {
            GL_CHECK(glStencilOpSeparate(GL_BACK,
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilFailOpBack),
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilZFailOpBack),
                                ENUM_CLASS_TO_GLENUM(_nextState.stencilZPassOpBack)));
        }
    }
    else
    {
        if (_currentState.stencilFuncFront != _nextState.stencilFuncFront ||
            _currentState.stencilRefFront != _nextState.stencilRefFront ||
            _currentState.stencilMaskFront != _nextState.stencilMaskFront)
        {
            GL_CHECK(glStencilFunc(ENUM_CLASS_TO_GLENUM(_nextState.stencilFuncFront),
                          ENUM_CLASS_TO_GLENUM(_nextState.stencilRefFront),
                          ENUM_CLASS_TO_GLENUM(_nextState.stencilMaskFront)));
        }
        
        if (_currentState.stencilWriteMaskFront != _nextState.stencilWriteMaskFront)
            GL_CHECK(glStencilMask(ENUM_CLASS_TO_GLENUM(_nextState.stencilWriteMaskFront)));
        
        if (_currentState.stencilFailOpFront != _nextState.stencilFailOpFront ||
            _currentState.stencilZFailOpFront != _nextState.stencilZFailOpFront ||
            _currentState.stencilZPassOpFront != _nextState.stencilZPassOpFront)
        {
            GL_CHECK(glStencilOp(ENUM_CLASS_TO_GLENUM(_nextState.stencilFuncFront),
                        ENUM_CLASS_TO_GLENUM(_nextState.stencilZFailOpFront),
                        ENUM_CLASS_TO_GLENUM(_nextState.stencilZPassOpFront)));
        }
    }
}

void DeviceGraphics::commitCullMode()
{
    if (_currentState.cullMode == _nextState.cullMode)
        return;
    
    if (_nextState.cullMode == CullMode::NONE)
    {
        GL_CHECK(glDisable(GL_CULL_FACE));
        return;
    }
    
    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glCullFace(ENUM_CLASS_TO_GLENUM(_nextState.cullMode)));
}
void DeviceGraphics::commitVertexBuffer()
{
    bool attrsDirty = false;
    
    if (-1 == _nextState.maxStream)
    {
        //TODO: log
        return;
    }
    
    if (_currentState.maxStream != _nextState.maxStream)
        attrsDirty = true;
    else if (_currentState.getProgram() != _nextState.getProgram())
        attrsDirty = true;
    else
    {
        for (int i = 0; i < _nextState.maxStream + 1; ++i)
        {
            if (_currentState.getVertexBuffer(i) != _nextState.getVertexBuffer(i) ||
                _currentState.getVertexBufferOffset(i) != _nextState.getVertexBufferOffset(i))
            {
                attrsDirty = true;
                break;
            }
        }
    }
    
    if (attrsDirty)
    {
        for (int i = 0; i < _caps.maxVertexAttributes; ++i)
            _newAttributes[i] = 0;
        
        for (int i = 0; i < _nextState.maxStream + 1; ++i)
        {
            auto vb = _nextState.getVertexBuffer(i);
            if (!vb)
                continue;
            
            GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vb->getHandle()));
            
            auto vboffset = _nextState.getVertexBufferOffset(i);
            const auto& attributes = _nextState.getProgram()->getAttributes();
            auto usedAttriLen = attributes.size();
            for (int j = 0; j < usedAttriLen; ++j)
            {
                const auto& attr = attributes[j];
                const auto& el = vb->getFormat().getElement(attr.name);
                if (!el.isValid())
                {
                    //TODO: log
                    continue;
                }
                
                if (0 == _enabledAtrributes[attr.location])
                {
                    GL_CHECK(glEnableVertexAttribArray(attr.location));
                    _enabledAtrributes[attr.location] = 1;
                }
                _newAttributes[attr.location] = 1;
                
                // glVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
                GL_CHECK(glVertexAttribPointer(attr.location,
                                      el.num,
                                      ENUM_CLASS_TO_GLENUM(el.type),
                                      el.normalize,
                                      el.stride,
                                      (GLvoid*)(el.offset + vboffset * el.stride)));
            }
        }
        
         // Disable unused attributes.
        for (int i = 0; i < _caps.maxVertexAttributes; ++i)
        {
            if (_enabledAtrributes[i] != _newAttributes[i])
            {
                GL_CHECK(glDisableVertexAttribArray(i));
                _enabledAtrributes[i] = 0;
            }
        }
    }
}

void DeviceGraphics::commitTextures()
{
    const auto& curTextureUnits = _currentState.getTextureUnits();
    int curTextureSize = static_cast<int>(curTextureUnits.size());
    const auto& nextTextureUnits = _nextState.getTextureUnits();
    int capacity = static_cast<int>(nextTextureUnits.size());
    for (int i = 0; i < capacity; ++i)
    {
        if (i >= curTextureSize || curTextureUnits[i] != nextTextureUnits[i])
        {
            auto texture = nextTextureUnits[i];
            GL_CHECK(glActiveTexture(GL_TEXTURE0 + i));
            GL_CHECK(glBindTexture(texture ? texture->getTarget() : GL_TEXTURE_2D,
                                   texture ? texture->getHandle() : 0));
        }
    }
}

void DeviceGraphics::setUniformToGL(GLint location, const Uniform& uniform) const
{
    
#define DEF_TO_INT(pointer)  (*(int*)(pointer))
#define DEF_TO_INT_STEP(pointer, step)  (*((int*)(pointer) + step))
#define DEF_TO_FLOAT(pointer)  (*(float*)(pointer))
#define DEF_TO_FLOAT_STEP(pointer, step) (*((float*)(pointer) + step))
    
    assert(uniform.type != Uniform::Type::UNKNOWN);
    
    GLsizei count = static_cast<GLsizei>(uniform.count);
    
    switch (uniform.type)
    {
        case Uniform::Type::INT:
            GL_CHECK(glUniform1i(location, DEF_TO_INT(uniform.value)));
            break;
        case Uniform::Type::INT2:
            GL_CHECK(glUniform2i(location, DEF_TO_INT(uniform.value), DEF_TO_INT_STEP(uniform.value, 1)));
            break;
        case Uniform::Type::INT3:
            GL_CHECK(glUniform3i(location,
                                 DEF_TO_INT(uniform.value),
                                 DEF_TO_INT_STEP(uniform.value, 1),
                                 DEF_TO_INT_STEP(uniform.value, 2)));
            break;
        case Uniform::Type::INT4:
            GL_CHECK(glUniform4i(location,
                                 DEF_TO_INT(uniform.value),
                                 DEF_TO_INT_STEP(uniform.value, 1),
                                 DEF_TO_INT_STEP(uniform.value, 2),
                                 DEF_TO_INT_STEP(uniform.value, 3)));
            break;
        case Uniform::Type::INT_ARRAY:
            GL_CHECK(glUniform1iv(location, count, (GLint*)uniform.value));
            break;
        case Uniform::Type::INT2_ARRAY:
            GL_CHECK(glUniform2iv(location, count, (GLint*)uniform.value));
            break;
        case Uniform::Type::INT3_ARRAY:
            GL_CHECK(glUniform3iv(location, count, (GLint*)uniform.value));
            break;
        case Uniform::Type::INT4_ARRAY:
            GL_CHECK(glUniform4iv(location, count, (GLint*)uniform.value));
            break;
        case Uniform::Type::FLOAT:
            GL_CHECK(glUniform1f(location, DEF_TO_FLOAT(uniform.value)));
            break;
        case Uniform::Type::FLOAT2:
            GL_CHECK(glUniform2f(location, DEF_TO_FLOAT(uniform.value), DEF_TO_FLOAT_STEP(uniform.value, 1)));
            break;
        case Uniform::Type::FLOAT3:
            GL_CHECK(glUniform3f(location,
                                 DEF_TO_FLOAT(uniform.value),
                                 DEF_TO_FLOAT_STEP(uniform.value, 1),
                                 DEF_TO_FLOAT_STEP(uniform.value, 2)));
            break;
        case Uniform::Type::FLOAT4:
            GL_CHECK(glUniform4f(location,
                                 DEF_TO_FLOAT(uniform.value),
                                 DEF_TO_FLOAT_STEP(uniform.value, 1),
                                 DEF_TO_FLOAT_STEP(uniform.value, 2),
                                 DEF_TO_FLOAT_STEP(uniform.value, 3)));
            break;
        case Uniform::Type::FLOAT_ARRAY:
            GL_CHECK(glUniform1fv(location, count, (GLfloat*)uniform.value));
            break;
        case Uniform::Type::FLOAT2_ARRAY:
            GL_CHECK(glUniform2fv(location, count, (GLfloat*)uniform.value));
            break;
        case Uniform::Type::FLOAT3_ARRAY:
            GL_CHECK(glUniform3fv(location, count, (GLfloat*)uniform.value));
            break;
        case Uniform::Type::FLOAT4_ARRAY:
            GL_CHECK(glUniform4fv(location, count, (GLfloat*)uniform.value));
            break;
        case Uniform::Type::MAT2:
        case Uniform::Type::MAT2_ARRAY:
            GL_CHECK(glUniformMatrix2fv(location,
                                        count,
                                        false,
                                        (GLfloat*)uniform.value));
        case Uniform::Type::MAT3:
        case Uniform::Type::MAT3_ARRAY:
            GL_CHECK(glUniformMatrix3fv(location,
                                        count,
                                        false,
                                        (GLfloat*)uniform.value));
            break;
        case Uniform::Type::MAT4:
        case Uniform::Type::MAT4_ARRAY:
            GL_CHECK(glUniformMatrix4fv(location,
                                        count,
                                        false,
                                        (GLfloat*)uniform.value));
            break;
        default:
            // error log
            break;
    }
}

//
// Uniform
//
DeviceGraphics::Uniform::Uniform()
: dirty(true)
, value(nullptr)
, type(Type::UNKNOWN)
, count(0)
{}

DeviceGraphics::Uniform::Uniform(const void* v, Type type, size_t bytes)
: type(type)
, value(nullptr)
, count(1)
{
    setValue(v, bytes);
}

DeviceGraphics::Uniform::Uniform(const void* v, Type type, size_t bytes, size_t count)
: type(type)
, value(nullptr)
, count(count)
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
    count = h.count;
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
    count = h.count;
    
    value = h.value;
    h.value = nullptr;
    
    return *this;
}

void DeviceGraphics::Uniform::setValue(const void* v, size_t bytes)
{
    if (value)
        free(value);
    value = malloc(bytes);
    memcpy(value, v, bytes);
}

GFX_END
