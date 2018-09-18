#pragma once

#include "Macros.h"

#include <cstdint>

CC_BACKEND_BEGIN

enum class BufferUsage : uint32_t
{
    READ,
    WRITE
};

enum class BufferType : uint32_t
{
    VERTEX,
    INDEX
};

enum class ShaderStage : uint32_t
{
    VERTEX,
    FRAGMENT
};

enum class VertexFormat : uint32_t
{
    FLOAT_R32G32B32A32,
    FLOAT_R32G32B32,
    FLOAT_R32G32,
    FLOAT_R32,
    INT_R32G32B32A32,
    INT_R32G32B32,
    INT_R32G32,
    INT_R32,
    USHORT_R16G16B16A16,
    USHORT_R16G16,
    UNORM_R8G8B8A8,
    UNORM_R8G8
};

enum class TextureFormat : uint32_t
{
    // Four 8-bit normalized unsigned integer components in RGBA order.
    R8G8B8A8,
    // Three 8-bit normalized unsigned integer components in RGB order.
    R8G8B8,
    // One 8-bit normalized unsigned integer component.
    A8,
    // Packed 16-bit format with normalized unsigned integer color components: 5 bits for red,
    // 6 bits for green, 5 bits in blue, packed into 16 bits.
    R5G6B5,
    // Packed 16-bit format with normalized unsigned integer color components: 4 bits each for
    // RGBA, packed into 16 bits.
    R4G4B4A4,
    // Packed 16-bit format with normalized unsigned integer color components: 5 bits each for
    // RGB and 1 bit for alpha, packed into 16 bits.
    R5G5B5A1,
    // A 16-bit depth format with one normallized unsigned integer component, typically used for
    // a depth render target.
    D16
};

enum class IndexFormat : uint32_t
{
    U_BYTE,
    U_SHORT,
    U_INT
};

enum class VertexStepMode : uint32_t
{
    VERTEX,
    INSTANCE
};

enum class LoadOp : uint32_t
{
    CLEAR,
    LOAD
};

enum class PrimitiveType : uint32_t
{
    POINT,
    LINE,
    LINE_STRIP,
    TRIANGLE,
    TRIANGLE_STRIP
};

enum class TextureType: uint32_t
{
    TEXTURE_2D,
    TEXTURE_CUBE
};

enum class SamplerAddressMode: uint32_t
{
    REPEAT,
    MIRROR_REPEAT,
    CLAMP_TO_EDGE
};

enum class SamplerFilter: uint32_t
{
    NONE,
    NEAREST,
    LINEAR
};

enum class StencilOperation: uint32_t
{
    KEEP,
    ZERO,
    REPLACE,
    INVERT,
    INCREMENT_WRAP,
    DECREMENT_WRAP
};

enum class CompareFunction: uint32_t
{
    NEVER,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
    EQUAL,
    NOT_EQUAL,
    ALWAYS
};

enum class BlendOperation: uint32_t
{
    ADD,
    SUBTRACT,
    RESERVE_SUBTRACT
};

enum class BlendFactor: uint32_t
{
    ZERO,
    ONE,
    SRC_COLOR,
    ONE_MINUS_SRC_COLOR,
    SRC_ALPHA,
    ONE_MINUS_SRC_ALPHA,
    DST_COLOR,
    ONE_MINUS_DST_COLOR,
    DST_ALPHA,
    ONE_MINUS_DST_ALPHA,
    SRC_ALPHA_SATURATE,
    BLEND_CLOLOR
};

enum class ColorWriteMask: uint32_t
{
    NONE = 0x00000000,
    RED = 0x00000001,
    GREEN = 0x00000002,
    BLUE = 0x00000004,
    ALPHA = 0x00000008,
    ALL = 0x0000000F
};

CC_BACKEND_END
