/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.

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

#include "config.hpp"

#if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_SM
#include "sm/SeApi.h"
#endif

#if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_V8
#include "v8/SeApi.h"
#endif

#if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_JSC
#include "jsc/SeApi.h"
#endif

#if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_CHAKRACORE
#include "chakracore/SeApi.h"
#endif

#include "Value.hpp"
#include "Object.hpp"
#include "State.hpp"
#include "HandleObject.hpp"
#include "MappingUtils.hpp"
