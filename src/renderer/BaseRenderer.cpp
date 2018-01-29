/****************************************************************************
 Copyright (c) 2018 Chukong Technologies
 
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
#include "ProgramLib.h"
#include "View.h"
#include "Scene.h"
#include "Effect.h"
#include "InputAssembler.h"

GFX_BEGIN

BaseRenderer::BaseRenderer(DeviceGraphics& device, std::vector<ProgramLib::Template>& programTemplates)
: _device(&device)
{
    _device->retain();
    _programLib = new (std::nothrow) ProgramLib(programTemplates);
}

BaseRenderer::~BaseRenderer()
{
    _device->release();
    _device = nullptr;
    
    delete _programLib;
    _programLib = nullptr;
}

// protected functions

void BaseRenderer::render(const View* view, const Scene* scene)
{
    // setup framebuffer
    _device->setFrameBuffer(view->frameBuffer);
    
    // setup viewport
    _device->setViewport(view->rect.origin.x,
                         view->rect.origin.y,
                         view->rect.size.width,
                         view->rect.size.height);
    
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
        switch (type)
        {
            case Effect::Property::Type::INT:
                break;
            case Effect::Property::Type::INT2:
                break;
            case Effect::Property::Type::INT3:
                break;
            case Effect::Property::Type::INT4:
                break;
            case Effect::Property::Type::FLOAT:
                break;
            case Effect::Property::Type::FLOAT2:
                break;
            case Effect::Property::Type::FLOAT3:
                break;
            case Effect::Property::Type::FLOAT4:
                break;
            case Effect::Property::Type::COLOR3:
                break;
            case Effect::Property::Type::COLOR4:
                break;
            case Effect::Property::Type::MAT2:
                break;
            case Effect::Property::Type::MAT3:
                break;
            case Effect::Property::Type::MAT4:
                break;
            case Effect::Property::Type::TEXTURE_2D:
                break;
            case Effect::Property::Type::TEXTURE_CUBE:
                break;
                
            default:
                break;
        }
        
        return ret;
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
    for (const auto& prop : item.technique->getParameters())
    {
        Effect::Property param = item.effect->getProperty(prop.name);
        if (nullptr == param.value)
            param = prop;
        
        if (nullptr == param.value)
            param = type2defaultValue(prop.type);
    }
}

void BaseRenderer::registerState(const std::string& name, const StageCallback& callback)
{
    _stage2fn.emplace(std::make_pair(name, callback));
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
