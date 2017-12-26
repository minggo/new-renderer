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

GFX_BEGIN

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
                glDepthFunc(_currentState.depthFunc);
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
        if (currentBuffer)
            currentBuffer->release();
        
        _nextState.vertexBuffers[stream] = buffer;
        if (buffer)
            buffer->retain();
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
    
    if (_nextState.indexBuffer)
        _nextState.indexBuffer->release();
    
    _nextState.indexBuffer = buffer;
    if (buffer)
        buffer->retain();
}

void DeviceGraphics::setProgram(Program *program)
{
    //TODO
}

void DeviceGraphics::setTexture(const std::string& name, Texture* texture, int slot)
{
    //TODO
}

void DeviceGraphics::setTextureArray(const std::string& name, const std::vector<Texture*>& texutres, const std::vector<int>& slots)
{
    //TODO
}

//TODO
// setUniform
void DeviceGraphics::setPrimitiveType(PrimitiveType type)
{
    _nextState.primitiveType = type;
}

void DeviceGraphics::draw(int base, size_t count)
{
    
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
}

DeviceGraphics::~DeviceGraphics()
{
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

void DeviceGraphics::restoreIndexBuffer()
{

}

GFX_END
