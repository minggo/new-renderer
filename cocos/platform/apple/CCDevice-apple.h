/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef CCDevice_apple_hpp
#define CCDevice_apple_hpp

#include "platform/CCDevice.h"

#import <CoreGraphics/CoreGraphics.h>

#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
#import <AppKit/AppKit.h>
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#import <UIKit/UIKit.h>
#endif

namespace FontUtils {
    typedef struct
    {
        unsigned int height;
        unsigned int width;
        bool         isPremultipliedAlpha;
        bool         hasShadow;
        CGSize       shadowOffset;
        float        shadowBlur;
        float        shadowOpacity;
        bool         hasStroke;
        float        strokeColorR;
        float        strokeColorG;
        float        strokeColorB;
        float        strokeColorA;
        float        strokeSize;
        float        tintColorR;
        float        tintColorG;
        float        tintColorB;
        float        tintColorA;
        
        unsigned char*  data;
        
    } tImageInfo;
    
    NSMutableParagraphStyle* _calculateParagraphStyle(bool enableWrap, int overflow);
    NSTextAlignment _calculateTextAlignment(cocos2d::Device::TextAlign align);
    CGFloat _calculateTextDrawStartWidth(cocos2d::Device::TextAlign align, CGSize realDimensions, CGSize dimensions);
}

#endif /* CCDevice_apple_hpp */
