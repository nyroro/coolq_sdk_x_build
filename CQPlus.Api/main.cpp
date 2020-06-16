#include "stdafx.h"

#include "./app.h"
#include "./api.h"
#include "./json.h"
#include "./utils.h"
#include "./jsonrpc.h"
#include "./event.h"

CQPLUS_INIT(HMODULE hModule) {
    cqplus::api::init();
}

CQPLUS_MAIN(HMODULE hModule) {
    cqplus::api::route("log", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;
        
        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto level = params.get("level", 0).asInt();
        auto tag = params.get("tag", "").asString();
        auto msg = params.get("msg", "").asString();
        auto api_ret = cqplus::api::raw::CQ_addLog(auth_code, level, cqplus::utils::string_to_coolq(tag).c_str(), cqplus::utils::string_to_coolq(msg).c_str());

        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::api::route("send_private_msg", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto user_id = params.get("user_id", 0).asInt64();
        auto msg = params.get("msg", "").asString();
        auto api_ret = cqplus::api::send_private_msg(auth_code, user_id, msg);

        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::api::route("send_group_msg", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto group_id = params.get("group_id", 0).asInt64();
        auto msg = params.get("msg", "").asString();
        auto api_ret = cqplus::api::send_group_msg(auth_code, group_id, msg);

        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::api::route("send_discuss_msg", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto discuss_id = params.get("discuss_id", 0).asInt64();
        auto msg = params.get("msg", "").asString();
        auto api_ret = cqplus::api::send_discuss_msg(auth_code, discuss_id, msg);

        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::api::route("delete_msg", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto msg_id = params.get("msg_id", 0).asInt64();
        cqplus::api::delete_msg(auth_code, msg_id);

        return ret;
    });

    cqplus::api::route("send_like", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto user_id = params.get("user_id", 0).asInt64();
        auto times = params.get("times", 1).asInt();
        cqplus::api::send_like(auth_code, user_id, times);

        return ret;
    });

    cqplus::api::route("set_group_kick", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto group_id = params.get("group_id", 0).asInt64();
        auto user_id = params.get("user_id", 0).asInt64();
        auto reject_add_request = params.get("reject_add_request", false).asBool();
        cqplus::api::set_group_kick(auth_code, group_id, user_id, reject_add_request);

        return ret;
    });

    cqplus::api::route("set_group_ban", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto group_id = params.get("group_id", 0).asInt64();
        auto user_id = params.get("user_id", 0).asInt64();
        auto duration = params.get("duration", 0).asInt64();
        cqplus::api::set_group_ban(auth_code, group_id, user_id, duration);

        return ret;
    });

    cqplus::api::route("set_group_anonymous_ban", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto group_id = params.get("group_id", 0).asInt64();
        auto flag = params.get("flag", "").asString();
        auto duration = params.get("duration", 0).asInt64();
        cqplus::api::set_group_anonymous_ban(auth_code, group_id, flag, duration);

        return ret;
    });

    cqplus::api::route("set_group_whole_ban", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto group_id = params.get("group_id", 0).asInt64();
        auto enable = params.get("enable", false).asBool();
        cqplus::api::set_group_whole_ban(auth_code, group_id, enable);

        return ret;
    });

    cqplus::api::route("set_group_admin", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto group_id = params.get("group_id", 0).asInt64();
        auto user_id = params.get("user_id", 0).asInt64();
        auto enable = params.get("enable", false).asBool();
        cqplus::api::set_group_admin(auth_code, group_id, user_id, enable);

        return ret;
    });

    cqplus::api::route("set_group_anonymous", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto group_id = params.get("group_id", 0).asInt64();
        auto enable = params.get("enable", false).asBool();
        cqplus::api::set_group_anonymous(auth_code, group_id, enable);

        return ret;
    });

    cqplus::api::route("set_group_card", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto group_id = params.get("group_id", 0).asInt64();
        auto user_id = params.get("user_id", 0).asInt64();
        auto card = params.get("card", "").asString();
        cqplus::api::set_group_card(auth_code, group_id, user_id, card);

        return ret;
    });

    cqplus::api::route("set_group_leave", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto group_id = params.get("group_id", 0).asInt64();
        auto is_dismiss = params.get("is_dismiss", false).asBool();
        cqplus::api::set_group_leave(auth_code, group_id, is_dismiss);

        return ret;
    });

    cqplus::api::route("set_group_special_title", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto group_id = params.get("group_id", 0).asInt64();
        auto user_id = params.get("user_id", 0).asInt64();
        auto special_title = params.get("special_title", "").asString();
        auto duration = params.get("duration", 0).asInt64();
        cqplus::api::set_group_special_title(auth_code, group_id, user_id, special_title, duration);

        return ret;
    });

    cqplus::api::route("set_discuss_leave", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto discuss_id = params.get("discuss_id", 0).asInt64();
        cqplus::api::set_discuss_leave(auth_code, discuss_id);

        return ret;
    });

    cqplus::api::route("set_friend_add_request", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto flag = params.get("flag", "").asString();
        auto operation = params.get("operation", 0).asInt();
        auto remark = params.get("remark", "").asString();
        cqplus::api::set_friend_add_request(auth_code, flag, operation, remark);

        return ret;
    });

    cqplus::api::route("set_group_add_request", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto flag = params.get("flag", "").asString();
        auto type = params.get("type", 0).asInt();
        auto operation = params.get("operation", 0).asInt();
        auto reason = params.get("reason", "").asString();
        cqplus::api::set_group_add_request(auth_code, flag, type, operation, reason);

        return ret;
    });

    cqplus::api::route("get_login_user_id", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto api_ret = cqplus::api::get_login_user_id(auth_code);

        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::api::route("get_login_nickname", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto api_ret = cqplus::api::get_login_nickname(auth_code);

        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::api::route("get_cookies", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto api_ret = cqplus::api::get_cookies(auth_code);

        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::api::route("get_csrf_token", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto api_ret = cqplus::api::get_csrf_token(auth_code);

        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::api::route("get_app_directory", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto api_ret = cqplus::api::get_app_directory(auth_code);

        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::api::route("get_record", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto file = params.get("file", "").asString();
        auto out_format = params.get("out_format", "").asString();
        auto api_ret = cqplus::api::get_record(auth_code, file, out_format);

        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::api::route("get_stranger_info", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto user_id = params.get("user_id", 0).asInt64();
        auto no_cache = params.get("no_cache", false).asBool();
        auto api_ret = cqplus::api::get_stranger_info(auth_code, user_id, no_cache);

        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::api::route("get_group_list", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();
        
        auto api_ret = cqplus::api::get_group_list(auth_code);
        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::api::route("get_group_member_list", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto group_id = params.get("group_id", 0).asInt64();
        auto api_ret = cqplus::api::get_group_member_list(auth_code, group_id);

        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::api::route("get_group_member_info", [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret;

        Json::Value env = params.get("env", Json::objectValue);
        auto auth_code = env.get("CQ_AUTH_CODE", 0).asInt();

        auto group_id = params.get("group_id", 0).asInt64();
        auto user_id = params.get("user_id", 0).asInt64();
        auto no_cache = params.get("no_cache", false).asBool();
        auto api_ret = cqplus::api::get_group_member_info(auth_code, group_id, user_id, no_cache);

        cqplus::jsonrpc::to_json_value(api_ret, ret);

        return ret;
    });

    cqplus::event::on_api_invoke = [](const Json::String& method, const Json::Value& params) -> Json::Value {
        return cqplus::api::handle(method, params);
    };
}
