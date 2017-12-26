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

#ifndef GFX_BEGIN
#define GFX_BEGIN namespace cocos2d { namespace gfx {
#endif // GFX_BEGIN

#ifndef GFX_END
#define GFX_END }}
#endif // GFX_END

//#ifndef DISALLOW_COPY_ASSIGN_AND_MOVE
    #define CC_DISALLOW_COPY_ASSIGN_AND_MOVE(type) \
        type(const type&) = delete; \
        type& operator =(const type&) = delete; \
        type(type &&) = delete; \
        type& operator =(const type &&) = delete;
//#endif // DISALLOW_COPY_ASSIGN_AND_MOVE

#define CC_UINT    unsigned int

#define GFX_LOGD printf
#define GFX_LOGI printf
#define GFX_LOGW printf
#define GFX_LOGE printf

#define GFX_DEBUG 1 // TODO: remove this

#define GFX_SAFE_RELEASE(p) do { if((p) != nullptr) (p)->release(); } while(false)
#define GFX_SAFE_RETAIN(p) do { if((p) != nullptr) (p)->retain(); } while(false)

#define GFX_DEFINE_CREATE_METHOD_0(clsName, initMethod) \
static clsName* create() \
{ \
    clsName* ret = new (std::nothrow) clsName(); \
    if (ret && ret->initMethod()) \
    { \
        ret->autorelease(); \
        return ret; \
    } \
    delete ret; \
    return nullptr; \
}

#define GFX_DEFINE_CREATE_METHOD_1(clsName, initMethod, arg0Type) \
static clsName* create(arg0Type arg0) \
{ \
    clsName* ret = new (std::nothrow) clsName(); \
    if (ret && ret->initMethod(arg0)) \
    { \
        ret->autorelease(); \
        return ret; \
    } \
    delete ret; \
    return nullptr; \
}

#define GFX_DEFINE_CREATE_METHOD_2(clsName, initMethod, arg0Type, arg1Type) \
static clsName* create(arg0Type arg0, arg1Type arg1) \
{ \
    clsName* ret = new (std::nothrow) clsName(); \
    if (ret && ret->initMethod(arg0, arg1)) \
    { \
        ret->autorelease(); \
        return ret; \
    } \
    delete ret; \
    return nullptr; \
}

#define GFX_DEFINE_CREATE_METHOD_3(clsName, initMethod, arg0Type, arg1Type, arg2Type) \
static clsName* create(arg0Type arg0, arg1Type arg1, arg2Type arg2) \
{ \
    clsName* ret = new (std::nothrow) clsName(); \
    if (ret && ret->initMethod(arg0, arg1, arg2)) \
    { \
        ret->autorelease(); \
        return ret; \
    } \
    delete ret; \
    return nullptr; \
}

#define GFX_DEFINE_CREATE_METHOD_4(clsName, initMethod, arg0Type, arg1Type, arg2Type, arg3Type) \
static clsName* create(arg0Type arg0, arg1Type arg1, arg2Type arg2, arg3Type arg3) \
{ \
    clsName* ret = new (std::nothrow) clsName(); \
    if (ret && ret->initMethod(arg0, arg1, arg2, arg3)) \
    { \
        ret->autorelease(); \
        return ret; \
    } \
    delete ret; \
    return nullptr; \
}

#define GFX_DEFINE_CREATE_METHOD_5(clsName, initMethod, arg0Type, arg1Type, arg2Type, arg3Type, arg4Type) \
static clsName* create(arg0Type arg0, arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4) \
{ \
    clsName* ret = new (std::nothrow) clsName(); \
    if (ret && ret->initMethod(arg0, arg1, arg2, arg3, arg4)) \
    { \
        ret->autorelease(); \
        return ret; \
    } \
    delete ret; \
    return nullptr; \
}

#define GFX_DEFINE_CREATE_METHOD_6(clsName, initMethod, arg0Type, arg1Type, arg2Type, arg3Type, arg4Type, arg5Type) \
static clsName* create(arg0Type arg0, arg1Type arg1, arg2Type arg2, arg3Type arg3, arg4Type arg4, arg5Type arg5) \
{ \
    clsName* ret = new (std::nothrow) clsName(); \
    if (ret && ret->initMethod(arg0, arg1, arg2, arg3, arg4, arg5)) \
    { \
        ret->autorelease(); \
        return ret; \
    } \
    delete ret; \
    return nullptr; \
}
