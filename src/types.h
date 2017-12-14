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

enum class ClearFlag : uint8_t
{
    NONE        = UINT8_C(0x0000),      // No clear flags.
    COLOR       = UINT8_C(0x0001),      // Clear color.
    DEPTH       = UINT8_C(0x0002),      // Clear depth.
    STENCIL     = UINT8_C(0x0004),      // Clear stencil.
};
