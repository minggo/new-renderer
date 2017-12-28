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

#pragma once

#include "TestBase.h"
#include "gfx/CCGFX.h"

class Bunny : public TestBaseI
{
public:
    DEFINE_CREATE_METHOD(Bunny)
    Bunny();
    ~Bunny();
    virtual void tick(float dt) override;

private:
    cocos2d::gfx::VertexBuffer *_vertexBuffer;
    cocos2d::gfx::IndexBuffer *_indexBuffer;
    cocos2d::gfx::Program *_program;
    cocos2d::gfx::DeviceGraphics *_device;

    cocos2d::Mat4 _model;
    cocos2d::Mat4 _view;
    cocos2d::Mat4 _projection;

    float _time;
};

