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

#if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_V8

#include "Base.h"
#include "../Value.hpp"
#include "ObjectWrap.h"

namespace se {
    
    namespace internal {

        struct PrivateData
        {
            void* data;
            Object* seObj;
        };

        void jsToSeArgs(const v8::FunctionCallbackInfo<v8::Value>& _v8args, ValueArray* outArr);
        void jsToSeValue(v8::Isolate* isolate, v8::Local<v8::Value> jsval, Value* v);
        void seToJsArgs(v8::Isolate* isolate, const ValueArray& args, std::vector<v8::Local<v8::Value>>* outArr);
        void seToJsValue(v8::Isolate* isolate, const Value& v, v8::Local<v8::Value>* outJsVal);

        void setReturnValue(const Value& data, const v8::FunctionCallbackInfo<v8::Value>& argv);
        void setReturnValue(const Value& data, const v8::PropertyCallbackInfo<v8::Value>& argv);

        bool hasPrivate(v8::Isolate* isolate, v8::Local<v8::Value> value);
        void setPrivate(v8::Isolate* isolate, ObjectWrap& wrap, void* data, PrivateData** outInternalData);
        void* getPrivate(v8::Isolate* isolate, v8::Local<v8::Value> value);
        void clearPrivate(v8::Isolate* isolate, ObjectWrap& wrap);

    } // namespace internal {
} // namespace se {

#endif // #if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_V8
