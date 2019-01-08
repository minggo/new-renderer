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

#include "backend/Backend.h"
#include "math/Mat4.h"
#include "../TestBase.h"

class PostProcessBackend : public TestBaseI
{
public:
    DEFINE_CREATE_METHOD(PostProcessBackend);
    PostProcessBackend();
    ~PostProcessBackend();
    virtual void tick(float dt) override;
    
private:
    cocos2d::backend::CommandBuffer* _commandBuffer = nullptr;
    cocos2d::backend::RenderPassDescriptor _renderPassDescriptorBunny1;
    cocos2d::backend::RenderPassDescriptor _renderPassDescriptorBunny2;
    cocos2d::backend::RenderPassDescriptor _renderPassDescriptorBg;
    cocos2d::backend::Texture* _colorTexture = nullptr;
    cocos2d::backend::Texture* _depthTexture = nullptr;
    cocos2d::backend::Program* _programBigTriangle = nullptr;
    
    
    float _t;
    
    cocos2d::Mat4 _view;
    cocos2d::Mat4 _model;
    cocos2d::Mat4 _projection;
    cocos2d::Vec3 _eye;
    cocos2d::Vec3 _center;
    cocos2d::Vec3 _up;
};
