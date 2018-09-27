#pragma once

#include "../RenderPipeline.h"
#include "../RenderPipelineDescriptor.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class RenderPipelineMTL : public RenderPipeline
{
public:
    RenderPipelineMTL(id<MTLDevice> mtlDevice, const RenderPipelineDescriptor& descriptor);
    
    inline id<MTLRenderPipelineState> getMTLRenderPipelineState() const { return _mtlRenderPipelineState; }
    
private:
    id<MTLRenderPipelineState> _mtlRenderPipelineState = nil;
};

CC_BACKEND_END
