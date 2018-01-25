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

#include <string>
#include <vector>
#include "platform/CCGL.h"
#include "base/CCVector.h"
#include "base/CCRef.h"
#include "../macro.h"

GFX_BEGIN

class Pass;

class Technique : public Ref
{
public:
    
    enum class ParameterType : uint8_t
    {
        INT = 0,
        INT2,
        INT3,
        INT4,
        FLOAT,
        FLOAT2,
        FLOAT3,
        FLOAT4,
        COLOR3,
        COLOR4,
        MAT2,
        MAT3,
        MAT4,
        TEXTURE_2D,
        TEXTURE_CUBE
    };
    
    struct Parameter
    {
        std::string name = "";
        GLsizei size = 0;
        ParameterType type = ParameterType::INT;
        void* value = nullptr;
    };
    
    Technique(const std::vector<std::string>& stages,
              const std::vector<Parameter>& parameters,
              const Vector<Pass*>& passes,
              int layer = 0);
    
    void setStages(const std::vector<std::string>& stages);
    
    // Should rename function name in binding codes.
    const Vector<Pass*>& getPasses() const { return _passes; }
    uint32_t getStageIDs() const { return _stageIDs; }
    
    // TODO: add get functions
    
private:
    static uint32_t _genID;
    
    uint32_t _id = 0;
    uint32_t _stageIDs = 0;
    int _layer = 0;
    std::vector<Parameter> _parameters;
    Vector<Pass*> _passes;
};

GFX_END
