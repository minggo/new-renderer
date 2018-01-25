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

#include "../macro.h"
#include "base/CCRef.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

GFX_BEGIN

class DeviceGraphics;
class Program;

class ProgramLib : public Ref
{
public:
    struct Option
    {
        std::string name;
        int32_t min = -1;
        int32_t max = -1;
        int32_t _offset = 0;
        int32_t _map_1(int32_t value)
        {
            return (value - min) << _offset;
        }
        int32_t _map_2(int32_t value)
        {
            if (value != -1) {
                return 1 << _offset;
            }
            return 0;
        }
        std::function<int32_t(int32_t)> _map;
    };

    struct Template
    {
        uint32_t id;
        std::string name;
        std::string vert;
        std::string frag;
        std::vector<Option> defines;
    };

    ProgramLib();

    void define(const std::string& name, const std::string& vert, const std::string& frag, std::vector<Option>& defines);
    uint32_t getKey(const std::string& name, const std::unordered_map<std::string, Option>& defines);
    Program* getProgram(const std::string& name, const std::unordered_map<std::string, Option>& defines);

private:
    DeviceGraphics* _device = nullptr;
    const char* _precision = "precision highp float;\n";
    std::unordered_map<std::string, Template> _templates;
    std::unordered_map<uint32_t, Program*> _cache;
};

GFX_END
