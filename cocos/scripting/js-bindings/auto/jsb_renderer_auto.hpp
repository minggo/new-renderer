#pragma once
#include "base/ccConfig.h"

#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"

extern se::Object* __jsb_cocos2d_gfx_View_proto;
extern se::Class* __jsb_cocos2d_gfx_View_class;

bool js_register_cocos2d_gfx_View(se::Object* obj);
bool register_all_renderer(se::Object* obj);
SE_DECLARE_FUNC(js_renderer_View_View);

extern se::Object* __jsb_cocos2d_gfx_Camera_proto;
extern se::Class* __jsb_cocos2d_gfx_Camera_class;

bool js_register_cocos2d_gfx_Camera(se::Object* obj);
bool register_all_renderer(se::Object* obj);
SE_DECLARE_FUNC(js_renderer_Camera_getDepth);
SE_DECLARE_FUNC(js_renderer_Camera_setFov);
SE_DECLARE_FUNC(js_renderer_Camera_getFrameBuffer);
SE_DECLARE_FUNC(js_renderer_Camera_setStencil);
SE_DECLARE_FUNC(js_renderer_Camera_getOrthoHeight);
SE_DECLARE_FUNC(js_renderer_Camera_getStencil);
SE_DECLARE_FUNC(js_renderer_Camera_setFrameBuffer);
SE_DECLARE_FUNC(js_renderer_Camera_setFar);
SE_DECLARE_FUNC(js_renderer_Camera_setRect);
SE_DECLARE_FUNC(js_renderer_Camera_setClearFlags);
SE_DECLARE_FUNC(js_renderer_Camera_getFar);
SE_DECLARE_FUNC(js_renderer_Camera_getType);
SE_DECLARE_FUNC(js_renderer_Camera_setNear);
SE_DECLARE_FUNC(js_renderer_Camera_setStages);
SE_DECLARE_FUNC(js_renderer_Camera_setOrthoHeight);
SE_DECLARE_FUNC(js_renderer_Camera_setDepth);
SE_DECLARE_FUNC(js_renderer_Camera_getStages);
SE_DECLARE_FUNC(js_renderer_Camera_getFov);
SE_DECLARE_FUNC(js_renderer_Camera_setColor);
SE_DECLARE_FUNC(js_renderer_Camera_getNear);
SE_DECLARE_FUNC(js_renderer_Camera_getClearFlags);
SE_DECLARE_FUNC(js_renderer_Camera_Camera);

