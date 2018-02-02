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
#include "INode.h"
#include "Model.h"

GFX_BEGIN

BaseRenderer::BaseRenderer()
{}

BaseRenderer::~BaseRenderer()
{
    _device->release();
    _device = nullptr;
    
    delete _programLib;
    _programLib = nullptr;
    
    GFX_SAFE_RELEASE(_defaultTexture);
    _defaultTexture = nullptr;
}

bool BaseRenderer::init(DeviceGraphics* device, std::vector<ProgramLib::Template>& programTemplates)
{
    _device = device;
    _device->retain();
    _programLib = new (std::nothrow) ProgramLib(programTemplates);
    return true;
}

bool BaseRenderer::init(DeviceGraphics* device, std::vector<ProgramLib::Template>& programTemplates, Texture2D* defaultTexture)
{
    _device = device;
    _device->retain();
    _defaultTexture = defaultTexture;
    GFX_SAFE_RETAIN(_defaultTexture);
    _programLib = new (std::nothrow) ProgramLib(programTemplates);
    return true;
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
                stageItem.node = item.node;
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
            fn(view, stageInfo.items);
        }
    }
}

void BaseRenderer::draw(const StageItem& item)
{
    //TODO: get world matrix of node
//    const Mat4& worldMatrix =

    Mat4 worldMatrix = item.node->getWorldMatrix();
    //TODO: Mat4 worldMatrix = item.model->getWorldMatrix();
    _device->setUniformMat4("model", worldMatrix.m);
    
    //TODO: add Mat3
    worldMatrix.inverse();
    worldMatrix.transpose();
    _device->setUniformMat4("normalMatrix", worldMatrix.m);
    
    // set technique uniforms
    auto ia = item.ia;
    Technique::Parameter::Type propType = Technique::Parameter::Type::UNKNOWN;
    for (const auto& param : item.technique->getParameters())
    {
        Effect::Property* prop = const_cast<Effect::Property*>(&item.effect->getProperty(param.getName()));
        
        if (Effect::Property::Type::UNKNOWN == prop->getType())
            *prop = param;
        
        if (nullptr == prop->getValue())
        {
            *prop = Effect::Property(param.getName(), param.getType());
            
            if (Effect::Property::Type::TEXTURE_2D == param.getType())
                prop->setTexture(_defaultTexture);
        }
        
        if (nullptr == prop->getValue())
        {
            GFX_LOGW("Failed to set technique property %s, value not found", param.getName().c_str());
            continue;
        }
        
        propType = prop->getType();
        if (Effect::Property::Type::TEXTURE_2D == propType ||
            Effect::Property::Type::TEXTURE_CUBE == propType)
        {
            uint8_t count = prop->getCount();
            if (0 != count)
            {
                if (count != param.getCount())
                {
                    GFX_LOGW("The length of texture array %d is not correct(expect %d)", count, param.getCount());
                    continue;
                }
                
                std::vector<int> slots;
                for (int i = 0; i < count; ++i)
                    slots.push_back(allocTextureUnit());
                _device->setTextureArray(prop->getName(),
                                         std::move(prop->getTextureArray()),
                                         slots);
            }
            else
                _device->setTexture(prop->getName(),
                                    (cocos2d::gfx::Texture *)(prop->getValue()),
                                    allocTextureUnit());
        }
        else
        {
            if (0 != prop->getCount())
            {
                if (Technique::Parameter::Type::COLOR3 == propType ||
                    Technique::Parameter::Type::INT3 == propType ||
                    Technique::Parameter::Type::FLOAT3 == propType ||
                    Technique::Parameter::Type::MAT3 == propType)
                {
                    GFX_LOGW("Uinform array of color3/int3/float3/mat3 can not be supported!");
                    continue;
                }
                
                uint8_t size = Technique::Parameter::getElements(propType);
                if (size * prop->getCount() > 64)
                {
                    GFX_LOGW("Uniform array is too long!");
                    continue;
                }
            }
            
            uint16_t bytes = prop->getBytes();
            if (Effect::Property::Type::INT == propType ||
                Effect::Property::Type::INT2 == propType ||
                Effect::Property::Type::INT4 == propType)
                _device->setUniformiv(param.getName(), bytes, (const int*)prop->getValue());
            else
                _device->setUniformfv(param.getName(), bytes, (const float*)prop->getValue());
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
