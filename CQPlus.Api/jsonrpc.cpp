#include "stdafx.h"
#include "./jsonrpc.h"
#include "./json.h"

namespace cqplus::jsonrpc {
#define FUNC_TO_JSON_VALUE(ObjectType) void to_json_value(const ObjectType& object, Json::Value& value);

#include "./jsonrpc_funcs.inl"
}

using namespace cqplus;

void jsonrpc::to_json_value(const int32_t& object, Json::Value& value) {
    value = Json::Value((int32_t)object);
}

void jsonrpc::to_json_value(const int64_t& object, Json::Value& value) {
    value = Json::Value((int64_t)object);
}

void jsonrpc::to_json_value(const double& object, Json::Value& value) {
    value = Json::Value((double)object);
}

void jsonrpc::to_json_value(const bool& object, Json::Value& value) {
    value = Json::Value((bool)object);
}

void jsonrpc::to_json_value(const std::string& object, Json::Value& value) {
    value = Json::Value(object);
}

void jsonrpc::to_json_value(const User& object, Json::Value& value) {
    if (!value.isObject()) {
        value = Json::Value(Json::objectValue);
    }
    value["user_id"] = object.user_id;
    value["nickname"] = object.nickname;
    value["sex"] = (int32_t)object.sex;
    value["age"] = object.age;
}

void jsonrpc::to_json_value(const Group& object, Json::Value& value) {
    if (!value.isObject()) {
        value = Json::Value(Json::objectValue);
    }
    value["group_id"] = object.group_id;
    value["group_name"] = object.group_name;
}

void jsonrpc::to_json_value(const GroupMember& object, Json::Value& value) {
    if (!value.isObject()) {
        value = Json::Value(Json::objectValue);
    }
    value["group_id"] = object.group_id;
    value["user_id"] = object.user_id;
    value["nickname"] = object.nickname;
    value["card"] = object.card;
    value["sex"] = (int32_t)object.sex;
    value["age"] = object.age;
    value["area"] = object.area;
    value["join_time"] = object.join_time;
    value["last_sent_time"] = object.last_sent_time;
    value["level"] = object.level;
    value["role"] = (int32_t)object.role;
    value["unfriendly"] = object.unfriendly;
    value["title"] = object.title;
    value["title_expire_time"] = object.title_expire_time;
    value["card_changeable"] = object.card_changeable;
}
