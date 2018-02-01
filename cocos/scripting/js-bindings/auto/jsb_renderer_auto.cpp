#include "scripting/js-bindings/auto/jsb_renderer_auto.hpp"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "Renderer.h"

se::Object* __jsb_cocos2d_gfx_View_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_View_class = nullptr;

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_View_finalize)

static bool js_renderer_View_constructor(se::State& s)
{
    cocos2d::gfx::View* cobj = new (std::nothrow) cocos2d::gfx::View();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_renderer_View_constructor, __jsb_cocos2d_gfx_View_class, js_cocos2d_gfx_View_finalize)




static bool js_cocos2d_gfx_View_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::View)", s.nativeThisObject());
    cocos2d::gfx::View* cobj = (cocos2d::gfx::View*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_View_finalize)

bool js_register_renderer_View(se::Object* obj)
{
    auto cls = se::Class::create("View", obj, nullptr, _SE(js_renderer_View_constructor));

    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_View_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::View>(cls);

    __jsb_cocos2d_gfx_View_proto = cls->getProto();
    __jsb_cocos2d_gfx_View_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_Camera_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_Camera_class = nullptr;

static bool js_renderer_Camera_getDepth(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_getDepth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getDepth();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_getDepth : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_getDepth)

static bool js_renderer_Camera_setFov(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_setFov : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_setFov : Error processing arguments");
        cobj->setFov(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_setFov)

static bool js_renderer_Camera_getFrameBuffer(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_getFrameBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::gfx::FrameBuffer* result = cobj->getFrameBuffer();
        ok &= native_ptr_to_seval<cocos2d::gfx::FrameBuffer>((cocos2d::gfx::FrameBuffer*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_getFrameBuffer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_getFrameBuffer)

static bool js_renderer_Camera_setStencil(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_setStencil : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (int)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_setStencil : Error processing arguments");
        cobj->setStencil(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_setStencil)

static bool js_renderer_Camera_getOrthoHeight(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_getOrthoHeight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getOrthoHeight();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_getOrthoHeight : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_getOrthoHeight)

static bool js_renderer_Camera_getStencil(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_getStencil : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getStencil();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_getStencil : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_getStencil)

static bool js_renderer_Camera_setFrameBuffer(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_setFrameBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::FrameBuffer* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_setFrameBuffer : Error processing arguments");
        cobj->setFrameBuffer(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_setFrameBuffer)

static bool js_renderer_Camera_setFar(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_setFar : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_setFar : Error processing arguments");
        cobj->setFar(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_setFar)

static bool js_renderer_Camera_setRect(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_setRect : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        float arg0 = 0;
        float arg1 = 0;
        float arg2 = 0;
        float arg3 = 0;
        ok &= seval_to_float(args[0], &arg0);
        ok &= seval_to_float(args[1], &arg1);
        ok &= seval_to_float(args[2], &arg2);
        ok &= seval_to_float(args[3], &arg3);
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_setRect : Error processing arguments");
        cobj->setRect(arg0, arg1, arg2, arg3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_setRect)

static bool js_renderer_Camera_setClearFlags(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_setClearFlags : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        uint8_t arg0;
        ok &= seval_to_uint8(args[0], (uint8_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_setClearFlags : Error processing arguments");
        cobj->setClearFlags(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_setClearFlags)

static bool js_renderer_Camera_getFar(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_getFar : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getFar();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_getFar : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_getFar)

static bool js_renderer_Camera_getType(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_getType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getType();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_getType : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_getType)

static bool js_renderer_Camera_setNear(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_setNear : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_setNear : Error processing arguments");
        cobj->setNear(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_setNear)

static bool js_renderer_Camera_setStages(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_setStages : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::vector<std::string> arg0;
        ok &= seval_to_std_vector_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_setStages : Error processing arguments");
        cobj->setStages(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_setStages)

static bool js_renderer_Camera_setOrthoHeight(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_setOrthoHeight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_setOrthoHeight : Error processing arguments");
        cobj->setOrthoHeight(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_setOrthoHeight)

static bool js_renderer_Camera_setDepth(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_setDepth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_setDepth : Error processing arguments");
        cobj->setDepth(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_setDepth)

static bool js_renderer_Camera_getStages(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_getStages : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<std::string>& result = cobj->getStages();
        ok &= std_vector_string_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_getStages : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_getStages)

static bool js_renderer_Camera_getFov(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_getFov : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getFov();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_getFov : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_getFov)

static bool js_renderer_Camera_setColor(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_setColor : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        float arg0 = 0;
        float arg1 = 0;
        float arg2 = 0;
        float arg3 = 0;
        ok &= seval_to_float(args[0], &arg0);
        ok &= seval_to_float(args[1], &arg1);
        ok &= seval_to_float(args[2], &arg2);
        ok &= seval_to_float(args[3], &arg3);
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_setColor : Error processing arguments");
        cobj->setColor(arg0, arg1, arg2, arg3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_setColor)

static bool js_renderer_Camera_getNear(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_getNear : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getNear();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_getNear : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_getNear)

static bool js_renderer_Camera_getClearFlags(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_getClearFlags : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        uint8_t result = cobj->getClearFlags();
        ok &= uint8_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_getClearFlags : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_getClearFlags)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_Camera_finalize)

static bool js_renderer_Camera_constructor(se::State& s)
{
    cocos2d::gfx::Camera* cobj = new (std::nothrow) cocos2d::gfx::Camera();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_renderer_Camera_constructor, __jsb_cocos2d_gfx_Camera_class, js_cocos2d_gfx_Camera_finalize)




static bool js_cocos2d_gfx_Camera_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::Camera)", s.nativeThisObject());
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_Camera_finalize)

bool js_register_renderer_Camera(se::Object* obj)
{
    auto cls = se::Class::create("Camera", obj, nullptr, _SE(js_renderer_Camera_constructor));

    cls->defineFunction("getDepth", _SE(js_renderer_Camera_getDepth));
    cls->defineFunction("setFov", _SE(js_renderer_Camera_setFov));
    cls->defineFunction("getFrameBuffer", _SE(js_renderer_Camera_getFrameBuffer));
    cls->defineFunction("setStencil", _SE(js_renderer_Camera_setStencil));
    cls->defineFunction("getOrthoHeight", _SE(js_renderer_Camera_getOrthoHeight));
    cls->defineFunction("getStencil", _SE(js_renderer_Camera_getStencil));
    cls->defineFunction("setFrameBuffer", _SE(js_renderer_Camera_setFrameBuffer));
    cls->defineFunction("setFar", _SE(js_renderer_Camera_setFar));
    cls->defineFunction("setRect", _SE(js_renderer_Camera_setRect));
    cls->defineFunction("setClearFlags", _SE(js_renderer_Camera_setClearFlags));
    cls->defineFunction("getFar", _SE(js_renderer_Camera_getFar));
    cls->defineFunction("getType", _SE(js_renderer_Camera_getType));
    cls->defineFunction("setNear", _SE(js_renderer_Camera_setNear));
    cls->defineFunction("setStages", _SE(js_renderer_Camera_setStages));
    cls->defineFunction("setOrthoHeight", _SE(js_renderer_Camera_setOrthoHeight));
    cls->defineFunction("setDepth", _SE(js_renderer_Camera_setDepth));
    cls->defineFunction("getStages", _SE(js_renderer_Camera_getStages));
    cls->defineFunction("getFov", _SE(js_renderer_Camera_getFov));
    cls->defineFunction("setColor", _SE(js_renderer_Camera_setColor));
    cls->defineFunction("getNear", _SE(js_renderer_Camera_getNear));
    cls->defineFunction("getClearFlags", _SE(js_renderer_Camera_getClearFlags));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_Camera_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::Camera>(cls);

    __jsb_cocos2d_gfx_Camera_proto = cls->getProto();
    __jsb_cocos2d_gfx_Camera_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_renderer(se::Object* obj)
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("renderer", &nsVal))
    {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("renderer", nsVal);
    }
    se::Object* ns = nsVal.toObject();

    js_register_renderer_Camera(ns);
    js_register_renderer_View(ns);
    return true;
}

