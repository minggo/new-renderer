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

#include "ProgramLib.h"

#include <regex>
#include <string>
#include <sstream>
#include <iostream>

namespace {
    uint32_t _shdID = 0;

    std::string generateDefines(std::)
    {

    }


    using RegexReplaceCallback = std::function<std::string(const std::match_results<std::string::const_iterator>&)>;

    static std::string regexReplaceString(const std::string& text, const std::string& pattern, const RegexReplaceCallback& replaceCallback)
    {
        std::string ret = text;
        std::regex re(pattern);

        std::string::const_iterator text_iter = text.cbegin();
        std::match_results<std::string::const_iterator> results;

        size_t start = 0;
        size_t offset = 0;
        while (std::regex_search(text_iter, text.end(), results, re))
        {
            offset = start + results.position();
            std::string replacement = replaceCallback(results);
            ret = ret.replace(offset, results.length(), replacement);
            start = offset + replacement.length();

            text_iter = results[0].second;
        }

        return ret;
    }

    std::string unrollLoops(const std::string& text)
    {
        auto func = [](const std::match_results<std::string::const_iterator>& results) -> std::string {
            assert(results.size() == 5);
            std::string snippet = results[4].str();
            std::string replacePatternStr = "\\{" + results[1].str() + "\\}";
            std::regex replacePattern(replacePatternStr);

            int32_t parsedBegin = atoi(results[2].str().c_str());
            int32_t parsedEnd = atoi(results[3].str().c_str());
            if (parsedBegin < 0 || parsedEnd < 0)
            {
                GFX_LOGE("Unroll For Loops Error: begin and end of range must be an int num.");
            }

            std::string unroll;
            for (int32_t i = parsedBegin; i < parsedEnd; ++i)
            {
                std::string replaceFormat = std::to_string(i);
                unroll += std::regex_replace(snippet, replacePattern, replaceFormat);
            }
            return unroll;
        };

        return regexReplaceString(text, "#pragma for (\\w+) in range\\(\\s*(\\d+)\\s*,\\s*(\\d+)\\s*\\)([\\s\\S]+?)#pragma endFor", func);
    }
}

std::string test_unrollLoops(const std::string& text)
{
    return unrollLoops(text);
}

GFX_BEGIN

ProgramLib::ProgramLib()
{

}

void ProgramLib::define(const std::string& name, const std::string& vert, const std::string& frag, std::vector<Option>& defines)
{
    auto iter = _templates.find(name);
    if (iter != _templates.end())
    {
        GFX_LOGW("Failed to define shader %s: already exists.", name.c_str());
        return;
    }

    uint32_t id = ++_shdID;

    // calculate option mask offset
    uint32_t offset = 0;
    for (auto& def : defines)
    {
        def._offset = offset;

        uint32_t cnt = 1;

        if (def.min != -1 && def.max != -1) {
            cnt = (uint32_t)std::ceil((def.max - def.min) * 0.5);

            def._map = std::bind(&Option::_map_1, def, std::placeholders::_1);
        } else {
            def._map = std::bind(&Option::_map_2, def, std::placeholders::_1);
        }

        offset += cnt;

        def._offset = offset;
    }

    std::string newVert = _precision + vert;
    std::string newFrag = _precision + frag;

    // store it
    _templates[name] = {
        id,
        name,
        newVert,
        newFrag,
        defines
    };
}

uint32_t ProgramLib::getKey(const std::string& name, const std::unordered_map<std::string, Option>& defines)
{
    auto iter = _templates.find(name);
    assert(iter != _templates.end());

    const auto& tmpl = iter->second;
    int32_t key = 0;
    for (const auto& tmplDefs : tmpl.defines) {
        auto iter2 = defines.find(tmplDefs.name);
        if (iter2 == defines.end()) {
            continue;
        }
        const auto& value = iter2->second;
        key |= tmplDefs._map(100); //FIXME:
    }

    return key << 8 | tmpl.id;
}

Program* ProgramLib::getProgram(const std::string& name, const std::unordered_map<std::string, Option>& defines)
{
    uint32_t key = getKey(name, defines);
    auto iter = _cache.find(key);
    if (iter != _cache.end()) {
        return iter->second;
    }

    Program* program = nullptr;
    // get template
//    let tmpl = _templates[name];
//    let customDef = _generateDefines(defines) + '\n';
//    let vert = _replaceMacroNums(tmpl.vert, defines);
//    vert = customDef + _unrollLoops(vert);
//    let frag = _replaceMacroNums(tmpl.frag, defines);
//    frag = customDef + _unrollLoops(frag);
//
//    program = new gfx.Program(this._device, {
//        vert,
//        frag
//    });
//    program.link();
//    _cache[key] = program;

    return program;
}

GFX_END
