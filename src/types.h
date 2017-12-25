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

#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#include "macro.h"
#include "platform.h"

GFX_BEGIN

enum ClearFlag : uint8_t
{
    NONE        = UINT8_C(0x0000),      // No clear flags.
    COLOR       = UINT8_C(0x0001),      // Clear color.
    DEPTH       = UINT8_C(0x0002),      // Clear depth.
    STENCIL     = UINT8_C(0x0004)       // Clear stencil.
};

enum class ComparisonFunc : uint8_t
{
    ALWAYS,
    NEVER,
    LESS,
    LESS_EQUAL,
    GREATOR,
    GREATOR_EQUAL,
    EQUAL,
    NOT_EQUAL
};
typedef ComparisonFunc DepthFunc;
typedef ComparisonFunc StencilFunc;
typedef ComparisonFunc SamplerFunc;

enum class StencilOp : uint8_t
{
    KEEP,
    ZERO,
    REPLACE,
    INCREMENT,
    INCREMENT_WRAP,
    DECREMENT,
    DECREMENT_WRAP,
    INVERT
};

enum class BlendFactor : uint16_t
{
    ZERO,
    ONE,
    SRC_COLOR,
    ONE_MINUS_SRC_COLOR,
    DST_COLOR,
    ONE_MINUS_DST_COLOR,
    SRC_ALPHA,
    ONE_MINUS_SRC_ALPAH,
    DST_ALPHA,
    ONE_MINUS_DST_ALPHA,
    CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA,
    SRC_ALPHA_SATURATE
};
enum class BlendOp : uint8_t
{
    ADD,
    SUBTRACT,
    REV_SUBTRACT
};

enum class CullMode : uint8_t
{
    NONE,
    BACK,
    FRONT,
    FRONT_AND_BACK
};

enum class PrimitiveType : uint8_t
{
    POINTS,
    LINES,
    LINE_LOOP,
    LINE_STRIP,
    TRIANGLES,
    TRIANGLE_STRIP,
    TRIANGLE_FAN
};

enum class Usage : uint16_t
{
    STATIC = GL_STATIC_DRAW,
    DYNAMIC = GL_DYNAMIC_DRAW,
    STREAM = GL_STREAM_DRAW
};

enum class IndexFormat : uint16_t
{
    UINT8 = GL_UNSIGNED_BYTE,
    UINT16 = GL_UNSIGNED_SHORT,
    UINT32 = GL_UNSIGNED_INT// (OES_element_index_uint)
};

// vertex attribute semantic

extern const char* ATTRIB_NAME_POSITION;
extern const char* ATTRIB_NAME_NORMAL;
extern const char* ATTRIB_NAME_TANGENT;
extern const char* ATTRIB_NAME_BITANGENT;
extern const char* ATTRIB_NAME_WEIGHTS;
extern const char* ATTRIB_NAME_JOINTS;
extern const char* ATTRIB_NAME_COLOR;
extern const char* ATTRIB_NAME_COLOR0;
extern const char* ATTRIB_NAME_COLOR1;
extern const char* ATTRIB_NAME_UV;
extern const char* ATTRIB_NAME_UV0;
extern const char* ATTRIB_NAME_UV1;
extern const char* ATTRIB_NAME_UV2;
extern const char* ATTRIB_NAME_UV3;
extern const char* ATTRIB_NAME_UV4;
extern const char* ATTRIB_NAME_UV5;
extern const char* ATTRIB_NAME_UV6;
extern const char* ATTRIB_NAME_UV7;

// vertex attribute type
enum class AttribType : uint16_t
{
    INVALID = 0,
    INT8 = GL_BYTE,
    UINT8 = GL_UNSIGNED_BYTE,
    INT16 = GL_SHORT,
    UINT16 = GL_UNSIGNED_SHORT,
    INT32 = GL_INT,
    UINT32 = GL_UNSIGNED_INT,
    FLOAT32 = GL_FLOAT
};

GFX_END
