//
//  jsb_gfx_manual.cpp
//  Test
//
//  Created by James Chen on 1/8/18.
//  Copyright © 2018 cocos. All rights reserved.
//

#include "jsb_gfx_manual.hpp"
#include "cocos/scripting/js-bindings/auto/jsb_gfx_auto.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_conversions.hpp"
#include "CCGFX.h"

using namespace cocos2d;
using namespace cocos2d::gfx;

static bool js_gfx_DeviceGraphics_clear(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_clear : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        uint8_t flags = 0;
        Color4F color(Color4F::BLACK);
        double depth = 1.0;
        int32_t stencil = 0;

        se::Object* arg1 = args[0].toObject();

        se::Value colorVal, depthVal, stencilVal;
        if (arg1->getProperty("color", &colorVal))
        {
            flags |= gfx::ClearFlag::COLOR;

            if (colorVal.isObject() && colorVal.toObject()->isArray())
            {
                se::Object* colorObj = colorVal.toObject();
                uint32_t length = 0;
                if (colorObj->getArrayLength(&length) && length == 4)
                {
                    se::Value tmp;
                    if (colorObj->getArrayElement(0, &tmp) && tmp.isNumber())
                    {
                        color.r = tmp.toFloat();
                    }
                    if (colorObj->getArrayElement(1, &tmp) && tmp.isNumber())
                    {
                        color.g = tmp.toFloat();
                    }
                    if (colorObj->getArrayElement(2, &tmp) && tmp.isNumber())
                    {
                        color.b = tmp.toFloat();
                    }
                    if (colorObj->getArrayElement(3, &tmp) && tmp.isNumber())
                    {
                        color.a = tmp.toFloat();
                    }
                }
            }
            else
            {
                SE_LOGE("Invalid clear color flag!\n");
            }
        }

        if (arg1->getProperty("depth", &depthVal))
        {
            flags |= gfx::ClearFlag::DEPTH;

            if (depthVal.isNumber())
            {
                depth = depthVal.toNumber();
            }
        }

        if (arg1->getProperty("stencil", &stencilVal))
        {
            flags |= gfx::ClearFlag::STENCIL;

            if (stencilVal.isNumber())
            {
                stencil = stencilVal.toInt32();
            }
        }

        cobj->clear(flags, &color, depth, stencil);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_clear)

static bool js_gfx_DeviceGraphics_setUniform(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setUniform : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        std::string name;
        ok = seval_to_std_string(args[0], &name);
        SE_PRECONDITION2(ok, false, "Convert uniform name failed!");

        se::Value arg1 = args[1];
        if (arg1.isObject())
        {
            se::Object* value = arg1.toObject();
            if (value->isTypedArray())
            {
                uint8_t* data = nullptr;
                size_t bytes = 0;
                if (value->getTypedArrayData(&data, &bytes))
                    cobj->setUniform(name, data, bytes);
            }
            else
            {
                assert(false);
            }
        }
        else if (arg1.isNumber())
        {
            double number = arg1.toNumber();
            double remainder = fmod(number, 1.0);
            if (std::abs(remainder) > 0)
            {
                float f = (float)number;
                cobj->setUniformf(name, f);
            }
            else
            {
                int integer = (int)number;
                cobj->setUniformi(name, integer);
            }
        }
        else if (arg1.isBoolean())
        {
            int v = arg1.toBoolean() ? 1 : 0;
            cobj->setUniformi(name, v);
        }
        else
        {
            assert(false);
        }

        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setUniform)

static bool js_gfx_VertexBuffer_init(se::State& s)
{
    cocos2d::gfx::VertexBuffer* cobj = (cocos2d::gfx::VertexBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_VertexBuffer_init : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 5) {
        cocos2d::gfx::DeviceGraphics* device;
        ok &= seval_to_native_ptr(args[0], &device);

        std::vector<VertexFormat::Info> formatInfos;

        Usage usage = (Usage) args[2].toUint16();
        uint8_t* data = nullptr;
        size_t dataByteLength = 0;
        uint32_t numVertices = 0;
        se::Object* vertexFmt = args[1].toObject();
        se::Value elementVal;
        if (vertexFmt->getProperty("_elements", &elementVal) && elementVal.isObject() && elementVal.toObject()->isArray())
        {
            se::Object* fmtArr = elementVal.toObject();
            uint32_t length = 0;
            if (fmtArr->getArrayLength(&length) && length > 0)
            {
                se::Value tmp;
                se::Value nameVal;
                se::Value typeVal;
                se::Value numVal;
                for (uint32_t i = 0; i < length; ++i)
                {
                    if (fmtArr->getArrayElement(i, &tmp) && tmp.isObject())
                    {
                        tmp.toObject()->getProperty("name", &nameVal);
                        tmp.toObject()->getProperty("type", &typeVal);
                        tmp.toObject()->getProperty("num", &numVal);

                        formatInfos.push_back({ nameVal.toString(), (AttribType)typeVal.toUint16(), numVal.toUint32() });
                    }
                }
            }
        }

        se::Object* typedArr = args[3].toObject();
        assert(typedArr->isTypedArray());
        ok = typedArr->getTypedArrayData(&data, &dataByteLength);
        assert(ok);

        ok = seval_to_uint32(args[4], &numVertices);
        assert(ok);
        
        VertexFormat format(formatInfos);
        cobj->init(device, format, usage, data, dataByteLength, numVertices);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 5);
    return false;
}
SE_BIND_FUNC(js_gfx_VertexBuffer_init)

static bool js_gfx_IndexBuffer_init(se::State& s)
{
    cocos2d::gfx::IndexBuffer* cobj = (cocos2d::gfx::IndexBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_IndexBuffer_init : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 5) {
        cocos2d::gfx::DeviceGraphics* device;
        ok &= seval_to_native_ptr(args[0], &device);

        IndexFormat format = (IndexFormat)args[1].toUint16();
        Usage usage = (Usage) args[2].toUint16();

        uint8_t* data = nullptr;
        size_t dataByteLength = 0;
        uint32_t numIndices = 0;
        se::Object* typedArr = args[3].toObject();
        assert(typedArr->isTypedArray());
        ok = typedArr->getTypedArrayData(&data, &dataByteLength);
        assert(ok);

        ok = seval_to_uint32(args[4], &numIndices);
        assert(ok);

        cobj->init(device, format, usage, data, dataByteLength, numIndices);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 5);
    return false;
}
SE_BIND_FUNC(js_gfx_IndexBuffer_init)

static bool js_cocos2dx_FileUtils_getStringFromFile(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_FileUtils_getStringFromFile : Error processing arguments");
        std::string result = FileUtils::getInstance()->getStringFromFile(arg0);
        ok &= std_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_FileUtils_getStringFromFile : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_FileUtils_getStringFromFile)

static bool js_cocos2dx_FileUtils_getDataFromFile(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_cocos2dx_FileUtils_getDataFromFile : Error processing arguments");
        cocos2d::Data result = FileUtils::getInstance()->getDataFromFile(arg0);
        ok &= Data_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_cocos2dx_FileUtils_getDataFromFile : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_cocos2dx_FileUtils_getDataFromFile)

bool jsb_register_gfx_manual(se::Object* global)
{
    __jsb_cocos2d_gfx_DeviceGraphics_proto->defineFunction("clear", _SE(js_gfx_DeviceGraphics_clear));
    __jsb_cocos2d_gfx_DeviceGraphics_proto->defineFunction("setUniform", _SE(js_gfx_DeviceGraphics_setUniform));
    __jsb_cocos2d_gfx_VertexBuffer_proto->defineFunction("init", _SE(js_gfx_VertexBuffer_init));
    __jsb_cocos2d_gfx_IndexBuffer_proto->defineFunction("init", _SE(js_gfx_IndexBuffer_init));

    global->defineFunction("getDataFromFile", _SE(js_cocos2dx_FileUtils_getDataFromFile));
    global->defineFunction("getStringFromFile", _SE(js_cocos2dx_FileUtils_getStringFromFile));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
