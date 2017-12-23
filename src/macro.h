//
//  macro.h
//  Test
//
//  Created by minggo on 12/14/17.
//  Copyright © 2017 cocos. All rights reserved.
//

#pragma once

#ifndef CC_BEGIN
    #define CC_BEGIN namespace cocos2d {
#endif // CC_BEGIN

#ifndef CC_END
    #define CC_END }
#endif // CC_END

//#ifndef DISALLOW_COPY_ASSIGN_AND_MOVE
    #define CC_DISALLOW_COPY_ASSIGN_AND_MOVE(type) \
        type(const type&) = delete; \
        type& operator =(const type&) = delete; \
        type(type &&) = delete; \
        type& operator =(type &&) = delete;
//#endif // DISALLOW_COPY_ASSIGN_AND_MOVE

#define CC_UINT    unsigned int

