/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

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

#include "Camera.h"
#include "gfx/CCFrameBuffer.h"

GFX_BEGIN

namespace
{
    Mat4 g_tempMatProj;
    Mat4 g_tempMatView;
    Mat4 g_tempMatViewProj;
    Mat4 g_tempMatInvViewProj;
    Vec3 g_tempVec3;
}

Camera::Camera()
{}

Camera::~Camera()
{
    GFX_SAFE_RELEASE(_framebuffer);
}

void Camera::setFrameBuffer(FrameBuffer* framebuffer)
{
    GFX_SAFE_RELEASE(_framebuffer);
    _framebuffer = framebuffer;
    GFX_SAFE_RETAIN(_framebuffer);
}

void Camera::extractView(View& out, int width, int height) const
{
    // rect
    out.rect.set(_rect.x * width,
                 _rect.y * height,
                 _rect.w * width,
                 _rect.h * height);
    
    // clear options
    out.color = _color;
    out.depth = _depth;
    out.stencil = _stencil;
    out.clearFlags = _clearFlags;
    
    // stage & framebuffer
    out.stages = _stages;
    out.frameBuffer = _framebuffer;
    
    // TODO: view matrix
    
    // projecton matrix
    float aspect = (float)width / height;
    if (ProjectionType::PERSPECTIVE == _projection)
        Mat4::createPerspective(_fov, aspect, _near, _far, &out.matProj);
    else
    {
        float x = _orthoHeight * aspect;
        float y = _orthoHeight;
        Mat4::createOrthographic(-x, x, -y, y, &out.matProj);
    }
    
    // view projection
    Mat4::multiply(out.matProj, out.matView, &out.matViewProj);
    out.matInvViewPorj = out.matViewProj.getInversed();
}

Vec3& Camera::screenToWorld(Vec3& out, const Vec3& screenPos, int width, int height) const
{
    float aspect = (float)width / height;
    float cx = _rect.x * width;
    float cy = _rect.y * height;
    float cw = _rect.w * width;
    float ch = _rect.h * height;
    
    // TODO: view matrix
    
    // projection matrix
    if (ProjectionType::PERSPECTIVE == _projection)
        Mat4::createPerspective(_fov, aspect, _near, _far, &g_tempMatProj);
    else
    {
        float x = _orthoHeight * aspect;
        float y = _orthoHeight;
        Mat4::createOrthographic(-x, x, -y, y, &g_tempMatProj);
    }
    
    // view projection
    Mat4::multiply(g_tempMatProj, g_tempMatView, &g_tempMatViewProj);
    
    // invert view projection
    g_tempMatInvViewProj = g_tempMatViewProj.getInversed();
    
    if (ProjectionType::PERSPECTIVE == _projection)
    {
        // Caculate screen pos in far clip plane.
        out.set((screenPos.x - cx) * 2.0f / cw - 1.0f,
                (screenPos.y - cy) * 2.0f / ch - 1.0f,
                1.0f);
        
        // Transform to world position.
        g_tempMatInvViewProj.transformPoint(&out);
        
        // TODO: get world position of the camera
        g_tempVec3.lerp(out, screenPos.z / _far);
        out = g_tempVec3;
    }
    else
    {
        float range = _far - _near;
        out.set((screenPos.x - cx) * 2.0f / cw - 1.0f,
                (screenPos.y - cy) * 2.0f / ch - 1.0f,
                (_far - screenPos.z) / range * 2.0f - 1.0f);
        
        // Transform to world position.
        g_tempMatInvViewProj.transformPoint(&out);
    }
    
    return out;
}

Vec3& Camera::worldToScreen(Vec3& out, const Vec3& worldPos, int width, int height) const
{
    float aspect = (float)width / height;
    float cx = _rect.x * width;
    float cy = _rect.y * height;
    float cw = _rect.w * width;
    float ch = _rect.h * height;
    
    // projection matrix
    if (ProjectionType::PERSPECTIVE == _projection)
        Mat4::createPerspective(_fov, aspect, _near, _far, &g_tempMatProj);
    else
    {
        float x = _orthoHeight * aspect;
        float y = _orthoHeight;
        Mat4::createOrthographic(-x, x, -y, y, &g_tempMatProj);
    }
    
    // TODO: view matrix
    
    // view projection
    Mat4::multiply(g_tempMatProj, g_tempMatView, &g_tempMatViewProj);
    
    // caculate w
    float w = worldPos.x * g_tempMatViewProj.m[3] +
              worldPos.y * g_tempMatViewProj.m[7] +
              worldPos.z * g_tempMatViewProj.m[11] +
              g_tempMatViewProj.m[15];
    
    g_tempMatViewProj.transformPoint(worldPos, &out);
    out.x = cx + (out.x / w + 1) * 0.5f * cw;
    out.y = cy + (out.y / w + 1) * 0.5f * ch;
    
    return out;
}

GFX_END
