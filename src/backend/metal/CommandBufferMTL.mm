#include "CommandBufferMTL.h"
#include "BufferMTL.h"
#include "DeviceMTL.h"
#include "RenderPipelineMTL.h"
#include "TextureMTL.h"
#include "Utils.h"
#include "ProgramMTL.h"

CC_BACKEND_BEGIN

namespace
{
    MTLPrimitiveType toMTLPrimitive(PrimitiveType primitiveType)
    {
        MTLPrimitiveType ret = MTLPrimitiveTypeTriangle;
        switch (primitiveType)
        {
            case PrimitiveType::POINT:
                ret = MTLPrimitiveTypePoint;
                break;
            case PrimitiveType::LINE:
                ret = MTLPrimitiveTypeLine;
                break;
            case PrimitiveType::LINE_STRIP:
                ret = MTLPrimitiveTypeLineStrip;
                break;
            case PrimitiveType::TRIANGLE:
                ret = MTLPrimitiveTypeTriangle;
                break;
            case PrimitiveType::TRIANGLE_STRIP:
                ret = MTLPrimitiveTypeTriangleStrip;
                break;
            default:
                break;
        }
        return ret;
    }
    
    MTLIndexType toMTLIndexType(IndexFormat indexFormat)
    {
        if (IndexFormat::U_SHORT == indexFormat)
            return MTLIndexTypeUInt16;
        else
            return MTLIndexTypeUInt32;
    }
    
    MTLCullMode toMTLCullMode(CullMode mode)
    {
        switch (mode) {
            case CullMode::NONE:
                return MTLCullModeNone;
            case CullMode::FRONT:
                return MTLCullModeFront;
            case CullMode::BACK:
                return MTLCullModeBack;
        }
    }
    
    MTLRenderPassDescriptor* toMTLRenderPassDescriptor(const RenderPassDescriptor& descriptor)
    {
        MTLRenderPassDescriptor* mtlDescritpor = [MTLRenderPassDescriptor renderPassDescriptor];
        
        // Set color attachments.
        if (descriptor.needColorAttachment)
        {
            bool hasCustomColorAttachment = false;
            for (int i = 0; i < MAX_COLOR_ATTCHMENT; ++i)
            {
                if (! descriptor.colorAttachmentsTexture[i])
                    continue;
                
                mtlDescritpor.colorAttachments[i].texture = static_cast<TextureMTL*>(descriptor.colorAttachmentsTexture[i])->getMTLTexture();
                if (descriptor.needClearColor)
                {
                    mtlDescritpor.colorAttachments[i].loadAction = MTLLoadActionClear;
                    mtlDescritpor.colorAttachments[i].clearColor = MTLClearColorMake(descriptor.clearColorValue[0],
                                                                                     descriptor.clearColorValue[1],
                                                                                     descriptor.clearColorValue[2],
                                                                                     descriptor.clearColorValue[3]);
                }
                
                hasCustomColorAttachment = true;
            }
            
            if (!hasCustomColorAttachment)
            {
                mtlDescritpor.colorAttachments[0].texture = DeviceMTL::getCurrentDrawable().texture;
                if (descriptor.needClearColor)
                {
                    mtlDescritpor.colorAttachments[0].loadAction = MTLLoadActionClear;
                    mtlDescritpor.colorAttachments[0].clearColor = MTLClearColorMake(descriptor.clearColorValue[0],
                                                                                     descriptor.clearColorValue[1],
                                                                                     descriptor.clearColorValue[2],
                                                                                     descriptor.clearColorValue[3]);
                }
                else
                    mtlDescritpor.colorAttachments[0].loadAction = MTLLoadActionLoad;
            }
        }
        
        // Set depth/stencil attachment
        if (descriptor.needDepthAttachment)
        {
            if (descriptor.depthAttachmentTexture)
                mtlDescritpor.depthAttachment.texture = static_cast<TextureMTL*>(descriptor.depthAttachmentTexture)->getMTLTexture();
            else
                mtlDescritpor.depthAttachment.texture = Utils::getDefaultDepthStencilTexture();
            
            if (descriptor.needClearDepth)
            {
                mtlDescritpor.depthAttachment.loadAction = MTLLoadActionClear;
                mtlDescritpor.depthAttachment.clearDepth = descriptor.clearDepthValue;
            }
            else
                mtlDescritpor.depthAttachment.loadAction = MTLLoadActionLoad;
        }
        if (descriptor.needStencilAttachment)
        {
            if (descriptor.stencilAttachmentTexture)
                mtlDescritpor.stencilAttachment.texture = static_cast<TextureMTL*>(descriptor.stencilAttachmentTexture)->getMTLTexture();
            else
                mtlDescritpor.stencilAttachment.texture = Utils::getDefaultDepthStencilTexture();
            
            if (descriptor.needClearStencil)
            {
                mtlDescritpor.stencilAttachment.loadAction = MTLLoadActionClear;
                mtlDescritpor.stencilAttachment.clearStencil = descriptor.clearStencilValue;
            }
            else
                mtlDescritpor.stencilAttachment.loadAction = MTLLoadActionLoad;
        }
        
        return mtlDescritpor;
    }
}

CommandBufferMTL::CommandBufferMTL(DeviceMTL* deviceMTL)
: _deviceMTL(deviceMTL)
, _mtlCommandQueue(deviceMTL->getMTLCommandQueue())
{
}

CommandBufferMTL::~CommandBufferMTL()
{
}

void CommandBufferMTL::beginFrame()
{
    _mtlCommandBuffer = [_mtlCommandQueue commandBuffer];
    [_mtlCommandBuffer retain];
    
    _deviceMTL->updateDrawable();
}

void CommandBufferMTL::beginRenderPass(const RenderPassDescriptor& descriptor)
{
    _renderPassDescriptor = descriptor;
    
    _mtlRenderEncoder = [_mtlCommandBuffer renderCommandEncoderWithDescriptor:toMTLRenderPassDescriptor(_renderPassDescriptor)];
    [_mtlRenderEncoder retain];
    [_mtlRenderEncoder setFrontFacingWinding:MTLWindingCounterClockwise];
}

void CommandBufferMTL::setRenderPipeline(RenderPipeline* renderPipeline)
{
    CC_SAFE_RETAIN(renderPipeline);
    CC_SAFE_RELEASE(_renderPipelineMTL);
    _renderPipelineMTL = static_cast<RenderPipelineMTL*>(renderPipeline);
    [_mtlRenderEncoder setRenderPipelineState:_renderPipelineMTL->getMTLRenderPipelineState()];
}

void CommandBufferMTL::setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    MTLViewport viewport;
    viewport.originX = x;
    // Metal coordinate origin is top-left, which is different from OpenGL,
    // so adjust the coordinate here.
    viewport.originY = DeviceMTL::getCAMetalLayer().drawableSize.height - y - h;
    viewport.width = w;
    viewport.height = h;
    viewport.znear = -1;
    viewport.zfar = 1;
    [_mtlRenderEncoder setViewport:viewport];
}

void CommandBufferMTL::setCullMode(CullMode mode)
{
    [_mtlRenderEncoder setCullMode:toMTLCullMode(mode)];
}

void CommandBufferMTL::setVertexBuffer(uint32_t index, Buffer* buffer)
{
    // Vertex buffer is bound in index 0.
    [_mtlRenderEncoder setVertexBuffer:static_cast<BufferMTL*>(buffer)->getMTLBuffer()
                                offset:0
                               atIndex:0];
}

void CommandBufferMTL::setIndexBuffer(Buffer* buffer)
{
    assert(buffer != nullptr);
    if (!buffer)
        return;
    
    _mtlIndexBuffer = static_cast<BufferMTL*>(buffer)->getMTLBuffer();
    [_mtlIndexBuffer retain];
}

void CommandBufferMTL::drawArrays(PrimitiveType primitiveType, uint32_t start,  uint32_t count)
{
    prepareDrawing();
    [_mtlRenderEncoder drawPrimitives:toMTLPrimitive(primitiveType)
                          vertexStart:start
                          vertexCount:count];
}

void CommandBufferMTL::drawElements(PrimitiveType primitiveType, IndexFormat indexType, uint32_t count)
{
    prepareDrawing();
    [_mtlRenderEncoder drawIndexedPrimitives:toMTLPrimitive(primitiveType)
                                  indexCount:count
                                   indexType:toMTLIndexType(indexType)
                                 indexBuffer:_mtlIndexBuffer
                           indexBufferOffset:0];
    
}

void CommandBufferMTL::endRenderPass()
{
    afterDraw();
    [_mtlRenderEncoder endEncoding];
    [_mtlRenderEncoder release];
}

void CommandBufferMTL::endFrame()
{
    [_mtlCommandBuffer presentDrawable:DeviceMTL::getCurrentDrawable()];
    [_mtlCommandBuffer commit];
    [_mtlCommandBuffer release];
}

void CommandBufferMTL::afterDraw()
{
    if (_mtlIndexBuffer)
    {
        [_mtlIndexBuffer release];
        _mtlIndexBuffer = nullptr;
    }
    
}

void CommandBufferMTL::prepareDrawing() const
{
    setUniformBuffer();
    setTextures();
    
    auto mtlDepthStencilState = _renderPipelineMTL->getMTLDepthStencilState();
    if (mtlDepthStencilState)
    {
        [_mtlRenderEncoder setDepthStencilState:mtlDepthStencilState];
        [_mtlRenderEncoder setStencilFrontReferenceValue:_stencilReferenceValueFront
                                      backReferenceValue:_stencilReferenceValueBack];
    }
}

void CommandBufferMTL::setTextures() const
{
    if (_renderPipelineMTL->getProgram())
    {
        doSetTextures(true);
        doSetTextures(false);
    }
}

void CommandBufferMTL::doSetTextures(bool isVertex) const
{
    const auto& bindTextureInfos = (isVertex)?_renderPipelineMTL->getProgram()->getVertexTextureInfos():_renderPipelineMTL->getProgram()->getFragmentTextureInfos();
    for(const auto& textureInfo : bindTextureInfos)
    {
        int i = 0;
        //FIXME: should support texture array.
        const auto& textures = textureInfo.textures;
        const auto& mtlTexture = static_cast<TextureMTL*>(textures[i]);
        
        if (isVertex)
        {
            [_mtlRenderEncoder setVertexTexture:mtlTexture->getMTLTexture()
                                        atIndex:textureInfo.location];
            [_mtlRenderEncoder setVertexSamplerState:mtlTexture->getMTLSamplerState()
                                             atIndex:textureInfo.location];
        }
        else
        {
            [_mtlRenderEncoder setFragmentTexture:mtlTexture->getMTLTexture()
                                          atIndex:textureInfo.location];
            [_mtlRenderEncoder setFragmentSamplerState:mtlTexture->getMTLSamplerState()
                                               atIndex:textureInfo.location];
        }
        
        ++i;
    }
}

void CommandBufferMTL::setUniformBuffer() const
{
    if (_renderPipelineMTL->getProgram())
    {
        // Uniform buffer is bound to index 1.
        const auto& vertexUniformBuffer = _renderPipelineMTL->getVertexUniformBuffer();
        if (vertexUniformBuffer)
        {
            auto size = _renderPipelineMTL->getVertexUniformBufferSize();
            [_mtlRenderEncoder setVertexBytes:vertexUniformBuffer.get()
                                       length:size atIndex:1];
        }
        
        const auto& fragUniformBuffer = _renderPipelineMTL->getFragmentUniformBuffer();
        if (fragUniformBuffer)
        {
            auto size = _renderPipelineMTL->getFragUniformBufferSize();
            [_mtlRenderEncoder setFragmentBytes:fragUniformBuffer.get()
                                         length:size
                                        atIndex:1];
        }
    }
}

CC_BACKEND_END
