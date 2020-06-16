#pragma once

#include "./json.h"
#include "./target.h"
#include "./types.h"

namespace cqplus::api {
    void init();

    namespace raw {
#include "./api_funcs.inl"
    }

    void route(const std::string&, std::function<Json::Value(const Json::String&, const Json::Value&)>);
    Json::Value handle(const Json::String&, const Json::Value&);

#pragma region Message

    inline int32_t send_private_msg(int32_t auth_code, const int64_t user_id, const std::string &msg) {
        const auto ret = raw::CQ_sendPrivateMsg(auth_code, user_id, utils::string_to_coolq(msg).c_str());
        
        return ret;
    }

    inline int32_t send_group_msg(int32_t auth_code, const int64_t group_id, const std::string &msg) {
        const auto ret = raw::CQ_sendGroupMsg(auth_code, group_id, utils::string_to_coolq(msg).c_str());
        
        return ret;
    }

    inline int32_t send_discuss_msg(int32_t auth_code, const int64_t discuss_id, const std::string &msg) {
        const auto ret = raw::CQ_sendDiscussMsg(auth_code, discuss_id, utils::string_to_coolq(msg).c_str());
        
        return ret;
    }

    inline void delete_msg(int32_t auth_code, const int64_t msg_id) {
        raw::CQ_deleteMsg(auth_code, msg_id);
    }

#pragma endregion

#pragma region Send Like

    inline void send_like(int32_t auth_code, const int64_t user_id) {
        raw::CQ_sendLike(auth_code, user_id);
    }

    inline void send_like(int32_t auth_code, const int64_t user_id, const int32_t times) {
        raw::CQ_sendLikeV2(auth_code, user_id, times);
    }

#pragma endregion

#pragma region Group &Discuss Operation

    inline void set_group_kick(int32_t auth_code, const int64_t group_id, const int64_t user_id, const bool reject_add_request) {
        raw::CQ_setGroupKick(auth_code, group_id, user_id, reject_add_request);
    }

    inline void set_group_ban(int32_t auth_code, const int64_t group_id, const int64_t user_id, const int64_t duration) {
        raw::CQ_setGroupBan(auth_code, group_id, user_id, duration);
    }

    inline void set_group_anonymous_ban(int32_t auth_code, const int64_t group_id, const std::string &flag, const int64_t duration) {
        raw::CQ_setGroupAnonymousBan(auth_code, group_id, utils::string_to_coolq(flag).c_str(), duration);
    }

    inline void set_group_whole_ban(int32_t auth_code, const int64_t group_id, const bool enable) {
        raw::CQ_setGroupWholeBan(auth_code, group_id, enable);
    }

    inline void set_group_admin(int32_t auth_code, const int64_t group_id, const int64_t user_id, const bool enable) {
        raw::CQ_setGroupAdmin(auth_code, group_id, user_id, enable);
    }

    inline void set_group_anonymous(int32_t auth_code, const int64_t group_id, const bool enable) {
        raw::CQ_setGroupAnonymous(auth_code, group_id, enable);
    }

    inline void set_group_card(int32_t auth_code, const int64_t group_id, const int64_t user_id, const std::string &card) {
            raw::CQ_setGroupCard(auth_code, group_id, user_id, utils::string_to_coolq(card).c_str());
    }

    inline void set_group_leave(int32_t auth_code, const int64_t group_id, const bool is_dismiss) {
        raw::CQ_setGroupLeave(auth_code, group_id, is_dismiss);
    }

    inline void set_group_special_title(int32_t auth_code, const int64_t group_id, const int64_t user_id, const std::string &special_title,const int64_t duration) {
        raw::CQ_setGroupSpecialTitle(auth_code, group_id, user_id, utils::string_to_coolq(special_title).c_str(), duration);
    }

    inline void set_discuss_leave(int32_t auth_code, const int64_t discuss_id) {
        raw::CQ_setDiscussLeave(auth_code, discuss_id);
    }

#pragma endregion

#pragma region Request Operation

    inline void set_friend_add_request(int32_t auth_code, const std::string &flag, int32_t operation, const std::string &remark) {
        raw::CQ_setFriendAddRequest(auth_code, utils::string_to_coolq(flag).c_str(), operation, utils::string_to_coolq(remark).c_str());
    }

    inline void set_group_add_request(int32_t auth_code, const std::string &flag, int32_t type, int32_t operation) {
        raw::CQ_setGroupAddRequest(auth_code, utils::string_to_coolq(flag).c_str(), type, operation);
    }

    inline void set_group_add_request(int32_t auth_code, const std::string &flag, int32_t type, const int32_t operation, const std::string &reason) {
        raw::CQ_setGroupAddRequestV2(auth_code,
            utils::string_to_coolq(flag).c_str(),
            type,
            operation,
            utils::string_to_coolq(reason).c_str()
        );
    }

#pragma endregion

#pragma region Get QQ Information

    inline int64_t get_login_user_id(int32_t auth_code) noexcept { return raw::CQ_getLoginQQ(auth_code); }

    inline std::string get_login_nickname(int32_t auth_code) {
        const auto ret = raw::CQ_getLoginNick(auth_code);
        
        return utils::string_from_coolq(ret);
    }

    inline std::string get_stranger_info_base64(int32_t auth_code, const int64_t user_id, const bool no_cache = false) {
        const auto ret = raw::CQ_getStrangerInfo(auth_code, user_id, no_cache);
        
        return utils::string_from_coolq(ret);
    }

    inline std::string get_group_list_base64(int32_t auth_code) {
        const auto ret = raw::CQ_getGroupList(auth_code);
        
        return utils::string_from_coolq(ret);
    }

    inline std::string get_group_member_list_base64(int32_t auth_code, const int64_t group_id) {
        const auto ret = raw::CQ_getGroupMemberList(auth_code, group_id);
        
        return utils::string_from_coolq(ret);
    }

    inline std::string get_group_member_info_base64(int32_t auth_code, const int64_t group_id, const int64_t user_id,
        const bool no_cache = false) {
        const auto ret = raw::CQ_getGroupMemberInfoV2(auth_code, group_id, user_id, no_cache);
        
        return utils::string_from_coolq(ret);
    }

#pragma endregion

#pragma region Get CoolQ Information

    inline std::string get_cookies(int32_t auth_code) {
        const auto ret = raw::CQ_getCookies(auth_code);
        
        return utils::string_from_coolq(ret);
    }

    inline int32_t get_csrf_token(int32_t auth_code) noexcept { return raw::CQ_getCsrfToken(auth_code); }

    inline std::string get_app_directory(int32_t auth_code) {
        const auto ret = raw::CQ_getAppDirectory(auth_code);
        
        return utils::string_from_coolq(ret);
    }

    inline std::string get_record(int32_t auth_code, const std::string &file, const std::string &out_format) {
        const auto ret = raw::CQ_getRecord(
            auth_code, utils::string_to_coolq(file).c_str(), utils::string_to_coolq(out_format).c_str());
        
        return utils::string_from_coolq(ret);
    }

#pragma endregion

#pragma region CoolQ Self - operation

//     int32_t set_fatal(int32_t auth_code, const char *error_info) {
//        return raw::CQ_setFatal(auth_code, error_info);
//     }
//    
//     int32_t set_restart(int32_t auth_code) {
//         return raw::CQ_setRestart(auth_code);
//     }

#pragma endregion

#pragma region CQSDK Bonus

    inline int64_t send_msg(int32_t auth_code, const Target &target, const std::string &msg) {
        if (target.group_id.has_value()) {
            return send_group_msg(auth_code, target.group_id.value(), msg);
        }
        if (target.discuss_id.has_value()) {
            return send_discuss_msg(auth_code, target.discuss_id.value(), msg);
        }
        if (target.user_id.has_value()) {
            return send_private_msg(auth_code, target.user_id.value(), msg);
        }
        return 0;
    }

    inline User get_stranger_info(int32_t auth_code, const int64_t user_id, const bool no_cache = false) {
        return ObjectHelper::from_base64<User>(get_stranger_info_base64(auth_code, user_id, no_cache));
    }

    inline std::vector<Group> get_group_list(int32_t auth_code) {
        return ObjectHelper::multi_from_base64<std::vector<Group>>(get_group_list_base64(auth_code));
    }

    inline std::vector<GroupMember> get_group_member_list(int32_t auth_code, const int64_t group_id) {
        return ObjectHelper::multi_from_base64<std::vector<GroupMember>>(get_group_member_list_base64(auth_code, group_id));
    }

    inline GroupMember get_group_member_info(int32_t auth_code, const int64_t group_id, const int64_t user_id, const bool no_cache = false) {
        return ObjectHelper::from_base64<GroupMember>(get_group_member_info_base64(auth_code, group_id, user_id, no_cache));
    }

    inline User get_login_info(int32_t auth_code) { return get_stranger_info(auth_code, get_login_user_id(auth_code)); }

#pragma endregion
}
