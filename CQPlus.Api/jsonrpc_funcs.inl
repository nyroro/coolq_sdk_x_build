#ifndef FUNC_TO_JSON_VALUE
#define FUNC_TO_JSON_VALUE(ObjectType) \
    extern void to_json_value(const ObjectType& object, Json::Value& value); \
    inline Json::Value to_json_value(const ObjectType& object) {\
        Json::Value value; \
        to_json_value(object, value); \
        return value; \
    } \
    inline void to_json_value(const std::vector<ObjectType>& object_list, Json::Value& value) { \
        if (!value.isArray()) { \
            value = Json::Value(Json::arrayValue); \
        } \
        for (auto it=object_list.cbegin(); it!=object_list.cend(); it++) { \
            value.append(to_json_value(static_cast<const ObjectType&>(*it))); \
        } \
    } \
    inline Json::Value to_json_value(const std::vector<ObjectType>& object_list) { \
        Json::Value value; \
        to_json_value(object_list, value); \
        return value; \
    }
#endif

FUNC_TO_JSON_VALUE(int32_t)
FUNC_TO_JSON_VALUE(int64_t)
FUNC_TO_JSON_VALUE(double)
FUNC_TO_JSON_VALUE(bool)
FUNC_TO_JSON_VALUE(std::string)
FUNC_TO_JSON_VALUE(User)
FUNC_TO_JSON_VALUE(Group)
FUNC_TO_JSON_VALUE(GroupMember)

#ifdef FUNC_TO_JSON_VALUE
#undef FUNC_TO_JSON_VALUE
#endif
