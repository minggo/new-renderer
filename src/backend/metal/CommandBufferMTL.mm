#include "CommandBufferMTL.h"
#include "BufferMTL.h"
#include "RenderPassMTL.h"
#include "DeviceMTL.h"
#include "RenderPipelineMTL.h"

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
}

CommandBufferMTL::CommandBufferMTL(id<MTLDevice> mtlDevice)
: _mtlCommandQueue([mtlDevice newCommandQueue])
{
}

CommandBufferMTL::~CommandBufferMTL()
{
    [_mtlCommandQueue release];
}

void CommandBufferMTL::beginRenderPass(RenderPass* renderPass)
{
    _mtlCommandBuffer = [_mtlCommandQueue commandBuffer];
    [_mtlCommandBuffer retain];
    
    if (renderPass)
        _mtlRenderEncoder = [_mtlCommandBuffer renderCommandEncoderWithDescriptor:static_cast<RenderPassMTL*>(renderPass)->getMTLRenderPassDescriptor()];
    else
        _mtlRenderEncoder = [_mtlCommandBuffer renderCommandEncoderWithDescriptor:DeviceMTL::getDefaultMTLRenderPassDescriptor()];
    
    [_mtlRenderEncoder retain];
    [_mtlRenderEncoder setFrontFacingWinding:MTLWindingCounterClockwise];
}

void CommandBufferMTL::setRenderPipeline(RenderPipeline* renderPipeline)
{
    CC_SAFE_RETAIN(renderPipeline);
    CC_SAFE_RELEASE(_renderPipelineMTL);
    _renderPipelineMTL = static_cast<RenderPipelineMTL*>(renderPipeline);
}

void CommandBufferMTL::setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    MTLViewport viewport;
    viewport.originX = x;
    viewport.originY = y;
    viewport.width = w;
    viewport.height = h;
    viewport.znear = -1;
    viewport.zfar = 1;
    [_mtlRenderEncoder setViewport:viewport];
}

void CommandBufferMTL::setVertexBuffer(uint32_t index, Buffer* buffer)
{
    [_mtlRenderEncoder setVertexBuffer:static_cast<BufferMTL*>(buffer)->getMTLBuffer()
                                offset:0
                               atIndex:index];
}

void CommandBufferMTL::setBindGroup(BindGroup* bindGroup)
{
    //TODO
}

void CommandBufferMTL::setIndexBuffer(uint32_t index, Buffer* buffer)
{
    //TODO
}

void CommandBufferMTL::drawArrays(PrimitiveType primitiveType, uint32_t start,  uint32_t count)
{
    [_mtlRenderEncoder setRenderPipelineState:_renderPipelineMTL->getMTLRenderPipelineState()];
    [_mtlRenderEncoder drawPrimitives:toMTLPrimitive(primitiveType)
                          vertexStart:start
                          vertexCount:count];
}

void CommandBufferMTL::drawElements(PrimitiveType primitiveType, IndexFormat indexType, uint32_t count)
{
    //TODO
}

void CommandBufferMTL::endRenderPass()
{
    [_mtlRenderEncoder endEncoding];
    [_mtlCommandBuffer presentDrawable:DeviceMTL::getCurrentDrawable()];
    [_mtlCommandBuffer commit];
    
    [_mtlCommandBuffer release];
    [_mtlRenderEncoder release];
}

CC_BACKEND_END
