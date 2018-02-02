//
//  jsb_conversions.cpp
//  cocos2d_js_bindings
//
//  Created by James Chen on 5/17/17.
//
//

#include "jsb_conversions.hpp"
#include <sstream>

// seval to native

bool seval_to_int32(const se::Value& v, int32_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toInt32(); //FIXME: need to check isNan?
        return true;
    }
    else if (v.isBoolean())
    {
        *ret = v.toBoolean() ? 1 : 0;
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_uint32(const se::Value& v, uint32_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toUint32();
        return true;
    }
    else if (v.isBoolean())
    {
        *ret = v.toBoolean() ? 1 : 0;
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_int8(const se::Value& v, int8_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toInt8();
        return true;
    }
    else if (v.isBoolean())
    {
        *ret = v.toBoolean() ? 1 : 0;
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_uint8(const se::Value& v, uint8_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toUint8();
        return true;
    }
    else if (v.isBoolean())
    {
        *ret = v.toBoolean() ? 1 : 0;
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_int16(const se::Value& v, int16_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toInt16();
        return true;
    }
    else if (v.isBoolean())
    {
        *ret = v.toBoolean() ? 1 : 0;
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_uint16(const se::Value& v, uint16_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toUint16();
        return true;
    }
    else if (v.isBoolean())
    {
        *ret = v.toBoolean() ? 1 : 0;
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_boolean(const se::Value& v, bool* ret)
{
    assert(ret != nullptr);
    if (v.isBoolean())
    {
        *ret = v.toBoolean();
    }
    else if (v.isNumber())
    {
        *ret = v.toInt32() != 0 ? true : false;
    }
    else if (v.isNullOrUndefined())
    {
        *ret = false;
    }
    else if (v.isObject())
    {
        *ret = true;
    }
    else if (v.isString())
    {
        *ret = v.toString().empty() ? false : true;
    }
    else
    {
        *ret = false;
        assert(false);
    }

    return true;
}

bool seval_to_float(const se::Value& v, float* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toFloat();
        return true;
    }
    *ret = 0.0f;
    return false;
}

bool seval_to_double(const se::Value& v, double* ret)
{
    if (v.isNumber())
    {
        *ret = v.toNumber();
        return true;
    }
    *ret = 0.0;
    return false;
}

bool seval_to_long(const se::Value& v, long* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toLong();
        return true;
    }
    *ret = 0L;
    return false;
}

bool seval_to_ulong(const se::Value& v, unsigned long* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = v.toUlong();
        return true;
    }
    *ret = 0UL;
    return false;
}

bool seval_to_longlong(const se::Value& v, long long* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = (long long)v.toLong();
        return true;
    }
    *ret = 0LL;
    return false;
}

bool seval_to_ssize(const se::Value& v, ssize_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = (ssize_t)v.toLong();
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_size(const se::Value& v, size_t* ret)
{
    assert(ret != nullptr);
    if (v.isNumber())
    {
        *ret = (size_t)v.toLong();
        return true;
    }
    *ret = 0;
    return false;
}

bool seval_to_std_string(const se::Value& v, std::string* ret)
{
    assert(ret != nullptr);
    *ret = v.toStringForce();
    return true;
}

bool seval_to_Vec2(const se::Value& v, cocos2d::Vec2* pt)
{
    assert(v.isObject() && pt != nullptr);
    se::Object* obj = v.toObject();
    se::Value x;
    se::Value y;
    bool ok = obj->getProperty("x", &x);
    SE_PRECONDITION3(ok && x.isNumber(), false, *pt = cocos2d::Vec2::ZERO);
    ok = obj->getProperty("y", &y);
    SE_PRECONDITION3(ok && y.isNumber(), false, *pt = cocos2d::Vec2::ZERO);
    pt->x = x.toFloat();
    pt->y = y.toFloat();
    return true;
}

bool seval_to_Vec3(const se::Value& v, cocos2d::Vec3* pt)
{
    assert(v.isObject() && pt != nullptr);
    se::Object* obj = v.toObject();
    se::Value x;
    se::Value y;
    se::Value z;
    bool ok = obj->getProperty("x", &x);
    SE_PRECONDITION3(ok && x.isNumber(), false, *pt = cocos2d::Vec3::ZERO);
    ok = obj->getProperty("y", &y);
    SE_PRECONDITION3(ok && y.isNumber(), false, *pt = cocos2d::Vec3::ZERO);
    ok = obj->getProperty("z", &z);
    SE_PRECONDITION3(ok && z.isNumber(), false, *pt = cocos2d::Vec3::ZERO);
    pt->x = x.toFloat();
    pt->y = y.toFloat();
    pt->z = z.toFloat();
    return true;
}

bool seval_to_Vec4(const se::Value& v, cocos2d::Vec4* pt)
{
    assert(v.isObject() && pt != nullptr);
    pt->x = pt->y = pt->z = pt->w = 0.0f;
    se::Object* obj = v.toObject();
    se::Value x;
    se::Value y;
    se::Value z;
    se::Value w;
    bool ok = obj->getProperty("x", &x);
    SE_PRECONDITION3(ok && x.isNumber(), false, *pt = cocos2d::Vec4::ZERO);
    ok = obj->getProperty("y", &y);
    SE_PRECONDITION3(ok && y.isNumber(), false, *pt = cocos2d::Vec4::ZERO);
    ok = obj->getProperty("z", &z);
    SE_PRECONDITION3(ok && z.isNumber(), false, *pt = cocos2d::Vec4::ZERO);
    ok = obj->getProperty("w", &w);
    SE_PRECONDITION3(ok && w.isNumber(), false, *pt = cocos2d::Vec4::ZERO);
    pt->x = x.toFloat();
    pt->y = y.toFloat();
    pt->z = z.toFloat();
    pt->w = w.toFloat();
    return true;
}

bool seval_to_Mat4(const se::Value& v, cocos2d::Mat4* mat)
{
    assert(v.isObject() && mat != nullptr);
    se::Object* obj = v.toObject();

    if (obj->isArray())
    {
        bool ok = false;
        uint32_t len = 0;
        ok = obj->getArrayLength(&len);
        SE_PRECONDITION3(ok, false, *mat = cocos2d::Mat4::IDENTITY);

        if (len != 16)
        {
            SE_REPORT_ERROR("Array length error: %d, was expecting 16", len);
            *mat = cocos2d::Mat4::IDENTITY;
            return false;
        }

        se::Value tmp;
        for (uint32_t i = 0; i < len; ++i)
        {
            ok = obj->getArrayElement(i, &tmp);
            SE_PRECONDITION3(ok, false, *mat = cocos2d::Mat4::IDENTITY);

            if (tmp.isNumber())
            {
                mat->m[i] = tmp.toFloat();
            }
            else
            {
                SE_REPORT_ERROR("%u, not supported type in matrix", i);
                *mat = cocos2d::Mat4::IDENTITY;
                return false;
            }

            tmp.setUndefined();
        }
    }
    else
    {
        se::Value tmp;
        obj->getProperty("m00", &tmp);
        mat->m[0] = tmp.toFloat();
        obj->getProperty("m01", &tmp);
        mat->m[1] = tmp.toFloat();
        obj->getProperty("m02", &tmp);
        mat->m[2] = tmp.toFloat();
        obj->getProperty("m03", &tmp);
        mat->m[3] = tmp.toFloat();
        obj->getProperty("m04", &tmp);
        mat->m[4] = tmp.toFloat();
        obj->getProperty("m05", &tmp);
        mat->m[5] = tmp.toFloat();
        obj->getProperty("m06", &tmp);
        mat->m[6] = tmp.toFloat();
        obj->getProperty("m07", &tmp);
        mat->m[7] = tmp.toFloat();
        obj->getProperty("m08", &tmp);
        mat->m[8] = tmp.toFloat();
        obj->getProperty("m09", &tmp);
        mat->m[9] = tmp.toFloat();
        obj->getProperty("m10", &tmp);
        mat->m[10] = tmp.toFloat();
        obj->getProperty("m11", &tmp);
        mat->m[11] = tmp.toFloat();
        obj->getProperty("m12", &tmp);
        mat->m[12] = tmp.toFloat();
        obj->getProperty("m13", &tmp);
        mat->m[13] = tmp.toFloat();
        obj->getProperty("m14", &tmp);
        mat->m[14] = tmp.toFloat();
        obj->getProperty("m15", &tmp);
        mat->m[15] = tmp.toFloat();
    }

    return true;
}

bool seval_to_Size(const se::Value& v, cocos2d::Size* size)
{
    assert(v.isObject() && size != nullptr);
    se::Object* obj = v.toObject();
    se::Value width;
    se::Value height;

    bool ok = obj->getProperty("width", &width);
    SE_PRECONDITION3(ok && width.isNumber(), false, *size = cocos2d::Size::ZERO);
    ok = obj->getProperty("height", &height);
    SE_PRECONDITION3(ok && height.isNumber(), false, *size = cocos2d::Size::ZERO);
    size->width = width.toFloat();
    size->height = height.toFloat();
    return true;
}

//bool seval_to_Rect(const se::Value& v, cocos2d::Rect* rect)
//{
//    assert(v.isObject() && rect != nullptr);
//    se::Object* obj = v.toObject();
//    se::Value x;
//    se::Value y;
//    se::Value width;
//    se::Value height;
//
//    bool ok = obj->getProperty("x", &x);
//    SE_PRECONDITION3(ok && x.isNumber(), false, *rect = cocos2d::Rect::ZERO);
//    ok = obj->getProperty("y", &y);
//    SE_PRECONDITION3(ok && y.isNumber(), false, *rect = cocos2d::Rect::ZERO);
//    ok = obj->getProperty("width", &width);
//    SE_PRECONDITION3(ok && width.isNumber(), false, *rect = cocos2d::Rect::ZERO);
//    ok = obj->getProperty("height", &height);
//    SE_PRECONDITION3(ok && height.isNumber(), false, *rect = cocos2d::Rect::ZERO);
//    rect->origin.x = x.toFloat();
//    rect->origin.y = y.toFloat();
//    rect->size.width = width.toFloat();
//    rect->size.height = height.toFloat();
//
//    return true;
//}

bool seval_to_Rect(const se::Value& v, cocos2d::gfx::Rect* rect)
{
    assert(v.isObject() && rect != nullptr);
    se::Object* obj = v.toObject();
    se::Value x;
    se::Value y;
    se::Value width;
    se::Value height;

    bool ok = obj->getProperty("x", &x);
    SE_PRECONDITION3(ok && x.isNumber(), false, *rect = cocos2d::gfx::Rect::ZERO);
    ok = obj->getProperty("y", &y);
    SE_PRECONDITION3(ok && y.isNumber(), false, *rect = cocos2d::gfx::Rect::ZERO);
    ok = obj->getProperty("w", &width);
    SE_PRECONDITION3(ok && width.isNumber(), false, *rect = cocos2d::gfx::Rect::ZERO);
    ok = obj->getProperty("h", &height);
    SE_PRECONDITION3(ok && height.isNumber(), false, *rect = cocos2d::gfx::Rect::ZERO);
    rect->x = x.toFloat();
    rect->y = y.toFloat();
    rect->w = width.toFloat();
    rect->h = height.toFloat();

    return true;
}

bool seval_to_Color3B(const se::Value& v, cocos2d::Color3B* color)
{
    assert(v.isObject() && color != nullptr);
    se::Object* obj = v.toObject();
    se::Value r;
    se::Value g;
    se::Value b;
    bool ok = obj->getProperty("r", &r);
    SE_PRECONDITION3(ok && r.isNumber(), false, *color = cocos2d::Color3B::BLACK);
    ok = obj->getProperty("g", &g);
    SE_PRECONDITION3(ok && g.isNumber(), false, *color = cocos2d::Color3B::BLACK);
    ok = obj->getProperty("b", &b);
    SE_PRECONDITION3(ok && b.isNumber(), false, *color = cocos2d::Color3B::BLACK);
    color->r = (GLubyte)r.toUint16();
    color->g = (GLubyte)g.toUint16();
    color->b = (GLubyte)b.toUint16();
    return true;
}

bool seval_to_Color4B(const se::Value& v, cocos2d::Color4B* color)
{
    assert(v.isObject() && color != nullptr);
    se::Object* obj = v.toObject();
    se::Value r;
    se::Value g;
    se::Value b;
    se::Value a;
    bool ok = obj->getProperty("r", &r);
    SE_PRECONDITION3(ok && r.isNumber(), false, *color = cocos2d::Color4B::BLACK);
    ok = obj->getProperty("g", &g);
    SE_PRECONDITION3(ok && g.isNumber(), false, *color = cocos2d::Color4B::BLACK);
    ok = obj->getProperty("b", &b);
    SE_PRECONDITION3(ok && b.isNumber(), false, *color = cocos2d::Color4B::BLACK);
    ok = obj->getProperty("a", &a);
    SE_PRECONDITION3(ok && b.isNumber(), false, *color = cocos2d::Color4B::BLACK);
    color->r = (GLubyte)r.toUint16();
    color->g = (GLubyte)g.toUint16();
    color->b = (GLubyte)b.toUint16();
    color->a = (GLubyte)a.toUint16();
    return true;
}

bool seval_to_Color4F(const se::Value& v, cocos2d::Color4F* color)
{
    assert(v.isObject() && color != nullptr);
    se::Object* obj = v.toObject();
    se::Value r;
    se::Value g;
    se::Value b;
    se::Value a;
    bool ok = obj->getProperty("r", &r);
    SE_PRECONDITION3(ok && r.isNumber(), false, *color = cocos2d::Color4F::BLACK);
    ok = obj->getProperty("g", &g);
    SE_PRECONDITION3(ok && g.isNumber(), false, *color = cocos2d::Color4F::BLACK);
    ok = obj->getProperty("b", &b);
    SE_PRECONDITION3(ok && b.isNumber(), false, *color = cocos2d::Color4F::BLACK);
    ok = obj->getProperty("a", &a);
    SE_PRECONDITION3(ok && b.isNumber(), false, *color = cocos2d::Color4F::BLACK);
    color->r = r.toFloat() / 255.0f;
    color->g = g.toFloat() / 255.0f;
    color->b = b.toFloat() / 255.0f;
    color->a = a.toFloat() / 255.0f;
    return true;
}

bool seval_to_Color3F(const se::Value& v, cocos2d::Color3F* color)
{
    assert(v.isObject() && color != nullptr);
    se::Object* obj = v.toObject();
    se::Value r;
    se::Value g;
    se::Value b;
    bool ok = obj->getProperty("r", &r);
    SE_PRECONDITION3(ok && r.isNumber(), false, *color = cocos2d::Color3F::BLACK);
    ok = obj->getProperty("g", &g);
    SE_PRECONDITION3(ok && g.isNumber(), false, *color = cocos2d::Color3F::BLACK);
    ok = obj->getProperty("b", &b);
    SE_PRECONDITION3(ok && b.isNumber(), false, *color = cocos2d::Color3F::BLACK);
    color->r = r.toFloat();
    color->g = g.toFloat();
    color->b = b.toFloat();
    return true;
}

bool seval_to_ccvalue(const se::Value& v, cocos2d::Value* ret)
{
    assert(ret != nullptr);
    bool ok = true;
    if (v.isObject())
    {
        se::Object* jsobj = v.toObject();
        if (!jsobj->isArray())
        {
            // It's a normal js object.
            cocos2d::ValueMap dictVal;
            ok = seval_to_ccvaluemap(v, &dictVal);
            SE_PRECONDITION3(ok, false, *ret = cocos2d::Value::Null);
            *ret = cocos2d::Value(dictVal);
        }
        else
        {
            // It's a js array object.
            cocos2d::ValueVector arrVal;
            ok = seval_to_ccvaluevector(v, &arrVal);
            SE_PRECONDITION3(ok, false, *ret = cocos2d::Value::Null);
            *ret = cocos2d::Value(arrVal);
        }
    }
    else if (v.isString())
    {
        *ret = v.toString();
    }
    else if (v.isNumber())
    {
        *ret = v.toNumber();
    }
    else if (v.isBoolean())
    {
        *ret = v.toBoolean();
    }
    else if (v.isNullOrUndefined())
    {
        *ret = cocos2d::Value::Null;
    }
    else
    {
        CCASSERT(false, "not supported type");
    }

    return ok;
}

bool seval_to_ccvaluemap(const se::Value& v, cocos2d::ValueMap* ret)
{
    assert(ret != nullptr);

    if (v.isNullOrUndefined())
    {
        ret->clear();
        return true;
    }

    assert(v.isObject());

    SE_PRECONDITION3(!v.isNullOrUndefined(), false, ret->clear());

    se::Object* obj = v.toObject();

    cocos2d::ValueMap& dict = *ret;

    std::vector<std::string> allKeys;
    SE_PRECONDITION3(obj->getAllKeys(&allKeys), false, ret->clear());

    bool ok = false;
    se::Value value;
    cocos2d::Value ccvalue;
    for (const auto& key : allKeys)
    {
        SE_PRECONDITION3(obj->getProperty(key.c_str(), &value), false, ret->clear());
        ok = seval_to_ccvalue(value, &ccvalue);
        SE_PRECONDITION3(ok, false, ret->clear());
        dict.emplace(key, ccvalue);
    }

    return true;
}

static bool isNumberString(const std::string& str)
{
    for (const auto& c : str)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

bool seval_to_ccvaluemapintkey(const se::Value& v, cocos2d::ValueMapIntKey* ret)
{
    assert(ret != nullptr);
    if (v.isNullOrUndefined())
    {
        ret->clear();
        return true;
    }

    assert(v.isObject());

    SE_PRECONDITION3(!v.isNullOrUndefined(), false, ret->clear());

    se::Object* obj = v.toObject();

    cocos2d::ValueMapIntKey& dict = *ret;

    std::vector<std::string> allKeys;
    SE_PRECONDITION3(obj->getAllKeys(&allKeys), false, ret->clear());

    bool ok = false;
    se::Value value;
    cocos2d::Value ccvalue;
    for (const auto& key : allKeys)
    {
        SE_PRECONDITION3(obj->getProperty(key.c_str(), &value), false, ret->clear());

        if (!isNumberString(key))
        {
            SE_LOGD("seval_to_ccvaluemapintkey, found not numeric key: %s", key.c_str());
            continue;
        }

        int intKey = atoi(key.c_str());

        ok = seval_to_ccvalue(value, &ccvalue);
        SE_PRECONDITION3(ok, false, ret->clear());
        dict.emplace(intKey, ccvalue);
    }
    
    return true;
}

bool seval_to_ccvaluevector(const se::Value& v,  cocos2d::ValueVector* ret)
{
    assert(ret != nullptr);

    assert(v.isObject());

    se::Object* obj = v.toObject();
    SE_PRECONDITION3(obj->isArray(), false, ret->clear());

    uint32_t len = 0;
    obj->getArrayLength(&len);

    bool ok = false;
    se::Value value;
    cocos2d::Value ccvalue;
    for (uint32_t i = 0; i < len; ++i)
    {
        if (obj->getArrayElement(i, &value))
        {
            ok = seval_to_ccvalue(value, &ccvalue);
            SE_PRECONDITION3(ok, false, ret->clear());
            ret->push_back(ccvalue);
        }
    }
    
    return true;
}

bool sevals_variadic_to_ccvaluevector(const se::ValueArray& args, cocos2d::ValueVector* ret)
{
    bool ok = false;
    cocos2d::Value ccvalue;

    for (const auto& arg : args)
    {
        ok = seval_to_ccvalue(arg, &ccvalue);
        SE_PRECONDITION3(ok, false, ret->clear());
        ret->push_back(ccvalue);
    }

    return true;
}

bool seval_to_blendfunc(const se::Value& v, cocos2d::BlendFunc* ret)
{
    assert(v.isObject());
    se::Object* obj = v.toObject();
    se::Value value;
    bool ok = false;

    ok = obj->getProperty("src", &value);
    SE_PRECONDITION3(ok, false, *ret = cocos2d::BlendFunc::DISABLE);
    ret->src = value.toUint32();
    ok = obj->getProperty("dst", &value);
    SE_PRECONDITION3(ok, false, *ret = cocos2d::BlendFunc::DISABLE);

    ret->dst = value.toUint32();
    return true;
}

bool seval_to_std_vector_string(const se::Value& v, std::vector<std::string>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    assert(obj->isArray());
    uint32_t len = 0;
    if (obj->getArrayLength(&len))
    {
        se::Value value;
        for (uint32_t i = 0; i < len; ++i)
        {
            SE_PRECONDITION3(obj->getArrayElement(i, &value), false, ret->clear());
            assert(value.isString());
            ret->push_back(value.toString());
        }
        return true;
    }

    ret->clear();
    return false;
}

bool seval_to_std_vector_int(const se::Value& v, std::vector<int>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();

    if (obj->isArray())
    {
        uint32_t len = 0;
        if (obj->getArrayLength(&len))
        {
            se::Value value;
            for (uint32_t i = 0; i < len; ++i)
            {
                SE_PRECONDITION3(obj->getArrayElement(i, &value), false, ret->clear());
                assert(value.isNumber());
                ret->push_back(value.toInt32());
            }
            return true;
        }
    }
    else if (obj->isTypedArray())
    {
        size_t bytesPerElements = 0;
        uint8_t* data = nullptr;
        size_t dataBytes = 0;
        se::Object::TypedArrayType type = obj->getTypedArrayType();

#define SE_UINT8_PTR_TO_INT(ptr)  (*((uint8_t*)(ptr)))
#define SE_UINT16_PTR_TO_INT(ptr) (*((uint16_t*)(ptr)))
#define SE_UINT32_PTR_TO_INT(ptr) (*((uint32_t*)(ptr)))

        if (obj->getTypedArrayData(&data, &dataBytes))
        {
            for (size_t i = 0; i < dataBytes; i += bytesPerElements)
            {
                switch (type) {
                    case se::Object::TypedArrayType::INT8:
                    case se::Object::TypedArrayType::UINT8:
                    case se::Object::TypedArrayType::UINT8_CLAMPED:
                        ret->push_back(SE_UINT8_PTR_TO_INT(data + i));
                        bytesPerElements = 1;
                        break;
                    case se::Object::TypedArrayType::INT16:
                    case se::Object::TypedArrayType::UINT16:
                        ret->push_back(SE_UINT16_PTR_TO_INT(data + i));
                        bytesPerElements = 2;
                        break;
                    case se::Object::TypedArrayType::INT32:
                    case se::Object::TypedArrayType::UINT32:
                        ret->push_back(SE_UINT32_PTR_TO_INT(data + i));
                        bytesPerElements = 4;
                        break;
                    default:
                        SE_LOGE("Unsupported typed array: %d\n", (int)type);
                        assert(false);
                        break;
                }
            }
        }

#undef SE_UINT8_PTR_TO_INT
#undef SE_UINT16_PTR_TO_INT
#undef SE_UINT32_PTR_TO_INT

        return true;
    }
    else
    {
        assert(false);
    }

    ret->clear();
    return false;
}

bool seval_to_std_vector_float(const se::Value& v, std::vector<float>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    assert(obj->isArray());
    uint32_t len = 0;
    if (obj->getArrayLength(&len))
    {
        se::Value value;
        for (uint32_t i = 0; i < len; ++i)
        {
            SE_PRECONDITION3(obj->getArrayElement(i, &value), false, ret->clear());
            assert(value.isNumber());
            ret->push_back(value.toFloat());
        }
        return true;
    }

    ret->clear();
    return false;
}

bool seval_to_std_vector_Vec2(const se::Value& v, std::vector<cocos2d::Vec2>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    assert(obj->isArray());
    uint32_t len = 0;
    if (obj->getArrayLength(&len))
    {
        se::Value value;
        cocos2d::Vec2 pt;
        for (uint32_t i = 0; i < len; ++i)
        {
            SE_PRECONDITION3(obj->getArrayElement(i, &value) && seval_to_Vec2(value, &pt), false, ret->clear());
            ret->push_back(pt);
        }
        return true;
    }

    ret->clear();
    return false;
}

//bool seval_to_std_vector_Touch(const se::Value& v, std::vector<cocos2d::Touch*>* ret)
//{
//    assert(ret != nullptr);
//    assert(v.isObject());
//    se::Object* obj = v.toObject();
//    assert(obj->isArray());
//    uint32_t len = 0;
//    if (obj->getArrayLength(&len))
//    {
//        se::Value value;
//        cocos2d::Touch* touch = nullptr;
//        for (uint32_t i = 0; i < len; ++i)
//        {
//            SE_PRECONDITION3(obj->getArrayElement(i, &value), false, ret->clear());
//            assert(value.isObject());
//            touch = (cocos2d::Touch*)value.toObject()->getPrivateData();
//            ret->push_back(touch);
//        }
//        return true;
//    }
//
//    ret->clear();
//    return false;
//}

bool seval_to_std_map_string_string(const se::Value& v, std::map<std::string, std::string>* ret)
{
    assert(ret != nullptr);

    if (v.isNullOrUndefined())
    {
        ret->clear();
        return true;
    }

    assert(v.isObject());

    SE_PRECONDITION3(!v.isNullOrUndefined(), false, ret->clear());

    se::Object* obj = v.toObject();

    std::vector<std::string> allKeys;
    SE_PRECONDITION3(obj->getAllKeys(&allKeys), false, ret->clear());

    bool ok = false;
    se::Value value;
    std::string strValue;
    for (const auto& key : allKeys)
    {
        SE_PRECONDITION3(obj->getProperty(key.c_str(), &value), false, ret->clear());
        ok = seval_to_std_string(value, &strValue);
        SE_PRECONDITION3(ok, false, ret->clear());
        ret->emplace(key, strValue);
    }
    
    return true;
}

bool seval_to_FontDefinition(const se::Value& v, cocos2d::FontDefinition* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();

    // default values
    const char* defautlFontName = "Arial";
    const int defaultFontSize = 32;
    cocos2d::TextHAlignment defaultTextAlignment = cocos2d::TextHAlignment::LEFT;
    cocos2d::TextVAlignment defaultTextVAlignment = cocos2d::TextVAlignment::TOP;

    // by default shadow and stroke are off
    ret->_shadow._shadowEnabled = false;
    ret->_stroke._strokeEnabled = false;

    // white text by default
    ret->_fontFillColor = cocos2d::Color3B::WHITE;

    se::Value tmp, tmp2;

    // font name
    if (obj->getProperty("fontName", &tmp) && tmp.isString())
    {
        if (tmp.toString().empty())
        {
            ret->_fontName = defautlFontName;
        }
        else
        {
            ret->_fontName = tmp.toString();
        }
    }
    else
    {
        ret->_fontName = defautlFontName;
    }

    // font size
    if (obj->getProperty("fontSize", &tmp) && tmp.isNumber())
    {
        ret->_fontSize = tmp.toInt32();
    }
    else
    {
        ret->_fontSize = defaultFontSize;
    }

    // font alignment horizontal
    if (obj->getProperty("textAlign", &tmp) && tmp.isNumber())
    {
        ret->_alignment = (cocos2d::TextHAlignment)tmp.toInt32();
    }
    else
    {
        ret->_alignment = defaultTextAlignment;
    }

    // font alignment vertical
    if (obj->getProperty("verticalAlign", &tmp) && tmp.isNumber())
    {
        ret->_vertAlignment = (cocos2d::TextVAlignment)tmp.toInt32();
    }
    else
    {
        ret->_vertAlignment = defaultTextVAlignment;
    }

    // font fill color
    if (obj->getProperty("fillStyle", &tmp) && tmp.isObject())
    {
        seval_to_Color3B(tmp, &ret->_fontFillColor);
    }

    // font rendering box dimensions
    if (obj->getProperty("boundingWidth", &tmp) && tmp.isNumber()
        && obj->getProperty("boundingHeight", &tmp2) && tmp2.isNumber())
    {
        ret->_dimensions.width = tmp.toFloat();
        ret->_dimensions.height = tmp2.toFloat();
    }

    // shadow
    if (obj->getProperty("shadowEnabled", &tmp) && tmp.isBoolean())
    {
        ret->_shadow._shadowEnabled = tmp.toBoolean();

        if (ret->_shadow._shadowEnabled)
        {
            // default shadow values
            ret->_shadow._shadowOffset  = cocos2d::Size(5, 5);
            ret->_shadow._shadowBlur    = 1;
            ret->_shadow._shadowOpacity = 1;

            // shadow offset
            if (obj->getProperty("shadowOffsetX", &tmp) && tmp.isNumber()
                && obj->getProperty("shadowOffsetY", &tmp2) && tmp2.isNumber())
            {
                ret->_shadow._shadowOffset.width = tmp.toFloat();
                ret->_shadow._shadowOffset.height = tmp2.toFloat();
            }

            // shadow blur
            if (obj->getProperty("shadowBlur", &tmp) && tmp.isNumber())
            {
                ret->_shadow._shadowBlur = tmp.toNumber();
            }

            // shadow intensity
            if (obj->getProperty("shadowOpacity", &tmp) && tmp.isNumber())
            {
                ret->_shadow._shadowOpacity = tmp.toNumber();
            }
        }
    }

    // stroke
    if (obj->getProperty("strokeEnabled", &tmp) && tmp.isBoolean())
    {
        ret->_stroke._strokeEnabled = tmp.toBoolean();
        if (ret->_stroke._strokeEnabled)
        {
            // default stroke values
            ret->_stroke._strokeSize  = 1;
            ret->_stroke._strokeColor = cocos2d::Color3B::BLUE;

            // stroke color
            if (obj->getProperty("strokeStyle", &tmp) && tmp.isObject())
            {
                seval_to_Color3B(tmp, &ret->_stroke._strokeColor);
            }

            // stroke size
            if (obj->getProperty("lineWidth", &tmp) && tmp.isNumber())
            {
                ret->_stroke._strokeSize = tmp.toNumber();
            }

            // stroke alpha
            if (obj->getProperty("strokeAlpha", &tmp) && tmp.isNumber())
            {
                ret->_stroke._strokeAlpha = tmp.toUint8();
            }
        }
    }

    return true;
}
//
//bool seval_to_Acceleration(const se::Value& v, cocos2d::Acceleration* ret)
//{
//    assert(ret != nullptr);
//    assert(v.isObject());
//    se::Object* obj = v.toObject();
//    bool ok = false;
//    se::Value tmp;
//
//    ok = obj->getProperty("x", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, ret->x = ret->y = ret->z = ret->timestamp = 0.0);
//    ret->x = tmp.toNumber();
//
//    ok = obj->getProperty("y", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, ret->x = ret->y = ret->z = ret->timestamp = 0.0);
//    ret->y = tmp.toNumber();
//
//    ok = obj->getProperty("z", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, ret->x = ret->y = ret->z = ret->timestamp = 0.0);
//    ret->z = tmp.toNumber();
//
//    ok = obj->getProperty("timestamp", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, ret->x = ret->y = ret->z = ret->timestamp = 0.0);
//    ret->timestamp = tmp.toNumber();
//
//    return true;
//}
//
//bool seval_to_Quaternion(const se::Value& v, cocos2d::Quaternion* ret)
//{
//    assert(ret != nullptr);
//    assert(v.isObject());
//    se::Object* obj = v.toObject();
//    bool ok = false;
//    se::Value tmp;
//
//    ok = obj->getProperty("x", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = cocos2d::Quaternion::ZERO);
//    ret->x = tmp.toFloat();
//
//    ok = obj->getProperty("y", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = cocos2d::Quaternion::ZERO);
//    ret->y = tmp.toFloat();
//
//    ok = obj->getProperty("z", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = cocos2d::Quaternion::ZERO);
//    ret->z = tmp.toFloat();
//
//    ok = obj->getProperty("w", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = cocos2d::Quaternion::ZERO);
//    ret->w = tmp.toFloat();
//
//    return true;
//}
//
//bool seval_to_AffineTransform(const se::Value& v, cocos2d::AffineTransform* ret)
//{
//    static cocos2d::AffineTransform ZERO = {0, 0, 0, 0, 0, 0};
//
//    assert(ret != nullptr);
//    assert(v.isObject());
//    se::Value tmp;
//    se::Object* obj = v.toObject();
//    bool ok = false;
//
//    ok = obj->getProperty("a", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
//    ret->a = tmp.toFloat();
//
//    ok = obj->getProperty("b", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
//    ret->b = tmp.toFloat();
//
//    ok = obj->getProperty("c", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
//    ret->c = tmp.toFloat();
//
//    ok = obj->getProperty("d", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
//    ret->d = tmp.toFloat();
//
//    ok = obj->getProperty("tx", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
//    ret->tx = tmp.toFloat();
//
//    ok = obj->getProperty("ty", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
//    ret->ty = tmp.toFloat();
//
//    return true;
//}

//bool seval_to_Viewport(const se::Value& v, cocos2d::experimental::Viewport* ret)
//{
//    static cocos2d::experimental::Viewport ZERO = {0, 0, 0, 0};
//
//    assert(ret != nullptr);
//    assert(v.isObject());
//    se::Value tmp;
//    se::Object* obj = v.toObject();
//    bool ok = false;
//
//    ok = obj->getProperty("left", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
//    ret->_left = tmp.toFloat();
//
//    ok = obj->getProperty("bottom", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
//    ret->_bottom = tmp.toFloat();
//
//    ok = obj->getProperty("width", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
//    ret->_width = tmp.toFloat();
//
//    ok = obj->getProperty("height", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
//    ret->_height = tmp.toFloat();
//
//    return true;
//}

bool seval_to_Data(const se::Value& v, cocos2d::Data* ret)
{
    assert(ret != nullptr);
    assert(v.isObject() && v.toObject()->isTypedArray());
    uint8_t* ptr = nullptr;
    size_t length = 0;
    bool ok = v.toObject()->getTypedArrayData(&ptr, &length);
    if (ok)
    {
        ret->copy(ptr, length);
    }
    else
    {
        ret->clear();
    }

    return ok;
}

//bool seval_to_DownloaderHints(const se::Value& v, cocos2d::network::DownloaderHints* ret)
//{
//    static cocos2d::network::DownloaderHints ZERO = {0, 0, ""};
//    assert(ret != nullptr);
//    assert(v.isObject());
//    se::Value tmp;
//    se::Object* obj = v.toObject();
//    bool ok = false;
//
//    ok = obj->getProperty("countOfMaxProcessingTasks", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
//    ret->countOfMaxProcessingTasks = tmp.toUint32();
//
//    ok = obj->getProperty("timeoutInSeconds", &tmp);
//    SE_PRECONDITION3(ok && tmp.isNumber(), false, *ret = ZERO);
//    ret->timeoutInSeconds = tmp.toUint32();
//
//    ok = obj->getProperty("tempFileNameSuffix", &tmp);
//    SE_PRECONDITION3(ok && tmp.isString(), false, *ret = ZERO);
//    ret->tempFileNameSuffix = tmp.toString();
//
//    return ok;
//}
//
//bool seval_to_TTFConfig(const se::Value& v, cocos2d::TTFConfig* ret)
//{
//    se::Value js_fontFilePath;
//    se::Value js_fontSize;
//    se::Value js_outlineSize;
//    se::Value js_glyphs;
//    se::Value js_customGlyphs;
//    se::Value js_distanceFieldEnable;
//
//    std::string fontFilePath,customGlyphs;
//
//    bool ok = v.isObject();
//    if (ok)
//    {
//        se::Object* obj = v.toObject();
//        if (obj->getProperty("fontFilePath", &js_fontFilePath) && js_fontFilePath.isString())
//        {
//            ok &= seval_to_std_string(js_fontFilePath, &ret->fontFilePath);
//        }
//
//        if (obj->getProperty("fontSize", &js_fontSize) && js_fontSize.isNumber())
//        {
//            ret->fontSize = (float)js_fontSize.toNumber();
//        }
//
//        if (obj->getProperty("outlineSize", &js_outlineSize) && js_outlineSize.isNumber())
//        {
//            ret->outlineSize = (int)js_outlineSize.toNumber();
//        }
//
//        if (obj->getProperty("glyphs", &js_glyphs) && js_glyphs.isNumber())
//        {
//            ret->glyphs = (cocos2d::GlyphCollection)(js_glyphs.toInt32());
//        }
//
//        if (obj->getProperty("customGlyphs", &js_customGlyphs) && js_customGlyphs.isString())
//        {
//            ok &= seval_to_std_string(js_customGlyphs,&customGlyphs);
//        }
//        if(ret->glyphs == cocos2d::GlyphCollection::CUSTOM && !customGlyphs.empty())
//            ret->customGlyphs = customGlyphs.c_str();
//        else
//            ret->customGlyphs = "";
//
//        if (obj->getProperty("distanceFieldEnable", &js_distanceFieldEnable) && js_distanceFieldEnable.isBoolean())
//        {
//            ret->distanceFieldEnabled = js_distanceFieldEnable.toBoolean();
//        }
//    }
//
//    SE_PRECONDITION2(ok, false, "Error processing arguments");
//
//    return true;
//}
//
//bool seval_to_b2Vec2(const se::Value& v, b2Vec2* ret)
//{
//    static b2Vec2 ZERO(0.0f, 0.0f);
//    assert(v.isObject() && ret != nullptr);
//    se::Object* obj = v.toObject();
//    se::Value x;
//    se::Value y;
//    bool ok = obj->getProperty("x", &x);
//    SE_PRECONDITION3(ok && x.isNumber(), false, *ret = ZERO);
//    ok = obj->getProperty("y", &y);
//    SE_PRECONDITION3(ok && y.isNumber(), false, *ret = ZERO);
//    ret->x = x.toFloat();
//    ret->y = y.toFloat();
//    return true;
//}
//
//bool seval_to_b2AABB(const se::Value& v, b2AABB* ret)
//{
//    static b2AABB ZERO;
//    static bool __isFirst = true;
//    if (__isFirst)
//    {
//        ZERO.lowerBound.x = ZERO.lowerBound.y = 0;
//        ZERO.upperBound.x = ZERO.upperBound.y = 0;
//        __isFirst = false;
//    }
//
//    assert(v.isObject() && ret != nullptr);
//    se::Object* obj = v.toObject();
//
//    bool ok = false;
//    se::Value tmp;
//    ok = obj->getProperty("lowerBound", &tmp);
//    SE_PRECONDITION3(ok && tmp.isObject(), false, *ret = ZERO);
//    ok = seval_to_b2Vec2(tmp, &ret->lowerBound);
//    SE_PRECONDITION3(ok, false, *ret = ZERO);
//
//    ok = obj->getProperty("upperBound", &tmp);
//    SE_PRECONDITION3(ok && tmp.isObject(), false, *ret = ZERO);
//    ok = seval_to_b2Vec2(tmp, &ret->upperBound);
//    SE_PRECONDITION3(ok, false, *ret = ZERO);
//
//    return true;
//}

bool seval_to_std_vector_Texture(const se::Value& v, std::vector<cocos2d::gfx::Texture*>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    assert(v.toObject()->isArray());

    se::Object* obj = v.toObject();

    uint32_t len = 0;
    if (obj->getArrayLength(&len) && len > 0)
    {
        for (uint32_t i = 0; i < len; ++i)
        {
            se::Value textureVal;
            if (obj->getArrayElement(i, &textureVal) && textureVal.isObject())
            {
                cocos2d::gfx::Texture* texture = nullptr;
                seval_to_native_ptr(textureVal, &texture);
                ret->push_back(texture);
            }
        }
    }

    return true;
}

bool seval_to_std_vector_RenderTarget(const se::Value& v, std::vector<cocos2d::gfx::RenderTarget*>* ret)
{
    assert(false);
    return true;
}

bool seval_to_TextureOptions(const se::Value& v, cocos2d::gfx::Texture::Options* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    se::Value images;
    if (obj->getProperty("images", &images) && images.isObject() && images.toObject()->isArray())
    {
        uint32_t len = 0;
        se::Object* arr = images.toObject();
        if (arr->getArrayLength(&len))
        {
            se::Value imageVal;
            for (uint32_t i = 0; i < len; ++i)
            {
                if (arr->getArrayElement(i, &imageVal))
                {
                    if (imageVal.isObject() && imageVal.toObject()->isTypedArray())
                    {
                        uint8_t* data = nullptr;
                        size_t bytes = 0;
                        cocos2d::Data imgData;
                        imageVal.toObject()->getTypedArrayData(&data, &bytes);
                        imgData.copy((unsigned char*)data, bytes);
                        ret->images.push_back(std::move(imgData));
                    }
                    else
                    {
                        SE_LOGE("Texture image isn't a typed array object!");
                        assert(false);
                    }
                }
            }
        }
    }

    se::Value tmp;
    if (obj->getProperty("mipmap", &tmp))
    {
        seval_to_boolean(tmp, &ret->hasMipmap);
    }

    if (obj->getProperty("width", &tmp))
    {
        seval_to_uint16(tmp, &ret->width);
    }

    if (obj->getProperty("height", &tmp))
    {
        seval_to_uint16(tmp, &ret->height);
    }

    if (obj->getProperty("format", &tmp))
    {
        seval_to_uint8(tmp, (uint8_t*)&ret->format);
    }

    if (obj->getProperty("anisotropy", &tmp))
    {
        seval_to_int32(tmp, &ret->anisotropy);
    }

    if (obj->getProperty("minFilter", &tmp))
    {
        seval_to_int8(tmp, (int8_t*)&ret->minFilter);
    }

    if (obj->getProperty("magFilter", &tmp))
    {
        seval_to_int8(tmp, (int8_t*)&ret->magFilter);
    }

    if (obj->getProperty("mipFilter", &tmp))
    {
        seval_to_int8(tmp, (int8_t*)&ret->mipFilter);
    }

    if (obj->getProperty("wrapS", &tmp))
    {
        seval_to_uint16(tmp, (uint16_t*)&ret->wrapS);
    }

    if (obj->getProperty("wrapT", &tmp))
    {
        seval_to_uint16(tmp, (uint16_t*)&ret->wrapT);
    }

    if (obj->getProperty("flipY", &tmp))
    {
        seval_to_boolean(tmp, &ret->flipY);
    }

    if (obj->getProperty("premultiplyAlpha", &tmp))
    {
        seval_to_boolean(tmp, &ret->premultiplyAlpha);
    }

    return true;
}

bool seval_to_TextureSubImageOption(const se::Value& v, cocos2d::gfx::Texture::SubImageOption* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    se::Value imageVal;
    if (obj->getProperty("image", &imageVal) && imageVal.isObject() && imageVal.toObject()->isTypedArray())
    {
        uint8_t* imgData = nullptr;
        size_t imgDataLen = 0;
        imageVal.toObject()->getTypedArrayData(&imgData, &imgDataLen);
        ret->image.copy(imgData, imgDataLen);
    }

    se::Value tmp;
    if (obj->getProperty("mipmap", &tmp))
    {
        seval_to_boolean(tmp, &ret->hasMipmap);
    }

    if (obj->getProperty("x", &tmp))
    {
        seval_to_uint16(tmp, &ret->x);
    }

    if (obj->getProperty("y", &tmp))
    {
        seval_to_uint16(tmp, &ret->y);
    }

    if (obj->getProperty("width", &tmp))
    {
        seval_to_uint16(tmp, &ret->width);
    }

    if (obj->getProperty("level", &tmp))
    {
        seval_to_int32(tmp, &ret->level);
    }
    
    if (obj->getProperty("height", &tmp))
    {
        seval_to_uint16(tmp, &ret->height);
    }

    if (obj->getProperty("format", &tmp))
    {
        seval_to_uint8(tmp, (uint8_t*)&ret->format);
    }

    if (obj->getProperty("anisotropy", &tmp))
    {
        seval_to_int32(tmp, &ret->anisotropy);
    }

    if (obj->getProperty("minFilter", &tmp))
    {
        seval_to_int8(tmp, (int8_t*)&ret->minFilter);
    }

    if (obj->getProperty("magFilter", &tmp))
    {
        seval_to_int8(tmp, (int8_t*)&ret->magFilter);
    }

    if (obj->getProperty("mipFilter", &tmp))
    {
        seval_to_int8(tmp, (int8_t*)&ret->mipFilter);
    }

    if (obj->getProperty("wrapS", &tmp))
    {
        seval_to_uint16(tmp, (uint16_t*)&ret->wrapS);
    }

    if (obj->getProperty("wrapT", &tmp))
    {
        seval_to_uint16(tmp, (uint16_t*)&ret->wrapT);
    }

    if (obj->getProperty("flipY", &tmp))
    {
        seval_to_boolean(tmp, &ret->flipY);
    }

    if (obj->getProperty("premultiplyAlpha", &tmp))
    {
        seval_to_boolean(tmp, &ret->premultiplyAlpha);
    }

    return true;
}

bool seval_to_TextureImageOption(const se::Value& v, cocos2d::gfx::Texture::ImageOption* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    se::Value imageVal;
    if (obj->getProperty("image", &imageVal) && imageVal.isObject() && imageVal.toObject()->isTypedArray())
    {
        uint8_t* imgData = nullptr;
        size_t imgDataLen = 0;
        imageVal.toObject()->getTypedArrayData(&imgData, &imgDataLen);
        ret->image.copy(imgData, imgDataLen);
    }

    se::Value tmp;
    if (obj->getProperty("mipmap", &tmp))
    {
        seval_to_boolean(tmp, &ret->hasMipmap);
    }

    if (obj->getProperty("width", &tmp))
    {
        seval_to_uint16(tmp, &ret->width);
    }

    if (obj->getProperty("level", &tmp))
    {
        seval_to_int32(tmp, &ret->level);
    }

    if (obj->getProperty("height", &tmp))
    {
        seval_to_uint16(tmp, &ret->height);
    }

    if (obj->getProperty("format", &tmp))
    {
        seval_to_uint8(tmp, (uint8_t*)&ret->format);
    }

    if (obj->getProperty("anisotropy", &tmp))
    {
        seval_to_int32(tmp, &ret->anisotropy);
    }

    if (obj->getProperty("minFilter", &tmp))
    {
        seval_to_int8(tmp, (int8_t*)&ret->minFilter);
    }

    if (obj->getProperty("magFilter", &tmp))
    {
        seval_to_int8(tmp, (int8_t*)&ret->magFilter);
    }

    if (obj->getProperty("mipFilter", &tmp))
    {
        seval_to_int8(tmp, (int8_t*)&ret->mipFilter);
    }

    if (obj->getProperty("wrapS", &tmp))
    {
        seval_to_uint16(tmp, (uint16_t*)&ret->wrapS);
    }

    if (obj->getProperty("wrapT", &tmp))
    {
        seval_to_uint16(tmp, (uint16_t*)&ret->wrapT);
    }

    if (obj->getProperty("flipY", &tmp))
    {
        seval_to_boolean(tmp, &ret->flipY);
    }

    if (obj->getProperty("premultiplyAlpha", &tmp))
    {
        seval_to_boolean(tmp, &ret->premultiplyAlpha);
    }

    return true;
}

bool seval_to_EffectProperty(const se::Value& v, std::unordered_map<std::string, cocos2d::gfx::Effect::Property>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());

    se::Object* obj = v.toObject();
    std::vector<std::string> keys;
    obj->getAllKeys(&keys);

    for (const auto& key : keys)
    {
        se::Value value;
        cocos2d::gfx::Effect::Property property;
        if (obj->getProperty(key.c_str(), &value) && value.isObject())
        {
            if (seval_to_TechniqueParameter(value, &property))
            {
                ret->emplace(key, std::move(property));
            }
        }
    }

    return true;
}

bool seval_to_EffectDefineTemplate(const se::Value& v, std::vector<cocos2d::ValueMap>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject() && v.toObject()->isArray());

    se::Object* obj = v.toObject();
    uint32_t len = 0;
    obj->getArrayLength(&len);
    for (uint32_t i = 0; i < len; ++i)
    {
        se::Value value;
        cocos2d::ValueMap valMap;
        if (obj->getArrayElement(i, &value) && value.isObject())
        {
            if (seval_to_ccvaluemap(value, &valMap))
            {
                ret->push_back(std::move(valMap));
            }
        }
    }

    return true;
}

bool seval_to_TechniqueParameter(const se::Value& v, cocos2d::gfx::Technique::Parameter* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    se::Value tmp;
    std::string name;
    uint8_t size = 0;
    cocos2d::gfx::Technique::Parameter::Type type = cocos2d::gfx::Technique::Parameter::Type::UNKNOWN;

    bool ok = false;
    if (obj->getProperty("name", &tmp))
    {
        ok = seval_to_std_string(tmp, &name);
        SE_PRECONDITION2(ok, false, "Convert Parameter name failed!");
    }

    if (obj->getProperty("type", &tmp))
    {
        uint8_t v = 0;
        ok = seval_to_uint8(tmp, &v);
        SE_PRECONDITION2(ok, false, "Convert Parameter type failed!");
        type = (cocos2d::gfx::Technique::Parameter::Type)v;
    }

    if (obj->getProperty("size", &tmp))
    {
        ok = seval_to_uint8(tmp, &size);
        SE_PRECONDITION2(ok, false, "Convert Parameter size failed!");
    }

    if (obj->getProperty("val", &tmp))
    {
        if (tmp.isNumber())
        {

        }
        else if (tmp.isObject())
        {
            se::Object* valObj = tmp.toObject();
            if (valObj->isArray())
            {

            }
            else if (valObj->isTypedArray())
            {
                uint8_t* data = nullptr;
                size_t len = 0;
                if (valObj->getTypedArrayData(&data, &len))
                {

                }
            }
            else if (valObj->isArrayBuffer())
            {
                uint8_t* data = nullptr;
                size_t len = 0;
                if (valObj->getArrayBufferData(&data, &len))
                {

                }
            }
            else
            {
                assert(false);
            }
        }
        else
        {
            assert(false);
        }
    }

    return true;
}

bool seval_to_std_vector_TechniqueParameter(const se::Value& v, std::vector<cocos2d::gfx::Technique::Parameter>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());

    se::Object* obj = v.toObject();
    uint32_t len = 0;
    obj->getArrayLength(&len);
    ret->reserve(len);
    for (uint32_t i = 0; i < len; ++i)
    {
        se::Value data;
        if (obj->getArrayElement(i, &data))
        {
            cocos2d::gfx::Technique::Parameter parameter;
            seval_to_TechniqueParameter(data, &parameter);
            ret->push_back(std::move(parameter));
        }
    }

    return true;
}

bool seval_to_ProgramLib_Template(const se::Value& v, cocos2d::gfx::ProgramLib::Template* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();

    bool ok = false;
    se::Value tmp;

    if (obj->getProperty("id", &tmp))
    {
        ok = seval_to_uint32(tmp, &ret->id);
        SE_PRECONDITION2(ok, false, "Convert id failed!");
    }

    if (obj->getProperty("name", &tmp))
    {
        ok = seval_to_std_string(tmp, &ret->name);
        SE_PRECONDITION2(ok, false, "Convert name failed!");
    }

    if (obj->getProperty("vert", &tmp))
    {
        ok = seval_to_std_string(tmp, &ret->vert);
        SE_PRECONDITION2(ok, false, "Convert vert failed!");
    }

    if (obj->getProperty("frag", &tmp))
    {
        ok = seval_to_std_string(tmp, &ret->frag);
        SE_PRECONDITION2(ok, false, "Convert frag failed!");
    }

    if (obj->getProperty("defines", &tmp))
    {
        ok = seval_to_ccvaluevector(tmp, &ret->defines);
        SE_PRECONDITION2(ok, false, "Convert defines failed!");
    }

    return true;
}

bool seval_to_std_vector_ProgramLib_Template(const se::Value& v, std::vector<cocos2d::gfx::ProgramLib::Template>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());

    se::Object* obj = v.toObject();
    uint32_t len = 0;
    obj->getArrayLength(&len);
    ret->reserve(len);
    for (uint32_t i = 0; i < len; ++i)
    {
        se::Value data;
        if (obj->getArrayElement(i, &data))
        {
            cocos2d::gfx::ProgramLib::Template parameter;
            if (seval_to_ProgramLib_Template(data, &parameter))
            {
                ret->push_back(std::move(parameter));
            }
        }
    }

    return true;
}


//////////////////////////////////////////////////////////////////////////////////
// native to seval

bool int32_to_seval(int32_t v, se::Value* ret)
{
    ret->setInt32(v);
    return true;
}

bool uint32_to_seval(uint32_t v, se::Value* ret)
{
    ret->setUint32(v);
    return true;
}

bool int16_to_seval(uint16_t v, se::Value* ret)
{
    ret->setInt16(v);
    return true;
}

bool uint16_to_seval(uint16_t v, se::Value* ret)
{
    ret->setUint16(v);
    return true;
}

bool int8_to_seval(int8_t v, se::Value* ret)
{
    ret->setInt8(v);
    return true;
}

bool uint8_to_seval(uint8_t v, se::Value* ret)
{
    ret->setUint8(v);
    return true;
}

bool boolean_to_seval(bool v, se::Value* ret)
{
    ret->setBoolean(v);
    return true;
}

bool float_to_seval(float v, se::Value* ret)
{
    ret->setFloat(v);
    return true;
}

bool double_to_seval(double v, se::Value* ret)
{
    ret->setNumber(v);
    return true;
}

bool long_to_seval(long v, se::Value* ret)
{
    ret->setLong(v);
    return true;
}

bool ulong_to_seval(unsigned long v, se::Value* ret)
{
    ret->setUlong(v);
    return true;
}

bool longlong_to_seval(long long v, se::Value* ret)
{
    ret->setLong((long)v);
    return true;
}

bool ssize_to_seval(ssize_t v, se::Value* ret)
{
    ret->setLong((long)v);
    return true;
}

bool std_string_to_seval(const std::string& v, se::Value* ret)
{
    ret->setString(v);
    return true;
}

bool Vec2_to_seval(const cocos2d::Vec2& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject obj(se::Object::createPlainObject());
    obj->setProperty("x", se::Value(v.x));
    obj->setProperty("y", se::Value(v.y));
    ret->setObject(obj);

    return true;
}

bool Vec3_to_seval(const cocos2d::Vec3& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject obj(se::Object::createPlainObject());
    obj->setProperty("x", se::Value(v.x));
    obj->setProperty("y", se::Value(v.y));
    obj->setProperty("z", se::Value(v.z));
    ret->setObject(obj);

    return true;
}

bool Vec4_to_seval(const cocos2d::Vec4& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject obj(se::Object::createPlainObject());
    obj->setProperty("x", se::Value(v.x));
    obj->setProperty("y", se::Value(v.y));
    obj->setProperty("z", se::Value(v.z));
    obj->setProperty("w", se::Value(v.w));
    ret->setObject(obj);

    return true;
}

bool Mat4_to_seval(const cocos2d::Mat4& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject obj(se::Object::createArrayObject(16));

    for (uint8_t i = 0; i < 16; ++i)
    {
        obj->setArrayElement(i, se::Value(v.m[i]));
    }

    ret->setObject(obj);
    return true;
}

bool Size_to_seval(const cocos2d::Size& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject obj(se::Object::createPlainObject());
    obj->setProperty("width", se::Value(v.width));
    obj->setProperty("height", se::Value(v.height));
    ret->setObject(obj);
    return true;
}

//bool Rect_to_seval(const cocos2d::Rect& v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    se::HandleObject obj(se::Object::createPlainObject());
//    obj->setProperty("x", se::Value(v.origin.x));
//    obj->setProperty("y", se::Value(v.origin.y));
//    obj->setProperty("width", se::Value(v.size.width));
//    obj->setProperty("height", se::Value(v.size.height));
//    ret->setObject(obj);
//
//    return true;
//}

bool Rect_to_seval(const cocos2d::gfx::Rect& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject obj(se::Object::createPlainObject());
    obj->setProperty("x", se::Value(v.x));
    obj->setProperty("y", se::Value(v.y));
    obj->setProperty("w", se::Value(v.w));
    obj->setProperty("h", se::Value(v.h));
    ret->setObject(obj);

    return true;
}

bool Color3B_to_seval(const cocos2d::Color3B& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject obj(se::Object::createPlainObject());
    obj->setProperty("r", se::Value(v.r));
    obj->setProperty("g", se::Value(v.g));
    obj->setProperty("b", se::Value(v.b));
    obj->setProperty("a", se::Value(255));
    ret->setObject(obj);

    return true;
}

bool Color4B_to_seval(const cocos2d::Color4B& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject obj(se::Object::createPlainObject());
    obj->setProperty("r", se::Value(v.r));
    obj->setProperty("g", se::Value(v.g));
    obj->setProperty("b", se::Value(v.b));
    obj->setProperty("a", se::Value(v.a));
    ret->setObject(obj);

    return true;
}

bool Color4F_to_seval(const cocos2d::Color4F& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject obj(se::Object::createPlainObject());
    obj->setProperty("r", se::Value(v.r));
    obj->setProperty("g", se::Value(v.g));
    obj->setProperty("b", se::Value(v.b));
    obj->setProperty("a", se::Value(v.a));
    ret->setObject(obj);

    return true;
}

bool Color3F_to_seval(const cocos2d::Color3F& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject obj(se::Object::createPlainObject());
    obj->setProperty("r", se::Value(v.r));
    obj->setProperty("g", se::Value(v.g));
    obj->setProperty("b", se::Value(v.b));
    ret->setObject(obj);
    return true;
}

bool ccvalue_to_seval(const cocos2d::Value& v, se::Value* ret)
{
    assert(ret != nullptr);
    bool ok = true;
    switch (v.getType())
    {
        case cocos2d::Value::Type::NONE:
            ret->setNull();
            break;
        case cocos2d::Value::Type::UNSIGNED:
            ret->setUint32(v.asUnsignedInt());
            break;
        case cocos2d::Value::Type::BOOLEAN:
            ret->setBoolean(v.asBool());
            break;
        case cocos2d::Value::Type::FLOAT:
        case cocos2d::Value::Type::DOUBLE:
            ret->setNumber(v.asDouble());
            break;
        case cocos2d::Value::Type::INTEGER:
            ret->setInt32(v.asInt());
            break;
        case cocos2d::Value::Type::STRING:
            ret->setString(v.asString());
            break;
        case cocos2d::Value::Type::VECTOR:
            ok = ccvaluevector_to_seval(v.asValueVector(), ret);
            break;
        case cocos2d::Value::Type::MAP:
            ok = ccvaluemap_to_seval(v.asValueMap(), ret);
            break;
        case cocos2d::Value::Type::INT_KEY_MAP:
            ok = ccvaluemapintkey_to_seval(v.asIntKeyMap(), ret);
            break;
        default:
            SE_LOGE("Could not the way to convert cocos2d::Value::Type (%d) type!", (int)v.getType());
            ok = false;
            break;
    }

    return ok;
}

bool ccvaluemap_to_seval(const cocos2d::ValueMap& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::HandleObject obj(se::Object::createPlainObject());
    bool ok = true;
    for (const auto& e : v)
    {
        const std::string& key = e.first;
        const cocos2d::Value& value = e.second;

        if (key.empty())
            continue;

        se::Value tmp;
        if (!ccvalue_to_seval(value, &tmp))
        {
            ok = false;
            ret->setUndefined();
            break;
        }

        obj->setProperty(key.c_str(), tmp);
    }
    if (ok)
        ret->setObject(obj);

    return ok;
}

bool ccvaluemapintkey_to_seval(const cocos2d::ValueMapIntKey& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::HandleObject obj(se::Object::createPlainObject());
    bool ok = true;
    for (const auto& e : v)
    {
        std::stringstream keyss;
        keyss << e.first;
        std::string key = keyss.str();
        const cocos2d::Value& value = e.second;

        if (key.empty())
            continue;

        se::Value tmp;
        if (!ccvalue_to_seval(value, &tmp))
        {
            ok = false;
            ret->setUndefined();
            break;
        }

        obj->setProperty(key.c_str(), tmp);
    }
    if (ok)
        ret->setObject(obj);

    return ok;
}

bool ccvaluevector_to_seval(const cocos2d::ValueVector& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject obj(se::Object::createArrayObject(v.size()));
    bool ok = true;

    uint32_t i = 0;
    for (const auto& value : v)
    {
        se::Value tmp;
        if (!ccvalue_to_seval(value, &tmp))
        {
            ok = false;
            ret->setUndefined();
            break;
        }

        obj->setArrayElement(i, tmp);
        ++i;
    }
    if (ok)
        ret->setObject(obj);

    return ok;
}

bool blendfunc_to_seval(const cocos2d::BlendFunc& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject obj(se::Object::createPlainObject());
    obj->setProperty("src", se::Value(v.src));
    obj->setProperty("dst", se::Value(v.dst));
    ret->setObject(obj);

    return true;
}

namespace {

    template<typename T>
    bool std_vector_T_to_seval(const std::vector<T>& v, se::Value* ret)
    {
        assert(ret != nullptr);
        se::HandleObject obj(se::Object::createArrayObject(v.size()));
        bool ok = true;

        uint32_t i = 0;
        for (const auto& value : v)
        {
            if (!obj->setArrayElement(i, se::Value(value)))
            {
                ok = false;
                ret->setUndefined();
                break;
            }
            ++i;
        }

        if (ok)
            ret->setObject(obj);

        return ok;
    }

}

bool std_vector_string_to_seval(const std::vector<std::string>& v, se::Value* ret)
{
    return std_vector_T_to_seval(v, ret);
}

bool std_vector_int_to_seval(const std::vector<int>& v, se::Value* ret)
{
    return std_vector_T_to_seval(v, ret);
}

bool std_vector_float_to_seval(const std::vector<float>& v, se::Value* ret)
{
    return std_vector_T_to_seval(v, ret);
}

//bool std_vector_Touch_to_seval(const std::vector<cocos2d::Touch*>& v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    se::HandleObject arr(se::Object::createArrayObject(v.size()));
//
//    uint32_t i = 0;
//    se::Value tmp;
//    bool ok = true;
//    for (const auto& touch : v)
//    {
//        if (!native_ptr_to_seval<cocos2d::Touch>(touch, &tmp))
//        {
//            ok = false;
//            break;
//        }
//        arr->setArrayElement(i, tmp);
//        ++i;
//    }
//    if (ok)
//        ret->setObject(arr);
//    else
//        ret->setUndefined();
//
//    return ok;
//}

bool std_map_string_string_to_seval(const std::map<std::string, std::string>& v, se::Value* ret)
{
    assert(ret != nullptr);

    se::HandleObject obj(se::Object::createPlainObject());
    bool ok = true;
    for (const auto& e : v)
    {
        const std::string& key = e.first;
        const std::string& value = e.second;

        if (key.empty())
            continue;

        se::Value tmp;
        if (!std_string_to_seval(value, &tmp))
        {
            ok = false;
            ret->setUndefined();
            break;
        }

        obj->setProperty(key.c_str(), tmp);
    }

    if (ok)
        ret->setObject(obj);
    
    return ok;
}

//FIXME: why v has to be a pointer?
//bool uniform_to_seval(const cocos2d::Uniform* v, se::Value* ret)
//{
//    assert(v != nullptr && ret != nullptr);
//    se::HandleObject obj(se::Object::createPlainObject());
//    obj->setProperty("location", se::Value(v->location));
//    obj->setProperty("size", se::Value(v->size));
//    obj->setProperty("type", se::Value(v->type));
//    obj->setProperty("name", se::Value(v->name));
//    ret->setObject(obj);
//
//    return true;
//}
//
//bool FontDefinition_to_seval(const cocos2d::FontDefinition& v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    se::Value tmp;
//
//    se::HandleObject obj(se::Object::createPlainObject());
//    bool ok = true;
//    do
//    {
//        obj->setProperty("fontName", se::Value(v._fontName));
//        obj->setProperty("fontSize", se::Value(v._fontSize));
//        obj->setProperty("textAlign", se::Value((int32_t)v._alignment));
//        obj->setProperty("verticalAlign", se::Value((int32_t)v._vertAlignment));
//
//        if (!Color3B_to_seval(v._fontFillColor, &tmp))
//        {
//            ok = false;
//            break;
//        }
//        obj->setProperty("fillStyle", tmp);
//        obj->setProperty("boundingWidth", se::Value(v._dimensions.width));
//        obj->setProperty("boundingHeight", se::Value(v._dimensions.height));
//
//        obj->setProperty("shadowEnabled", se::Value(v._shadow._shadowEnabled));
//        obj->setProperty("shadowOffsetX", se::Value(v._shadow._shadowOffset.width));
//        obj->setProperty("shadowOffsetY", se::Value(v._shadow._shadowOffset.height));
//        obj->setProperty("shadowBlur", se::Value(v._shadow._shadowBlur));
//        obj->setProperty("shadowOpacity", se::Value(v._shadow._shadowOpacity));
//
//        obj->setProperty("strokeEnabled", se::Value(v._stroke._strokeEnabled));
//        if (!Color3B_to_seval(v._stroke._strokeColor, &tmp))
//        {
//            ok = false;
//            break;
//        }
//
//        obj->setProperty("strokeStyle", tmp);
//        obj->setProperty("lineWidth", se::Value(v._stroke._strokeSize));
//        obj->setProperty("strokeAlpha", se::Value(v._stroke._strokeAlpha));
//    } while (false);
//
//    ret->setObject(obj);
//
//    return ok;
//}
//
////FIXME: why v has to be a pointer?
//bool Acceleration_to_seval(const cocos2d::Acceleration* v, se::Value* ret)
//{
//    assert(v != nullptr && ret != nullptr);
//    se::HandleObject obj(se::Object::createPlainObject());
//    obj->setProperty("x", se::Value(v->x));
//    obj->setProperty("y", se::Value(v->y));
//    obj->setProperty("z", se::Value(v->z));
//    obj->setProperty("timestamp", se::Value(v->timestamp));
//    ret->setObject(obj);
//
//    return true;
//}
//
//bool Quaternion_to_seval(const cocos2d::Quaternion& v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    se::HandleObject obj(se::Object::createPlainObject());
//    obj->setProperty("x", se::Value(v.x));
//    obj->setProperty("y", se::Value(v.y));
//    obj->setProperty("z", se::Value(v.z));
//    obj->setProperty("w", se::Value(v.w));
//    ret->setObject(obj);
//
//    return true;
//}
//
//bool ManifestAsset_to_seval(const cocos2d::extension::ManifestAsset& v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    se::HandleObject obj(se::Object::createPlainObject());
//    obj->setProperty("md5", se::Value(v.md5));
//    obj->setProperty("path", se::Value(v.path));
//    obj->setProperty("compressed", se::Value(v.compressed));
//    obj->setProperty("size", se::Value(v.size));
//    obj->setProperty("downloadState", se::Value(v.downloadState));
//    ret->setObject(obj);
//
//    return true;
//}
//
//bool AffineTransform_to_seval(const cocos2d::AffineTransform& v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    se::HandleObject obj(se::Object::createPlainObject());
//    obj->setProperty("a", se::Value(v.a));
//    obj->setProperty("b", se::Value(v.b));
//    obj->setProperty("c", se::Value(v.c));
//    obj->setProperty("d", se::Value(v.d));
//    obj->setProperty("tx", se::Value(v.tx));
//    obj->setProperty("ty", se::Value(v.ty));
//    ret->setObject(obj);
//
//    return true;
//}

//bool Viewport_to_seval(const cocos2d::experimental::Viewport& v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    se::HandleObject obj(se::Object::createPlainObject());
//    obj->setProperty("left", se::Value(v._left));
//    obj->setProperty("bottom", se::Value(v._bottom));
//    obj->setProperty("width", se::Value(v._width));
//    obj->setProperty("height", se::Value(v._height));
//    ret->setObject(obj);
//
//    return true;
//}

bool Data_to_seval(const cocos2d::Data& v, se::Value* ret)
{
    assert(ret != nullptr);
    assert(!v.isNull());
    se::HandleObject obj(se::Object::createTypedArray(se::Object::TypedArrayType::UINT8, v.getBytes(), v.getSize()));
    ret->setObject(obj);
    return true;
}

//bool DownloadTask_to_seval(const cocos2d::network::DownloadTask& v, se::Value* ret)
//{
//    assert(ret != nullptr);
//
//    se::HandleObject obj(se::Object::createPlainObject());
//    obj->setProperty("identifier", se::Value(v.identifier));
//    obj->setProperty("requestURL", se::Value(v.requestURL));
//    obj->setProperty("storagePath", se::Value(v.storagePath));
//    ret->setObject(obj);
//
//    return true;
//}
//
//// Spine conversions
//bool speventdata_to_seval(const spEventData* v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    if (v == nullptr)
//    {
//        ret->setNull();
//        return true;
//    }
//
//    se::HandleObject obj(se::Object::createPlainObject());
//    obj->setProperty("name", se::Value(v->name));
//    obj->setProperty("intValue", se::Value(v->intValue));
//    obj->setProperty("floatValue", se::Value(v->floatValue));
//    obj->setProperty("stringValue", se::Value(v->stringValue));
//    ret->setObject(obj);
//
//    return true;
//}
//
//bool spevent_to_seval(const spEvent* v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    if (v == nullptr)
//    {
//        ret->setNull();
//        return true;
//    }
//
//    se::HandleObject obj(se::Object::createPlainObject());
//
//    se::Value dataVal;
//    SE_PRECONDITION3(speventdata_to_seval(v->data, &dataVal), false, ret->setUndefined());
//    obj->setProperty("data", dataVal);
//    obj->setProperty("time", se::Value(v->time));
//    obj->setProperty("intValue", se::Value(v->intValue));
//    obj->setProperty("floatValue", se::Value(v->floatValue));
//    obj->setProperty("stringValue", se::Value(v->stringValue));
//    ret->setObject(obj);
//
//    return true;
//}
//
//bool spbonedata_to_seval(const spBoneData* v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    if (v == nullptr)
//    {
//        ret->setNull();
//        return true;
//    }
//
//    se::HandleObject obj(se::Object::createPlainObject());
//
//    // root haven't parent
//    se::Value parentVal;
//    if (0 != strcmp(v->name, "root") && v->parent)
//    {
//        SE_PRECONDITION3(spbonedata_to_seval(v->parent, &parentVal), false, ret->setUndefined());
//    }
//
//    obj->setProperty("index", se::Value(v->index));
//    obj->setProperty("name", se::Value(v->name));
//    obj->setProperty("parent", parentVal);
//    obj->setProperty("length", se::Value(v->length));
//    obj->setProperty("x", se::Value(v->x));
//    obj->setProperty("y", se::Value(v->y));
//    obj->setProperty("rotation", se::Value(v->rotation));
//    obj->setProperty("scaleX", se::Value(v->scaleX));
//    obj->setProperty("scaleY", se::Value(v->scaleY));
//    obj->setProperty("shearX", se::Value(v->shearX));
//    obj->setProperty("shearY", se::Value(v->shearY));
//    obj->setProperty("transformMode", se::Value(v->transformMode));
//
//    ret->setObject(obj);
//
//    return true;
//}
//
//bool spbone_to_seval(const spBone* v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    if (v == nullptr)
//    {
//        ret->setNull();
//        return true;
//    }
//
//    se::HandleObject obj(se::Object::createPlainObject());
//
//    // root haven't parent
//    se::Value parentVal;
//    if (0 != strcmp(v->data->name, "root") && v->parent)
//    {
//        SE_PRECONDITION3(spbone_to_seval(v->parent, &parentVal), false, ret->setUndefined());
//    }
//
//    se::Value data;
//    SE_PRECONDITION3(spbonedata_to_seval(v->data, &data), false, ret->setUndefined());
//
//    obj->setProperty("data", data);
//    obj->setProperty("parent", parentVal);
//    obj->setProperty("x", se::Value(v->x));
//    obj->setProperty("y", se::Value(v->y));
//    obj->setProperty("rotation", se::Value(v->rotation));
//    obj->setProperty("scaleX", se::Value(v->scaleX));
//    obj->setProperty("scaleY", se::Value(v->scaleY));
//    obj->setProperty("shearX", se::Value(v->shearX));
//    obj->setProperty("shearY", se::Value(v->shearY));
//    obj->setProperty("m00", se::Value(v->a));
//    obj->setProperty("m01", se::Value(v->b));
//    obj->setProperty("m10", se::Value(v->c));
//    obj->setProperty("m11", se::Value(v->d));
//    obj->setProperty("worldX", se::Value(v->worldX));
//    obj->setProperty("worldY", se::Value(v->worldY));
//
//    ret->setObject(obj);
//
//    return true;
//}
//
//bool spskeleton_to_seval(const spSkeleton* v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    if (v == nullptr)
//    {
//        ret->setNull();
//        return true;
//    }
//
//    se::HandleObject obj(se::Object::createPlainObject());
//
//    obj->setProperty("x", se::Value(v->x));
//    obj->setProperty("y", se::Value(v->y));
//    obj->setProperty("flipX", se::Value(v->flipX));
//    obj->setProperty("flipY", se::Value(v->flipY));
//    obj->setProperty("time", se::Value(v->time));
//    obj->setProperty("boneCount", se::Value(v->bonesCount));
//    obj->setProperty("slotCount", se::Value(v->slotsCount));
//
//    ret->setObject(obj);
//    return true;
//}
//
//bool spattachment_to_seval(const spAttachment* v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    if (v == nullptr)
//    {
//        ret->setNull();
//        return true;
//    }
//
//    se::HandleObject obj(se::Object::createPlainObject());
//
//    obj->setProperty("name", se::Value(v->name));
//    obj->setProperty("type", se::Value((int32_t)v->type));
//
//    ret->setObject(obj);
//    return true;
//}
//
//bool spslotdata_to_seval(const spSlotData* v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    if (v == nullptr)
//    {
//        ret->setNull();
//        return true;
//    }
//
//    se::HandleObject obj(se::Object::createPlainObject());
//
//    se::Value boneData;
//    SE_PRECONDITION3(spbonedata_to_seval(v->boneData, &boneData), false, ret->setUndefined());
//
//    obj->setProperty("name", se::Value(v->name));
//    obj->setProperty("attachmentName", se::Value(v->attachmentName));
//    obj->setProperty("r", se::Value(v->r));
//    obj->setProperty("g", se::Value(v->g));
//    obj->setProperty("b", se::Value(v->b));
//    obj->setProperty("a", se::Value(v->a));
//    obj->setProperty("blendMode", se::Value((int32_t)v->blendMode));
//    obj->setProperty("boneData", boneData);
//
//    ret->setObject(obj);
//    return true;
//}
//
//bool spslot_to_seval(const spSlot* v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    if (v == nullptr)
//    {
//        ret->setNull();
//        return true;
//    }
//
//    se::HandleObject obj(se::Object::createPlainObject());
//
//    se::Value bone;
//    SE_PRECONDITION3(spbone_to_seval(v->bone, &bone), false, ret->setUndefined());
//
//    se::Value attachment;
//    SE_PRECONDITION3(spattachment_to_seval(v->attachment, &attachment), false, ret->setUndefined());
//
//    se::Value data;
//    SE_PRECONDITION3(spslotdata_to_seval(v->data, &data), false, ret->setUndefined());
//
//    obj->setProperty("r", se::Value(v->r));
//    obj->setProperty("g", se::Value(v->g));
//    obj->setProperty("b", se::Value(v->b));
//    obj->setProperty("a", se::Value(v->a));
//    obj->setProperty("bone", bone);
//    obj->setProperty("attachment", attachment);
//    obj->setProperty("data", data);
//
//    ret->setObject(obj);
//
//    return true;
//}
//
//bool sptimeline_to_seval(const spTimeline* v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    if (v == nullptr)
//    {
//        ret->setNull();
//        return true;
//    }
//
//    se::HandleObject obj(se::Object::createPlainObject());
//
//    obj->setProperty("type", se::Value((int32_t)v->type));
//
//    ret->setObject(obj);
//    return true;
//}
//
//bool spanimationstate_to_seval(const spAnimationState* v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    if (v == nullptr)
//    {
//        ret->setNull();
//        return true;
//    }
//
//    se::HandleObject obj(se::Object::createPlainObject());
//
//    obj->setProperty("timeScale", se::Value(v->timeScale));
//    obj->setProperty("trackCount", se::Value(v->tracksCount));
//
//    ret->setObject(obj);
//    return true;
//}
//
//bool spanimation_to_seval(const spAnimation* v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    if (v == nullptr)
//    {
//        ret->setNull();
//        return true;
//    }
//
//    se::HandleObject obj(se::Object::createPlainObject());
//
//    se::Value timelines;
//    SE_PRECONDITION3(sptimeline_to_seval(*v->timelines, &timelines), false, ret->setUndefined());
//
//    obj->setProperty("name", se::Value(v->name));
//    obj->setProperty("duration", se::Value(v->duration));
//    obj->setProperty("timelineCount", se::Value(v->timelinesCount));
//    obj->setProperty("timelines", timelines);
//
//    ret->setObject(obj);
//    return true;
//}
//
//bool sptrackentry_to_seval(const spTrackEntry* v, se::Value* ret)
//{
//    return native_ptr_to_rooted_seval<spTrackEntry>((spTrackEntry*)v, ret);
//}

// Box2d
//bool b2Vec2_to_seval(const b2Vec2& v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    se::HandleObject obj(se::Object::createPlainObject());
//    obj->setProperty("x", se::Value(v.x));
//    obj->setProperty("y", se::Value(v.y));
//    ret->setObject(obj);
//
//    return true;
//}
//
//bool b2Manifold_to_seval(const b2Manifold* v, se::Value* ret)
//{
//    assert(v != nullptr);
//    assert(ret != nullptr);
//    bool ok = false;
//    se::HandleObject obj(se::Object::createPlainObject());
//
//    do
//    {
//        se::Value tmp;
//        ok = b2Vec2_to_seval(v->localPoint, &tmp);
//        if (!ok) break;
//        obj->setProperty("localPoint", tmp);
//
//        ok = b2Vec2_to_seval(v->localNormal, &tmp);
//        if (!ok) break;
//        obj->setProperty("localNormal", tmp);
//
//        obj->setProperty("pointCount", se::Value(v->pointCount));
//        obj->setProperty("type", se::Value((int32_t)v->type));
//
//        se::HandleObject arr(se::Object::createArrayObject(v->pointCount));
//
//        for (int32 i = 0; i < v->pointCount; ++i)
//        {
//            const b2ManifoldPoint& p = v->points[i];
//
//            se::HandleObject arrElement(se::Object::createPlainObject());
//
//            arrElement->setProperty("normalImpulse", se::Value(p.normalImpulse));
//            arrElement->setProperty("tangentImpulse", se::Value(p.tangentImpulse));
//            se::Value localPointVal;
//            ok = b2Vec2_to_seval(p.localPoint, &localPointVal);
//            if (!ok) break;
//            arrElement->setProperty("localPoint", localPointVal);
//
//            arr->setArrayElement(i, se::Value(arrElement));
//        }
//
//        if (ok)
//            obj->setProperty("points", se::Value(arr));
//
//    } while(false);
//
//    if (ok)
//        ret->setObject(obj);
//    else
//        ret->setNull();
//    return false;
//}
//
//bool b2AABB_to_seval(const b2AABB& v, se::Value* ret)
//{
//    assert(ret != nullptr);
//    se::HandleObject obj(se::Object::createPlainObject());
//
//    se::HandleObject lowerBound(se::Object::createPlainObject());
//    lowerBound->setProperty("x", se::Value(v.lowerBound.x));
//    lowerBound->setProperty("y", se::Value(v.lowerBound.y));
//
//    obj->setProperty("lowerBound", se::Value(lowerBound));
//
//    se::HandleObject upperBound(se::Object::createPlainObject());
//    upperBound->setProperty("x", se::Value(v.upperBound.x));
//    upperBound->setProperty("y", se::Value(v.upperBound.y));
//
//    obj->setProperty("upperBound", se::Value(upperBound));
//
//    ret->setObject(obj);
//
//    return true;
//}

bool VertexFormat_to_seval(const cocos2d::gfx::VertexFormat& v, se::Value* ret)
{
    assert(false);
    return true;
}

bool TechniqueParameter_to_seval(const cocos2d::gfx::Technique::Parameter& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject obj(se::Object::createPlainObject());
    obj->setProperty("name", se::Value(v.getName()));
    obj->setProperty("type", se::Value((uint8_t)v.getType()));
    obj->setProperty("size", se::Value(v.getCount()));

    auto type = v.getType();
    if (type == cocos2d::gfx::Technique::Parameter::Type::TEXTURE_2D || type == cocos2d::gfx::Technique::Parameter::Type::TEXTURE_CUBE)
    {
        auto texArray = v.getTextureArray();
        auto count = v.getCount();
        if (count > 1)
        {
            se::HandleObject arr(se::Object::createArrayObject(count));
            for (uint8_t i = 0; i < count; ++i)
            {
                se::Value val;
                native_ptr_to_seval<cocos2d::gfx::Texture>(texArray[0], &val);
                arr->setArrayElement(i, val);
            }
            obj->setProperty("val", se::Value(arr));
        }
        else
        {
            assert(texArray.size() == 1);
            se::Value val;
            native_ptr_to_seval<cocos2d::gfx::Texture>(texArray[0], &val);
            obj->setProperty("val", val);
        }
    }
    else
    {
        void* data = v.getValue();
        auto bytes = v.getBytes();

        if (type == cocos2d::gfx::Technique::Parameter::Type::INT
            || type == cocos2d::gfx::Technique::Parameter::Type::INT2
            || type == cocos2d::gfx::Technique::Parameter::Type::INT3
            || type == cocos2d::gfx::Technique::Parameter::Type::INT4)
        {
            se::HandleObject typedArr(se::Object::createTypedArray(se::Object::TypedArrayType::INT32, data, bytes));
            obj->setProperty("val", se::Value(typedArr));
        }
    }

    ret->setObject(obj);
    return true;
}

bool std_vector_TechniqueParameter_to_seval(const std::vector<cocos2d::gfx::Technique::Parameter>& v, se::Value* ret)
{
    assert(ret != nullptr);
    se::HandleObject arr(se::Object::createArrayObject(v.size()));
    ret->setObject(arr);

    uint32_t i = 0;
    for (const auto& param : v)
    {
        se::Value out;
        if (TechniqueParameter_to_seval(param, &out))
        {
            arr->setArrayElement(i, out);
            ++i;
        }
    }
    return true;
}

bool std_vector_RenderTarget_to_seval(const std::vector<cocos2d::gfx::RenderTarget*>& v, se::Value* ret)
{
    assert(false);
    return true;
}

