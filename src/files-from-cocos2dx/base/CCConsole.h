/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.

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

#ifndef __CCCONSOLE_H__
#define __CCCONSOLE_H__
/// @cond DO_NOT_SHOW

#if defined(_MSC_VER) || defined(__MINGW32__)
#include <BaseTsd.h>
#include <WinSock2.h>

#ifndef __SSIZE_T
#define __SSIZE_T
typedef SSIZE_T ssize_t;
#endif // __SSIZE_T

#else
#include <sys/select.h>
#endif

#include <thread>
#include <vector>
#include <map>
#include <functional>
#include <string>
#include <mutex>
#include <stdarg.h>

#include "base/CCRef.h"
#include "base/ccMacros.h"
#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

/// The max length of CCLog message.
static const int MAX_LOG_LENGTH = 16*1024;

/**
 @brief Output Debug message.
 */
void CC_DLL log(const char * format, ...) CC_FORMAT_PRINTF(1, 2);

NS_CC_END

/// @endcond
#endif /* defined(__CCCONSOLE_H__) */
