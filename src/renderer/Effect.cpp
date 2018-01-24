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

#include "Effect.h"
#include "Config.h"

GFX_BEGIN

Effect::Effect(const Vector<Technique*>& techniques,
               const std::unordered_map<std::string, Property>& properties,
               const std::vector<Define>& defines)
: _techniques(techniques)
, _properties(properties)
, _defines(defines)
{
}

void Effect::clear()
{
    _techniques.clear();
    _properties.clear();
    _defines.clear();
}

Technique* Effect::getTechnique(const std::string& stage) const
{
    int stageID = Config::getStageID(stage);
    if (-1 == stageID)
        return nullptr;
    
    for (const auto& tech : _techniques)
    {
        if (tech->getStageIDs() & stageID)
            return tech;
    }
    
    return nullptr;
}

Property Effect::getProperty(const std::string& name) const
{
    if (_properties.end() != _properties.find(name))
        return _properties.at(name);
    else
        return Property();
}

DefineValue Effect::getDefine(const std::string& name) const
{
    for (const auto& def : _defines)
    {
        if (name == def.at("name").asString())
            return def.at("value");
    }
    
    GFX_LOGW("Failed to set define %s, define not found.", name.c_str());
    return Value::Null;
}

void Effect::setDefine(const std::string& name, const DefineValue& value)
{
    for (auto& def : _defines)
    {
        if (name == def.at("name").asString())
        {
            def["value"] = value;
            return;
        }
    }
}

ValueMap* Effect::extractDefines(ValueMap& out) const
{
    for (auto& def : _defines)
        out[def.at("name").asString()] = def.at("value");
    
    return &out;
}

GFX_END
