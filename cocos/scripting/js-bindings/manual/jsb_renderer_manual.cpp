#include "jsb_renderer_manual.hpp"
#include "cocos/scripting/js-bindings/auto/jsb_renderer_auto.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_conversions.hpp"
#include "Renderer.h"

using namespace cocos2d;
using namespace cocos2d::gfx;

static bool js_renderer_Camera_getColor(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_getColor : Invalid Native Object");
    auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        Color4F color;
        cobj->getColor(color);
        se::Object* arg0Obj = args[0].toObject();
        arg0Obj->setProperty("r", se::Value(color.r));
        arg0Obj->setProperty("g", se::Value(color.g));
        arg0Obj->setProperty("b", se::Value(color.b));
        s.rval().setObject(arg0Obj);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_getColor)

static bool js_renderer_Camera_getRect(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_getRect : Invalid Native Object");
    auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::gfx::Rect rect;
        cobj->getRect(rect);
        se::Object* arg0Obj = args[0].toObject();
        arg0Obj->setProperty("x", se::Value(rect.x));
        arg0Obj->setProperty("y", se::Value(rect.y));
        arg0Obj->setProperty("w", se::Value(rect.w));
        arg0Obj->setProperty("h", se::Value(rect.h));
        s.rval().setObject(arg0Obj);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_getRect)

static bool js_renderer_Camera_extractView(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_extractView : Invalid Native Object");
    auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        cocos2d::gfx::View* view = nullptr;
        ok = seval_to_native_ptr(args[0], &view);
        SE_PRECONDITION2(ok, false, "Convert arg0 failed!");
        int32_t width = 0;
        ok = seval_to_int32(args[1], &width);
        SE_PRECONDITION2(ok, false, "Convert arg1 failed!");
        int32_t height = 0;
        ok = seval_to_int32(args[2], &height);
        SE_PRECONDITION2(ok, false, "Convert arg2 failed!");
        cobj->extractView(*view, width, height);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_extractView)

static bool js_renderer_Camera_screenToWorld(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_screenToWorld : Invalid Native Object");
    auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        cocos2d::Vec3 out;
        cocos2d::Vec3 screenPos;
        ok = seval_to_Vec3(args[1], &screenPos);
        SE_PRECONDITION2(ok, false, "Convert arg1 failed!");
        int32_t width = 0;
        ok = seval_to_int32(args[2], &width);
        SE_PRECONDITION2(ok, false, "Convert arg2 failed!");
        int32_t height = 0;
        ok = seval_to_int32(args[3], &height);
        SE_PRECONDITION2(ok, false, "Convert arg3 failed!");
        cobj->screenToWorld(out, screenPos, width, height);
        se::Object* arg0Obj = args[0].toObject();
        arg0Obj->setProperty("x", se::Value(out.x));
        arg0Obj->setProperty("y", se::Value(out.y));
        arg0Obj->setProperty("z", se::Value(out.z));
        s.rval().setObject(arg0Obj);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_screenToWorld)

static bool js_renderer_Camera_worldToScreen(se::State& s)
{
    cocos2d::gfx::Camera* cobj = (cocos2d::gfx::Camera*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_renderer_Camera_worldToScreen : Invalid Native Object");
    auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        cocos2d::Vec3 out;
        cocos2d::Vec3 worldPos;
        ok = seval_to_Vec3(args[1], &worldPos);
        SE_PRECONDITION2(ok, false, "Convert arg1 failed!");
        int32_t width = 0;
        ok = seval_to_int32(args[2], &width);
        SE_PRECONDITION2(ok, false, "Convert arg2 failed!");
        int32_t height = 0;
        ok = seval_to_int32(args[3], &height);
        SE_PRECONDITION2(ok, false, "Convert arg3 failed!");
        cobj->worldToScreen(out, worldPos, width, height);
        se::Object* arg0Obj = args[0].toObject();
        arg0Obj->setProperty("x", se::Value(out.x));
        arg0Obj->setProperty("y", se::Value(out.y));
        arg0Obj->setProperty("z", se::Value(out.z));
        s.rval().setObject(arg0Obj);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_renderer_Camera_worldToScreen)

bool jsb_register_renderer_manual(se::Object* global)
{
    // Camera
    __jsb_cocos2d_gfx_Camera_proto->defineFunction("getColor", _SE(js_renderer_Camera_getColor));
    __jsb_cocos2d_gfx_Camera_proto->defineFunction("getRect", _SE(js_renderer_Camera_getRect));
    __jsb_cocos2d_gfx_Camera_proto->defineFunction("extractView", _SE(js_renderer_Camera_extractView));
    __jsb_cocos2d_gfx_Camera_proto->defineFunction("screenToWorld", _SE(js_renderer_Camera_screenToWorld));
    __jsb_cocos2d_gfx_Camera_proto->defineFunction("worldToScreen", _SE(js_renderer_Camera_worldToScreen));

    // Effect
//    __jsb_coco2d_gfx_Effect_proto-

    return true;
}
