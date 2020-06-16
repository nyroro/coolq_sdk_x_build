#pragma once

#include "./app.h"
#include "./json.h"
#include "./logging.h"

namespace cqplus::script {
    void init();

    extern HMODULE cqplus_dll;

    namespace raw {
#include "./script_funcs.inl"
    }

    inline Json::Value rpc_invoke(const std::string &method, const Json::Value &params) {
        Json::Value ret(Json::objectValue);

        Json::String p = params.toStyledString();

        if (cqplus_dll != NULL) {
            cqplus::logging::debug(u8"RPC调用成功：" + method);
            cqplus::logging::debug(params.toStyledString());

            const char* ret_s = raw::CQPLUS_rpc_invoke(method.c_str(), p.c_str());
            json_loads(ret_s, &ret);
            raw::CQPLUS_rpc_free((void*)ret_s);
        }
        else
        {
            cqplus::logging::error(u8"RPC调用失败：" + method);
            cqplus::logging::debug(params.toStyledString());
        }

        return ret;
    }
}


#define CQPLUS_RPC_ENV __env__
#define CQPLUS_RPC_RET __ret__
#define CQPLUS_RPC_PARAMS __params__

#define CQPLUS_RPC_INIT_PARAMS() \
    Json::Value CQPLUS_RPC_RET(Json::nullValue); \
    \
    Json::Value CQPLUS_RPC_ENV(Json::objectValue); \
    CQPLUS_RPC_ENV["CQ_HOME"] = cqplus::app::cq_home; \
    CQPLUS_RPC_ENV["CQ_APP_ID"] = cqplus::app::app_id; \
    CQPLUS_RPC_ENV["CQ_AUTH_CODE"] = cqplus::app::auth_code; \
    \
    Json::Value CQPLUS_RPC_PARAMS(Json::objectValue); \
    CQPLUS_RPC_PARAMS["env"] = CQPLUS_RPC_ENV; \
    \
    CQPLUS_RPC_PARAMS["settings"] = cqplus::settings::raw;

#define CQPLUS_RPC_INVOKE(method) \
    try { \
        CQPLUS_RPC_RET = cqplus::script::rpc_invoke(method, CQPLUS_RPC_PARAMS); \
    } catch (const std::exception &) { \
    }

#define CQPLUS_RPC_INVOKE_NO_PARAM(method) \
    CQPLUS_RPC_INIT_PARAMS(); \
    CQPLUS_RPC_INVOKE(method);

#define CQPLUS_RPC_INVOKE_ON_MENU(name) \
    CQPLUS_RPC_INIT_PARAMS(); \
    CQPLUS_RPC_PARAMS["name"] = name; \
    try { \
        CQPLUS_RPC_RET = cqplus::script::rpc_invoke("on_menu", CQPLUS_RPC_PARAMS); \
    } catch (const std::exception &) { \
    }
