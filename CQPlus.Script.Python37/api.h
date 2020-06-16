#pragma once

#include "./app.h"
#include "./json.h"

namespace cqplus::api {
    void init();

    extern HMODULE cqplus_dll;

    namespace raw {
#include "./api_funcs.inl"
    }

    inline Json::Value api_invoke(const std::string &method, const Json::Value &params) {
        Json::Value ret(Json::objectValue);

        Json::String p = params.toStyledString();

        if (cqplus_dll != NULL) {
            const char* ret_s = raw::CQPLUS_api_invoke(method.c_str(), p.c_str());
            json_loads(ret_s, &ret);
            raw::CQPLUS_api_free((void*)ret_s);
        }

        return ret;
    }
}

#define CQPLUS_API_RET __ret__
#define CQPLUS_API_PARAMS __params__

#define CQPLUS_API_INIT_PARAMS() \
    Json::Value CQPLUS_API_RET(Json::nullValue); \
    \
    Json::Value CQPLUS_API_PARAMS(Json::objectValue); \
    CQPLUS_API_PARAMS["env"] = env;

#define CQPLUS_API_INVOKE(method) \
    try { \
        CQPLUS_API_RET = cqplus::api::api_invoke(method, CQPLUS_API_PARAMS); \
    } catch (const std::exception &) { \
    }

#define CQPLUS_API_INVOKE_NO_PARAM(method) \
    CQPLUS_API_INIT_PARAMS(); \
    CQPLUS_API_INVOKE(method);
