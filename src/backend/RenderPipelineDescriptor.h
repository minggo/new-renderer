#pragma once

#include "Macros.h"
#include "Types.h"
#include "VertexLayout.h"

#include <vector>

CC_BACKEND_BEGIN

class ShaderModule;
class DepthStencilState;
class BlendState;
class Program;

struct RenderPipelineDescriptor
{
    Program* program = nullptr;
    DepthStencilState* depthStencilState = nullptr;
    BlendState* blendState = nullptr;
    std::vector<VertexLayout> vertexLayouts;
    TextureFormat colorAttachmentsFormat[MAX_COLOR_ATTCHMENT] = { TextureFormat::SYSTEM_DEFAULT, TextureFormat::NONE };
    TextureFormat depthAttachmentFormat = TextureFormat::NONE;
    TextureFormat stencilAttachmentFormat = TextureFormat::NONE;
};

CC_BACKEND_END
