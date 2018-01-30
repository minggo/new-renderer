/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

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

#include "BaseRenderer.h"
#include <new>
#include "gfx/CCDeviceGraphics.h"
#include "gfx/CCTexture2D.h"
#include "ProgramLib.h"
#include "View.h"
#include "Scene.h"
#include "Effect.h"
#include "InputAssembler.h"
#include "Pass.h"
#include "Camera.h"

GFX_BEGIN

BaseRenderer::BaseRenderer(DeviceGraphics& device, std::vector<ProgramLib::Template>& programTemplates)
: _device(&device)
{
    _device->retain();
    _programLib = new (std::nothrow) ProgramLib(programTemplates);
}

BaseRenderer::BaseRenderer(DeviceGraphics& device, std::vector<ProgramLib::Template>& programTemplates, Texture2D* defaultTexture)
: _device(&device)
, _defaultTexture(defaultTexture)
{
    _device->retain();
    GFX_SAFE_RETAIN(_defaultTexture);
    _programLib = new (std::nothrow) ProgramLib(programTemplates);
}

BaseRenderer::~BaseRenderer()
{
    _device->release();
    _device = nullptr;
    
    delete _programLib;
    _programLib = nullptr;
    
    GFX_SAFE_RELEASE(_defaultTexture);
    _defaultTexture = nullptr;
}

void BaseRenderer::registerStage(const std::string& name, const StageCallback& callback)
{
    _stage2fn.emplace(std::make_pair(name, callback));
}

// protected functions

void BaseRenderer::render(const View* view, const Scene* scene)
{
    // setup framebuffer
    _device->setFrameBuffer(view->frameBuffer);
    
    // setup viewport
    _device->setViewport(view->rect.x,
                         view->rect.y,
                         view->rect.w,
                         view->rect.h);
    
    // setup clear
    Color4F clearColor;
    if (ClearFlag::COLOR & view->clearFlags)
        clearColor = view->color;
    _device->clear(view->clearFlags, &clearColor, view->depth, view->stencil);
    
    // get all draw items
    _drawItems.clear();
    int modelViewId = -1;
    uint32_t drawItemCount = 0;
    DrawItem drawItem;
    for (const auto& model : scene->getModels())
    {
        modelViewId = model->getViewId();
        if (view->cullingByID)
        {
            if (modelViewId != view->id)
                continue;
        }
        else
        {
            if (-1 == modelViewId)
                continue;
        }
        
        drawItemCount = model->getDrawItemCount();
        for (uint32_t i = 0; i < drawItemCount; ++i)
        {
            model->extractDrawItem(drawItem, i);
            _drawItems.push_back(drawItem);
        }
    }
    
    // dispatch draw items to different stage
    _stageInfos.clear();
    StageItem stageItem;
    StageInfo stageInfo;
    for (const auto& stage : view->stages)
    {
        std::vector<StageItem> stageItems;
        for (const auto& item : _drawItems)
        {
            auto tech = item.effect->getTechnique(stage);
            if (tech)
            {
                stageItem.model = item.model;
                stageItem.ia = item.ia;
                stageItem.effect = item.effect;
                stageItem.defines = item.defines;
                stageItem.technique = tech;
                stageItem.sortKey = -1;
                
                stageItems.push_back(stageItem);
            }
        }
        
        stageInfo.stage = stage;
        stageInfo.items = std::move(stageItems);
        _stageInfos.push_back(std::move(stageInfo));
    }
    
    // render stages
    for (const auto& stageInfo : _stageInfos)
    {
        if (_stage2fn.end() != _stage2fn.find(stageInfo.stage))
        {
            auto& fn = _stage2fn.at(stageInfo.stage);
            fn(*view, stageInfo.items);
        }
    }
}

namespace
{
    Effect::Property type2defaultValue(Effect::Property::Type type)
    {
        Effect::Property ret;
        
        if (Effect::Property::Type::TEXTURE_2D == type ||
            Effect::Property::Type::TEXTURE_CUBE == type ||
            Effect::Property::Type::UNKNOWN == type)
            return ret;

        ret.type = type;
        ret.size = 1;
        uint8_t bytes = 0;
        switch (type)
        {
            case Effect::Property::Type::INT:
                bytes = sizeof(int);
                ret.value = malloc(bytes);
                memset(ret.value, 0, bytes);
                break;
            case Effect::Property::Type::INT2:
                bytes = sizeof(int) * 2;
                ret.value = malloc(bytes);
                memset(ret.value, 0, bytes);
                break;
            case Effect::Property::Type::INT3:
                bytes = sizeof(int) * 3;
                ret.value = malloc(bytes);
                memset(ret.value, 0, bytes);
                break;
            case Effect::Property::Type::INT4:
                bytes = sizeof(int) * 4;
                ret.value = malloc(bytes);
                memset(ret.value, 0, bytes);
                break;
            case Effect::Property::Type::FLOAT:
                bytes = sizeof(float);
                ret.value = malloc(bytes);
                memset(ret.value, 0, bytes);
                break;
            case Effect::Property::Type::FLOAT2:
                bytes = sizeof(float) * 2;
                ret.value = malloc(bytes);
                memset(ret.value, 0, bytes);
                break;
            case Effect::Property::Type::FLOAT3:
                bytes = sizeof(float) * 3;
                ret.value = malloc(bytes);
                memset(ret.value, 0, bytes);
                break;
            case Effect::Property::Type::FLOAT4:
                bytes = sizeof(float) * 4;
                ret.value = malloc(bytes);
                memset(ret.value, 0, bytes);
                break;
            case Effect::Property::Type::COLOR3:
                bytes = sizeof(float) * 3;
                ret.value = malloc(bytes);
                memset(ret.value, 0, bytes);
                break;
            case Effect::Property::Type::COLOR4:
                bytes = sizeof(float) * 4;
                ret.value = malloc(bytes);
                memset(ret.value, 0, bytes);
                *((float*)ret.value + 3) = 1.f;
                break;
            case Effect::Property::Type::MAT2:
                bytes = sizeof(float) * 4;
                ret.value = malloc(bytes);
                memset(ret.value, 0, bytes);
                break;
            case Effect::Property::Type::MAT3:
                bytes = sizeof(float) * 9;
                ret.value = malloc(bytes);
                memset(ret.value, 0, bytes);
                break;
            case Effect::Property::Type::MAT4:
                bytes = sizeof(float) * 16;
                ret.value = malloc(bytes);
                memset(ret.value, 0, bytes);
                break;
//            case Effect::Property::Type::TEXTURE_2D:
//                break;
//            case Effect::Property::Type::TEXTURE_CUBE:
//                break;
                
            default:
                break;
        }
        
        return ret;
    }
    
    void freeDefaultValue(Effect::Property& property)
    {
        free(property.value);
        property.value = nullptr;
        
        property.size = 0;
    }
    
    uint8_t getBytesOfType(Effect::Property::Type type)
    {
        uint8_t bytes = 0;
        switch (type)
        {
            case Effect::Property::Type::INT:
                bytes = sizeof(int);
                break;
            case Effect::Property::Type::INT2:
                bytes = sizeof(int) * 2;
                break;
            case Effect::Property::Type::INT4:
                bytes = sizeof(int) * 4;
                break;
            case Effect::Property::Type::FLOAT:
                bytes = sizeof(float);
                break;
            case Effect::Property::Type::FLOAT2:
                bytes = sizeof(float) * 2;
                break;
            case Effect::Property::Type::FLOAT4:
                bytes = sizeof(float) * 4;
                break;
            case Effect::Property::Type::COLOR4:
                bytes = sizeof(float) * 4;
                break;
            case Effect::Property::Type::MAT2:
                bytes = sizeof(float) * 4;
                break;
            case Effect::Property::Type::MAT4:
                bytes = sizeof(float) * 16;
                break;
            // doesn't support array of these types
            case Effect::Property::Type::INT3:
            case Effect::Property::Type::FLOAT3:
            case Effect::Property::Type::COLOR3:
            case Effect::Property::Type::MAT3:
            case Effect::Property::Type::TEXTURE_2D:
            case Effect::Property::Type::TEXTURE_CUBE:
                    break;
                
            default:
                break;
        }
        
        return bytes;
    }
}

void BaseRenderer::draw(const StageItem& item)
{
    //TODO: get world matrix of node
//    const Mat4& worldMatrix =
    Mat4 worldMatrix;
    _device->setUniformMat4("model", worldMatrix.m);
    
    //TODO: add Mat3
    worldMatrix.inverse();
    worldMatrix.transpose();
    _device->setUniformMat4("normalMatrix", worldMatrix.m);
    
    // set technique uniforms
    auto ia = item.ia;
    for (const auto& prop : item.technique->getParameters())
    {
        Effect::Property param = item.effect->getProperty(prop.name);
        if (nullptr == param.value)
            param = prop;
        
        if (Effect::Property::Type::UNKNOWN == param.type)
        {
            GFX_LOGW("Failed to set technique property %s, value not found", prop.name.c_str());
            continue;
        }
        
        if (nullptr == param.value)
        {
            param = type2defaultValue(prop.type);
            if (Effect::Property::Type::TEXTURE_2D == prop.type)
                param.value = _defaultTexture;
        }
        
        if (Effect::Property::Type::TEXTURE_2D == prop.type ||
            Effect::Property::Type::TEXTURE_CUBE == prop.type)
        {
            if (prop.size != 0)
            {
                if (prop.size != param.size)
                {
                    GFX_LOGW("The length of texture array %d is not correct(expect %d)", param.size, prop.size);
                    continue;
                }
                
                std::vector<int> slots;
                for (int i = 0; i < param.size; ++i)
                    slots.push_back(allocTextureUnit());
                _device->setTextureArray(param.name,
                                         *(const std::vector<Texture *>*)(param.value),
                                         slots);
            }
            else
                _device->setTexture(param.name,
                                    (cocos2d::gfx::Texture *)(param.value),
                                    allocTextureUnit());
        }
        else
        {
            uint8_t bytes = getBytesOfType(prop.type);
            if (0 != param.size)
            {
                if (0 == bytes)
                {
                    GFX_LOGW("Uinform array of color3/int3/float3/mat3 can not be supported!");
                    continue;
                }
                if (bytes * param.size > 64)
                {
                    GFX_LOGW("Uniform array is too long!");
                    continue;
                }
            }
            
            if (Effect::Property::Type::INT == prop.type ||
                Effect::Property::Type::INT2 == prop.type ||
                Effect::Property::Type::INT4 == prop.type)
                _device->setUniformiv(prop.name, bytes, (const int*)param.value);
            else
                _device->setUniformfv(prop.name, bytes, (const float*)param.value);
            
            freeDefaultValue(param);
        }
        
        // for each pass
        for (const auto& pass : item.technique->getPasses())
        {
            // set vertex buffer
            if (ia->_indexBuffer)
                _device->setIndexBuffer(ia->_indexBuffer);
            
            // set primitive type
            _device->setPrimitiveType(ia->_primitiveType);
            
            // set program
            auto program = _programLib->getProgram(pass->_programName, *(item.defines));
            _device->setProgram(program);
            
            // cull mode
            _device->setCullMode(pass->_cullMode);
            
            // blend
            if (pass->_blend)
            {
                _device->enableBlend();
                _device->setBlendFuncSeparate(pass->_blendSrc,
                                              pass->_blendDst,
                                              pass->_blendSrcAlpha,
                                              pass->_blendDstAlpha);
                _device->setBlendEquationSeparate(pass->_blendEq, pass->_blendAlphaEq);
                _device->setBlendColor(pass->_blendColor);
            }
            
            // depth test & write
            if (pass->_depthTest)
            {
                _device->enableDepthTest();
                _device->setDepthFunc(pass->_depthFunc);
            }
            if (pass->_depthWrite)
                _device->enableDepthWrite();
            
            // setencil
            if (pass->_stencilTest)
            {
                _device->enableStencilTest();
                
                // front
                _device->setStencilFuncFront(pass->_stencilFuncFront,
                                             pass->_stencilRefFront,
                                             pass->_stencilMaskFront);
                _device->setStencilOpFront(pass->_stencilFailOpFront,
                                           pass->_stencilZFailOpFront,
                                           pass->_stencilZPassOpFront,
                                           pass->_stencilWriteMaskFront);
                
                // back
                _device->setStencilFuncBack(pass->_stencilFuncBack,
                                            pass->_stencilRefBack,
                                            pass->_stencilMaskBack);
                _device->setStencilOpBack(pass->_stencilFailOpBack,
                                          pass->_stencilZFailOpBack,
                                          pass->_stencilZPassOpBack,
                                          pass->_stencilWriteMaskBack);
                
                // draw pass
                _device->draw(ia->_start, ia->getPrimitiveCount());
                
                resetTextureUint();
            }
        }
    }
}

// private functions

void BaseRenderer::resetTextureUint()
{
    _usedTextureUnits = 0;
}

int BaseRenderer::allocTextureUnit()
{
    int maxTexureUnits = _device->getCapacity().maxTextureUnits;
    if (_usedTextureUnits >= maxTexureUnits)
        GFX_LOGW("Trying to use %d texture uints while this GPU only supports %d", _usedTextureUnits, maxTexureUnits);
    
    return ++_usedTextureUnits;
}

void BaseRenderer::reset()
{
    
}

View* BaseRenderer::requestView()
{
    return new (std::nothrow) View();
}

GFX_END
