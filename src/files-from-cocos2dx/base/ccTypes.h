#pragma once

struct  Color4F
{
    Color4F();
    Color4F(float _r, float _g, float _b, float _a);
//    explicit Color4F(const Color3B& color, float _a = 1.0f);
//    explicit Color4F(const Color4B& color);
    
    bool operator==(const Color4F& right) const;
//    bool operator==(const Color3B& right) const;
//    bool operator==(const Color4B& right) const;
    bool operator!=(const Color4F& right) const;
//    bool operator!=(const Color3B& right) const;
//    bool operator!=(const Color4B& right) const;
    
    bool equals(const Color4F &other) const
    {
        return (*this == other);
    }
    
    float r;
    float g;
    float b;
    float a;
    
    static const Color4F WHITE;
    static const Color4F YELLOW;
    static const Color4F BLUE;
    static const Color4F GREEN;
    static const Color4F RED;
    static const Color4F MAGENTA;
    static const Color4F BLACK;
    static const Color4F ORANGE;
    static const Color4F GRAY;
};
