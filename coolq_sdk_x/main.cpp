// coolq_sdk_v6.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include "./app.h"
#include "./utils.h"
#include "./menu.h"
#include "./event.h"
#include "./json.h"
#include "./logging.h"
#include "./settings.h"
#include "./script.h"
#include "./timer.h"


CQPLUS_INIT(HMODULE hModule) {
    cqplus::app::cq_home = cqplus::utils::string_from_coolq(path_dirname(os_getmodulefilename(NULL)));
    cqplus::app::app_id = cqplus::utils::string_from_coolq(path_splitext(path_basename(os_getmodulefilename(hModule)))[0]);
}

CQPLUS_MAIN(HMODULE hModule) {
    cqplus::app::on_initialize = [] {

    };

    cqplus::app::on_coolq_start = [] {

    };

    cqplus::app::on_enable = [] {
        cqplus::settings::init();
        cqplus::script::init();
        cqplus::timer::init();

        CQPLUS_RPC_INVOKE_NO_PARAM("on_enable");
    };

    cqplus::app::on_disable = [] {
        CQPLUS_RPC_INVOKE_NO_PARAM("on_disable");

        cqplus::timer::fini();
    };

    cqplus::app::on_coolq_exit = [] {

    };

    cqplus::event::on_private_msg = [](const cqplus::event::PrivateMessageEvent &e) {
        CQPLUS_RPC_INIT_PARAMS();
        CQPLUS_RPC_PARAMS["sub_type"] = (int32_t)e.sub_type;
        CQPLUS_RPC_PARAMS["msg_id"] = e.message_id;
        CQPLUS_RPC_PARAMS["from_qq"] = e.user_id;
        CQPLUS_RPC_PARAMS["msg"] = e.raw_message;
        CQPLUS_RPC_PARAMS["font"] = e.font;
        CQPLUS_RPC_INVOKE("on_private_msg");

        if (CQPLUS_RPC_RET.asBool())
        {
            e.block();
        }
    };

    cqplus::event::on_group_msg = [](const cqplus::event::GroupMessageEvent &e) {
        CQPLUS_RPC_INIT_PARAMS();
        CQPLUS_RPC_PARAMS["sub_type"] = (int32_t)e.sub_type;
        CQPLUS_RPC_PARAMS["msg_id"] = e.message_id;
        CQPLUS_RPC_PARAMS["from_group"] = e.group_id;
        CQPLUS_RPC_PARAMS["from_qq"] = e.user_id;
        CQPLUS_RPC_PARAMS["is_anonymous"] = e.is_anonymous();

        Json::Value anonymous;
        if (e.is_anonymous()) {
            anonymous["id"] = e.anonymous.id;
            anonymous["name"] = e.anonymous.name;
            anonymous["flag"] = e.anonymous.flag;
            anonymous["token"] = e.anonymous.token;
        }

        CQPLUS_RPC_PARAMS["anonymous"] = anonymous;
        CQPLUS_RPC_PARAMS["msg"] = e.raw_message;
        CQPLUS_RPC_PARAMS["font"] = e.font;
        CQPLUS_RPC_INVOKE("on_group_msg");

        if (CQPLUS_RPC_RET.asBool())
        {
            e.block();
        }
    };

    cqplus::event::on_discuss_msg = [](const cqplus::event::DiscussMessageEvent &e) {
        CQPLUS_RPC_INIT_PARAMS();
        CQPLUS_RPC_PARAMS["sub_type"] = (int32_t)e.sub_type;
        CQPLUS_RPC_PARAMS["msg_id"] = e.message_id;
        CQPLUS_RPC_PARAMS["from_discuss"] = e.discuss_id;
        CQPLUS_RPC_PARAMS["from_qq"] = e.user_id;
        CQPLUS_RPC_PARAMS["msg"] = e.raw_message;
        CQPLUS_RPC_PARAMS["font"] = e.font;
        CQPLUS_RPC_INVOKE("on_discuss_msg");

        if (CQPLUS_RPC_RET.asBool())
        {
            e.block();
        }
    };

    cqplus::event::on_group_upload = [](const cqplus::event::GroupUploadEvent &e) {
        CQPLUS_RPC_INIT_PARAMS();
        CQPLUS_RPC_PARAMS["sub_type"] = (int32_t)e.sub_type;
        CQPLUS_RPC_PARAMS["send_time"] = e.time;
        CQPLUS_RPC_PARAMS["from_group"] = e.group_id;
        CQPLUS_RPC_PARAMS["from_qq"] = e.user_id;

        Json::Value file;
        file["id"] = e.file.id;
        file["name"] = e.file.name;
        file["size"] = e.file.size;
        file["busid"] = e.file.busid;
        CQPLUS_RPC_PARAMS["file"] = file;

        CQPLUS_RPC_INVOKE("on_group_upload");

        if (CQPLUS_RPC_RET.asBool())
        {
            e.block();
        }
    };

    cqplus::event::on_group_admin = [](const cqplus::event::GroupAdminEvent &e) {
        CQPLUS_RPC_INIT_PARAMS();
        CQPLUS_RPC_PARAMS["sub_type"] = (int32_t)e.sub_type;
        CQPLUS_RPC_PARAMS["send_time"] = e.time;
        CQPLUS_RPC_PARAMS["from_group"] = e.group_id;
        CQPLUS_RPC_PARAMS["being_operate_qq"] = e.user_id;
        CQPLUS_RPC_INVOKE("on_group_admin");

        if (CQPLUS_RPC_RET.asBool())
        {
            e.block();
        }
    };

    cqplus::event::on_group_member_decrease = [](const cqplus::event::GroupMemberDecreaseEvent &e) {
        CQPLUS_RPC_INIT_PARAMS();
        CQPLUS_RPC_PARAMS["sub_type"] = (int32_t)e.sub_type;
        CQPLUS_RPC_PARAMS["send_time"] = e.time;
        CQPLUS_RPC_PARAMS["from_group"] = e.group_id;
        CQPLUS_RPC_PARAMS["from_qq"] = e.operator_id;
        CQPLUS_RPC_PARAMS["being_operate_qq"] = e.user_id;
        CQPLUS_RPC_INVOKE("on_group_member_decrease");

        if (CQPLUS_RPC_RET.asBool())
        {
            e.block();
        }
    };

    cqplus::event::on_group_member_increase = [](const cqplus::event::GroupMemberIncreaseEvent &e) {
        CQPLUS_RPC_INIT_PARAMS();
        CQPLUS_RPC_PARAMS["sub_type"] = (int32_t)e.sub_type;
        CQPLUS_RPC_PARAMS["send_time"] = e.time;
        CQPLUS_RPC_PARAMS["from_group"] = e.group_id;
        CQPLUS_RPC_PARAMS["from_qq"] = e.operator_id;
        CQPLUS_RPC_PARAMS["being_operate_qq"] = e.user_id;
        CQPLUS_RPC_INVOKE("on_group_member_increase");

        if (CQPLUS_RPC_RET.asBool())
        {
            e.block();
        }
    };

    cqplus::event::on_friend_add = [](const cqplus::event::FriendAddEvent &e) {
        CQPLUS_RPC_INIT_PARAMS();
        CQPLUS_RPC_PARAMS["sub_type"] = (int32_t)e.sub_type;
        CQPLUS_RPC_PARAMS["send_time"] = e.time;
        CQPLUS_RPC_PARAMS["from_qq"] = e.user_id;
        CQPLUS_RPC_INVOKE("on_friend_add");

        if (CQPLUS_RPC_RET.asBool())
        {
            e.block();
        }
    };

    cqplus::event::on_friend_request = [](const cqplus::event::FriendRequestEvent &e) {
        CQPLUS_RPC_INIT_PARAMS();
        CQPLUS_RPC_PARAMS["sub_type"] = (int32_t)e.sub_type;
        CQPLUS_RPC_PARAMS["send_time"] = e.time;
        CQPLUS_RPC_PARAMS["from_qq"] = e.user_id;
        CQPLUS_RPC_PARAMS["msg"] = e.comment;
        CQPLUS_RPC_PARAMS["response_flag"] = e.flag;
        CQPLUS_RPC_INVOKE("on_friend_request");

        if (CQPLUS_RPC_RET.asBool())
        {
            e.block();
        }
    };

    cqplus::event::on_group_request = [](const cqplus::event::GroupRequestEvent &e) {
        CQPLUS_RPC_INIT_PARAMS();
        CQPLUS_RPC_PARAMS["sub_type"] = (int32_t)e.sub_type;
        CQPLUS_RPC_PARAMS["send_time"] = e.time;
        CQPLUS_RPC_PARAMS["from_group"] = e.group_id;
        CQPLUS_RPC_PARAMS["from_qq"] = e.user_id;
        CQPLUS_RPC_PARAMS["msg"] = e.comment;
        CQPLUS_RPC_PARAMS["response_flag"] = e.flag;
        CQPLUS_RPC_INVOKE("on_group_request");

        if (CQPLUS_RPC_RET.asBool())
        {
            e.block();
        }
    };

    cqplus::timer::on_timer = [](const std::string& name) {
        CQPLUS_RPC_INIT_PARAMS();
        CQPLUS_RPC_PARAMS["name"] = name;
        CQPLUS_RPC_INVOKE("on_timer")
    };
}

CQPLUS_MENU(menu01) {
    CQPLUS_RPC_INVOKE_ON_MENU("menu01");
}

CQPLUS_MENU(menu02) {
    CQPLUS_RPC_INVOKE_ON_MENU("menu02");
}

CQPLUS_MENU(menu03) {
    CQPLUS_RPC_INVOKE_ON_MENU("menu03");
}

CQPLUS_MENU(menu04) {
    CQPLUS_RPC_INVOKE_ON_MENU("menu04");
}

CQPLUS_MENU(menu05) {
    CQPLUS_RPC_INVOKE_ON_MENU("menu05");
}

CQPLUS_MENU(menu06) {
    CQPLUS_RPC_INVOKE_ON_MENU("menu06");
}

CQPLUS_MENU(menu07) {
    CQPLUS_RPC_INVOKE_ON_MENU("menu07");
}

CQPLUS_MENU(menu08) {
    CQPLUS_RPC_INVOKE_ON_MENU("menu08");
}

CQPLUS_MENU(menu09) {
    CQPLUS_RPC_INVOKE_ON_MENU("menu09");
}
