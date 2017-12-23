//
//  types.h
//  Test
//
//  Created by minggo on 12/14/17.
//  Copyright © 2017 cocos. All rights reserved.
//

#pragma once

#include <stdint.h>
#include "macro.h"

CC_BEGIN

enum class ClearFlag : uint8_t
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

CC_END
