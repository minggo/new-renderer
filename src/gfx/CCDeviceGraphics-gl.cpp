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
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>

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
        //TODO
    }
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


GFX_END
