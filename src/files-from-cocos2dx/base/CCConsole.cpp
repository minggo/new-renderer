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

#include "base/CCConsole.h"

#include <thread>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

#if defined(_MSC_VER) || defined(__MINGW32__)
#include <io.h>
#include <WS2tcpip.h>
#include <Winsock2.h>

#if defined(__MINGW32__)
#include "platform/win32/inet_pton_mingw.h"
#endif

#ifndef bzero
#define bzero(a, b) memset(a, 0, b);
#endif

#else
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#ifndef bzero
#define bzero(a, b) memset(a, 0, b);
#endif

#endif

#include "platform/CCPlatformConfig.h"
#include "base/CCConfiguration.h"
#include "platform/CCFileUtils.h"
//#include "base/ccUtils.h"

bool CC_DLL cc_assert_script_compatible(const char *msg)
{
    //    cocos2d::ScriptEngineProtocol* engine = cocos2d::ScriptEngineManager::getInstance()->getScriptEngine();
    //    if (engine && engine->handleAssert(msg))
    //    {
    //        return true;
    //    }
    return false;
}

NS_CC_BEGIN

/** private functions */
namespace {
#if defined(__MINGW32__)
    // inet
    const char* inet_ntop(int af, const void* src, char* dst, int cnt)
    {
        struct sockaddr_in srcaddr;
        
        memset(&srcaddr, 0, sizeof(struct sockaddr_in));
        memcpy(&(srcaddr.sin_addr), src, sizeof(srcaddr.sin_addr));
        
        srcaddr.sin_family = af;
        if (WSAAddressToStringA((struct sockaddr*) &srcaddr, sizeof(struct sockaddr_in), 0, dst, (LPDWORD) &cnt) != 0)
        {
            return nullptr;
        }
        return dst;
    }
#endif
    
    //
    // Free functions to log
    //
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    void SendLogToWindow(const char *log)
    {
        static const int CCLOG_STRING_TAG = 1;
        // Send data as a message
        COPYDATASTRUCT myCDS;
        myCDS.dwData = CCLOG_STRING_TAG;
        myCDS.cbData = (DWORD)strlen(log) + 1;
        myCDS.lpData = (PVOID)log;
        if (Director::getInstance()->getOpenGLView())
        {
            HWND hwnd = Director::getInstance()->getOpenGLView()->getWin32Window();
            SendMessage(hwnd,
                        WM_COPYDATA,
                        (WPARAM)(HWND)hwnd,
                        (LPARAM)(LPVOID)&myCDS);
        }
    }
#endif
    
    void _log(const char *format, va_list args)
    {
        int bufferSize = MAX_LOG_LENGTH;
        char* buf = nullptr;
        
        do
        {
            buf = new (std::nothrow) char[bufferSize];
            if (buf == nullptr)
                return; // not enough memory
            
            int ret = vsnprintf(buf, bufferSize - 3, format, args);
            if (ret < 0)
            {
                bufferSize *= 2;
                
                delete [] buf;
            }
            else
                break;
            
        } while (true);
        
        strcat(buf, "\n");
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        __android_log_print(ANDROID_LOG_DEBUG, "cocos2d-x debug info", "%s", buf);
        
#elif CC_TARGET_PLATFORM ==  CC_PLATFORM_WIN32
        
        int pos = 0;
        int len = strlen(buf);
        char tempBuf[MAX_LOG_LENGTH + 1] = { 0 };
        WCHAR wszBuf[MAX_LOG_LENGTH + 1] = { 0 };
        
        do
        {
            std::copy(buf + pos, buf + pos + MAX_LOG_LENGTH, tempBuf);
            
            tempBuf[MAX_LOG_LENGTH] = 0;
            
            MultiByteToWideChar(CP_UTF8, 0, tempBuf, -1, wszBuf, sizeof(wszBuf));
            OutputDebugStringW(wszBuf);
            WideCharToMultiByte(CP_ACP, 0, wszBuf, -1, tempBuf, sizeof(tempBuf), nullptr, FALSE);
            printf("%s", tempBuf);
            
            pos += MAX_LOG_LENGTH;
            
        } while (pos < len);
        SendLogToWindow(buf);
        fflush(stdout);
#else
        // Linux, Mac, iOS, etc
        fprintf(stdout, "%s", buf);
        fflush(stdout);
#endif
        
        delete [] buf;
    }
}

void log(const char * format, ...)
{
    va_list args;
    va_start(args, format);
    _log(format, args);
    va_end(args);
}

NS_CC_END
