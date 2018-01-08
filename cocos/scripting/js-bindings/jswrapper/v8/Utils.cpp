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
#include "Utils.hpp"

#if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_V8

#include "Object.hpp"
#include "Class.hpp"
#include "ScriptEngine.hpp"

namespace se {

    namespace internal {

        void jsToSeArgs(const v8::FunctionCallbackInfo<v8::Value>& v8args, ValueArray* outArr)
        {
            assert(outArr != nullptr);
            v8::Isolate* isolate = v8args.GetIsolate();
            for (int i = 0; i < v8args.Length(); i++)
            {
                Value v;
                jsToSeValue(isolate, v8args[i], &v);
                outArr->push_back(v);
            }
        }

        void seToJsArgs(v8::Isolate* isolate, const ValueArray& args, std::vector<v8::Local<v8::Value>>* outArr)
        {
            assert(outArr != nullptr);
            for (const auto& data : args)
            {
                v8::Local<v8::Value> jsval;
                seToJsValue(isolate, data, &jsval);
                outArr->push_back(jsval);
            }
        }

        void seToJsValue(v8::Isolate* isolate, const Value& v, v8::Local<v8::Value>* outJsVal)
        {
            assert(outJsVal != nullptr);
            switch (v.getType())
            {
                case Value::Type::Number:
                    *outJsVal = v8::Number::New(isolate, v.toNumber());
                    break;
                case Value::Type::String:
                {
                    v8::MaybeLocal<v8::String> str = v8::String::NewFromUtf8(isolate, v.toString().c_str(), v8::NewStringType::kNormal);
                    if (!str.IsEmpty())
                        *outJsVal = str.ToLocalChecked();
                    else
                        outJsVal->Clear();
                }
                    break;
                case Value::Type::Boolean:
                    *outJsVal = v8::Boolean::New(isolate, v.toBoolean());
                    break;
                case Value::Type::Object:
                    *outJsVal = v.toObject()->_getJSObject();
                    break;
                case Value::Type::Null:
                    *outJsVal = v8::Null(isolate);
                    break;
                case Value::Type::Undefined:
                    *outJsVal = v8::Undefined(isolate);
                    break;

                default:
                    assert(false);
                    break;
            }
        }

        void jsToSeValue(v8::Isolate* isolate, v8::Local<v8::Value> jsval, Value* v)
        {
            assert(v != nullptr);
            v8::HandleScope handle_scope(isolate);

            if (jsval->IsUndefined()) {
                v->setUndefined();
            } else if (jsval->IsNull()) {
                v->setNull();
            } else if (jsval->IsNumber()) {
                v8::MaybeLocal<v8::Number> jsNumber = jsval->ToNumber(isolate->GetCurrentContext());
                if (!jsNumber.IsEmpty())
                    v->setNumber(jsNumber.ToLocalChecked()->Value());
                else
                    v->setUndefined();
            } else if (jsval->IsString()) {
                v8::String::Utf8Value utf8(jsval);
                v->setString(std::string(*utf8));
            } else if (jsval->IsBoolean()) {
                v8::MaybeLocal<v8::Boolean> jsBoolean = jsval->ToBoolean(isolate->GetCurrentContext());
                if (!jsBoolean.IsEmpty())
                    v->setBoolean(jsBoolean.ToLocalChecked()->Value());
                else
                    v->setUndefined();
            } else if (jsval->IsObject()) {
                v8::MaybeLocal<v8::Object> jsObj = jsval->ToObject(isolate->GetCurrentContext());
                if (!jsObj.IsEmpty())
                {
                    void* nativePtr = internal::getPrivate(isolate, jsObj.ToLocalChecked());
                    Object* obj = nullptr;
                    if (nativePtr != nullptr)
                    {
                        obj = Object::getObjectWithPtr(nativePtr);
                    }

                    if (obj == nullptr)
                    {
                        obj = Object::_createJSObject(nullptr, jsObj.ToLocalChecked());
                    }
                    v->setObject(obj, true);
                    obj->decRef();
                }
                else
                {
                    v->setUndefined();
                }
            }
        }

        template<typename T>
        void _setReturnValue(const Value& data, const T& argv)
        {
            if (data.getType() == Value::Type::Undefined) {
                argv.GetReturnValue().Set(v8::Undefined(argv.GetIsolate()));
            } else if (data.getType() == Value::Type::Null) {
                argv.GetReturnValue().Set(v8::Null(argv.GetIsolate()));
            } else if (data.getType() == Value::Type::Number) {
                argv.GetReturnValue().Set(v8::Number::New(argv.GetIsolate(), data.toNumber()));
            } else if (data.getType() == Value::Type::String) {
                v8::MaybeLocal<v8::String> value = v8::String::NewFromUtf8(argv.GetIsolate(), data.toString().c_str(), v8::NewStringType::kNormal);
                assert(!value.IsEmpty());
                argv.GetReturnValue().Set(value.ToLocalChecked());
            } else if (data.getType() == Value::Type::Boolean) {
                argv.GetReturnValue().Set(v8::Boolean::New(argv.GetIsolate(), data.toBoolean()));
            } else if (data.getType() == Value::Type::Object) {
                argv.GetReturnValue().Set(data.toObject()->_getJSObject());
            }
        }

        void setReturnValue(const Value& data, const v8::FunctionCallbackInfo<v8::Value>& argv)
        {
            _setReturnValue(data, argv);
        }

        void setReturnValue(const Value& data, const v8::PropertyCallbackInfo<v8::Value>& argv)
        {
            _setReturnValue(data, argv);
        }

        const char* KEY_PRIVATE_DATA = "__cc_private_data";

        bool hasPrivate(v8::Isolate* isolate, v8::Local<v8::Value> value)
        {
            v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(value);
            int c =  obj->InternalFieldCount();
            if (c > 0)
                return true;

            // Pure JS subclass object doesn't have a internal field
            v8::MaybeLocal<v8::String> key = v8::String::NewFromUtf8(isolate, KEY_PRIVATE_DATA, v8::NewStringType::kNormal);
            if (key.IsEmpty())
                return false;

            v8::Maybe<bool> ret = obj->Has(isolate->GetCurrentContext(), key.ToLocalChecked());
            return ret.IsJust() && ret.FromJust();
        }

        void setPrivate(v8::Isolate* isolate, ObjectWrap& wrap, void* data, PrivateData** outInternalData)
        {
            v8::Local<v8::Object> obj = wrap.handle(isolate);
            int c =  obj->InternalFieldCount();
            if (c > 0)
            {
                wrap.wrap(data);
//                SE_LOGD("setPrivate1: %p\n", data);
                if (outInternalData != nullptr)
                    *outInternalData = nullptr;
            }
            else
            {
                Object* privateObj = Object::createObjectWithClass(__jsb_CCPrivateData_class);
                PrivateData* privateData = (PrivateData*)malloc(sizeof(PrivateData));
                privateData->data = data;
                privateData->seObj = privateObj;

                privateObj->_getWrap().setFinalizeCallback(__jsb_CCPrivateData_class->_getFinalizeFunction());
                privateObj->_getWrap().wrap(privateData);

                v8::MaybeLocal<v8::String> key = v8::String::NewFromUtf8(isolate, KEY_PRIVATE_DATA, v8::NewStringType::kNormal);
                assert(!key.IsEmpty());
                v8::Maybe<bool> ret = obj->Set(isolate->GetCurrentContext(), key.ToLocalChecked(), privateObj->_getJSObject());
                assert(!ret.IsNothing());
//                SE_LOGD("setPrivate: native data: %p\n", privateData);
//                privateObj->decRef(); // NOTE: it's released in ScriptEngine::privateDataFinalize

                if (outInternalData != nullptr)
                    *outInternalData = privateData;
            }
        }

        void* getPrivate(v8::Isolate* isolate, v8::Local<v8::Value> value)
        {
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            v8::MaybeLocal<v8::Object> obj = value->ToObject(context);
            if (obj.IsEmpty())
                return nullptr;

            v8::Local<v8::Object> objChecked = obj.ToLocalChecked();
            int c =  objChecked->InternalFieldCount();
            if (c > 0)
            {
                void* nativeObj = ObjectWrap::unwrap(objChecked);
//                SE_LOGD("getPrivate1: %p\n", nativeObj);
                return nativeObj;
            }

            // Pure JS subclass object doesn't have a internal field
            v8::MaybeLocal<v8::String> key = v8::String::NewFromUtf8(isolate, KEY_PRIVATE_DATA, v8::NewStringType::kNormal);
            if (key.IsEmpty())
                return nullptr;

            v8::Local<v8::String> keyChecked = key.ToLocalChecked();
            v8::Maybe<bool> mbHas = objChecked->Has(context, keyChecked);
            if (mbHas.IsNothing() || !mbHas.FromJust())
                return nullptr;

            v8::MaybeLocal<v8::Value> mbVal = objChecked->Get(context, keyChecked);
            if (mbVal.IsEmpty())
                return nullptr;

            v8::MaybeLocal<v8::Object> privateObj = mbVal.ToLocalChecked()->ToObject(context);
            if (privateObj.IsEmpty())
                return nullptr;
            PrivateData* privateData =  (PrivateData*)ObjectWrap::unwrap(privateObj.ToLocalChecked());
//                SE_LOGD("getPrivate: native data: %p\n", privateData);
            return privateData->data;
        }

        void clearPrivate(v8::Isolate* isolate, ObjectWrap& wrap)
        {
            v8::Local<v8::Object> obj = wrap.handle(isolate);
            int c =  obj->InternalFieldCount();
            if (c > 0)
            {
                wrap.wrap(nullptr);
            }
            else
            {
                v8::Local<v8::Context> context = isolate->GetCurrentContext();
                // Pure JS subclass object doesn't have a internal field
                v8::MaybeLocal<v8::String> key = v8::String::NewFromUtf8(isolate, KEY_PRIVATE_DATA, v8::NewStringType::kNormal);
                if (key.IsEmpty())
                    return;

                v8::Local<v8::String> keyChecked = key.ToLocalChecked();
                v8::Maybe<bool> mbHas = obj->Has(context, keyChecked);
                if (mbHas.IsNothing() || !mbHas.FromJust())
                    return;

                v8::MaybeLocal<v8::Value> mbVal = obj->Get(context, keyChecked);
                if (mbVal.IsEmpty())
                    return;

                v8::MaybeLocal<v8::Object> privateObj = mbVal.ToLocalChecked()->ToObject(context);
                if (privateObj.IsEmpty())
                    return;

                PrivateData* privateData =  (PrivateData*)ObjectWrap::unwrap(privateObj.ToLocalChecked());
                free(privateData);
                v8::Maybe<bool> ok = obj->Delete(context, keyChecked);
                if (ok.IsNothing())
                    return;

                assert(ok.FromJust());
            }
        }

    } // namespace internal {
} // namespace se {

#endif // #if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_V8
