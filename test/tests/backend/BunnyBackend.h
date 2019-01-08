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

#include "TestBase.h"
#include "backend/RenderPipeline.h"
#include "backend/Buffer.h"
#include "backend/CommandBuffer.h"
#include "backend/DepthStencilState.h"

#include "math/Mat4.h"

class BunnyBackend : public TestBaseI
{
public:
    DEFINE_CREATE_METHOD(BunnyBackend);
    BunnyBackend();
    ~BunnyBackend();
    virtual void tick(float dt) override;

private:
    cocos2d::backend::Buffer* _vertexBuffer = nullptr;
    cocos2d::backend::Buffer* _indexBuffer = nullptr;
    cocos2d::backend::CommandBuffer* _commandBuffer = nullptr;
    cocos2d::backend::RenderPassDescriptor _renderPassDescriptor;
    cocos2d::backend::RenderPipeline* _renderPipeline = nullptr;

    cocos2d::Mat4 _model;
    cocos2d::Mat4 _view;
    cocos2d::Mat4 _projection;

    float _time = 0.f;
    int _modelLocation = -1;
    int _viewLocation = -1;
    int _projectionLocation = -1;
    int _colorLocation = -1;
};

