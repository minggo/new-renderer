#pragma once
#include "base/ccConfig.h"

#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"

extern se::Object* __jsb_cocos2d_gfx_GraphicsHandle_proto;
extern se::Class* __jsb_cocos2d_gfx_GraphicsHandle_class;

bool js_register_cocos2d_gfx_GraphicsHandle(se::Object* obj);
bool register_all_gfx(se::Object* obj);
SE_DECLARE_FUNC(js_gfx_GraphicsHandle_getHandle);
SE_DECLARE_FUNC(js_gfx_GraphicsHandle_GraphicsHandle);

extern se::Object* __jsb_cocos2d_gfx_IndexBuffer_proto;
extern se::Class* __jsb_cocos2d_gfx_IndexBuffer_class;

bool js_register_cocos2d_gfx_IndexBuffer(se::Object* obj);
bool register_all_gfx(se::Object* obj);
SE_DECLARE_FUNC(js_gfx_IndexBuffer_getBytesPerIndex);
SE_DECLARE_FUNC(js_gfx_IndexBuffer_getCount);
SE_DECLARE_FUNC(js_gfx_IndexBuffer_getFormat);
SE_DECLARE_FUNC(js_gfx_IndexBuffer_IndexBuffer);

extern se::Object* __jsb_cocos2d_gfx_VertexBuffer_proto;
extern se::Class* __jsb_cocos2d_gfx_VertexBuffer_class;

bool js_register_cocos2d_gfx_VertexBuffer(se::Object* obj);
bool register_all_gfx(se::Object* obj);
SE_DECLARE_FUNC(js_gfx_VertexBuffer_getCount);
SE_DECLARE_FUNC(js_gfx_VertexBuffer_getFormat);
SE_DECLARE_FUNC(js_gfx_VertexBuffer_VertexBuffer);

extern se::Object* __jsb_cocos2d_gfx_DeviceGraphics_proto;
extern se::Class* __jsb_cocos2d_gfx_DeviceGraphics_class;

bool js_register_cocos2d_gfx_DeviceGraphics(se::Object* obj);
bool register_all_gfx(se::Object* obj);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setTexture);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setBlendFuncSeparate);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_enableBlend);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setPrimitiveType);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setBlendEquationSeparate);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setIndexBuffer);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setProgram);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setFrameBuffer);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setStencilFunc);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setBlendColor);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setScissor);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setVertexBuffer);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_enableDepthWrite);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setTextureArray);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setStencilOpBack);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setViewport);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_draw);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setDepthFunc);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_enableDepthTest);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setBlendEquation);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setStencilFuncFront);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setStencilOpFront);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setStencilFuncBack);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setBlendFunc);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setCullMode);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_supportGLExtension);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_setStencilOp);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_enableStencilTest);
SE_DECLARE_FUNC(js_gfx_DeviceGraphics_getInstance);

extern se::Object* __jsb_cocos2d_gfx_FrameBuffer_proto;
extern se::Class* __jsb_cocos2d_gfx_FrameBuffer_class;

bool js_register_cocos2d_gfx_FrameBuffer(se::Object* obj);
bool register_all_gfx(se::Object* obj);
SE_DECLARE_FUNC(js_gfx_FrameBuffer_setColorBuffer);
SE_DECLARE_FUNC(js_gfx_FrameBuffer_setStencilBuffer);
SE_DECLARE_FUNC(js_gfx_FrameBuffer_getDepthBuffer);
SE_DECLARE_FUNC(js_gfx_FrameBuffer_setDepthStencilBuffer);
SE_DECLARE_FUNC(js_gfx_FrameBuffer_getStencilBuffer);
SE_DECLARE_FUNC(js_gfx_FrameBuffer_setColorBuffers);
SE_DECLARE_FUNC(js_gfx_FrameBuffer_getColorBuffers);
SE_DECLARE_FUNC(js_gfx_FrameBuffer_setDepthBuffer);
SE_DECLARE_FUNC(js_gfx_FrameBuffer_getDepthStencilBuffer);
SE_DECLARE_FUNC(js_gfx_FrameBuffer_FrameBuffer);

extern se::Object* __jsb_cocos2d_gfx_RenderTarget_proto;
extern se::Class* __jsb_cocos2d_gfx_RenderTarget_class;

bool js_register_cocos2d_gfx_RenderTarget(se::Object* obj);
bool register_all_gfx(se::Object* obj);

extern se::Object* __jsb_cocos2d_gfx_RenderBuffer_proto;
extern se::Class* __jsb_cocos2d_gfx_RenderBuffer_class;

bool js_register_cocos2d_gfx_RenderBuffer(se::Object* obj);
bool register_all_gfx(se::Object* obj);
SE_DECLARE_FUNC(js_gfx_RenderBuffer_init);
SE_DECLARE_FUNC(js_gfx_RenderBuffer_create);
SE_DECLARE_FUNC(js_gfx_RenderBuffer_RenderBuffer);

extern se::Object* __jsb_cocos2d_gfx_Texture_proto;
extern se::Class* __jsb_cocos2d_gfx_Texture_class;

bool js_register_cocos2d_gfx_Texture(se::Object* obj);
bool register_all_gfx(se::Object* obj);
SE_DECLARE_FUNC(js_gfx_Texture_getWidth);
SE_DECLARE_FUNC(js_gfx_Texture_getHeight);
SE_DECLARE_FUNC(js_gfx_Texture_getTarget);

extern se::Object* __jsb_cocos2d_gfx_Texture2D_proto;
extern se::Class* __jsb_cocos2d_gfx_Texture2D_class;

bool js_register_cocos2d_gfx_Texture2D(se::Object* obj);
bool register_all_gfx(se::Object* obj);
SE_DECLARE_FUNC(js_gfx_Texture2D_updateImage);
SE_DECLARE_FUNC(js_gfx_Texture2D_init);
SE_DECLARE_FUNC(js_gfx_Texture2D_updateSubImage);
SE_DECLARE_FUNC(js_gfx_Texture2D_update);
SE_DECLARE_FUNC(js_gfx_Texture2D_create);
SE_DECLARE_FUNC(js_gfx_Texture2D_Texture2D);

extern se::Object* __jsb_cocos2d_gfx_Program_proto;
extern se::Class* __jsb_cocos2d_gfx_Program_class;

bool js_register_cocos2d_gfx_Program(se::Object* obj);
bool register_all_gfx(se::Object* obj);
SE_DECLARE_FUNC(js_gfx_Program_isLinked);
SE_DECLARE_FUNC(js_gfx_Program_getID);
SE_DECLARE_FUNC(js_gfx_Program_init);
SE_DECLARE_FUNC(js_gfx_Program_link);
SE_DECLARE_FUNC(js_gfx_Program_Program);

