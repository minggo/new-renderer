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

namespace se {

    class Object;

    /**
     * se::Class represents a definition of how to create a native binding object.
     */
    class Class final
    {
    public:
        /**
         *  @brief Creates a class used for creating relevant native binding objects.
         *  @param[in] className A null-terminated UTF8 string containing the class's name.
         *  @param[in] obj The object that current class proto object attaches to. Should not be nullptr.
         *  @param[in] parentProto The parent proto object that current class inherits from. Passing nullptr means a new class has no parent.
         *  @param[in] ctor A callback to invoke when your constructor is used in a 'new' expression. Pass nullptr to use the default object constructor.
         *  @return A class instance used for creating relevant native binding objects.
         *  @note Don't need to delete the pointer return by this method, it's managed internally.
         */
        static Class* create(const std::string& className, Object* obj, Object* parentProto, JSObjectCallAsConstructorCallback ctor);

        /**
         *  @brief Defines a member function with a callback. Each objects created by class will have this function property.
         *  @param[in] name A null-terminated UTF8 string containing the function name.
         *  @param[in] func A callback to invoke when the property is called as a function.
         *  @return true if succeed, otherwise false.
         */
        bool defineFunction(const char *name, JSObjectCallAsFunctionCallback func);

        /**
         *  @brief Defines a property with accessor callbacks. Each objects created by class will have this property.
         *  @param[in] name A null-terminated UTF8 string containing the property name.
         *  @param[in] getter A callback to invoke when the property is read.
         *  @param[in] setter A callback to invoke when the property is set.
         *  @return true if succeed, otherwise false.
         */
        bool defineProperty(const char *name, JSObjectCallAsFunctionCallback getter, JSObjectCallAsFunctionCallback setter);

        /**
         *  @brief Defines a static function with a callback. Only JavaScript constructor object will have this function.
         *  @param[in] name A null-terminated UTF8 string containing the function name.
         *  @param[in] func A callback to invoke when the constructor's property is called as a function.
         *  @return true if succeed, otherwise false.
         */
        bool defineStaticFunction(const char *name, JSObjectCallAsFunctionCallback func);

        /**
         *  @brief Defines a static property with accessor callbacks. Only JavaScript constructor object will have this property.
         *  @param[in] name A null-terminated UTF8 string containing the property name.
         *  @param[in] getter A callback to invoke when the constructor's property is read.
         *  @param[in] setter A callback to invoke when the constructor's property is set.
         *  @return true if succeed, otherwise false.
         */
        bool defineStaticProperty(const char *name, JSObjectCallAsFunctionCallback getter, JSObjectCallAsFunctionCallback setter);

        /**
         *  @brief Defines the finalize function with a callback.
         *  @param[in] func The callback to invoke when a JavaScript object is garbage collected.
         *  @return true if succeed, otherwise false.
         */
        bool defineFinalizeFunction(JSObjectFinalizeCallback func);

        /**
         *  @brief Installs class to JavaScript VM.
         *  @return true if succeed, otherwise false.
         *  @note After this method, an object could be created by `var foo = new Foo();`.
         */
        bool install();

        /**
         *  @brief Gets the proto object of this class.
         *  @return The proto object of this class.
         *  @note Don't need to be released in user code.
         */
        Object* getProto();

        /**
         *  @brief Gets the class name.
         *  @return The class name.
         */
        const char* getName() const { return _name.c_str(); }

    private:
        Class();
        ~Class();

        bool init(const std::string& clsName, Object* obj, Object* parentProto, JSObjectCallAsConstructorCallback ctor);
        void destroy();

        static JSObjectRef _createJSObjectWithClass(Class* cls);
        
        static void setContext(JSContextRef cx);
        static void cleanup();

        struct JSPropertySpec
        {
            const char* name;
            JSObjectCallAsFunctionCallback getter;
            JSObjectCallAsFunctionCallback setter;
            JSPropertyAttributes attributes;
        };

        std::string _name;
        Object* _parent;
        Object* _proto;
        Object* _parentProto;

        JSObjectCallAsConstructorCallback _ctor;

        JSClassRef _jsCls;
        JSClassDefinition _jsClsDef;

        std::vector<JSStaticFunction> _funcs;
        std::vector<JSStaticFunction> _staticFuncs;
        std::vector<JSPropertySpec> _properties;
        std::vector<JSPropertySpec> _staticProperties;
        JSObjectFinalizeCallback _finalizeOp;

        friend class ScriptEngine;
        friend class Object;
    };

} // namespace se {

#endif // #if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_JSC

