#pragma once

#include "scripting/js-bindings/jswrapper/SeApi.h"
#include "scripting/js-bindings/manual/jsb_classtype.hpp"

#include "cocos2d.h"
#include "gfx/CCGFX.h"
#include "renderer/Renderer.h"
//#include "cocos/ui/CocosGUI.h"
//#include "extensions/cocos-ext.h"
//#include "cocos/editor-support/spine/spine.h"
//#include "Box2D/Box2D.h"

#define SE_PRECONDITION2_VOID(condition, ...) \
    do { \
        if ( ! (condition) ) { \
            cocos2d::log("jsb: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ ); \
            cocos2d::log(__VA_ARGS__); \
            return; \
        } \
    } while(0)

#define SE_PRECONDITION2(condition, ret_value, ...) \
    do { \
        if ( ! (condition) ) { \
            cocos2d::log("jsb: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ ); \
            cocos2d::log(__VA_ARGS__); \
            return (ret_value); \
        } \
    } while(0)


#define SE_PRECONDITION3(condition, ret_value, failed_code) \
    do { \
        if (!(condition)) \
        { \
            failed_code; \
            return (ret_value); \
        } \
    } while(0)

#define SE_PRECONDITION_ERROR_BREAK(condition, ...) \
    if ( ! (condition) ) { \
        cocos2d::log("jsb: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ ); \
        cocos2d::log(__VA_ARGS__); \
        break; \
    }


// se value -> native value
bool seval_to_int32(const se::Value& v, int32_t* ret);
bool seval_to_uint32(const se::Value& v, uint32_t* ret);
bool seval_to_int8(const se::Value& v, int8_t* ret);
bool seval_to_uint8(const se::Value& v, uint8_t* ret);
bool seval_to_int16(const se::Value& v, int16_t* ret);
bool seval_to_uint16(const se::Value& v, uint16_t* ret);
bool seval_to_boolean(const se::Value& v, bool* ret);
bool seval_to_float(const se::Value& v, float* ret);
bool seval_to_double(const se::Value& v, double* ret);
bool seval_to_long(const se::Value& v, long* ret);
bool seval_to_ulong(const se::Value& v, unsigned long* ret);
bool seval_to_longlong(const se::Value& v, long long* ret);
bool seval_to_ssize(const se::Value& v, ssize_t* ret);
bool seval_to_size(const se::Value& v, size_t* ret);
bool seval_to_std_string(const se::Value& v, std::string* ret);
bool seval_to_Vec2(const se::Value& v, cocos2d::Vec2* pt);
bool seval_to_Vec3(const se::Value& v, cocos2d::Vec3* pt);
bool seval_to_Vec4(const se::Value& v, cocos2d::Vec4* pt);
bool seval_to_Mat4(const se::Value& v, cocos2d::Mat4* mat);
bool seval_to_Size(const se::Value& v, cocos2d::Size* size);
//bool seval_to_Rect(const se::Value& v, cocos2d::Rect* rect);
bool seval_to_Rect(const se::Value& v, cocos2d::gfx::Rect* rect);
bool seval_to_Color3B(const se::Value& v, cocos2d::Color3B* color);
bool seval_to_Color4B(const se::Value& v, cocos2d::Color4B* color);
bool seval_to_Color3F(const se::Value& v, cocos2d::Color3F* color);
bool seval_to_Color4F(const se::Value& v, cocos2d::Color4F* color);
bool seval_to_ccvalue(const se::Value& v, cocos2d::Value* ret);
bool seval_to_ccvaluemap(const se::Value& v, cocos2d::ValueMap* ret);
bool seval_to_ccvaluemapintkey(const se::Value& v, cocos2d::ValueMapIntKey* ret);
bool seval_to_ccvaluevector(const se::Value& v, cocos2d::ValueVector* ret);
bool sevals_variadic_to_ccvaluevector(const se::ValueArray& args, cocos2d::ValueVector* ret);
bool seval_to_blendfunc(const se::Value& v, cocos2d::BlendFunc* ret);
bool seval_to_std_vector_string(const se::Value& v, std::vector<std::string>* ret);
bool seval_to_std_vector_int(const se::Value& v, std::vector<int>* ret);
bool seval_to_std_vector_float(const se::Value& v, std::vector<float>* ret);
bool seval_to_std_vector_Vec2(const se::Value& v, std::vector<cocos2d::Vec2>* ret);
//bool seval_to_std_vector_Touch(const se::Value& v, std::vector<cocos2d::Touch*>* ret);
bool seval_to_std_map_string_string(const se::Value& v, std::map<std::string, std::string>* ret);
bool seval_to_FontDefinition(const se::Value& v, cocos2d::FontDefinition* ret);
//bool seval_to_Acceleration(const se::Value& v, cocos2d::Acceleration* ret);
//bool seval_to_Quaternion(const se::Value& v, cocos2d::Quaternion* ret);
//bool seval_to_AffineTransform(const se::Value& v, cocos2d::AffineTransform* ret);
////bool seval_to_Viewport(const se::Value& v, cocos2d::experimental::Viewport* ret);
//bool seval_to_Data(const se::Value& v, cocos2d::Data* ret);
//bool seval_to_DownloaderHints(const se::Value& v, cocos2d::network::DownloaderHints* ret);
//bool seval_to_TTFConfig(const se::Value& v, cocos2d::TTFConfig* ret);

//box2d seval to native convertion
//bool seval_to_b2Vec2(const se::Value& v, b2Vec2* ret);
//bool seval_to_b2AABB(const se::Value& v, b2AABB* ret);

bool seval_to_std_vector_Texture(const se::Value& v, std::vector<cocos2d::gfx::Texture*>* ret);
bool seval_to_std_vector_RenderTarget(const se::Value& v, std::vector<cocos2d::gfx::RenderTarget*>* ret);
bool seval_to_TextureOptions(const se::Value& v, cocos2d::gfx::Texture::Options* ret);
bool seval_to_TextureSubImageOption(const se::Value& v, cocos2d::gfx::Texture::SubImageOption* ret);
bool seval_to_TextureImageOption(const se::Value& v, cocos2d::gfx::Texture::ImageOption* ret);
bool seval_to_EffectProperty(const se::Value& v, std::unordered_map<std::string, cocos2d::gfx::Effect::Property>* ret);
bool seval_to_EffectDefineTemplate(const se::Value& v, std::vector<cocos2d::ValueMap>* ret);
bool seval_to_TechniqueParameter(const se::Value& v, cocos2d::gfx::Technique::Parameter* ret);
bool seval_to_std_vector_TechniqueParameter(const se::Value& v, std::vector<cocos2d::gfx::Technique::Parameter>* ret);
bool seval_to_std_vector_ProgramLib_Template(const se::Value& v, std::vector<cocos2d::gfx::ProgramLib::Template>* ret);

template<typename T>
bool seval_to_native_ptr(const se::Value& v, T* ret)
{
    assert(ret != nullptr);

    if (v.isObject())
    {
        T ptr = (T)v.toObject()->getPrivateData();
        if (ptr == nullptr)
        {
            // This should never happen, return 'false' to mark the conversion fails.
            *ret = nullptr;
            return false;
        }

        *ret = ptr;
        return true;
    }
    else if (v.isNullOrUndefined())
    {
        // If js value is null or undefined, the convertion should be successful.
        // So we should return 'true' to indicate the convertion succeeds and mark
        // the out value to 'nullptr'.
        *ret = nullptr;
        return true;
    }

    // If js value isn't null, undefined and Object, mark the convertion fails.
    *ret = nullptr;
    return false;
}

template<typename T>
bool seval_to_Vector(const se::Value& v, cocos2d::Vector<T>* ret)
{
    assert(ret != nullptr);
    assert(v.isObject());
    se::Object* obj = v.toObject();
    assert(obj->isArray());

    bool ok = true;
    uint32_t len = 0;
    ok = obj->getArrayLength(&len);
    if (!ok)
    {
        ret->clear();
        return false;
    }

    se::Value tmp;
    for (uint32_t i = 0; i < len; ++i)
    {
        ok = obj->getArrayElement(i, &tmp);
        if (!ok || !tmp.isObject())
        {
            ret->clear();
            return false;
        }

        T nativeObj = (T)tmp.toObject()->getPrivateData();

        ret->pushBack(nativeObj);
    }

    return true;
}
//
//template<typename T>
//bool seval_to_Map_string_key(const se::Value& v, cocos2d::Map<std::string, T>* ret)
//{
//    assert(ret != nullptr);
//    assert(v.isObject());
//    se::Object* obj = v.toObject();
//
//    std::vector<std::string> allKeys;
//    bool ok = obj->getAllKeys(&allKeys);
//    if (!ok)
//    {
//        ret->clear();
//        return false;
//    }
//
//    se::Value tmp;
//    for (const auto& key : allKeys)
//    {
//        ok = obj->getProperty(key.c_str(), &tmp);
//        if (!ok || !tmp.isObject())
//        {
//            ret->clear();
//            return false;
//        }
//
//        T nativeObj = (T)tmp.toObject()->getPrivateData();
//
//        ret->insert(key, nativeObj);
//    }
//
//    return true;
//}

// native value -> se value
bool int8_to_seval(int8_t v, se::Value* ret);
bool uint8_to_seval(uint8_t v, se::Value* ret);
bool int32_to_seval(int32_t v, se::Value* ret);
bool uint32_to_seval(uint32_t v, se::Value* ret);
bool int16_to_seval(uint16_t v, se::Value* ret);
bool uint16_to_seval(uint16_t v, se::Value* ret);
bool boolean_to_seval(bool v, se::Value* ret);
bool float_to_seval(float v, se::Value* ret);
bool double_to_seval(double v, se::Value* ret);
bool long_to_seval(long v, se::Value* ret);
bool ulong_to_seval(unsigned long v, se::Value* ret);
bool longlong_to_seval(long long v, se::Value* ret);
bool ssize_to_seval(ssize_t v, se::Value* ret);
bool std_string_to_seval(const std::string& v, se::Value* ret);

bool Vec2_to_seval(const cocos2d::Vec2& v, se::Value* ret);
bool Vec3_to_seval(const cocos2d::Vec3& v, se::Value* ret);
bool Vec4_to_seval(const cocos2d::Vec4& v, se::Value* ret);
bool Mat4_to_seval(const cocos2d::Mat4& v, se::Value* ret);
bool Size_to_seval(const cocos2d::Size& v, se::Value* ret);
//bool Rect_to_seval(const cocos2d::Rect& v, se::Value* ret);
bool Rect_to_seval(const cocos2d::gfx::Rect& v, se::Value* ret);
bool Color3B_to_seval(const cocos2d::Color3B& v, se::Value* ret);
bool Color4B_to_seval(const cocos2d::Color4B& v, se::Value* ret);
bool Color3F_to_seval(const cocos2d::Color3F& v, se::Value* ret);
bool Color4F_to_seval(const cocos2d::Color4F& v, se::Value* ret);
bool ccvalue_to_seval(const cocos2d::Value& v, se::Value* ret);
bool ccvaluemap_to_seval(const cocos2d::ValueMap& v, se::Value* ret);
bool ccvaluemapintkey_to_seval(const cocos2d::ValueMapIntKey& v, se::Value* ret);
bool ccvaluevector_to_seval(const cocos2d::ValueVector& v, se::Value* ret);
bool blendfunc_to_seval(const cocos2d::BlendFunc& v, se::Value* ret);
bool std_vector_string_to_seval(const std::vector<std::string>& v, se::Value* ret);
bool std_vector_int_to_seval(const std::vector<int>& v, se::Value* ret);
bool std_vector_float_to_seval(const std::vector<float>& v, se::Value* ret);
//bool std_vector_Touch_to_seval(const std::vector<cocos2d::Touch*>& v, se::Value* ret);
bool std_map_string_string_to_seval(const std::map<std::string, std::string>& v, se::Value* ret);
//bool uniform_to_seval(const cocos2d::Uniform* v, se::Value* ret);
//bool FontDefinition_to_seval(const cocos2d::FontDefinition& v, se::Value* ret);
//bool Acceleration_to_seval(const cocos2d::Acceleration* v, se::Value* ret);
//bool Quaternion_to_seval(const cocos2d::Quaternion& v, se::Value* ret);
//bool ManifestAsset_to_seval(const cocos2d::extension::ManifestAsset& v, se::Value* ret);
//bool AffineTransform_to_seval(const cocos2d::AffineTransform& v, se::Value* ret);
////bool Viewport_to_seval(const cocos2d::experimental::Viewport& v, se::Value* ret);
bool Data_to_seval(const cocos2d::Data& v, se::Value* ret);
//bool DownloadTask_to_seval(const cocos2d::network::DownloadTask& v, se::Value* ret);

bool VertexFormat_to_seval(const cocos2d::gfx::VertexFormat& v, se::Value* ret);
bool TechniqueParameter_to_seval(const cocos2d::gfx::Technique::Parameter& v, se::Value* ret);
bool std_vector_TechniqueParameter_to_seval(const std::vector<cocos2d::gfx::Technique::Parameter>& v, se::Value* ret);

template<typename T>
bool recreate_seval_by_native_ptr(typename std::enable_if<!std::is_base_of<cocos2d::Ref,T>::value,T>::type* v, se::Class* cls, se::Value* ret)
{
    assert(ret != nullptr);
    assert(cls != nullptr);
    if (v == nullptr)
    {
        ret->setNull();
        return true;
    }

    auto iter = se::NativePtrToObjectMap::find(v);
    if (iter != se::NativePtrToObjectMap::end())
    {
        se::Object* seObj = iter->second;
        seObj->clearPrivateData();
        seObj->decRef();
    }

    se::Object* obj = se::Object::createObjectWithClass(cls);
    ret->setObject(obj, true);
    obj->setPrivateData(v);

    return true;
}

template<typename T>
bool native_ptr_to_seval(typename std::enable_if<!std::is_base_of<cocos2d::Ref,T>::value,T>::type* v, se::Value* ret, bool* isReturnCachedValue = nullptr)
{
    assert(ret != nullptr);
    if (v == nullptr)
    {
        ret->setNull();
        return true;
    }

    se::Object* obj = nullptr;
    auto iter = se::NativePtrToObjectMap::find(v);
    if (iter == se::NativePtrToObjectMap::end())
    { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
        // CCLOGWARN("WARNING: non-Ref type: (%s) isn't catched!", typeid(*v).name());
        se::Class* cls = JSBClassType::findClass<T>(v);
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        ret->setObject(obj, true);
        obj->setPrivateData(v);
        if (isReturnCachedValue != nullptr)
        {
            *isReturnCachedValue = false;
        }
    }
    else
    {
        obj = iter->second;
        if (isReturnCachedValue != nullptr)
        {
            *isReturnCachedValue = true;
        }
        ret->setObject(obj);
    }

    return true;
}

template<typename T>
bool native_ptr_to_rooted_seval(typename std::enable_if<!std::is_base_of<cocos2d::Ref,T>::value,T>::type* v, se::Value* ret, bool* isReturnCachedValue = nullptr)
{
    assert(ret != nullptr);
    if (v == nullptr)
    {
        ret->setNull();
        return true;
    }

    se::Object* obj = nullptr;
    auto iter = se::NativePtrToObjectMap::find(v);
    if (iter == se::NativePtrToObjectMap::end())
    { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
        se::Class* cls = JSBClassType::findClass<T>(v);
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        obj->root();
        obj->setPrivateData(v);

        if (isReturnCachedValue != nullptr)
        {
            *isReturnCachedValue = false;
        }
        // CCLOGWARN("WARNING: non-Ref type: (%s) isn't catched!", typeid(*v).name());
    }
    else
    {
        obj = iter->second;
        assert(obj->isRooted());
        if (isReturnCachedValue != nullptr)
        {
            *isReturnCachedValue = true;
        }
        // CCLOG("return cached object: %s, se::Object:%p, native: %p", typeid(*v).name(), obj, v);
    }

    ret->setObject(obj);
    return true;
}

template<typename T>
bool native_ptr_to_seval(typename std::enable_if<!std::is_base_of<cocos2d::Ref,T>::value,T>::type* v, se::Class* cls, se::Value* ret, bool* isReturnCachedValue = nullptr)
{
    assert(ret != nullptr);
    if (v == nullptr)
    {
        ret->setNull();
        return true;
    }

    se::Object* obj = nullptr;
    auto iter = se::NativePtrToObjectMap::find(v);
    if (iter == se::NativePtrToObjectMap::end())
    { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
//        CCLOGWARN("WARNING: Ref type: (%s) isn't catched!", typeid(*v).name());
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        ret->setObject(obj, true);
        obj->setPrivateData(v);

        if (isReturnCachedValue != nullptr)
        {
            *isReturnCachedValue = false;
        }
    }
    else
    {
        obj = iter->second;
        if (isReturnCachedValue != nullptr)
        {
            *isReturnCachedValue = true;
        }
        ret->setObject(obj);
    }

    return true;
}

template<typename T>
bool native_ptr_to_rooted_seval(typename std::enable_if<!std::is_base_of<cocos2d::Ref,T>::value,T>::type* v, se::Class* cls, se::Value* ret, bool* isReturnCachedValue = nullptr)
{
    assert(ret != nullptr);
    if (v == nullptr)
    {
        ret->setNull();
        return true;
    }

    se::Object* obj = nullptr;
    auto iter = se::NativePtrToObjectMap::find(v);
    if (iter == se::NativePtrToObjectMap::end())
    { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        obj->root();
        obj->setPrivateData(v);

        if (isReturnCachedValue != nullptr)
        {
            *isReturnCachedValue = false;
        }
        // CCLOGWARN("WARNING: non-Ref type: (%s) isn't catched, se::Object:%p, native: %p", typeid(*v).name(), obj, v);
    }
    else
    {
        obj = iter->second;
        assert(obj->isRooted());
        if (isReturnCachedValue != nullptr)
        {
            *isReturnCachedValue = true;
        }
        // CCLOG("return cached object: %s, se::Object:%p, native: %p", typeid(*v).name(), obj, v);
    }

    ret->setObject(obj);
    return true;
}

template<typename T>
bool native_ptr_to_seval(typename std::enable_if<std::is_base_of<cocos2d::Ref,T>::value,T>::type* v, se::Value* ret, bool* isReturnCachedValue = nullptr)
{
    assert(ret != nullptr);
    if (v == nullptr)
    {
        ret->setNull();
        return true;
    }

    se::Object* obj = nullptr;
    auto iter = se::NativePtrToObjectMap::find(v);
    if (iter == se::NativePtrToObjectMap::end())
    { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
//        CCLOGWARN("WARNING: Ref type: (%s) isn't catched!", typeid(*v).name());
        se::Class* cls = JSBClassType::findClass<T>(v);
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        ret->setObject(obj, true);
        obj->setPrivateData(v);
        v->retain(); // Retain the native object to unify the logic in finalize method of js object.
        if (isReturnCachedValue != nullptr)
        {
            *isReturnCachedValue = false;
        }
    }
    else
    {
        obj = iter->second;
//        CCLOG("INFO: Found Ref type: (%s, native: %p, se: %p) from cache!", typeid(*v).name(), v, obj);
        if (isReturnCachedValue != nullptr)
        {
            *isReturnCachedValue = true;
        }
        ret->setObject(obj);
    }

    return true;
}

template<typename T>
bool native_ptr_to_seval(typename std::enable_if<std::is_base_of<cocos2d::Ref,T>::value,T>::type* v, se::Class* cls, se::Value* ret, bool* isReturnCachedValue = nullptr)
{
    assert(ret != nullptr);
    if (v == nullptr)
    {
        ret->setNull();
        return true;
    }

    se::Object* obj = nullptr;
    auto iter = se::NativePtrToObjectMap::find(v);
    if (iter == se::NativePtrToObjectMap::end())
    { // If we couldn't find native object in map, then the native object is created from native code. e.g. TMXLayer::getTileAt
//        CCLOGWARN("WARNING: Ref type: (%s) isn't catched!", typeid(*v).name());
        assert(cls != nullptr);
        obj = se::Object::createObjectWithClass(cls);
        ret->setObject(obj, true);
        obj->setPrivateData(v);
        v->retain(); // Retain the native object to unify the logic in finalize method of js object.
        if (isReturnCachedValue != nullptr)
        {
            *isReturnCachedValue = false;
        }
    }
    else
    {
        obj = iter->second;
        if (isReturnCachedValue != nullptr)
        {
            *isReturnCachedValue = true;
        }
        ret->setObject(obj);
    }

    return true;
}

template<typename T>
bool Vector_to_seval(const cocos2d::Vector<T*>& v, se::Value* ret)
{
    assert(ret != nullptr);
    bool ok = true;
    se::HandleObject obj(se::Object::createArrayObject(v.size()));

    uint32_t i = 0;
    se::Value tmp;
    for (const auto& e : v)
    {
        native_ptr_to_seval<T>(e, &tmp);
        obj->setArrayElement(i, tmp);
        ++i;
    }

    ret->setObject(obj, true);

    return ok;
}
//
//template<typename T>
//bool Map_string_key_to_seval(const cocos2d::Map<std::string, T*>& v, se::Value* ret)
//{
//    assert(ret != nullptr);
//
//    se::HandleObject obj(se::Object::createPlainObject());
//
//    se::Value tmp;
//    for (const auto& e : v)
//    {
//        native_ptr_to_seval<T>(e.second, &tmp);
//        obj->setProperty(e.first.c_str(), tmp);
//    }
//
//    ret->setObject(obj, true);
//    return false;
//}

//// Spine conversions
//bool speventdata_to_seval(const spEventData* v, se::Value* ret);
//bool spevent_to_seval(const spEvent* v, se::Value* ret);
//bool spbonedata_to_seval(const spBoneData* v, se::Value* ret);
//bool spbone_to_seval(const spBone* v, se::Value* ret);
//bool spskeleton_to_seval(const spSkeleton* v, se::Value* ret);
//bool spattachment_to_seval(const spAttachment* v, se::Value* ret);
//bool spslotdata_to_seval(const spSlotData* v, se::Value* ret);
//bool spslot_to_seval(const spSlot* v, se::Value* ret);
//bool sptimeline_to_seval(const spTimeline* v, se::Value* ret);
//bool spanimationstate_to_seval(const spAnimationState* v, se::Value* ret);
//bool spanimation_to_seval(const spAnimation* v, se::Value* ret);
//bool sptrackentry_to_seval(const spTrackEntry* v, se::Value* ret);
//
//// Box2d
//bool b2Vec2_to_seval(const b2Vec2& v, se::Value* ret);
//bool b2Manifold_to_seval(const b2Manifold* v, se::Value* ret);
//bool b2AABB_to_seval(const b2AABB& v, se::Value* ret);

bool std_vector_RenderTarget_to_seval(const std::vector<cocos2d::gfx::RenderTarget*>& v, se::Value* ret);

