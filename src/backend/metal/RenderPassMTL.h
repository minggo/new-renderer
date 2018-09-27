#pragma once

#include "../RenderPass.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class RenderPassMTL : public RenderPass
{
public:
    RenderPassMTL(const RenderPassDescriptor& descriptor);
    
    inline MTLRenderPassDescriptor* getMTLRenderPassDescriptor() const { return _renderPassDescritprMTL; }
    
private:
    MTLRenderPassDescriptor* _renderPassDescritprMTL = nil;
};

CC_BACKEND_END
