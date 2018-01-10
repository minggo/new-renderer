#include "scripting/js-bindings/auto/jsb_gfx_auto.hpp"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "CCGFX.h"

se::Object* __jsb_cocos2d_gfx_GraphicsHandle_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_GraphicsHandle_class = nullptr;

static bool js_gfx_GraphicsHandle_getHandle(se::State& s)
{
    cocos2d::gfx::GraphicsHandle* cobj = (cocos2d::gfx::GraphicsHandle*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GraphicsHandle_getHandle : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getHandle();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GraphicsHandle_getHandle : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GraphicsHandle_getHandle)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_GraphicsHandle_finalize)

static bool js_gfx_GraphicsHandle_constructor(se::State& s)
{
    cocos2d::gfx::GraphicsHandle* cobj = new (std::nothrow) cocos2d::gfx::GraphicsHandle();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_gfx_GraphicsHandle_constructor, __jsb_cocos2d_gfx_GraphicsHandle_class, js_cocos2d_gfx_GraphicsHandle_finalize)




static bool js_cocos2d_gfx_GraphicsHandle_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::GraphicsHandle)", s.nativeThisObject());
    cocos2d::gfx::GraphicsHandle* cobj = (cocos2d::gfx::GraphicsHandle*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_GraphicsHandle_finalize)

bool js_register_gfx_GraphicsHandle(se::Object* obj)
{
    auto cls = se::Class::create("GraphicsHandle", obj, nullptr, _SE(js_gfx_GraphicsHandle_constructor));

    cls->defineFunction("getHandle", _SE(js_gfx_GraphicsHandle_getHandle));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_GraphicsHandle_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::GraphicsHandle>(cls);

    __jsb_cocos2d_gfx_GraphicsHandle_proto = cls->getProto();
    __jsb_cocos2d_gfx_GraphicsHandle_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_IndexBuffer_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_IndexBuffer_class = nullptr;

static bool js_gfx_IndexBuffer_getBytesPerIndex(se::State& s)
{
    cocos2d::gfx::IndexBuffer* cobj = (cocos2d::gfx::IndexBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_IndexBuffer_getBytesPerIndex : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getBytesPerIndex();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_IndexBuffer_getBytesPerIndex : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_IndexBuffer_getBytesPerIndex)

static bool js_gfx_IndexBuffer_getCount(se::State& s)
{
    cocos2d::gfx::IndexBuffer* cobj = (cocos2d::gfx::IndexBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_IndexBuffer_getCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getCount();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_IndexBuffer_getCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_IndexBuffer_getCount)

static bool js_gfx_IndexBuffer_getFormat(se::State& s)
{
    cocos2d::gfx::IndexBuffer* cobj = (cocos2d::gfx::IndexBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_IndexBuffer_getFormat : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getFormat();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_IndexBuffer_getFormat : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_IndexBuffer_getFormat)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_IndexBuffer_finalize)

static bool js_gfx_IndexBuffer_constructor(se::State& s)
{
    cocos2d::gfx::IndexBuffer* cobj = new (std::nothrow) cocos2d::gfx::IndexBuffer();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_gfx_IndexBuffer_constructor, __jsb_cocos2d_gfx_IndexBuffer_class, js_cocos2d_gfx_IndexBuffer_finalize)



extern se::Object* __jsb_cocos2d_gfx_GraphicsHandle_proto;

static bool js_cocos2d_gfx_IndexBuffer_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::IndexBuffer)", s.nativeThisObject());
    cocos2d::gfx::IndexBuffer* cobj = (cocos2d::gfx::IndexBuffer*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_IndexBuffer_finalize)

bool js_register_gfx_IndexBuffer(se::Object* obj)
{
    auto cls = se::Class::create("IndexBuffer", obj, __jsb_cocos2d_gfx_GraphicsHandle_proto, _SE(js_gfx_IndexBuffer_constructor));

    cls->defineFunction("getBytesPerIndex", _SE(js_gfx_IndexBuffer_getBytesPerIndex));
    cls->defineFunction("getCount", _SE(js_gfx_IndexBuffer_getCount));
    cls->defineFunction("getFormat", _SE(js_gfx_IndexBuffer_getFormat));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_IndexBuffer_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::IndexBuffer>(cls);

    __jsb_cocos2d_gfx_IndexBuffer_proto = cls->getProto();
    __jsb_cocos2d_gfx_IndexBuffer_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_VertexBuffer_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_VertexBuffer_class = nullptr;

static bool js_gfx_VertexBuffer_getCount(se::State& s)
{
    cocos2d::gfx::VertexBuffer* cobj = (cocos2d::gfx::VertexBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_VertexBuffer_getCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getCount();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_VertexBuffer_getCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_VertexBuffer_getCount)

static bool js_gfx_VertexBuffer_getFormat(se::State& s)
{
    cocos2d::gfx::VertexBuffer* cobj = (cocos2d::gfx::VertexBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_VertexBuffer_getFormat : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::gfx::VertexFormat& result = cobj->getFormat();
        ok &= VertexFormat_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_VertexBuffer_getFormat : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_VertexBuffer_getFormat)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_VertexBuffer_finalize)

static bool js_gfx_VertexBuffer_constructor(se::State& s)
{
    cocos2d::gfx::VertexBuffer* cobj = new (std::nothrow) cocos2d::gfx::VertexBuffer();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_gfx_VertexBuffer_constructor, __jsb_cocos2d_gfx_VertexBuffer_class, js_cocos2d_gfx_VertexBuffer_finalize)



extern se::Object* __jsb_cocos2d_gfx_GraphicsHandle_proto;

static bool js_cocos2d_gfx_VertexBuffer_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::VertexBuffer)", s.nativeThisObject());
    cocos2d::gfx::VertexBuffer* cobj = (cocos2d::gfx::VertexBuffer*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_VertexBuffer_finalize)

bool js_register_gfx_VertexBuffer(se::Object* obj)
{
    auto cls = se::Class::create("VertexBuffer", obj, __jsb_cocos2d_gfx_GraphicsHandle_proto, _SE(js_gfx_VertexBuffer_constructor));

    cls->defineFunction("getCount", _SE(js_gfx_VertexBuffer_getCount));
    cls->defineFunction("getFormat", _SE(js_gfx_VertexBuffer_getFormat));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_VertexBuffer_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::VertexBuffer>(cls);

    __jsb_cocos2d_gfx_VertexBuffer_proto = cls->getProto();
    __jsb_cocos2d_gfx_VertexBuffer_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_DeviceGraphics_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_DeviceGraphics_class = nullptr;

static bool js_gfx_DeviceGraphics_setTexture(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setTexture : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        std::string arg0;
        cocos2d::gfx::Texture* arg1 = nullptr;
        int arg2 = 0;
        ok &= seval_to_std_string(args[0], &arg0);
        ok &= seval_to_native_ptr(args[1], &arg1);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (int)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setTexture : Error processing arguments");
        cobj->setTexture(arg0, arg1, arg2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setTexture)

static bool js_gfx_DeviceGraphics_setBlendFuncSeparate(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setBlendFuncSeparate : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        cocos2d::gfx::BlendFactor arg0;
        cocos2d::gfx::BlendFactor arg1;
        cocos2d::gfx::BlendFactor arg2;
        cocos2d::gfx::BlendFactor arg3;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setBlendFuncSeparate : Error processing arguments");
        cobj->setBlendFuncSeparate(arg0, arg1, arg2, arg3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setBlendFuncSeparate)

static bool js_gfx_DeviceGraphics_enableBlend(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_enableBlend : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->enableBlend();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_enableBlend)

static bool js_gfx_DeviceGraphics_setPrimitiveType(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setPrimitiveType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::PrimitiveType arg0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::PrimitiveType)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setPrimitiveType : Error processing arguments");
        cobj->setPrimitiveType(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setPrimitiveType)

static bool js_gfx_DeviceGraphics_setBlendEquationSeparate(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setBlendEquationSeparate : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        cocos2d::gfx::BlendOp arg0;
        cocos2d::gfx::BlendOp arg1;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setBlendEquationSeparate : Error processing arguments");
        cobj->setBlendEquationSeparate(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setBlendEquationSeparate)

static bool js_gfx_DeviceGraphics_setIndexBuffer(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setIndexBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::IndexBuffer* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setIndexBuffer : Error processing arguments");
        cobj->setIndexBuffer(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setIndexBuffer)

static bool js_gfx_DeviceGraphics_setProgram(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setProgram : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Program* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setProgram : Error processing arguments");
        cobj->setProgram(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setProgram)

static bool js_gfx_DeviceGraphics_setFrameBuffer(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setFrameBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        const cocos2d::gfx::FrameBuffer* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setFrameBuffer : Error processing arguments");
        cobj->setFrameBuffer(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setFrameBuffer)

static bool js_gfx_DeviceGraphics_setStencilFunc(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setStencilFunc : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        cocos2d::gfx::ComparisonFunc arg0;
        int arg1 = 0;
        unsigned int arg2 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (int)tmp; } while(false);
        ok &= seval_to_uint32(args[2], (uint32_t*)&arg2);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setStencilFunc : Error processing arguments");
        cobj->setStencilFunc(arg0, arg1, arg2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setStencilFunc)

static bool js_gfx_DeviceGraphics_setBlendColor(se::State& s)
{
    CC_UNUSED bool ok = true;
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2( cobj, false, "js_gfx_DeviceGraphics_setBlendColor : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    do {
        if (argc == 4) {
            uint8_t arg0;
            ok &= seval_to_uint8(args[0], (uint8_t*)&arg0);
            if (!ok) { ok = true; break; }
            uint8_t arg1;
            ok &= seval_to_uint8(args[1], (uint8_t*)&arg1);
            if (!ok) { ok = true; break; }
            uint8_t arg2;
            ok &= seval_to_uint8(args[2], (uint8_t*)&arg2);
            if (!ok) { ok = true; break; }
            uint8_t arg3;
            ok &= seval_to_uint8(args[3], (uint8_t*)&arg3);
            if (!ok) { ok = true; break; }
            cobj->setBlendColor(arg0, arg1, arg2, arg3);
            return true;
        }
    } while(false);

    do {
        if (argc == 1) {
            unsigned int arg0 = 0;
            ok &= seval_to_uint32(args[0], (uint32_t*)&arg0);
            if (!ok) { ok = true; break; }
            cobj->setBlendColor(arg0);
            return true;
        }
    } while(false);

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setBlendColor)

static bool js_gfx_DeviceGraphics_setScissor(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setScissor : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        int arg0 = 0;
        int arg1 = 0;
        int arg2 = 0;
        int arg3 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (int)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (int)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (int)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (int)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setScissor : Error processing arguments");
        cobj->setScissor(arg0, arg1, arg2, arg3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setScissor)

static bool js_gfx_DeviceGraphics_setVertexBuffer(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setVertexBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        int arg0 = 0;
        cocos2d::gfx::VertexBuffer* arg1 = nullptr;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (int)tmp; } while(false);
        ok &= seval_to_native_ptr(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setVertexBuffer : Error processing arguments");
        cobj->setVertexBuffer(arg0, arg1);
        return true;
    }
    if (argc == 3) {
        int arg0 = 0;
        cocos2d::gfx::VertexBuffer* arg1 = nullptr;
        int arg2 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (int)tmp; } while(false);
        ok &= seval_to_native_ptr(args[1], &arg1);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (int)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setVertexBuffer : Error processing arguments");
        cobj->setVertexBuffer(arg0, arg1, arg2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setVertexBuffer)

static bool js_gfx_DeviceGraphics_enableDepthWrite(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_enableDepthWrite : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->enableDepthWrite();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_enableDepthWrite)

static bool js_gfx_DeviceGraphics_setTextureArray(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setTextureArray : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        std::string arg0;
        std::vector<cocos2d::gfx::Texture *> arg1;
        std::vector<int> arg2;
        ok &= seval_to_std_string(args[0], &arg0);
        ok &= seval_to_std_vector_Texture(args[1], &arg1);
        ok &= seval_to_std_vector_int(args[2], &arg2);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setTextureArray : Error processing arguments");
        cobj->setTextureArray(arg0, arg1, arg2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setTextureArray)

static bool js_gfx_DeviceGraphics_setStencilOpBack(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setStencilOpBack : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        cocos2d::gfx::StencilOp arg0;
        cocos2d::gfx::StencilOp arg1;
        cocos2d::gfx::StencilOp arg2;
        unsigned int arg3 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        ok &= seval_to_uint32(args[3], (uint32_t*)&arg3);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setStencilOpBack : Error processing arguments");
        cobj->setStencilOpBack(arg0, arg1, arg2, arg3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setStencilOpBack)

static bool js_gfx_DeviceGraphics_setViewport(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setViewport : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        int arg0 = 0;
        int arg1 = 0;
        int arg2 = 0;
        int arg3 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (int)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (int)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (int)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (int)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setViewport : Error processing arguments");
        cobj->setViewport(arg0, arg1, arg2, arg3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setViewport)

static bool js_gfx_DeviceGraphics_draw(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_draw : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        size_t arg0 = 0;
        int arg1 = 0;
        ok &= seval_to_size(args[0], &arg0);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (int)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_draw : Error processing arguments");
        cobj->draw(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_draw)

static bool js_gfx_DeviceGraphics_setDepthFunc(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setDepthFunc : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::ComparisonFunc arg0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setDepthFunc : Error processing arguments");
        cobj->setDepthFunc(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setDepthFunc)

static bool js_gfx_DeviceGraphics_enableDepthTest(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_enableDepthTest : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->enableDepthTest();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_enableDepthTest)

static bool js_gfx_DeviceGraphics_setBlendEquation(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setBlendEquation : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::BlendOp arg0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setBlendEquation : Error processing arguments");
        cobj->setBlendEquation(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setBlendEquation)

static bool js_gfx_DeviceGraphics_setStencilFuncFront(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setStencilFuncFront : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        cocos2d::gfx::ComparisonFunc arg0;
        int arg1 = 0;
        unsigned int arg2 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (int)tmp; } while(false);
        ok &= seval_to_uint32(args[2], (uint32_t*)&arg2);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setStencilFuncFront : Error processing arguments");
        cobj->setStencilFuncFront(arg0, arg1, arg2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setStencilFuncFront)

static bool js_gfx_DeviceGraphics_setStencilOpFront(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setStencilOpFront : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        cocos2d::gfx::StencilOp arg0;
        cocos2d::gfx::StencilOp arg1;
        cocos2d::gfx::StencilOp arg2;
        unsigned int arg3 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        ok &= seval_to_uint32(args[3], (uint32_t*)&arg3);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setStencilOpFront : Error processing arguments");
        cobj->setStencilOpFront(arg0, arg1, arg2, arg3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setStencilOpFront)

static bool js_gfx_DeviceGraphics_setStencilFuncBack(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setStencilFuncBack : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        cocos2d::gfx::ComparisonFunc arg0;
        int arg1 = 0;
        unsigned int arg2 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (int)tmp; } while(false);
        ok &= seval_to_uint32(args[2], (uint32_t*)&arg2);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setStencilFuncBack : Error processing arguments");
        cobj->setStencilFuncBack(arg0, arg1, arg2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setStencilFuncBack)

static bool js_gfx_DeviceGraphics_setBlendFunc(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setBlendFunc : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        cocos2d::gfx::BlendFactor arg0;
        cocos2d::gfx::BlendFactor arg1;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setBlendFunc)

static bool js_gfx_DeviceGraphics_setCullMode(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setCullMode : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::CullMode arg0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::CullMode)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setCullMode : Error processing arguments");
        cobj->setCullMode(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setCullMode)

static bool js_gfx_DeviceGraphics_supportGLExtension(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_supportGLExtension : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_supportGLExtension : Error processing arguments");
        bool result = cobj->supportGLExtension(arg0);
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_supportGLExtension : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_supportGLExtension)

static bool js_gfx_DeviceGraphics_setStencilOp(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_setStencilOp : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        cocos2d::gfx::StencilOp arg0;
        cocos2d::gfx::StencilOp arg1;
        cocos2d::gfx::StencilOp arg2;
        unsigned int arg3 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        ok &= seval_to_uint32(args[3], (uint32_t*)&arg3);
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_setStencilOp : Error processing arguments");
        cobj->setStencilOp(arg0, arg1, arg2, arg3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_setStencilOp)

static bool js_gfx_DeviceGraphics_enableStencilTest(se::State& s)
{
    cocos2d::gfx::DeviceGraphics* cobj = (cocos2d::gfx::DeviceGraphics*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_DeviceGraphics_enableStencilTest : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->enableStencilTest();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_enableStencilTest)

static bool js_gfx_DeviceGraphics_getInstance(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::gfx::DeviceGraphics* result = cocos2d::gfx::DeviceGraphics::getInstance();
        ok &= native_ptr_to_seval<cocos2d::gfx::DeviceGraphics>((cocos2d::gfx::DeviceGraphics*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_DeviceGraphics_getInstance : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_DeviceGraphics_getInstance)




bool js_register_gfx_DeviceGraphics(se::Object* obj)
{
    auto cls = se::Class::create("Device", obj, nullptr, nullptr);

    cls->defineFunction("setTexture", _SE(js_gfx_DeviceGraphics_setTexture));
    cls->defineFunction("setBlendFuncSep", _SE(js_gfx_DeviceGraphics_setBlendFuncSeparate));
    cls->defineFunction("enableBlend", _SE(js_gfx_DeviceGraphics_enableBlend));
    cls->defineFunction("setPrimitiveType", _SE(js_gfx_DeviceGraphics_setPrimitiveType));
    cls->defineFunction("setBlendEqSep", _SE(js_gfx_DeviceGraphics_setBlendEquationSeparate));
    cls->defineFunction("setIndexBuffer", _SE(js_gfx_DeviceGraphics_setIndexBuffer));
    cls->defineFunction("setProgram", _SE(js_gfx_DeviceGraphics_setProgram));
    cls->defineFunction("setFrameBuffer", _SE(js_gfx_DeviceGraphics_setFrameBuffer));
    cls->defineFunction("setStencilFunc", _SE(js_gfx_DeviceGraphics_setStencilFunc));
    cls->defineFunction("setBlendColor", _SE(js_gfx_DeviceGraphics_setBlendColor));
    cls->defineFunction("setScissor", _SE(js_gfx_DeviceGraphics_setScissor));
    cls->defineFunction("setVertexBuffer", _SE(js_gfx_DeviceGraphics_setVertexBuffer));
    cls->defineFunction("enableDepthWrite", _SE(js_gfx_DeviceGraphics_enableDepthWrite));
    cls->defineFunction("setTextureArray", _SE(js_gfx_DeviceGraphics_setTextureArray));
    cls->defineFunction("setStencilOpBack", _SE(js_gfx_DeviceGraphics_setStencilOpBack));
    cls->defineFunction("setViewport", _SE(js_gfx_DeviceGraphics_setViewport));
    cls->defineFunction("draw", _SE(js_gfx_DeviceGraphics_draw));
    cls->defineFunction("setDepthFunc", _SE(js_gfx_DeviceGraphics_setDepthFunc));
    cls->defineFunction("enableDepthTest", _SE(js_gfx_DeviceGraphics_enableDepthTest));
    cls->defineFunction("setBlendEquation", _SE(js_gfx_DeviceGraphics_setBlendEquation));
    cls->defineFunction("setStencilFuncFront", _SE(js_gfx_DeviceGraphics_setStencilFuncFront));
    cls->defineFunction("setStencilOpFront", _SE(js_gfx_DeviceGraphics_setStencilOpFront));
    cls->defineFunction("setStencilFuncBack", _SE(js_gfx_DeviceGraphics_setStencilFuncBack));
    cls->defineFunction("setBlendFunc", _SE(js_gfx_DeviceGraphics_setBlendFunc));
    cls->defineFunction("setCullMode", _SE(js_gfx_DeviceGraphics_setCullMode));
    cls->defineFunction("supportGLExtension", _SE(js_gfx_DeviceGraphics_supportGLExtension));
    cls->defineFunction("setStencilOp", _SE(js_gfx_DeviceGraphics_setStencilOp));
    cls->defineFunction("enableStencilTest", _SE(js_gfx_DeviceGraphics_enableStencilTest));
    cls->defineStaticFunction("getInstance", _SE(js_gfx_DeviceGraphics_getInstance));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::DeviceGraphics>(cls);

    __jsb_cocos2d_gfx_DeviceGraphics_proto = cls->getProto();
    __jsb_cocos2d_gfx_DeviceGraphics_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_FrameBuffer_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_FrameBuffer_class = nullptr;

static bool js_gfx_FrameBuffer_setColorBuffer(se::State& s)
{
    cocos2d::gfx::FrameBuffer* cobj = (cocos2d::gfx::FrameBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_FrameBuffer_setColorBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        cocos2d::gfx::RenderTarget* arg0 = nullptr;
        int arg1 = 0;
        ok &= seval_to_native_ptr(args[0], &arg0);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (int)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_gfx_FrameBuffer_setColorBuffer : Error processing arguments");
        cobj->setColorBuffer(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_FrameBuffer_setColorBuffer)

static bool js_gfx_FrameBuffer_setStencilBuffer(se::State& s)
{
    cocos2d::gfx::FrameBuffer* cobj = (cocos2d::gfx::FrameBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_FrameBuffer_setStencilBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::RenderTarget* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_gfx_FrameBuffer_setStencilBuffer : Error processing arguments");
        cobj->setStencilBuffer(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_FrameBuffer_setStencilBuffer)

static bool js_gfx_FrameBuffer_getDepthBuffer(se::State& s)
{
    cocos2d::gfx::FrameBuffer* cobj = (cocos2d::gfx::FrameBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_FrameBuffer_getDepthBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::gfx::RenderTarget* result = cobj->getDepthBuffer();
        ok &= native_ptr_to_seval<cocos2d::gfx::RenderTarget>((cocos2d::gfx::RenderTarget*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_FrameBuffer_getDepthBuffer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_FrameBuffer_getDepthBuffer)

static bool js_gfx_FrameBuffer_setDepthStencilBuffer(se::State& s)
{
    cocos2d::gfx::FrameBuffer* cobj = (cocos2d::gfx::FrameBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_FrameBuffer_setDepthStencilBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::RenderTarget* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_gfx_FrameBuffer_setDepthStencilBuffer : Error processing arguments");
        cobj->setDepthStencilBuffer(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_FrameBuffer_setDepthStencilBuffer)

static bool js_gfx_FrameBuffer_getStencilBuffer(se::State& s)
{
    cocos2d::gfx::FrameBuffer* cobj = (cocos2d::gfx::FrameBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_FrameBuffer_getStencilBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::gfx::RenderTarget* result = cobj->getStencilBuffer();
        ok &= native_ptr_to_seval<cocos2d::gfx::RenderTarget>((cocos2d::gfx::RenderTarget*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_FrameBuffer_getStencilBuffer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_FrameBuffer_getStencilBuffer)

static bool js_gfx_FrameBuffer_setColorBuffers(se::State& s)
{
    cocos2d::gfx::FrameBuffer* cobj = (cocos2d::gfx::FrameBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_FrameBuffer_setColorBuffers : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::vector<cocos2d::gfx::RenderTarget *> arg0;
        ok &= seval_to_std_vector_RenderTarget(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_gfx_FrameBuffer_setColorBuffers : Error processing arguments");
        cobj->setColorBuffers(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_FrameBuffer_setColorBuffers)

static bool js_gfx_FrameBuffer_getColorBuffers(se::State& s)
{
    cocos2d::gfx::FrameBuffer* cobj = (cocos2d::gfx::FrameBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_FrameBuffer_getColorBuffers : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::gfx::RenderTarget *>& result = cobj->getColorBuffers();
        ok &= std_vector_RenderTarget_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_FrameBuffer_getColorBuffers : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_FrameBuffer_getColorBuffers)

static bool js_gfx_FrameBuffer_setDepthBuffer(se::State& s)
{
    cocos2d::gfx::FrameBuffer* cobj = (cocos2d::gfx::FrameBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_FrameBuffer_setDepthBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::RenderTarget* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_gfx_FrameBuffer_setDepthBuffer : Error processing arguments");
        cobj->setDepthBuffer(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_FrameBuffer_setDepthBuffer)

static bool js_gfx_FrameBuffer_getDepthStencilBuffer(se::State& s)
{
    cocos2d::gfx::FrameBuffer* cobj = (cocos2d::gfx::FrameBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_FrameBuffer_getDepthStencilBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::gfx::RenderTarget* result = cobj->getDepthStencilBuffer();
        ok &= native_ptr_to_seval<cocos2d::gfx::RenderTarget>((cocos2d::gfx::RenderTarget*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_FrameBuffer_getDepthStencilBuffer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_FrameBuffer_getDepthStencilBuffer)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_FrameBuffer_finalize)

static bool js_gfx_FrameBuffer_constructor(se::State& s)
{
    cocos2d::gfx::FrameBuffer* cobj = new (std::nothrow) cocos2d::gfx::FrameBuffer();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_gfx_FrameBuffer_constructor, __jsb_cocos2d_gfx_FrameBuffer_class, js_cocos2d_gfx_FrameBuffer_finalize)



extern se::Object* __jsb_cocos2d_gfx_GraphicsHandle_proto;

static bool js_cocos2d_gfx_FrameBuffer_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::FrameBuffer)", s.nativeThisObject());
    cocos2d::gfx::FrameBuffer* cobj = (cocos2d::gfx::FrameBuffer*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_FrameBuffer_finalize)

bool js_register_gfx_FrameBuffer(se::Object* obj)
{
    auto cls = se::Class::create("FrameBuffer", obj, __jsb_cocos2d_gfx_GraphicsHandle_proto, _SE(js_gfx_FrameBuffer_constructor));

    cls->defineFunction("setColorBuffer", _SE(js_gfx_FrameBuffer_setColorBuffer));
    cls->defineFunction("setStencilBuffer", _SE(js_gfx_FrameBuffer_setStencilBuffer));
    cls->defineFunction("getDepthBuffer", _SE(js_gfx_FrameBuffer_getDepthBuffer));
    cls->defineFunction("setDepthStencilBuffer", _SE(js_gfx_FrameBuffer_setDepthStencilBuffer));
    cls->defineFunction("getStencilBuffer", _SE(js_gfx_FrameBuffer_getStencilBuffer));
    cls->defineFunction("setColorBuffers", _SE(js_gfx_FrameBuffer_setColorBuffers));
    cls->defineFunction("getColorBuffers", _SE(js_gfx_FrameBuffer_getColorBuffers));
    cls->defineFunction("setDepthBuffer", _SE(js_gfx_FrameBuffer_setDepthBuffer));
    cls->defineFunction("getDepthStencilBuffer", _SE(js_gfx_FrameBuffer_getDepthStencilBuffer));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_FrameBuffer_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::FrameBuffer>(cls);

    __jsb_cocos2d_gfx_FrameBuffer_proto = cls->getProto();
    __jsb_cocos2d_gfx_FrameBuffer_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_RenderTarget_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_RenderTarget_class = nullptr;


extern se::Object* __jsb_cocos2d_gfx_GraphicsHandle_proto;

static bool js_cocos2d_gfx_RenderTarget_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::RenderTarget)", s.nativeThisObject());
    cocos2d::gfx::RenderTarget* cobj = (cocos2d::gfx::RenderTarget*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_RenderTarget_finalize)

bool js_register_gfx_RenderTarget(se::Object* obj)
{
    auto cls = se::Class::create("RenderTarget", obj, __jsb_cocos2d_gfx_GraphicsHandle_proto, nullptr);

    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_RenderTarget_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::RenderTarget>(cls);

    __jsb_cocos2d_gfx_RenderTarget_proto = cls->getProto();
    __jsb_cocos2d_gfx_RenderTarget_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_RenderBuffer_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_RenderBuffer_class = nullptr;

static bool js_gfx_RenderBuffer_init(se::State& s)
{
    cocos2d::gfx::RenderBuffer* cobj = (cocos2d::gfx::RenderBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_RenderBuffer_init : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        cocos2d::gfx::DeviceGraphics* arg0 = nullptr;
        cocos2d::gfx::RenderBuffer::Format arg1;
        unsigned short arg2 = 0;
        unsigned short arg3 = 0;
        ok &= seval_to_native_ptr(args[0], &arg0);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::RenderBuffer::Format)tmp; } while(false);
        ok &= seval_to_uint16(args[2], &arg2);
        ok &= seval_to_uint16(args[3], &arg3);
        SE_PRECONDITION2(ok, false, "js_gfx_RenderBuffer_init : Error processing arguments");
        bool result = cobj->init(arg0, arg1, arg2, arg3);
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_RenderBuffer_init : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_gfx_RenderBuffer_init)

static bool js_gfx_RenderBuffer_create(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        cocos2d::gfx::DeviceGraphics* arg0 = nullptr;
        cocos2d::gfx::RenderBuffer::Format arg1;
        unsigned short arg2 = 0;
        unsigned short arg3 = 0;
        ok &= seval_to_native_ptr(args[0], &arg0);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::RenderBuffer::Format)tmp; } while(false);
        ok &= seval_to_uint16(args[2], &arg2);
        ok &= seval_to_uint16(args[3], &arg3);
        SE_PRECONDITION2(ok, false, "js_gfx_RenderBuffer_create : Error processing arguments");
        auto result = cocos2d::gfx::RenderBuffer::create(arg0, arg1, arg2, arg3);
        result->retain();
        auto obj = se::Object::createObjectWithClass(__jsb_cocos2d_gfx_RenderBuffer_class);
        obj->setPrivateData(result);
        s.rval().setObject(obj);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_gfx_RenderBuffer_create)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_RenderBuffer_finalize)

static bool js_gfx_RenderBuffer_constructor(se::State& s)
{
    cocos2d::gfx::RenderBuffer* cobj = new (std::nothrow) cocos2d::gfx::RenderBuffer();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_gfx_RenderBuffer_constructor, __jsb_cocos2d_gfx_RenderBuffer_class, js_cocos2d_gfx_RenderBuffer_finalize)



extern se::Object* __jsb_cocos2d_gfx_RenderTarget_proto;

static bool js_cocos2d_gfx_RenderBuffer_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::RenderBuffer)", s.nativeThisObject());
    cocos2d::gfx::RenderBuffer* cobj = (cocos2d::gfx::RenderBuffer*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_RenderBuffer_finalize)

bool js_register_gfx_RenderBuffer(se::Object* obj)
{
    auto cls = se::Class::create("RenderBuffer", obj, __jsb_cocos2d_gfx_RenderTarget_proto, _SE(js_gfx_RenderBuffer_constructor));

    cls->defineFunction("init", _SE(js_gfx_RenderBuffer_init));
    cls->defineStaticFunction("create", _SE(js_gfx_RenderBuffer_create));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_RenderBuffer_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::RenderBuffer>(cls);

    __jsb_cocos2d_gfx_RenderBuffer_proto = cls->getProto();
    __jsb_cocos2d_gfx_RenderBuffer_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_Texture_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_Texture_class = nullptr;

static bool js_gfx_Texture_getWidth(se::State& s)
{
    cocos2d::gfx::Texture* cobj = (cocos2d::gfx::Texture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_Texture_getWidth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned short result = cobj->getWidth();
        ok &= int16_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_Texture_getWidth : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_Texture_getWidth)

static bool js_gfx_Texture_getHeight(se::State& s)
{
    cocos2d::gfx::Texture* cobj = (cocos2d::gfx::Texture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_Texture_getHeight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned short result = cobj->getHeight();
        ok &= int16_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_Texture_getHeight : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_Texture_getHeight)

static bool js_gfx_Texture_getTarget(se::State& s)
{
    cocos2d::gfx::Texture* cobj = (cocos2d::gfx::Texture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_Texture_getTarget : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getTarget();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_Texture_getTarget : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_Texture_getTarget)


extern se::Object* __jsb_cocos2d_gfx_RenderTarget_proto;

static bool js_cocos2d_gfx_Texture_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::Texture)", s.nativeThisObject());
    cocos2d::gfx::Texture* cobj = (cocos2d::gfx::Texture*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_Texture_finalize)

bool js_register_gfx_Texture(se::Object* obj)
{
    auto cls = se::Class::create("Texture", obj, __jsb_cocos2d_gfx_RenderTarget_proto, nullptr);

    cls->defineFunction("getWidth", _SE(js_gfx_Texture_getWidth));
    cls->defineFunction("getHeight", _SE(js_gfx_Texture_getHeight));
    cls->defineFunction("getTarget", _SE(js_gfx_Texture_getTarget));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_Texture_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::Texture>(cls);

    __jsb_cocos2d_gfx_Texture_proto = cls->getProto();
    __jsb_cocos2d_gfx_Texture_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_Texture2D_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_Texture2D_class = nullptr;

static bool js_gfx_Texture2D_updateImage(se::State& s)
{
    cocos2d::gfx::Texture2D* cobj = (cocos2d::gfx::Texture2D*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_Texture2D_updateImage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Texture::ImageOption arg0;
        ok &= seval_to_TextureImageOption(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_gfx_Texture2D_updateImage : Error processing arguments");
        cobj->updateImage(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_Texture2D_updateImage)

static bool js_gfx_Texture2D_init(se::State& s)
{
    cocos2d::gfx::Texture2D* cobj = (cocos2d::gfx::Texture2D*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_Texture2D_init : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        cocos2d::gfx::DeviceGraphics* arg0 = nullptr;
        cocos2d::gfx::Texture::Options arg1;
        ok &= seval_to_native_ptr(args[0], &arg0);
        ok &= seval_to_TextureOptions(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_gfx_Texture2D_init : Error processing arguments");
        bool result = cobj->init(arg0, arg1);
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_Texture2D_init : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_Texture2D_init)

static bool js_gfx_Texture2D_updateSubImage(se::State& s)
{
    cocos2d::gfx::Texture2D* cobj = (cocos2d::gfx::Texture2D*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_Texture2D_updateSubImage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Texture::SubImageOption arg0;
        ok &= seval_to_TextureSubImageOption(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_gfx_Texture2D_updateSubImage : Error processing arguments");
        cobj->updateSubImage(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_Texture2D_updateSubImage)

static bool js_gfx_Texture2D_update(se::State& s)
{
    cocos2d::gfx::Texture2D* cobj = (cocos2d::gfx::Texture2D*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_Texture2D_update : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Texture::Options arg0;
        ok &= seval_to_TextureOptions(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_gfx_Texture2D_update : Error processing arguments");
        cobj->update(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_Texture2D_update)

static bool js_gfx_Texture2D_create(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        cocos2d::gfx::DeviceGraphics* arg0 = nullptr;
        cocos2d::gfx::Texture::Options arg1;
        ok &= seval_to_native_ptr(args[0], &arg0);
        ok &= seval_to_TextureOptions(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_gfx_Texture2D_create : Error processing arguments");
        auto result = cocos2d::gfx::Texture2D::create(arg0, arg1);
        result->retain();
        auto obj = se::Object::createObjectWithClass(__jsb_cocos2d_gfx_Texture2D_class);
        obj->setPrivateData(result);
        s.rval().setObject(obj);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_Texture2D_create)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_Texture2D_finalize)

static bool js_gfx_Texture2D_constructor(se::State& s)
{
    cocos2d::gfx::Texture2D* cobj = new (std::nothrow) cocos2d::gfx::Texture2D();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_gfx_Texture2D_constructor, __jsb_cocos2d_gfx_Texture2D_class, js_cocos2d_gfx_Texture2D_finalize)



extern se::Object* __jsb_cocos2d_gfx_Texture_proto;

static bool js_cocos2d_gfx_Texture2D_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::Texture2D)", s.nativeThisObject());
    cocos2d::gfx::Texture2D* cobj = (cocos2d::gfx::Texture2D*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_Texture2D_finalize)

bool js_register_gfx_Texture2D(se::Object* obj)
{
    auto cls = se::Class::create("Texture2D", obj, __jsb_cocos2d_gfx_Texture_proto, _SE(js_gfx_Texture2D_constructor));

    cls->defineFunction("updateImage", _SE(js_gfx_Texture2D_updateImage));
    cls->defineFunction("init", _SE(js_gfx_Texture2D_init));
    cls->defineFunction("updateSubImage", _SE(js_gfx_Texture2D_updateSubImage));
    cls->defineFunction("update", _SE(js_gfx_Texture2D_update));
    cls->defineStaticFunction("create", _SE(js_gfx_Texture2D_create));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_Texture2D_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::Texture2D>(cls);

    __jsb_cocos2d_gfx_Texture2D_proto = cls->getProto();
    __jsb_cocos2d_gfx_Texture2D_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_Program_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_Program_class = nullptr;

static bool js_gfx_Program_isLinked(se::State& s)
{
    cocos2d::gfx::Program* cobj = (cocos2d::gfx::Program*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_Program_isLinked : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isLinked();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_Program_isLinked : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_Program_isLinked)

static bool js_gfx_Program_getID(se::State& s)
{
    cocos2d::gfx::Program* cobj = (cocos2d::gfx::Program*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_Program_getID : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getID();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_Program_getID : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_Program_getID)

static bool js_gfx_Program_init(se::State& s)
{
    cocos2d::gfx::Program* cobj = (cocos2d::gfx::Program*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_Program_init : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        cocos2d::gfx::DeviceGraphics* arg0 = nullptr;
        const char* arg1 = nullptr;
        const char* arg2 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        std::string arg1_tmp; ok &= seval_to_std_string(args[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        std::string arg2_tmp; ok &= seval_to_std_string(args[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
        SE_PRECONDITION2(ok, false, "js_gfx_Program_init : Error processing arguments");
        bool result = cobj->init(arg0, arg1, arg2);
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_Program_init : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_gfx_Program_init)

static bool js_gfx_Program_link(se::State& s)
{
    cocos2d::gfx::Program* cobj = (cocos2d::gfx::Program*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_Program_link : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->link();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_Program_link)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_Program_finalize)

static bool js_gfx_Program_constructor(se::State& s)
{
    cocos2d::gfx::Program* cobj = new (std::nothrow) cocos2d::gfx::Program();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_gfx_Program_constructor, __jsb_cocos2d_gfx_Program_class, js_cocos2d_gfx_Program_finalize)



extern se::Object* __jsb_cocos2d_gfx_GraphicsHandle_proto;

static bool js_cocos2d_gfx_Program_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::Program)", s.nativeThisObject());
    cocos2d::gfx::Program* cobj = (cocos2d::gfx::Program*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_Program_finalize)

bool js_register_gfx_Program(se::Object* obj)
{
    auto cls = se::Class::create("Program", obj, __jsb_cocos2d_gfx_GraphicsHandle_proto, _SE(js_gfx_Program_constructor));

    cls->defineFunction("isLinked", _SE(js_gfx_Program_isLinked));
    cls->defineFunction("getID", _SE(js_gfx_Program_getID));
    cls->defineFunction("init", _SE(js_gfx_Program_init));
    cls->defineFunction("link", _SE(js_gfx_Program_link));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_Program_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::Program>(cls);

    __jsb_cocos2d_gfx_Program_proto = cls->getProto();
    __jsb_cocos2d_gfx_Program_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_gfx(se::Object* obj)
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("gfx", &nsVal))
    {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("gfx", nsVal);
    }
    se::Object* ns = nsVal.toObject();

    js_register_gfx_GraphicsHandle(ns);
    js_register_gfx_RenderTarget(ns);
    js_register_gfx_RenderBuffer(ns);
    js_register_gfx_VertexBuffer(ns);
    js_register_gfx_DeviceGraphics(ns);
    js_register_gfx_Texture(ns);
    js_register_gfx_Program(ns);
    js_register_gfx_Texture2D(ns);
    js_register_gfx_IndexBuffer(ns);
    js_register_gfx_FrameBuffer(ns);
    return true;
}

