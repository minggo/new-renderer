#pragma once

#include "../RenderPass.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class RenderPassMTL : public RenderPass
{
public:
    RenderPassMTL(id<MTLDevice> mtlDevice, const RenderPassDescriptor& descriptor);
    ~RenderPassMTL();
    
    inline MTLRenderPassDescriptor* getMTLRenderPassDescriptor() const { return _renderPassDescritprMTL; }
    
private:
    MTLRenderPassDescriptor* _renderPassDescritprMTL = nil;
    bool _newRenderPassDescriptorMTL = false;
};

CC_BACKEND_END
