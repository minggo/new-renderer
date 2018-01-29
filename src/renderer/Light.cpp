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

#include "Light.h"
#include <new>
#include "gfx/CCDeviceGraphics.h"
#include "gfx/CCTexture2D.h"
#include "gfx/CCRenderBuffer.h"
#include "gfx/CCFrameBuffer.h"

GFX_BEGIN

Light::Light()
{
}

void Light::setColor(float r, float g, float b)
{
    _color.set(r, g, b, 0);
    _colorUniform.set(r * _intensity, g * _intensity, b * _intensity);
}

void Light::setIntensity(float val)
{
    _intensity = val;
    _colorUniform.set(_color.r * _intensity,
                      _color.g * _intensity,
                      _color.b * _intensity);
}

void Light::setSpotAngle(float val)
{
    _spotAngle = val;
    _spotUniform[0] = std::cos(_spotAngle * 0.5f);
}

void Light::setSpotExp(float val)
{
    _spotExp = val;
    _spotUniform[1] = _spotExp;
}

void Light::setShadowType(ShadowType val)
{
    if (ShadowType::NONE == _shadowType &&
        ShadowType::NONE != val)
    {
        _shadowMapDirty = true;
    }
    
    _shadowType = val;
}

void Light::setShadowResolution(uint32_t val)
{
    if (_shadowResolution != val)
    {
        _shadowMapDirty = true;
        _shadowResolution = val;
    }
}

float Light::getShadowMinDepth() const
{
    if (LightType::DIRECTIONAL == _type)
        return 1.0f;
    else
        return _shadowMinDepth;
}

float Light::getShadowMaxDepth() const
{
    if (LightType::DIRECTIONAL == _type)
        return 1.0f;
    else
        return _shadowMaxDepth;
}

void Light::extractView(View& out, const std::vector<std::string>& stages)
{
    out.shadowLight = const_cast<Light*>(this);
    out.rect = { 0, 0, (float)_shadowResolution, (float)_shadowResolution };
    
    // clear options
    out.color.set(1.f, 1.f, 1.f, 1.f);
    out.depth = 1;
    out.stencil = 1;
    out.clearFlags = ClearFlag::COLOR | ClearFlag::DEPTH;
    
    // stage & framebuffer
    out.stages = stages;
    out.frameBuffer = _shadowFrameBuffer;
    
    // view projection matrix
    switch (_type)
    {
        case LightType::SPOT:
            computeSpotLightViewProjMatrix(out.matView, out.matProj);
            break;
        case LightType::DIRECTIONAL:
            computeDirectionalLightViewProjMatrix(out.matView, out.matProj);
            break;
        case LightType::POINT:
            computePointLightViewProjMatrix(out.matView, out.matProj);
            break;
        default:
            GFX_LOGW("Shadow of this light type is not supported");
            break;
    }
    
    // view-porjection
    Mat4::multiply(out.matView, out.matProj, &out.matViewProj);
    out.matInvViewPorj = out.matViewProj.getInversed();
    
    _viewProjMatrix.set(out.matViewProj);
}

void Light::update(DeviceGraphics* device)
{
    updateLightPositionAndDirection();
    
    if (ShadowType::NONE == _shadowType)
        destroyShadowMap();
    else
    {
        destroyShadowMap();
        generateShadowMap(device);
        _shadowMapDirty = false;
    }
}

// private functions

namespace
{
    Mat4 g_tempMat4;
    const Vec3 g_forward(0, 0, -1.f);
}

void Light::updateLightPositionAndDirection()
{
    //TODO: get node world position
    g_tempMat4.transformVector(g_forward, &_directionUniform);
    _positionUniform.set(g_tempMat4.m[12], g_tempMat4.m[13], g_tempMat4.m[14]);
}

void Light::generateShadowMap(DeviceGraphics* device)
{
    _shadowMap = new (std::nothrow) Texture2D();
    if (!_shadowMap)
        return;
    
    _shadowDepthBuffer = new (std::nothrow) RenderBuffer();
    if (!_shadowDepthBuffer)
    {
        _shadowMap->release();
        _shadowMap = nullptr;
        
        return;
    }
    
    _shadowFrameBuffer = new (std::nothrow) FrameBuffer();
    if (!_shadowFrameBuffer)
    {
        _shadowMap->release();
        _shadowDepthBuffer->release();
        _shadowMap = nullptr;
        _shadowDepthBuffer = nullptr;
        
        return;
    }
    
    Texture2D::Options options;
    options.width = _shadowResolution;
    options.height = _shadowResolution;
    options.format = Texture2D::Format::RGBA8;
    options.wrapS = Texture2D::WrapMode::CLAMP;
    options.wrapT = Texture2D::WrapMode::CLAMP;
    _shadowMap->init(device, options);
    
    _shadowDepthBuffer->init(device, RenderBuffer::Format::D16, _shadowResolution, _shadowResolution);
    
    _shadowFrameBuffer->init(device, _shadowResolution, _shadowResolution);
    _shadowFrameBuffer->setColorBuffer(_shadowMap, 0);
    _shadowFrameBuffer->setDepthBuffer(_shadowDepthBuffer);
}

void Light::destroyShadowMap()
{
    if (_shadowMap)
    {
        _shadowMap->release();
        _shadowMap = nullptr;
        
        GFX_SAFE_RELEASE(_shadowDepthBuffer);
        _shadowDepthBuffer = nullptr;
        
        GFX_SAFE_RELEASE(_shadowFrameBuffer);
        _shadowFrameBuffer = nullptr;
    }
}

void Light::computeSpotLightViewProjMatrix(Mat4& matView, Mat4& matProj) const
{
    //TODO: get world rotation and translation matrix
    matView.inverse();
    
    Mat4::createPerspective(_spotAngle * _spotAngleScale,
                            1,
                            _shadowMinDepth,
                            _shadowMaxDepth,
                            &matProj);
}

void Light::computeDirectionalLightViewProjMatrix(Mat4& matView, Mat4& matProj) const
{
    //TODO: get world rotation and translation matrix
    matView.inverse();
    
    uint32_t halfSize = _shadowFustumSize / 2;
    Mat4::createOrthographic(-halfSize, halfSize, -halfSize, halfSize, &matProj);
}

void Light::computePointLightViewProjMatrix(Mat4& matView, Mat4& matProj) const
{
    //TODO
}

GFX_END
