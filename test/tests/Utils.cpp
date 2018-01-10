/****************************************************************************
 Copyright (c) 2018 Chukong Technologies
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Utils.h"
#include "platform/CCImage.h"

using namespace cocos2d;

namespace utils
{
    const float PI = 3.1415926;

    int WINDOW_WIDTH = 0;
    int WINDOW_HEIGHT = 0;

    cocos2d::Data loadData(const std::string& filePath)
    {
        auto img = new cocos2d::Image();
        img->initWithImageFile(filePath);
        
        cocos2d::Data data;
        data.copy(img->getData(), img->getDataLen());
        
        img->release();
        
        return data;
    }

    void fillRectWithColor(uint8_t* buf, uint32_t totalWidth, uint32_t totalHeight, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint8_t r, uint8_t g, uint8_t b)
    {
        assert(x + width <= totalWidth);
        assert(y + height <=  totalHeight);

        uint32_t y0 = totalHeight - (y + height);
        uint32_t y1 = totalHeight - y;
        uint8_t* p;
        for (uint32_t offsetY = y0; offsetY < y1; ++offsetY)
        {
            for (uint32_t offsetX = x; offsetX < (x + width); ++offsetX)
            {
                p = buf + (totalWidth * offsetY + offsetX) * 3;
                *p++ = r;
                *p++ = g;
                *p++ = b;
            }
        }
    }

    /**
     * Generates a random vector with the given scale
     * @param scale Length of the resulting vector. If ommitted, a unit vector will be returned
     */
    Vec3 vec3Random(float scale/* = 1.0f */)
    {
        Vec3 out;
        float r = CCRANDOM_0_1() * 2.0 * PI;
        float z = (CCRANDOM_0_1() * 2.0) - 1.0;
        float zScale = sqrtf(1.0 - z * z) * scale;

        out.x = cosf(r) * zScale;
        out.y = sinf(r) * zScale;
        out.z = z * scale;
        return out;
    };

    Vec3 vec3ScaleAndAdd(const Vec3& a, const Vec3& b, float scale)
    {
        Vec3 out;
        out.x = a.x + (b.x * scale);
        out.y = a.y + (b.y * scale);
        out.z = a.z + (b.z * scale);
        return out;
    };
}
