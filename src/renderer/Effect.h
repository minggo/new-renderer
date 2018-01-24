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

#pragma once

#include <vector>
#include "base/CCValue.h"
#include "../macro.h"
#include "Technique.h"

GFX_BEGIN

// Define may look like `{ name: 'lightCount', min: 1, max: 4 }`, so it may have many keys.
// FIXME: Property is the same.
typedef ValueMap Define;
typedef ValueMap Property;
typedef Value DefineValue;

class Effect
{
public:
    Effect(const Vector<Technique*>& techniques,
           const std::unordered_map<std::string, Property>& properties,
           const std::vector<Define>& defines);
    
    void clear();
    
    Technique* getTechnique(const std::string& stage) const;
    Property getProperty(const std::string& name) const;
    
    DefineValue getDefine(const std::string& name) const;
    void setDefine(const std::string& name, const DefineValue& value);
    void extractDefines(ValueMap& out) const;
    
private:
    Vector<Technique*> _techniques;
    std::unordered_map<std::string, Property> _properties;
    std::vector<Define> _defines;
};

GFX_END
