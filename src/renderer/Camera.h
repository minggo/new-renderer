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

#pragma once

#include <vector>
#include <string>
#include "base/ccTypes.h"
#include "math/Vec3.h"
#include "math/Mat4.h"
#include "../macro.h"
#include "../types.h"
#include "View.h"

GFX_BEGIN

class FrameBuffer;
class INode;

class Camera : public Ref
{
public:
    Camera();
    ~Camera();
    
    ProjectionType getType() const { return _projection; }
    
    inline float getOrthoHeight() const { return _orthoHeight; }
    inline void setOrthoHeight(float value) { _orthoHeight = value; }
    
    inline float getFov() const { return _fov; }
    inline void setFov(float fov) { _fov = fov; }
    
    inline float getNear() const { return _near; }
    inline void setNear(float near) { _near = near; }
    
    inline float getFar() const { return _far; }
    inline void setFar(float far) { _far = far; }
    
    inline void getColor(Color4F& out) const { out = _color; }
    inline void setColor(float r, float g, float b, float a) { _color.set(r, g, b, a); }
    
    inline float getDepth() const { return _depth; }
    inline void setDepth(float depth) { _depth = depth; }
    
    inline int getStencil() const { return _stencil; }
    inline void setStencil(int stencil) { _stencil = stencil; }
    
    inline uint8_t getClearFlags() const { return _clearFlags; }
    inline void setClearFlags(uint8_t flags ) { _clearFlags = flags; }
    
    inline Rect* getRect(Rect& out) const { out = _rect; return &out; }
    inline void setRect(float x, float y, float w, float h) { _rect.set(x, y, w, h); }
    
    inline const std::vector<std::string>& getStages() const { return _stages; }
    inline void setStages(const std::vector<std::string>& stages) { _stages = stages; }
    
    inline FrameBuffer* getFrameBuffer() const { return _framebuffer; }
    void setFrameBuffer(FrameBuffer* framebuffer);
    
    void setWorldMatrix(const Mat4& worldMatrix);
    
    void extractView(View& out, int width, int height) const;
    
    Vec3& screenToWorld(Vec3& out, const Vec3& screenPos, int width, int height) const;
    Vec3& worldToScreen(Vec3& out, const Vec3& worldPos, int width, int height) const;

    inline void setNode(INode* node) { _node = node; }
    inline INode* getNode() const { return _node; }
    
private:
    INode* _node = nullptr;
    ProjectionType _projection = ProjectionType::PERSPECTIVE;
    
    // clear options
    Color4F _color = {0.2f, 0.3f, 0.47f, 1.f};
    float _depth = 1.f;
    int _stencil = 1;
    uint8_t _clearFlags = ClearFlag::COLOR | ClearFlag::DEPTH;
    
    // stage & framebuffer
    std::vector<std::string> _stages;
    FrameBuffer* _framebuffer = nullptr;
    
    // projection properties
    float _near = 0.01f;
    float _far = 1000.0f;
    float _fov = GFX_PI / 4.0f;
    Rect _rect = {0, 0, 1, 1};
    
    // ortho properties
    float _orthoHeight = 10.f;
    
    Mat4 _worldRTInv;
    Vec3 _worldPos;
};

GFX_END
