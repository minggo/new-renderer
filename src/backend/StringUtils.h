//
//  StringUtils.hpp
//  Test
//
//  Created by Cocos on 2018/11/2.
//  Copyright © 2018 cocos. All rights reserved.
//

#ifndef StringUtils_hpp
#define StringUtils_hpp

#include <string>
#include "Types.h"
CC_BACKEND_BEGIN

class StringUtils
{
public:
    static std::string TextureFormat2String(const TextureFormat& textureFormat);
    static std::string TextureType2String(const TextureType& textureType);
    static std::string TextureUsage2String(const TextureUsage& textureUsage);
    static std::string SamplerFilterType2String(const SamplerFilter& filterType);
    static std::string SamplerAddressMode2String(const SamplerAddressMode& addressMode);
    static std::string SamplerDescriptor2String(const SamplerDescriptor& descriptor);
    static std::string StencilOperation2String(const StencilOperation& operation);
    static std::string CompareFunction2String(const CompareFunction& compareFunction);
    static std::string ColorWriteMask2String(const ColorWriteMask& colorWriteMask);
    static std::string BlendOperation2String(const BlendOperation& blendOperation);
    static std::string BlendFactor2String(const BlendFactor& blendFactor);
};

CC_BACKEND_END
#endif /* StringUtils_hpp */
