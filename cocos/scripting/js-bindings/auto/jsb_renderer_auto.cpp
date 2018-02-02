#include "scripting/js-bindings/auto/jsb_renderer_auto.hpp"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "Renderer.h"

se::Object* __jsb_cocos2d_gfx_ProgramLib_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_ProgramLib_class = nullptr;

static bool js_renderer_ProgramLib_getProgram(se::State& s)
{
    cocos2d::gfx::ProgramLib* cobj = (cocos2d::gfx::ProgramLib*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_ProgramLib_getProgram : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        std::string arg0;
        cocos2d::ValueMap arg1;
        ok &= seval_to_std_string(args[0], &arg0);
        ok &= seval_to_ccvaluemap(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_renderer_ProgramLib_getProgram : Error processing arguments");
        cocos2d::gfx::Program* result = cobj->getProgram(arg0, arg1);
        ok &= native_ptr_to_seval<cocos2d::gfx::Program>((cocos2d::gfx::Program*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_ProgramLib_getProgram : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_renderer_ProgramLib_getProgram)

static bool js_renderer_ProgramLib_define(se::State& s)
{
    cocos2d::gfx::ProgramLib* cobj = (cocos2d::gfx::ProgramLib*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_ProgramLib_define : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        cocos2d::ValueVector arg3;
        ok &= seval_to_std_string(args[0], &arg0);
        ok &= seval_to_std_string(args[1], &arg1);
        ok &= seval_to_std_string(args[2], &arg2);
        ok &= seval_to_ccvaluevector(args[3], &arg3);
        SE_PRECONDITION2(ok, false, "js_renderer_ProgramLib_define : Error processing arguments");
        cobj->define(arg0, arg1, arg2, arg3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_renderer_ProgramLib_define)

static bool js_renderer_ProgramLib_getKey(se::State& s)
{
    cocos2d::gfx::ProgramLib* cobj = (cocos2d::gfx::ProgramLib*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_ProgramLib_getKey : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        std::string arg0;
        cocos2d::ValueMap arg1;
        ok &= seval_to_std_string(args[0], &arg0);
        ok &= seval_to_ccvaluemap(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_renderer_ProgramLib_getKey : Error processing arguments");
        unsigned int result = cobj->getKey(arg0, arg1);
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_ProgramLib_getKey : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_renderer_ProgramLib_getKey)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_ProgramLib_finalize)

static bool js_renderer_ProgramLib_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    std::vector<cocos2d::gfx::ProgramLib::Template> arg0;
    ok &= seval_to_std_vector_ProgramLib_Template(args[0], &arg0);
    SE_PRECONDITION2(ok, false, "js_renderer_ProgramLib_constructor : Error processing arguments");
    cocos2d::gfx::ProgramLib* cobj = new (std::nothrow) cocos2d::gfx::ProgramLib(arg0);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_renderer_ProgramLib_constructor, __jsb_cocos2d_gfx_ProgramLib_class, js_cocos2d_gfx_ProgramLib_finalize)




static bool js_cocos2d_gfx_ProgramLib_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::ProgramLib)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::gfx::ProgramLib* cobj = (cocos2d::gfx::ProgramLib*)s.nativeThisObject();
        delete cobj;
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_ProgramLib_finalize)

bool js_register_renderer_ProgramLib(se::Object* obj)
{
    auto cls = se::Class::create("ProgramLib", obj, nullptr, _SE(js_renderer_ProgramLib_constructor));

    cls->defineFunction("getProgram", _SE(js_renderer_ProgramLib_getProgram));
    cls->defineFunction("define", _SE(js_renderer_ProgramLib_define));
    cls->defineFunction("getKey", _SE(js_renderer_ProgramLib_getKey));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_ProgramLib_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::ProgramLib>(cls);

    __jsb_cocos2d_gfx_ProgramLib_proto = cls->getProto();
    __jsb_cocos2d_gfx_ProgramLib_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_Model_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_Model_class = nullptr;

static bool js_renderer_Model_getInputAssemblerCount(se::State& s)
{
    cocos2d::gfx::Model* cobj = (cocos2d::gfx::Model*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Model_getInputAssemblerCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getInputAssemblerCount();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Model_getInputAssemblerCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Model_getInputAssemblerCount)

static bool js_renderer_Model_getDrawItemCount(se::State& s)
{
    cocos2d::gfx::Model* cobj = (cocos2d::gfx::Model*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Model_getDrawItemCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getDrawItemCount();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Model_getDrawItemCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Model_getDrawItemCount)

static bool js_renderer_Model_setViewId(se::State& s)
{
    cocos2d::gfx::Model* cobj = (cocos2d::gfx::Model*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Model_setViewId : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (int)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Model_setViewId : Error processing arguments");
        cobj->setViewId(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Model_setViewId)

static bool js_renderer_Model_isDynamicIA(se::State& s)
{
    cocos2d::gfx::Model* cobj = (cocos2d::gfx::Model*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Model_isDynamicIA : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isDynamicIA();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Model_isDynamicIA : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Model_isDynamicIA)

static bool js_renderer_Model_addEffect(se::State& s)
{
    cocos2d::gfx::Model* cobj = (cocos2d::gfx::Model*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Model_addEffect : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Effect* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Model_addEffect : Error processing arguments");
        cobj->addEffect(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Model_addEffect)

static bool js_renderer_Model_setWorldMatix(se::State& s)
{
    cocos2d::gfx::Model* cobj = (cocos2d::gfx::Model*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Model_setWorldMatix : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::Mat4 arg0;
        ok &= seval_to_Mat4(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Model_setWorldMatix : Error processing arguments");
        cobj->setWorldMatix(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Model_setWorldMatix)

static bool js_renderer_Model_clearEffects(se::State& s)
{
    cocos2d::gfx::Model* cobj = (cocos2d::gfx::Model*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Model_clearEffects : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->clearEffects();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Model_clearEffects)

static bool js_renderer_Model_setDynamicIA(se::State& s)
{
    cocos2d::gfx::Model* cobj = (cocos2d::gfx::Model*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Model_setDynamicIA : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        bool arg0;
        ok &= seval_to_boolean(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Model_setDynamicIA : Error processing arguments");
        cobj->setDynamicIA(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Model_setDynamicIA)

static bool js_renderer_Model_getViewId(se::State& s)
{
    cocos2d::gfx::Model* cobj = (cocos2d::gfx::Model*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Model_getViewId : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getViewId();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Model_getViewId : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Model_getViewId)

static bool js_renderer_Model_clearInputAssemblers(se::State& s)
{
    cocos2d::gfx::Model* cobj = (cocos2d::gfx::Model*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Model_clearInputAssemblers : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->clearInputAssemblers();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Model_clearInputAssemblers)

static bool js_renderer_Model_addInputAssembler(se::State& s)
{
    cocos2d::gfx::Model* cobj = (cocos2d::gfx::Model*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Model_addInputAssembler : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::InputAssembler* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Model_addInputAssembler : Error processing arguments");
        cobj->addInputAssembler(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Model_addInputAssembler)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_Model_finalize)

static bool js_renderer_Model_constructor(se::State& s)
{
    cocos2d::gfx::Model* cobj = new (std::nothrow) cocos2d::gfx::Model();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_renderer_Model_constructor, __jsb_cocos2d_gfx_Model_class, js_cocos2d_gfx_Model_finalize)




static bool js_cocos2d_gfx_Model_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::Model)", s.nativeThisObject());
    cocos2d::gfx::Model* cobj = (cocos2d::gfx::Model*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_Model_finalize)

bool js_register_renderer_Model(se::Object* obj)
{
    auto cls = se::Class::create("Model", obj, nullptr, _SE(js_renderer_Model_constructor));

    cls->defineFunction("getInputAssemblerCount", _SE(js_renderer_Model_getInputAssemblerCount));
    cls->defineFunction("getDrawItemCount", _SE(js_renderer_Model_getDrawItemCount));
    cls->defineFunction("setViewId", _SE(js_renderer_Model_setViewId));
    cls->defineFunction("isDynamicIA", _SE(js_renderer_Model_isDynamicIA));
    cls->defineFunction("addEffect", _SE(js_renderer_Model_addEffect));
    cls->defineFunction("setWorldMatix", _SE(js_renderer_Model_setWorldMatix));
    cls->defineFunction("clearEffects", _SE(js_renderer_Model_clearEffects));
    cls->defineFunction("setDynamicIA", _SE(js_renderer_Model_setDynamicIA));
    cls->defineFunction("getViewId", _SE(js_renderer_Model_getViewId));
    cls->defineFunction("clearInputAssemblers", _SE(js_renderer_Model_clearInputAssemblers));
    cls->defineFunction("addInputAssembler", _SE(js_renderer_Model_addInputAssembler));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_Model_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::Model>(cls);

    __jsb_cocos2d_gfx_Model_proto = cls->getProto();
    __jsb_cocos2d_gfx_Model_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_BaseRenderer_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_BaseRenderer_class = nullptr;

static bool js_renderer_BaseRenderer_init(se::State& s)
{
    CC_UNUSED bool ok = true;
    cocos2d::gfx::BaseRenderer* cobj = (cocos2d::gfx::BaseRenderer*)s.nativeThisObject();
    SE_PRECONDITION2( cobj, false, "js_renderer_BaseRenderer_init : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    do {
        if (argc == 3) {
            cocos2d::gfx::DeviceGraphics* arg0 = nullptr;
            ok &= seval_to_native_ptr(args[0], &arg0);
            if (!ok) { ok = true; break; }
            std::vector<cocos2d::gfx::ProgramLib::Template> arg1;
            ok &= seval_to_std_vector_ProgramLib_Template(args[1], &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::gfx::Texture2D* arg2 = nullptr;
            ok &= seval_to_native_ptr(args[2], &arg2);
            if (!ok) { ok = true; break; }
            bool result = cobj->init(arg0, arg1, arg2);
            ok &= boolean_to_seval(result, &s.rval());
            SE_PRECONDITION2(ok, false, "js_renderer_BaseRenderer_init : Error processing arguments");
            return true;
        }
    } while(false);

    do {
        if (argc == 2) {
            cocos2d::gfx::DeviceGraphics* arg0 = nullptr;
            ok &= seval_to_native_ptr(args[0], &arg0);
            if (!ok) { ok = true; break; }
            std::vector<cocos2d::gfx::ProgramLib::Template> arg1;
            ok &= seval_to_std_vector_ProgramLib_Template(args[1], &arg1);
            if (!ok) { ok = true; break; }
            bool result = cobj->init(arg0, arg1);
            ok &= boolean_to_seval(result, &s.rval());
            SE_PRECONDITION2(ok, false, "js_renderer_BaseRenderer_init : Error processing arguments");
            return true;
        }
    } while(false);

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(js_renderer_BaseRenderer_init)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_BaseRenderer_finalize)

static bool js_renderer_BaseRenderer_constructor(se::State& s)
{
    cocos2d::gfx::BaseRenderer* cobj = new (std::nothrow) cocos2d::gfx::BaseRenderer();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_renderer_BaseRenderer_constructor, __jsb_cocos2d_gfx_BaseRenderer_class, js_cocos2d_gfx_BaseRenderer_finalize)




static bool js_cocos2d_gfx_BaseRenderer_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::BaseRenderer)", s.nativeThisObject());
    cocos2d::gfx::BaseRenderer* cobj = (cocos2d::gfx::BaseRenderer*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_BaseRenderer_finalize)

bool js_register_renderer_BaseRenderer(se::Object* obj)
{
    auto cls = se::Class::create("Base", obj, nullptr, _SE(js_renderer_BaseRenderer_constructor));

    cls->defineFunction("init", _SE(js_renderer_BaseRenderer_init));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_BaseRenderer_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::BaseRenderer>(cls);

    __jsb_cocos2d_gfx_BaseRenderer_proto = cls->getProto();
    __jsb_cocos2d_gfx_BaseRenderer_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_ForwardRenderer_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_ForwardRenderer_class = nullptr;

static bool js_renderer_ForwardRenderer_init(se::State& s)
{
    cocos2d::gfx::ForwardRenderer* cobj = (cocos2d::gfx::ForwardRenderer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_ForwardRenderer_init : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        cocos2d::gfx::DeviceGraphics* arg0 = nullptr;
        std::vector<cocos2d::gfx::ProgramLib::Template> arg1;
        int arg2 = 0;
        int arg3 = 0;
        ok &= seval_to_native_ptr(args[0], &arg0);
        ok &= seval_to_std_vector_ProgramLib_Template(args[1], &arg1);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (int)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (int)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_ForwardRenderer_init : Error processing arguments");
        bool result = cobj->init(arg0, arg1, arg2, arg3);
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_ForwardRenderer_init : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_renderer_ForwardRenderer_init)

static bool js_renderer_ForwardRenderer_render(se::State& s)
{
    cocos2d::gfx::ForwardRenderer* cobj = (cocos2d::gfx::ForwardRenderer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_ForwardRenderer_render : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Scene* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_ForwardRenderer_render : Error processing arguments");
        cobj->render(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_ForwardRenderer_render)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_ForwardRenderer_finalize)

static bool js_renderer_ForwardRenderer_constructor(se::State& s)
{
    cocos2d::gfx::ForwardRenderer* cobj = new (std::nothrow) cocos2d::gfx::ForwardRenderer();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_renderer_ForwardRenderer_constructor, __jsb_cocos2d_gfx_ForwardRenderer_class, js_cocos2d_gfx_ForwardRenderer_finalize)



extern se::Object* __jsb_cocos2d_gfx_BaseRenderer_proto;

static bool js_cocos2d_gfx_ForwardRenderer_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::ForwardRenderer)", s.nativeThisObject());
    cocos2d::gfx::ForwardRenderer* cobj = (cocos2d::gfx::ForwardRenderer*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_ForwardRenderer_finalize)

bool js_register_renderer_ForwardRenderer(se::Object* obj)
{
    auto cls = se::Class::create("ForwardRenderer", obj, __jsb_cocos2d_gfx_BaseRenderer_proto, _SE(js_renderer_ForwardRenderer_constructor));

    cls->defineFunction("init", _SE(js_renderer_ForwardRenderer_init));
    cls->defineFunction("render", _SE(js_renderer_ForwardRenderer_render));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_ForwardRenderer_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::ForwardRenderer>(cls);

    __jsb_cocos2d_gfx_ForwardRenderer_proto = cls->getProto();
    __jsb_cocos2d_gfx_ForwardRenderer_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

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

static bool js_renderer_Camera_setWorldMatrix(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_setWorldMatrix : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::Mat4 arg0;
        ok &= seval_to_Mat4(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Camera_setWorldMatrix : Error processing arguments");
        cobj->setWorldMatrix(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_setWorldMatrix)

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
    cls->defineFunction("setWorldMatrix", _SE(js_renderer_Camera_setWorldMatrix));
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

se::Object* __jsb_cocos2d_gfx_Technique_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_Technique_class = nullptr;

static bool js_renderer_Technique_getPasses(se::State& s)
{
    cocos2d::gfx::Technique* cobj = (cocos2d::gfx::Technique*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Technique_getPasses : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::Vector<cocos2d::gfx::Pass *>& result = cobj->getPasses();
        ok &= Vector_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Technique_getPasses : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Technique_getPasses)

static bool js_renderer_Technique_getStageIDs(se::State& s)
{
    cocos2d::gfx::Technique* cobj = (cocos2d::gfx::Technique*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Technique_getStageIDs : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getStageIDs();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Technique_getStageIDs : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Technique_getStageIDs)

static bool js_renderer_Technique_setStages(se::State& s)
{
    cocos2d::gfx::Technique* cobj = (cocos2d::gfx::Technique*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Technique_setStages : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::vector<std::string> arg0;
        ok &= seval_to_std_vector_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Technique_setStages : Error processing arguments");
        cobj->setStages(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Technique_setStages)

static bool js_renderer_Technique_getParameters(se::State& s)
{
    cocos2d::gfx::Technique* cobj = (cocos2d::gfx::Technique*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Technique_getParameters : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::gfx::Technique::Parameter>& result = cobj->getParameters();
        ok &= std_vector_TechniqueParameter_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Technique_getParameters : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Technique_getParameters)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_Technique_finalize)

static bool js_renderer_Technique_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    std::vector<std::string> arg0;
    std::vector<cocos2d::gfx::Technique::Parameter> arg1;
    cocos2d::Vector<cocos2d::gfx::Pass *> arg2;
    ok &= seval_to_std_vector_string(args[0], &arg0);
    ok &= seval_to_std_vector_TechniqueParameter(args[1], &arg1);
    ok &= seval_to_Vector(args[2], &arg2);
    SE_PRECONDITION2(ok, false, "js_renderer_Technique_constructor : Error processing arguments");
    cocos2d::gfx::Technique* cobj = new (std::nothrow) cocos2d::gfx::Technique(arg0, arg1, arg2);
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_renderer_Technique_constructor, __jsb_cocos2d_gfx_Technique_class, js_cocos2d_gfx_Technique_finalize)




static bool js_cocos2d_gfx_Technique_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::Technique)", s.nativeThisObject());
    cocos2d::gfx::Technique* cobj = (cocos2d::gfx::Technique*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_Technique_finalize)

bool js_register_renderer_Technique(se::Object* obj)
{
    auto cls = se::Class::create("Technique", obj, nullptr, _SE(js_renderer_Technique_constructor));

    cls->defineFunction("getPasses", _SE(js_renderer_Technique_getPasses));
    cls->defineFunction("getStageIDs", _SE(js_renderer_Technique_getStageIDs));
    cls->defineFunction("setStages", _SE(js_renderer_Technique_setStages));
    cls->defineFunction("getParameters", _SE(js_renderer_Technique_getParameters));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_Technique_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::Technique>(cls);

    __jsb_cocos2d_gfx_Technique_proto = cls->getProto();
    __jsb_cocos2d_gfx_Technique_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_Effect_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_Effect_class = nullptr;

static bool js_renderer_Effect_getDefineValue(se::State& s)
{
    cocos2d::gfx::Effect* cobj = (cocos2d::gfx::Effect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Effect_getDefineValue : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Effect_getDefineValue : Error processing arguments");
        cocos2d::Value result = cobj->getDefineValue(arg0);
        ok &= ccvalue_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Effect_getDefineValue : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Effect_getDefineValue)

static bool js_renderer_Effect_getProperty(se::State& s)
{
    cocos2d::gfx::Effect* cobj = (cocos2d::gfx::Effect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Effect_getProperty : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Effect_getProperty : Error processing arguments");
        const cocos2d::gfx::Technique::Parameter& result = cobj->getProperty(arg0);
        ok &= TechniqueParameter_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Effect_getProperty : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Effect_getProperty)

static bool js_renderer_Effect_clear(se::State& s)
{
    cocos2d::gfx::Effect* cobj = (cocos2d::gfx::Effect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Effect_clear : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->clear();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Effect_clear)

static bool js_renderer_Effect_setDefineValue(se::State& s)
{
    cocos2d::gfx::Effect* cobj = (cocos2d::gfx::Effect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Effect_setDefineValue : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        std::string arg0;
        cocos2d::Value arg1;
        ok &= seval_to_std_string(args[0], &arg0);
        ok &= seval_to_ccvalue(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_renderer_Effect_setDefineValue : Error processing arguments");
        cobj->setDefineValue(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_renderer_Effect_setDefineValue)

static bool js_renderer_Effect_setProperty(se::State& s)
{
    cocos2d::gfx::Effect* cobj = (cocos2d::gfx::Effect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Effect_setProperty : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        std::string arg0;
        cocos2d::gfx::Technique::Parameter arg1;
        ok &= seval_to_std_string(args[0], &arg0);
        ok &= seval_to_TechniqueParameter(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_renderer_Effect_setProperty : Error processing arguments");
        cobj->setProperty(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_renderer_Effect_setProperty)

static bool js_renderer_Effect_getTechnique(se::State& s)
{
    cocos2d::gfx::Effect* cobj = (cocos2d::gfx::Effect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Effect_getTechnique : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Effect_getTechnique : Error processing arguments");
        cocos2d::gfx::Technique* result = cobj->getTechnique(arg0);
        ok &= native_ptr_to_seval<cocos2d::gfx::Technique>((cocos2d::gfx::Technique*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Effect_getTechnique : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Effect_getTechnique)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_Effect_finalize)

static bool js_renderer_Effect_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    cocos2d::Vector<cocos2d::gfx::Technique *> arg0;
    std::unordered_map<std::string, cocos2d::gfx::Technique::Parameter> arg1;
    std::vector<std::unordered_map<std::string, cocos2d::Value>> arg2;
    ok &= seval_to_Vector(args[0], &arg0);
    ok &= seval_to_EffectProperty(args[1], &arg1);
    ok &= seval_to_EffectDefineTemplate(args[2], &arg2);
    SE_PRECONDITION2(ok, false, "js_renderer_Effect_constructor : Error processing arguments");
    cocos2d::gfx::Effect* cobj = new (std::nothrow) cocos2d::gfx::Effect(arg0, arg1, arg2);
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_renderer_Effect_constructor, __jsb_cocos2d_gfx_Effect_class, js_cocos2d_gfx_Effect_finalize)




static bool js_cocos2d_gfx_Effect_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::Effect)", s.nativeThisObject());
    cocos2d::gfx::Effect* cobj = (cocos2d::gfx::Effect*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_Effect_finalize)

bool js_register_renderer_Effect(se::Object* obj)
{
    auto cls = se::Class::create("Effect", obj, nullptr, _SE(js_renderer_Effect_constructor));

    cls->defineFunction("getDefineValue", _SE(js_renderer_Effect_getDefineValue));
    cls->defineFunction("getProperty", _SE(js_renderer_Effect_getProperty));
    cls->defineFunction("clear", _SE(js_renderer_Effect_clear));
    cls->defineFunction("setDefineValue", _SE(js_renderer_Effect_setDefineValue));
    cls->defineFunction("setProperty", _SE(js_renderer_Effect_setProperty));
    cls->defineFunction("getTechnique", _SE(js_renderer_Effect_getTechnique));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_Effect_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::Effect>(cls);

    __jsb_cocos2d_gfx_Effect_proto = cls->getProto();
    __jsb_cocos2d_gfx_Effect_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_InputAssembler_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_InputAssembler_class = nullptr;

static bool js_renderer_InputAssembler_setVertexBuffer(se::State& s)
{
    cocos2d::gfx::InputAssembler* cobj = (cocos2d::gfx::InputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_InputAssembler_setVertexBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::VertexBuffer* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_setVertexBuffer : Error processing arguments");
        cobj->setVertexBuffer(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_InputAssembler_setVertexBuffer)

static bool js_renderer_InputAssembler_getStart(se::State& s)
{
    cocos2d::gfx::InputAssembler* cobj = (cocos2d::gfx::InputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_InputAssembler_getStart : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getStart();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_getStart : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_InputAssembler_getStart)

static bool js_renderer_InputAssembler_setStart(se::State& s)
{
    cocos2d::gfx::InputAssembler* cobj = (cocos2d::gfx::InputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_InputAssembler_setStart : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (int)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_setStart : Error processing arguments");
        cobj->setStart(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_InputAssembler_setStart)

static bool js_renderer_InputAssembler_setPrimitiveType(se::State& s)
{
    cocos2d::gfx::InputAssembler* cobj = (cocos2d::gfx::InputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_InputAssembler_setPrimitiveType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::PrimitiveType arg0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::PrimitiveType)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_setPrimitiveType : Error processing arguments");
        cobj->setPrimitiveType(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_InputAssembler_setPrimitiveType)

static bool js_renderer_InputAssembler_getPrimitiveCount(se::State& s)
{
    cocos2d::gfx::InputAssembler* cobj = (cocos2d::gfx::InputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_InputAssembler_getPrimitiveCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getPrimitiveCount();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_getPrimitiveCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_InputAssembler_getPrimitiveCount)

static bool js_renderer_InputAssembler_setCount(se::State& s)
{
    cocos2d::gfx::InputAssembler* cobj = (cocos2d::gfx::InputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_InputAssembler_setCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (int)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_setCount : Error processing arguments");
        cobj->setCount(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_InputAssembler_setCount)

static bool js_renderer_InputAssembler_init(se::State& s)
{
    cocos2d::gfx::InputAssembler* cobj = (cocos2d::gfx::InputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_InputAssembler_init : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        cocos2d::gfx::VertexBuffer* arg0 = nullptr;
        cocos2d::gfx::IndexBuffer* arg1 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        ok &= seval_to_native_ptr(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_init : Error processing arguments");
        bool result = cobj->init(arg0, arg1);
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_init : Error processing arguments");
        return true;
    }
    if (argc == 3) {
        cocos2d::gfx::VertexBuffer* arg0 = nullptr;
        cocos2d::gfx::IndexBuffer* arg1 = nullptr;
        cocos2d::gfx::PrimitiveType arg2;
        ok &= seval_to_native_ptr(args[0], &arg0);
        ok &= seval_to_native_ptr(args[1], &arg1);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (cocos2d::gfx::PrimitiveType)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_init : Error processing arguments");
        bool result = cobj->init(arg0, arg1, arg2);
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_init : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_renderer_InputAssembler_init)

static bool js_renderer_InputAssembler_getVertexBuffer(se::State& s)
{
    cocos2d::gfx::InputAssembler* cobj = (cocos2d::gfx::InputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_InputAssembler_getVertexBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::gfx::VertexBuffer* result = cobj->getVertexBuffer();
        ok &= native_ptr_to_seval<cocos2d::gfx::VertexBuffer>((cocos2d::gfx::VertexBuffer*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_getVertexBuffer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_InputAssembler_getVertexBuffer)

static bool js_renderer_InputAssembler_getIndexBuffer(se::State& s)
{
    cocos2d::gfx::InputAssembler* cobj = (cocos2d::gfx::InputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_InputAssembler_getIndexBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::gfx::IndexBuffer* result = cobj->getIndexBuffer();
        ok &= native_ptr_to_seval<cocos2d::gfx::IndexBuffer>((cocos2d::gfx::IndexBuffer*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_getIndexBuffer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_InputAssembler_getIndexBuffer)

static bool js_renderer_InputAssembler_getCount(se::State& s)
{
    cocos2d::gfx::InputAssembler* cobj = (cocos2d::gfx::InputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_InputAssembler_getCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getCount();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_getCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_InputAssembler_getCount)

static bool js_renderer_InputAssembler_getPrimitiveType(se::State& s)
{
    cocos2d::gfx::InputAssembler* cobj = (cocos2d::gfx::InputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_InputAssembler_getPrimitiveType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getPrimitiveType();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_getPrimitiveType : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_InputAssembler_getPrimitiveType)

static bool js_renderer_InputAssembler_setIndexBuffer(se::State& s)
{
    cocos2d::gfx::InputAssembler* cobj = (cocos2d::gfx::InputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_InputAssembler_setIndexBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::IndexBuffer* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_InputAssembler_setIndexBuffer : Error processing arguments");
        cobj->setIndexBuffer(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_InputAssembler_setIndexBuffer)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_InputAssembler_finalize)

static bool js_renderer_InputAssembler_constructor(se::State& s)
{
    cocos2d::gfx::InputAssembler* cobj = new (std::nothrow) cocos2d::gfx::InputAssembler();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_renderer_InputAssembler_constructor, __jsb_cocos2d_gfx_InputAssembler_class, js_cocos2d_gfx_InputAssembler_finalize)




static bool js_cocos2d_gfx_InputAssembler_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::InputAssembler)", s.nativeThisObject());
    cocos2d::gfx::InputAssembler* cobj = (cocos2d::gfx::InputAssembler*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_InputAssembler_finalize)

bool js_register_renderer_InputAssembler(se::Object* obj)
{
    auto cls = se::Class::create("InputAssembler", obj, nullptr, _SE(js_renderer_InputAssembler_constructor));

    cls->defineFunction("setVertexBuffer", _SE(js_renderer_InputAssembler_setVertexBuffer));
    cls->defineFunction("getStart", _SE(js_renderer_InputAssembler_getStart));
    cls->defineFunction("setStart", _SE(js_renderer_InputAssembler_setStart));
    cls->defineFunction("setPrimitiveType", _SE(js_renderer_InputAssembler_setPrimitiveType));
    cls->defineFunction("getPrimitiveCount", _SE(js_renderer_InputAssembler_getPrimitiveCount));
    cls->defineFunction("setCount", _SE(js_renderer_InputAssembler_setCount));
    cls->defineFunction("init", _SE(js_renderer_InputAssembler_init));
    cls->defineFunction("getVertexBuffer", _SE(js_renderer_InputAssembler_getVertexBuffer));
    cls->defineFunction("getIndexBuffer", _SE(js_renderer_InputAssembler_getIndexBuffer));
    cls->defineFunction("getCount", _SE(js_renderer_InputAssembler_getCount));
    cls->defineFunction("getPrimitiveType", _SE(js_renderer_InputAssembler_getPrimitiveType));
    cls->defineFunction("setIndexBuffer", _SE(js_renderer_InputAssembler_setIndexBuffer));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_InputAssembler_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::InputAssembler>(cls);

    __jsb_cocos2d_gfx_InputAssembler_proto = cls->getProto();
    __jsb_cocos2d_gfx_InputAssembler_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_Light_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_Light_class = nullptr;

static bool js_renderer_Light_getShadowScale(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getShadowScale : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getShadowScale();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getShadowScale : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getShadowScale)

static bool js_renderer_Light_getRange(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getRange : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getRange();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getRange : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getRange)

static bool js_renderer_Light_setShadowResolution(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setShadowResolution : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= seval_to_uint32(args[0], (uint32_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setShadowResolution : Error processing arguments");
        cobj->setShadowResolution(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setShadowResolution)

static bool js_renderer_Light_getFrustumEdgeFalloff(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getFrustumEdgeFalloff : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getFrustumEdgeFalloff();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getFrustumEdgeFalloff : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getFrustumEdgeFalloff)

static bool js_renderer_Light_setSpotExp(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setSpotExp : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setSpotExp : Error processing arguments");
        cobj->setSpotExp(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setSpotExp)

static bool js_renderer_Light_setShadowType(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setShadowType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Light::ShadowType arg0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::Light::ShadowType)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setShadowType : Error processing arguments");
        cobj->setShadowType(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setShadowType)

static bool js_renderer_Light_setType(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Light::LightType arg0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::Light::LightType)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setType : Error processing arguments");
        cobj->setType(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setType)

static bool js_renderer_Light_getViewProjMatrix(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getViewProjMatrix : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::Mat4& result = cobj->getViewProjMatrix();
        ok &= Mat4_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getViewProjMatrix : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getViewProjMatrix)

static bool js_renderer_Light_getShadowBias(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getShadowBias : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getShadowBias();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getShadowBias : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getShadowBias)

static bool js_renderer_Light_getShadowDarkness(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getShadowDarkness : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getShadowDarkness();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getShadowDarkness : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getShadowDarkness)

static bool js_renderer_Light_getSpotAngle(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getSpotAngle : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getSpotAngle();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getSpotAngle : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getSpotAngle)

static bool js_renderer_Light_getSpotExp(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getSpotExp : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getSpotExp();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getSpotExp : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getSpotExp)

static bool js_renderer_Light_getViewPorjMatrix(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getViewPorjMatrix : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::Mat4 result = cobj->getViewPorjMatrix();
        ok &= Mat4_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getViewPorjMatrix : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getViewPorjMatrix)

static bool js_renderer_Light_getType(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getType();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getType : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getType)

static bool js_renderer_Light_getIntensity(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getIntensity : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getIntensity();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getIntensity : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getIntensity)

static bool js_renderer_Light_getShadowMaxDepth(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getShadowMaxDepth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getShadowMaxDepth();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getShadowMaxDepth : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getShadowMaxDepth)

static bool js_renderer_Light_getShadowMap(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getShadowMap : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::gfx::Texture2D* result = cobj->getShadowMap();
        ok &= native_ptr_to_seval<cocos2d::gfx::Texture2D>((cocos2d::gfx::Texture2D*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getShadowMap : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getShadowMap)

static bool js_renderer_Light_getColor(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getColor : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::Color3F result = cobj->getColor();
        ok &= Color3F_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getColor : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getColor)

static bool js_renderer_Light_setIntensity(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setIntensity : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setIntensity : Error processing arguments");
        cobj->setIntensity(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setIntensity)

static bool js_renderer_Light_getShadowMinDepth(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getShadowMinDepth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getShadowMinDepth();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getShadowMinDepth : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getShadowMinDepth)

static bool js_renderer_Light_setShadowMinDepth(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setShadowMinDepth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setShadowMinDepth : Error processing arguments");
        cobj->setShadowMinDepth(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setShadowMinDepth)

static bool js_renderer_Light_update(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_update : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::DeviceGraphics* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_update : Error processing arguments");
        cobj->update(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_update)

static bool js_renderer_Light_setShadowDarkness(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setShadowDarkness : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= seval_to_uint32(args[0], (uint32_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setShadowDarkness : Error processing arguments");
        cobj->setShadowDarkness(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setShadowDarkness)

static bool js_renderer_Light_setSpotAngle(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setSpotAngle : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setSpotAngle : Error processing arguments");
        cobj->setSpotAngle(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setSpotAngle)

static bool js_renderer_Light_setRange(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setRange : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setRange : Error processing arguments");
        cobj->setRange(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setRange)

static bool js_renderer_Light_setShadowScale(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setShadowScale : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setShadowScale : Error processing arguments");
        cobj->setShadowScale(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setShadowScale)

static bool js_renderer_Light_setColor(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setColor : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        float arg0 = 0;
        float arg1 = 0;
        float arg2 = 0;
        ok &= seval_to_float(args[0], &arg0);
        ok &= seval_to_float(args[1], &arg1);
        ok &= seval_to_float(args[2], &arg2);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setColor : Error processing arguments");
        cobj->setColor(arg0, arg1, arg2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setColor)

static bool js_renderer_Light_setShadowMaxDepth(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setShadowMaxDepth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setShadowMaxDepth : Error processing arguments");
        cobj->setShadowMaxDepth(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setShadowMaxDepth)

static bool js_renderer_Light_setFrustumEdgeFalloff(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setFrustumEdgeFalloff : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= seval_to_uint32(args[0], (uint32_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setFrustumEdgeFalloff : Error processing arguments");
        cobj->setFrustumEdgeFalloff(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setFrustumEdgeFalloff)

static bool js_renderer_Light_getShadowType(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getShadowType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getShadowType();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getShadowType : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getShadowType)

static bool js_renderer_Light_getShadowResolution(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_getShadowResolution : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getShadowResolution();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Light_getShadowResolution : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_getShadowResolution)

static bool js_renderer_Light_setShadowBias(se::State& s)
{
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Light_setShadowBias : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Light_setShadowBias : Error processing arguments");
        cobj->setShadowBias(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Light_setShadowBias)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_Light_finalize)

static bool js_renderer_Light_constructor(se::State& s)
{
    cocos2d::gfx::Light* cobj = new (std::nothrow) cocos2d::gfx::Light();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_renderer_Light_constructor, __jsb_cocos2d_gfx_Light_class, js_cocos2d_gfx_Light_finalize)




static bool js_cocos2d_gfx_Light_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::Light)", s.nativeThisObject());
    cocos2d::gfx::Light* cobj = (cocos2d::gfx::Light*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_Light_finalize)

bool js_register_renderer_Light(se::Object* obj)
{
    auto cls = se::Class::create("Light", obj, nullptr, _SE(js_renderer_Light_constructor));

    cls->defineFunction("getShadowScale", _SE(js_renderer_Light_getShadowScale));
    cls->defineFunction("getRange", _SE(js_renderer_Light_getRange));
    cls->defineFunction("setShadowResolution", _SE(js_renderer_Light_setShadowResolution));
    cls->defineFunction("getFrustumEdgeFalloff", _SE(js_renderer_Light_getFrustumEdgeFalloff));
    cls->defineFunction("setSpotExp", _SE(js_renderer_Light_setSpotExp));
    cls->defineFunction("setShadowType", _SE(js_renderer_Light_setShadowType));
    cls->defineFunction("setType", _SE(js_renderer_Light_setType));
    cls->defineFunction("getViewProjMatrix", _SE(js_renderer_Light_getViewProjMatrix));
    cls->defineFunction("getShadowBias", _SE(js_renderer_Light_getShadowBias));
    cls->defineFunction("getShadowDarkness", _SE(js_renderer_Light_getShadowDarkness));
    cls->defineFunction("getSpotAngle", _SE(js_renderer_Light_getSpotAngle));
    cls->defineFunction("getSpotExp", _SE(js_renderer_Light_getSpotExp));
    cls->defineFunction("getViewPorjMatrix", _SE(js_renderer_Light_getViewPorjMatrix));
    cls->defineFunction("getType", _SE(js_renderer_Light_getType));
    cls->defineFunction("getIntensity", _SE(js_renderer_Light_getIntensity));
    cls->defineFunction("getShadowMaxDepth", _SE(js_renderer_Light_getShadowMaxDepth));
    cls->defineFunction("getShadowMap", _SE(js_renderer_Light_getShadowMap));
    cls->defineFunction("getColor", _SE(js_renderer_Light_getColor));
    cls->defineFunction("setIntensity", _SE(js_renderer_Light_setIntensity));
    cls->defineFunction("getShadowMinDepth", _SE(js_renderer_Light_getShadowMinDepth));
    cls->defineFunction("setShadowMinDepth", _SE(js_renderer_Light_setShadowMinDepth));
    cls->defineFunction("update", _SE(js_renderer_Light_update));
    cls->defineFunction("setShadowDarkness", _SE(js_renderer_Light_setShadowDarkness));
    cls->defineFunction("setSpotAngle", _SE(js_renderer_Light_setSpotAngle));
    cls->defineFunction("setRange", _SE(js_renderer_Light_setRange));
    cls->defineFunction("setShadowScale", _SE(js_renderer_Light_setShadowScale));
    cls->defineFunction("setColor", _SE(js_renderer_Light_setColor));
    cls->defineFunction("setShadowMaxDepth", _SE(js_renderer_Light_setShadowMaxDepth));
    cls->defineFunction("setFrustumEdgeFalloff", _SE(js_renderer_Light_setFrustumEdgeFalloff));
    cls->defineFunction("getShadowType", _SE(js_renderer_Light_getShadowType));
    cls->defineFunction("getShadowResolution", _SE(js_renderer_Light_getShadowResolution));
    cls->defineFunction("setShadowBias", _SE(js_renderer_Light_setShadowBias));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_Light_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::Light>(cls);

    __jsb_cocos2d_gfx_Light_proto = cls->getProto();
    __jsb_cocos2d_gfx_Light_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_Pass_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_Pass_class = nullptr;

static bool js_renderer_Pass_setStencilBack(se::State& s)
{
    cocos2d::gfx::Pass* cobj = (cocos2d::gfx::Pass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Pass_setStencilBack : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cobj->setStencilBack();
        return true;
    }
    if (argc == 1) {
        cocos2d::gfx::ComparisonFunc arg0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilBack : Error processing arguments");
        cobj->setStencilBack(arg0);
        return true;
    }
    if (argc == 2) {
        cocos2d::gfx::ComparisonFunc arg0;
        unsigned int arg1 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        ok &= seval_to_uint32(args[1], (uint32_t*)&arg1);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilBack : Error processing arguments");
        cobj->setStencilBack(arg0, arg1);
        return true;
    }
    if (argc == 3) {
        cocos2d::gfx::ComparisonFunc arg0;
        unsigned int arg1 = 0;
        uint8_t arg2;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        ok &= seval_to_uint32(args[1], (uint32_t*)&arg1);
        ok &= seval_to_uint8(args[2], (uint8_t*)&arg2);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilBack : Error processing arguments");
        cobj->setStencilBack(arg0, arg1, arg2);
        return true;
    }
    if (argc == 4) {
        cocos2d::gfx::ComparisonFunc arg0;
        unsigned int arg1 = 0;
        uint8_t arg2;
        cocos2d::gfx::StencilOp arg3;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        ok &= seval_to_uint32(args[1], (uint32_t*)&arg1);
        ok &= seval_to_uint8(args[2], (uint8_t*)&arg2);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilBack : Error processing arguments");
        cobj->setStencilBack(arg0, arg1, arg2, arg3);
        return true;
    }
    if (argc == 5) {
        cocos2d::gfx::ComparisonFunc arg0;
        unsigned int arg1 = 0;
        uint8_t arg2;
        cocos2d::gfx::StencilOp arg3;
        cocos2d::gfx::StencilOp arg4;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        ok &= seval_to_uint32(args[1], (uint32_t*)&arg1);
        ok &= seval_to_uint8(args[2], (uint8_t*)&arg2);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[4], &tmp); arg4 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilBack : Error processing arguments");
        cobj->setStencilBack(arg0, arg1, arg2, arg3, arg4);
        return true;
    }
    if (argc == 6) {
        cocos2d::gfx::ComparisonFunc arg0;
        unsigned int arg1 = 0;
        uint8_t arg2;
        cocos2d::gfx::StencilOp arg3;
        cocos2d::gfx::StencilOp arg4;
        cocos2d::gfx::StencilOp arg5;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        ok &= seval_to_uint32(args[1], (uint32_t*)&arg1);
        ok &= seval_to_uint8(args[2], (uint8_t*)&arg2);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[4], &tmp); arg4 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[5], &tmp); arg5 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilBack : Error processing arguments");
        cobj->setStencilBack(arg0, arg1, arg2, arg3, arg4, arg5);
        return true;
    }
    if (argc == 7) {
        cocos2d::gfx::ComparisonFunc arg0;
        unsigned int arg1 = 0;
        uint8_t arg2;
        cocos2d::gfx::StencilOp arg3;
        cocos2d::gfx::StencilOp arg4;
        cocos2d::gfx::StencilOp arg5;
        uint8_t arg6;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        ok &= seval_to_uint32(args[1], (uint32_t*)&arg1);
        ok &= seval_to_uint8(args[2], (uint8_t*)&arg2);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[4], &tmp); arg4 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[5], &tmp); arg5 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        ok &= seval_to_uint8(args[6], (uint8_t*)&arg6);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilBack : Error processing arguments");
        cobj->setStencilBack(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 7);
    return false;
}
SE_BIND_FUNC(js_renderer_Pass_setStencilBack)

static bool js_renderer_Pass_setCullMode(se::State& s)
{
    cocos2d::gfx::Pass* cobj = (cocos2d::gfx::Pass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Pass_setCullMode : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::CullMode arg0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::CullMode)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setCullMode : Error processing arguments");
        cobj->setCullMode(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Pass_setCullMode)

static bool js_renderer_Pass_setBlend(se::State& s)
{
    cocos2d::gfx::Pass* cobj = (cocos2d::gfx::Pass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Pass_setBlend : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cobj->setBlend();
        return true;
    }
    if (argc == 1) {
        cocos2d::gfx::BlendOp arg0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setBlend : Error processing arguments");
        cobj->setBlend(arg0);
        return true;
    }
    if (argc == 2) {
        cocos2d::gfx::BlendOp arg0;
        cocos2d::gfx::BlendFactor arg1;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setBlend : Error processing arguments");
        cobj->setBlend(arg0, arg1);
        return true;
    }
    if (argc == 3) {
        cocos2d::gfx::BlendOp arg0;
        cocos2d::gfx::BlendFactor arg1;
        cocos2d::gfx::BlendFactor arg2;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setBlend : Error processing arguments");
        cobj->setBlend(arg0, arg1, arg2);
        return true;
    }
    if (argc == 4) {
        cocos2d::gfx::BlendOp arg0;
        cocos2d::gfx::BlendFactor arg1;
        cocos2d::gfx::BlendFactor arg2;
        cocos2d::gfx::BlendOp arg3;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setBlend : Error processing arguments");
        cobj->setBlend(arg0, arg1, arg2, arg3);
        return true;
    }
    if (argc == 5) {
        cocos2d::gfx::BlendOp arg0;
        cocos2d::gfx::BlendFactor arg1;
        cocos2d::gfx::BlendFactor arg2;
        cocos2d::gfx::BlendOp arg3;
        cocos2d::gfx::BlendFactor arg4;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[4], &tmp); arg4 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setBlend : Error processing arguments");
        cobj->setBlend(arg0, arg1, arg2, arg3, arg4);
        return true;
    }
    if (argc == 6) {
        cocos2d::gfx::BlendOp arg0;
        cocos2d::gfx::BlendFactor arg1;
        cocos2d::gfx::BlendFactor arg2;
        cocos2d::gfx::BlendOp arg3;
        cocos2d::gfx::BlendFactor arg4;
        cocos2d::gfx::BlendFactor arg5;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[4], &tmp); arg4 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[5], &tmp); arg5 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setBlend : Error processing arguments");
        cobj->setBlend(arg0, arg1, arg2, arg3, arg4, arg5);
        return true;
    }
    if (argc == 7) {
        cocos2d::gfx::BlendOp arg0;
        cocos2d::gfx::BlendFactor arg1;
        cocos2d::gfx::BlendFactor arg2;
        cocos2d::gfx::BlendOp arg3;
        cocos2d::gfx::BlendFactor arg4;
        cocos2d::gfx::BlendFactor arg5;
        unsigned int arg6 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[1], &tmp); arg1 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (cocos2d::gfx::BlendOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[4], &tmp); arg4 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[5], &tmp); arg5 = (cocos2d::gfx::BlendFactor)tmp; } while(false);
        ok &= seval_to_uint32(args[6], (uint32_t*)&arg6);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setBlend : Error processing arguments");
        cobj->setBlend(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 7);
    return false;
}
SE_BIND_FUNC(js_renderer_Pass_setBlend)

static bool js_renderer_Pass_setStencilFront(se::State& s)
{
    cocos2d::gfx::Pass* cobj = (cocos2d::gfx::Pass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Pass_setStencilFront : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cobj->setStencilFront();
        return true;
    }
    if (argc == 1) {
        cocos2d::gfx::ComparisonFunc arg0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilFront : Error processing arguments");
        cobj->setStencilFront(arg0);
        return true;
    }
    if (argc == 2) {
        cocos2d::gfx::ComparisonFunc arg0;
        unsigned int arg1 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        ok &= seval_to_uint32(args[1], (uint32_t*)&arg1);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilFront : Error processing arguments");
        cobj->setStencilFront(arg0, arg1);
        return true;
    }
    if (argc == 3) {
        cocos2d::gfx::ComparisonFunc arg0;
        unsigned int arg1 = 0;
        uint8_t arg2;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        ok &= seval_to_uint32(args[1], (uint32_t*)&arg1);
        ok &= seval_to_uint8(args[2], (uint8_t*)&arg2);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilFront : Error processing arguments");
        cobj->setStencilFront(arg0, arg1, arg2);
        return true;
    }
    if (argc == 4) {
        cocos2d::gfx::ComparisonFunc arg0;
        unsigned int arg1 = 0;
        uint8_t arg2;
        cocos2d::gfx::StencilOp arg3;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        ok &= seval_to_uint32(args[1], (uint32_t*)&arg1);
        ok &= seval_to_uint8(args[2], (uint8_t*)&arg2);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilFront : Error processing arguments");
        cobj->setStencilFront(arg0, arg1, arg2, arg3);
        return true;
    }
    if (argc == 5) {
        cocos2d::gfx::ComparisonFunc arg0;
        unsigned int arg1 = 0;
        uint8_t arg2;
        cocos2d::gfx::StencilOp arg3;
        cocos2d::gfx::StencilOp arg4;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        ok &= seval_to_uint32(args[1], (uint32_t*)&arg1);
        ok &= seval_to_uint8(args[2], (uint8_t*)&arg2);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[4], &tmp); arg4 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilFront : Error processing arguments");
        cobj->setStencilFront(arg0, arg1, arg2, arg3, arg4);
        return true;
    }
    if (argc == 6) {
        cocos2d::gfx::ComparisonFunc arg0;
        unsigned int arg1 = 0;
        uint8_t arg2;
        cocos2d::gfx::StencilOp arg3;
        cocos2d::gfx::StencilOp arg4;
        cocos2d::gfx::StencilOp arg5;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        ok &= seval_to_uint32(args[1], (uint32_t*)&arg1);
        ok &= seval_to_uint8(args[2], (uint8_t*)&arg2);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[4], &tmp); arg4 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[5], &tmp); arg5 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilFront : Error processing arguments");
        cobj->setStencilFront(arg0, arg1, arg2, arg3, arg4, arg5);
        return true;
    }
    if (argc == 7) {
        cocos2d::gfx::ComparisonFunc arg0;
        unsigned int arg1 = 0;
        uint8_t arg2;
        cocos2d::gfx::StencilOp arg3;
        cocos2d::gfx::StencilOp arg4;
        cocos2d::gfx::StencilOp arg5;
        uint8_t arg6;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        ok &= seval_to_uint32(args[1], (uint32_t*)&arg1);
        ok &= seval_to_uint8(args[2], (uint8_t*)&arg2);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[3], &tmp); arg3 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[4], &tmp); arg4 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[5], &tmp); arg5 = (cocos2d::gfx::StencilOp)tmp; } while(false);
        ok &= seval_to_uint8(args[6], (uint8_t*)&arg6);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setStencilFront : Error processing arguments");
        cobj->setStencilFront(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 7);
    return false;
}
SE_BIND_FUNC(js_renderer_Pass_setStencilFront)

static bool js_renderer_Pass_setDepth(se::State& s)
{
    cocos2d::gfx::Pass* cobj = (cocos2d::gfx::Pass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Pass_setDepth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cobj->setDepth();
        return true;
    }
    if (argc == 1) {
        bool arg0;
        ok &= seval_to_boolean(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setDepth : Error processing arguments");
        cobj->setDepth(arg0);
        return true;
    }
    if (argc == 2) {
        bool arg0;
        bool arg1;
        ok &= seval_to_boolean(args[0], &arg0);
        ok &= seval_to_boolean(args[1], &arg1);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setDepth : Error processing arguments");
        cobj->setDepth(arg0, arg1);
        return true;
    }
    if (argc == 3) {
        bool arg0;
        bool arg1;
        cocos2d::gfx::ComparisonFunc arg2;
        ok &= seval_to_boolean(args[0], &arg0);
        ok &= seval_to_boolean(args[1], &arg1);
        do { int32_t tmp = 0; ok &= seval_to_int32(args[2], &tmp); arg2 = (cocos2d::gfx::ComparisonFunc)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_renderer_Pass_setDepth : Error processing arguments");
        cobj->setDepth(arg0, arg1, arg2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_renderer_Pass_setDepth)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_Pass_finalize)

static bool js_renderer_Pass_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    std::string arg0;
    ok &= seval_to_std_string(args[0], &arg0);
    SE_PRECONDITION2(ok, false, "js_renderer_Pass_constructor : Error processing arguments");
    cocos2d::gfx::Pass* cobj = new (std::nothrow) cocos2d::gfx::Pass(arg0);
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_renderer_Pass_constructor, __jsb_cocos2d_gfx_Pass_class, js_cocos2d_gfx_Pass_finalize)




static bool js_cocos2d_gfx_Pass_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::Pass)", s.nativeThisObject());
    cocos2d::gfx::Pass* cobj = (cocos2d::gfx::Pass*)s.nativeThisObject();
    if (cobj->getReferenceCount() == 1)
        cobj->autorelease();
    else
        cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_Pass_finalize)

bool js_register_renderer_Pass(se::Object* obj)
{
    auto cls = se::Class::create("Pass", obj, nullptr, _SE(js_renderer_Pass_constructor));

    cls->defineFunction("setStencilBack", _SE(js_renderer_Pass_setStencilBack));
    cls->defineFunction("setCullMode", _SE(js_renderer_Pass_setCullMode));
    cls->defineFunction("setBlend", _SE(js_renderer_Pass_setBlend));
    cls->defineFunction("setStencilFront", _SE(js_renderer_Pass_setStencilFront));
    cls->defineFunction("setDepth", _SE(js_renderer_Pass_setDepth));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_Pass_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::Pass>(cls);

    __jsb_cocos2d_gfx_Pass_proto = cls->getProto();
    __jsb_cocos2d_gfx_Pass_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_gfx_Scene_proto = nullptr;
se::Class* __jsb_cocos2d_gfx_Scene_class = nullptr;

static bool js_renderer_Scene_reset(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_reset : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->reset();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_reset)

static bool js_renderer_Scene_getCameraCount(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_getCameraCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getCameraCount();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_getCameraCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_getCameraCount)

static bool js_renderer_Scene_addCamera(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_addCamera : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Camera* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_addCamera : Error processing arguments");
        cobj->addCamera(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_addCamera)

static bool js_renderer_Scene_removeCamera(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_removeCamera : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Camera* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_removeCamera : Error processing arguments");
        cobj->removeCamera(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_removeCamera)

static bool js_renderer_Scene_getLightCount(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_getLightCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getLightCount();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_getLightCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_getLightCount)

static bool js_renderer_Scene_getModel(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_getModel : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= seval_to_uint32(args[0], (uint32_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_getModel : Error processing arguments");
        cocos2d::gfx::Model* result = cobj->getModel(arg0);
        ok &= native_ptr_to_seval<cocos2d::gfx::Model>((cocos2d::gfx::Model*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_getModel : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_getModel)

static bool js_renderer_Scene_removeModel(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_removeModel : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Model* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_removeModel : Error processing arguments");
        cobj->removeModel(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_removeModel)

static bool js_renderer_Scene_getModelCount(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_getModelCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getModelCount();
        ok &= uint32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_getModelCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_getModelCount)

static bool js_renderer_Scene_getCamera(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_getCamera : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= seval_to_uint32(args[0], (uint32_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_getCamera : Error processing arguments");
        cocos2d::gfx::Camera* result = cobj->getCamera(arg0);
        ok &= native_ptr_to_seval<cocos2d::gfx::Camera>((cocos2d::gfx::Camera*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_getCamera : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_getCamera)

static bool js_renderer_Scene_getLight(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_getLight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= seval_to_uint32(args[0], (uint32_t*)&arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_getLight : Error processing arguments");
        cocos2d::gfx::Light* result = cobj->getLight(arg0);
        ok &= native_ptr_to_seval<cocos2d::gfx::Light>((cocos2d::gfx::Light*)result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_getLight : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_getLight)

static bool js_renderer_Scene_getCameras(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_getCameras : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::Vector<cocos2d::gfx::Camera *>& result = cobj->getCameras();
        ok &= Vector_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_getCameras : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_getCameras)

static bool js_renderer_Scene_getModels(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_getModels : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::Vector<cocos2d::gfx::Model *>& result = cobj->getModels();
        ok &= Vector_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_getModels : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_getModels)

static bool js_renderer_Scene_addView(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_addView : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::View* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_addView : Error processing arguments");
        cobj->addView(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_addView)

static bool js_renderer_Scene_setDebugCamera(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_setDebugCamera : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Camera* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_setDebugCamera : Error processing arguments");
        cobj->setDebugCamera(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_setDebugCamera)

static bool js_renderer_Scene_addModel(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_addModel : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Model* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_addModel : Error processing arguments");
        cobj->addModel(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_addModel)

static bool js_renderer_Scene_removeView(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_removeView : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::View* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_removeView : Error processing arguments");
        cobj->removeView(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_removeView)

static bool js_renderer_Scene_addLight(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_addLight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Light* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_addLight : Error processing arguments");
        cobj->addLight(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_addLight)

static bool js_renderer_Scene_removeLight(se::State& s)
{
    cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Scene_removeLight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Light* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_renderer_Scene_removeLight : Error processing arguments");
        cobj->removeLight(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Scene_removeLight)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_gfx_Scene_finalize)

static bool js_renderer_Scene_constructor(se::State& s)
{
    cocos2d::gfx::Scene* cobj = new (std::nothrow) cocos2d::gfx::Scene();
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_renderer_Scene_constructor, __jsb_cocos2d_gfx_Scene_class, js_cocos2d_gfx_Scene_finalize)




static bool js_cocos2d_gfx_Scene_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::gfx::Scene)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::gfx::Scene* cobj = (cocos2d::gfx::Scene*)s.nativeThisObject();
        delete cobj;
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_gfx_Scene_finalize)

bool js_register_renderer_Scene(se::Object* obj)
{
    auto cls = se::Class::create("Scene", obj, nullptr, _SE(js_renderer_Scene_constructor));

    cls->defineFunction("reset", _SE(js_renderer_Scene_reset));
    cls->defineFunction("getCameraCount", _SE(js_renderer_Scene_getCameraCount));
    cls->defineFunction("addCamera", _SE(js_renderer_Scene_addCamera));
    cls->defineFunction("removeCamera", _SE(js_renderer_Scene_removeCamera));
    cls->defineFunction("getLightCount", _SE(js_renderer_Scene_getLightCount));
    cls->defineFunction("getModel", _SE(js_renderer_Scene_getModel));
    cls->defineFunction("removeModel", _SE(js_renderer_Scene_removeModel));
    cls->defineFunction("getModelCount", _SE(js_renderer_Scene_getModelCount));
    cls->defineFunction("getCamera", _SE(js_renderer_Scene_getCamera));
    cls->defineFunction("getLight", _SE(js_renderer_Scene_getLight));
    cls->defineFunction("getCameras", _SE(js_renderer_Scene_getCameras));
    cls->defineFunction("getModels", _SE(js_renderer_Scene_getModels));
    cls->defineFunction("addView", _SE(js_renderer_Scene_addView));
    cls->defineFunction("setDebugCamera", _SE(js_renderer_Scene_setDebugCamera));
    cls->defineFunction("addModel", _SE(js_renderer_Scene_addModel));
    cls->defineFunction("removeView", _SE(js_renderer_Scene_removeView));
    cls->defineFunction("addLight", _SE(js_renderer_Scene_addLight));
    cls->defineFunction("removeLight", _SE(js_renderer_Scene_removeLight));
    cls->defineFinalizeFunction(_SE(js_cocos2d_gfx_Scene_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::gfx::Scene>(cls);

    __jsb_cocos2d_gfx_Scene_proto = cls->getProto();
    __jsb_cocos2d_gfx_Scene_class = cls;

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

    js_register_renderer_ProgramLib(ns);
    js_register_renderer_Light(ns);
    js_register_renderer_Technique(ns);
    js_register_renderer_Effect(ns);
    js_register_renderer_Scene(ns);
    js_register_renderer_Camera(ns);
    js_register_renderer_BaseRenderer(ns);
    js_register_renderer_Pass(ns);
    js_register_renderer_InputAssembler(ns);
    js_register_renderer_Model(ns);
    js_register_renderer_ForwardRenderer(ns);
    js_register_renderer_View(ns);
    return true;
}

