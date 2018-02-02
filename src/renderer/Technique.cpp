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

#include "Technique.h"
#include "Config.h"
#include "Pass.h"
#include "gfx/CCTexture.h"
#include "gfx/CCTexture2D.h"

GFX_BEGIN

// implementation of Parameter

uint8_t Technique::Parameter::elementsOfType[] = {
    1, // INT
    2, // INT2
    3, // INT3
    4, // INT4
    1, // FLOAT
    2, // FLOAT2
    3, // FLOAT3
    4, // FLOAT4
    3, // COLOR3
    4, // COLOR4
    4, // MAT2
    9, // MAT3
    16,// MAT4
    1, // TEXTURE_2D
    1, // TEXTURE_CUBE
    0, // UNKNOWN
};

uint8_t Technique::Parameter::getElements(Type type)
{
    return Parameter::elementsOfType[(int)type];
}


Technique::Parameter Technique::Parameter::createDefault(Type type)
{
    Parameter ret;
    ret._type = type;
    
    if (Type::TEXTURE_2D == ret._type ||
        Type::TEXTURE_CUBE == ret._type ||
        Type::UNKNOWN == ret._type)
        return ret;
    
    uint8_t elements = Parameter::getElements(type);
    switch (type)
    {
        case Type::INT:
        case Type::INT2:
        case Type::INT3:
        case Type::INT4:
            ret._bytes = sizeof(int) * elements;
            break;
        case Type::FLOAT:
        case Type::FLOAT2:
        case Type::FLOAT3:
        case Type::FLOAT4:
        case Type::COLOR3:
        case Type::COLOR4:
        case Type::MAT2:
        case Type::MAT3:
        case Type::MAT4:
            ret._bytes = sizeof(float) * elements;
            break;
        default:
            break;
    }
    
    ret._count = 1;
    ret._value = malloc(ret._bytes);
    memset(ret._value, 0, ret._bytes);
    if (Type::COLOR4 == type)
        *((float*)(ret._value) + 3) = 1.0f;
    
    return ret;
}

Technique::Parameter::Parameter()
{}

Technique::Parameter::Parameter(const std::string& name, Type type, int* value, uint8_t count)
: _name(name)
, _type(type)
, _count(count)
{
    uint8_t bytes = sizeof(int);
    switch (_type)
    {
        case Type::INT:
            bytes *= _count;
            break;
        case Type::INT2:
            bytes *= 2 * _count;
            break;
        case Type::INT3:
            bytes *= 3 * _count;
            break;
        case Type::INT4:
            bytes *= 4 * _count;
            break;
        default:
            GFX_LOGW("This constructor only supports INT/INT2/INT3/INT4.");
            return;
            break;
    }
    
    if (value)
    {
        _value = malloc(bytes);
        if (_value)
            memcpy(_value, value, bytes);
    }
}

Technique::Parameter::Parameter(const std::string& name, Type type, float* value, uint8_t count)
: _name(name)
, _type(type)
, _count(count)
{
    uint16_t bytes = sizeof(float);
    switch (_type)
    {
        case Type::FLOAT:
            bytes *= _count;
            break;
        case Type::FLOAT2:
            bytes *= 2 * _count;
            break;
        case Type::FLOAT3:
            bytes *= 3 * _count;
            break;
        case Type::FLOAT4:
            bytes *= 4 * _count;
            break;
        case Type::MAT2:
            bytes *= 4 * _count;
            break;
        case Type::MAT3:
            bytes *= 9 * _count;
            break;
        case Type::MAT4:
            bytes *= 16 * _count;
            break;
            
        default:
            GFX_LOGW("This constructor only supports FLAOT/FLOAT2/FLOAT3/FLOAT4/MAT2/MAT3/MAT4.");
            return;
            break;
    }
    
    if (value)
    {
        _bytes = bytes;
        _value = malloc(_bytes);
        if (_value)
            memcpy(_value, value, _bytes);
    }
}

Technique::Parameter::Parameter(const std::string& name, Texture2D* value)
: _name(name)
, _count(1)
, _type(Type::TEXTURE_2D)
{
    if (value)
    {
        auto tempVec = new Vector<Texture*>();
        tempVec->pushBack(value);
        _value = tempVec;
    }
}

Technique::Parameter::Parameter(const std::string& name, const std::vector<Texture2D*>& textures)
: _name(name)
, _count(textures.size())
, _type(Type::TEXTURE_2D)
{
    if (textures.empty())
        return;
    
    size_t size = textures.size();
    _value = malloc(sizeof(void*) * size);
    Texture2D* texture = (Texture2D*)_value;
    for (size_t i = 0; i < size; ++i)
    {
        texture = textures[i];
        texture++;
    }
    
    _bytes *= size;
}

Technique::Parameter::Parameter(Parameter&& rh)
{
    if (this == &rh)
        return;
    
    freeValue();
    
    _name = rh._name;
    _type = rh._type;
    _value = rh._value;
    _count = rh._count;
    _bytes = rh._bytes;
    
    rh._value = nullptr;
}

Technique::Parameter::Parameter(const Parameter& rh)
{
    freeValue();
    copyValue(rh);
}

Technique::Parameter::~Parameter()
{
    freeValue();
}

Technique::Parameter& Technique::Parameter::operator=(const Parameter& rh)
{
    freeValue();
    copyValue(rh);
    
    return *this;
}

std::vector<Texture*> Technique::Parameter::getTextureArray() const
{
    std::vector<Texture*> ret;
    if (Type::TEXTURE_2D != _type &&
        Type::TEXTURE_CUBE != _type)
        return ret;
    
    Texture* texture = (Texture*)_value;
    for (int i = 0; i < _count; ++i)
    {
        ret.push_back(texture);
        ++texture;
    }
    
    return ret;
}

void Technique::Parameter::setTexture2D(cocos2d::gfx::Texture2D *texture)
{
    freeValue();
    
    _value = malloc(sizeof(void*));
    _value = texture;
    GFX_SAFE_RETAIN(texture);
    
    _type = Type::TEXTURE_2D;
    _count = 1;
}

void Technique::Parameter::copyValue(const Parameter& rh)
{
    _name = rh._name;
    _type = rh._type;
    _count = rh._count;
    _bytes = rh._bytes;
    
    if (!_value && !rh._value)
        memcpy(_value, rh._value, _bytes);
    
    _value = malloc(_bytes);
    if (Type::TEXTURE_2D == _type ||
        Type::TEXTURE_CUBE == _type)
    {
        Texture* texture = static_cast<Texture*>(_value);
        for (uint8_t i = 0; i < _count; ++i)
        {
            GFX_SAFE_RETAIN(texture);
            ++texture;
        }
    }
}

void Technique::Parameter::freeValue()
{
    if (_value)
    {
        if (Type::TEXTURE_2D == _type ||
            Type::TEXTURE_CUBE == _type)
        {
            Texture* texture = static_cast<Texture*>(_value);
            for (int i = 0; i < _count; ++i)
            {
                GFX_SAFE_RELEASE(texture);
                ++texture;
            }
        }
        
        free(_value);
        _value = nullptr;
    }
}

// implementation of Technique

uint32_t Technique::_genID = 0;

Technique::Technique(const std::vector<std::string>& stages,
                     const std::vector<Parameter>& parameters,
                     const Vector<Pass*>& passes,
                     int layer)
: _id(_genID++)
, _stageIDs(Config::getStageIDs(stages))
, _parameters(parameters)
, _passes(passes)
, _layer(layer)
{
    GFX_LOGD("Technique construction: %p", this);
}

Technique::~Technique()
{
    GFX_LOGD("Technique destruction: %p", this);
}

void Technique::setStages(const std::vector<std::string>& stages)
{
    _stageIDs = Config::getStageIDs(stages);
}

GFX_END
