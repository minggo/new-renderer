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

#include "CCGFXUtils.h"
#include "macro.h"

#include <stdio.h>

const char* glEnumName(GLenum _enum)
{
#define GLENUM(_ty) case _ty: return #_ty

    switch (_enum)
    {
            GLENUM(GL_TEXTURE);
            GLENUM(GL_RENDERBUFFER);

            GLENUM(GL_INVALID_ENUM);
            GLENUM(GL_INVALID_FRAMEBUFFER_OPERATION);
            GLENUM(GL_INVALID_VALUE);
            GLENUM(GL_INVALID_OPERATION);
            GLENUM(GL_OUT_OF_MEMORY);

            GLENUM(GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
            GLENUM(GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);
            //            GLENUM(GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER);
            //            GLENUM(GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER);
            GLENUM(GL_FRAMEBUFFER_UNSUPPORTED);
    }

#undef GLENUM

    GFX_LOGW("Unknown enum? %x", _enum);
    return "<GLenum?>";
}

