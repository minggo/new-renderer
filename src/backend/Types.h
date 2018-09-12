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
    R5G5B5A1
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

enum class SamplerAddressMode
{
    REPEAT,
    MIRROR_REPEAT,
    CLAMP_TO_EDGE
};

enum class SamplerFilter
{
    NEAREST,
    LINEAR
};

enum class StencilOperation
{
    KEEP,
    ZERO,
    REPLACE,
    INVERT,
    INCREMENT_WRAP,
    DECREMENT_WRAP
};

enum class CompareFunction
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

CC_BACKEND_END
