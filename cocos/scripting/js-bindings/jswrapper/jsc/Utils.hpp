/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.

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

#include "../config.hpp"

#if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_JSC

#include "Base.h"

#include "../Value.hpp"

namespace se {
    
    namespace internal {

        struct PrivateData
        {
            void* data;
            JSObjectFinalizeCallback finalizeCb;
        };
        
        void setContext(JSContextRef cx);

        bool defineProperty(Object* obj, const char* name, JSObjectCallAsFunctionCallback jsGetter, JSObjectCallAsFunctionCallback jsSetter);

        void jsToSeArgs(JSContextRef cx, unsigned short argc, const JSValueRef* argv, ValueArray* outArr);
        void seToJsArgs(JSContextRef cx, const ValueArray& args, JSValueRef* outArr);
        void jsToSeValue(JSContextRef cx, JSValueRef jsval, Value* v);
        void seToJsValue(JSContextRef cx, const Value& v, JSValueRef* jsval);

        void forceConvertJsValueToStdString(JSContextRef cx, JSValueRef jsval, std::string* ret);
        void jsStringToStdString(JSContextRef cx, JSStringRef jsStr, std::string* ret);

        bool hasPrivate(JSObjectRef obj);
        void setPrivate(JSObjectRef obj, void* data, JSObjectFinalizeCallback finalizeCb);
        void* getPrivate(JSObjectRef obj);
        void clearPrivate(JSObjectRef obj);

    } // namespace internal {
} // namespace se {

#endif // #if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_JSC
