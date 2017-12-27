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

#include <new>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#include "macro.h"
#include "platform/CCGL.h"

GFX_BEGIN

enum ClearFlag : uint8_t
{
    NONE        = UINT8_C(0x0000),      // No clear flags.
    COLOR       = UINT8_C(0x0001),      // Clear color.
    DEPTH       = UINT8_C(0x0002),      // Clear depth.
    STENCIL     = UINT8_C(0x0004)       // Clear stencil.
};

enum class ComparisonFunc : uint16_t
{
    NEVER               = GL_NEVER,
    LESS                = GL_LESS,
    EQUAL               = GL_EQUAL,
    LESS_EQUAL          = GL_LEQUAL,
    GREATER             = GL_GREATER,
    NOT_EQUAL           = GL_NOTEQUAL,
    GREATOR_EQUAL       = GL_GEQUAL,
    ALWAYS              = GL_ALWAYS
};
typedef ComparisonFunc DepthFunc;
typedef ComparisonFunc StencilFunc;
typedef ComparisonFunc SamplerFunc;

enum class StencilOp : uint16_t
{
    ZERO                    = GL_ZERO,
    KEEP                    = GL_KEEP,
    REPLACE                 = GL_REPLACE,
    INCR                    = GL_INCR,
    DECR                    = GL_DECR,
    INVERT                  = GL_INVERT,
    
    // Does these two belongs to stencil operation?
    INCR_WRAP                = GL_INCR_WRAP,
    DECR_WRAP                = GL_DECR_WRAP
};

enum class BlendFactor : uint16_t
{
    ZERO                        = GL_ZERO,
    ONE                         = GL_ONE,
    SRC_COLOR                   = GL_SRC_COLOR,
    ONE_MINUS_SRC_COLOR         = GL_ONE_MINUS_SRC_COLOR,
    SRC_ALPHA                   = GL_SRC_ALPHA,
    ONE_MINUS_SRC_ALPAH         = GL_ONE_MINUS_SRC_ALPHA,
    DST_ALPHA                   = GL_DST_ALPHA,
    ONE_MINUS_DST_ALPHA         = GL_ONE_MINUS_DST_ALPHA,
    DST_COLOR                   = GL_DST_COLOR,
    ONE_MINUS_DST_COLOR         = GL_ONE_MINUS_DST_COLOR,
    SRC_ALPHA_SATURATE          = GL_SRC_ALPHA_SATURATE,
    
    CONSTANT_COLOR              = GL_CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR    = GL_ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA              = GL_CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA    = GL_ONE_MINUS_CONSTANT_ALPHA
};
enum class BlendOp : uint16_t
{
    ADD                 = GL_FUNC_ADD,
    SUBTRACT            = GL_FUNC_SUBTRACT,
    REVERSE_SUBTRACT    = GL_FUNC_REVERSE_SUBTRACT
};

enum class CullMode : uint16_t
{
    NONE                    = GL_NONE,
    BACK                    = GL_BACK,
    FRONT                   = GL_FRONT,
    FRONT_AND_BACK          = GL_FRONT_AND_BACK
};

enum class PrimitiveType : uint16_t
{
    POINTS                  = GL_POINTS,
    LINES                   = GL_LINES,
    LINE_LOOP               = GL_LINE_LOOP,
    LINE_STRIP              = GL_LINE_STRIP,
    TRIANGLES               = GL_TRIANGLES,
    TRIANGLE_STRIP          = GL_TRIANGLE_STRIP,
    TRIANGLE_FAN            = GL_TRIANGLE_FAN
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

// texture filter
enum class TextureFilter : int8_t
{
    NONE = -1,
    NEAREST = 0,
    LINEAR = 1
};

// texture wrap mode
enum class TextureWrapMode : uint16_t
{
    REPEAT = GL_REPEAT,
    CLAMP = GL_CLAMP_TO_EDGE,
    MIRROR = GL_MIRRORED_REPEAT
};

// texture format
enum class TextureFormat : uint8_t
{
    BEGIN = 0,
// compress formats
    RGB_DXT1 = 0,
    RGBA_DXT1 = 1,
    RGBA_DXT3 = 2,
    RGBA_DXT5 = 3,
    RGB_ETC1 = 4,
    RGB_PVRTC_2BPPV1 = 5,
    RGBA_PVRTC_2BPPV1 = 6,
    RGB_PVRTC_4BPPV1 = 7,
    RGBA_PVRTC_4BPPV1 = 8,
//
// normal formats
    A8 = 9,
    L8 = 10,
    L8_A8 = 11,
    R5_G6_B5 = 12,
    R5_G5_B5_A1 = 13,
    R4_G4_B4_A4 = 14,
    RGB8 = 15,
    RGBA8 = 16,
    RGB16F = 17,
    RGBA16F = 18,
    RGB32F = 19,
    RGBA32F = 20,
    R32F = 21,
    _111110F = 22,
    SRGB = 23,
    SRGBA = 24,
//
// depth formats
    D16 = 25,
    D32 = 26,
    D24S8 = 27,
    END = 27
//
};

extern const uint32_t INVALID_UINT32;

GFX_END
