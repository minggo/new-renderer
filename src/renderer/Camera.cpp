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

#include "Camera.h"

GFX_BEGIN

Camera::Camera()
{}

Camera::~Camera()
{
    GFX_SAFE_RELEASE(_framebuffer);
}

void Camera::setFrameBuffer(FrameBuffer* framebuffer)
{
    _framebuffer = framebuffer;
    GFX_SAFE_RETAIN(_framebuffer);
}

void Camera::extractView(View& out, int width, int height) const
{
    // rect
    out.rect.setRect(_rect.origin.x * width,
                     _rect.origin.y * height,
                     _rect.size.width * width,
                     _rect.size.height * height);
    
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
    float aspect = ((float)width) / height;
    if (ProjectionType::PERSPECTIVE == _projection)
        Mat4::createPerspective(_fov, aspect, _near, _far, &out.matProj);
    else
    {
        float x = _orthoHeight * aspect;
        float y = _orthoHeight;
        Mat4::createOrthographic(-x, -y, _near, _far, &out.matProj);
    }
    
    // view projection
    Mat4::multiply(out.matProj, out.matView, &out.matViewProj);
    
}

void Camera::screenToWorld(Mat4& out, float screenPos, int width, int height) const
{
    
}

void Camera::worldToScreen(Mat4& out, float worldPos, int width, int height) const
{
    
}

GFX_END
