// coolq_sdk_v6.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include "./app.h"
#include "./utils.h"
#include "./event.h"
#include "./json.h"
#include "./logging.h"
#include "./settings.h"
#include "./script_engine.h"


CQPLUS_INIT(HMODULE hModule) {
    cqplus::app::cq_home = cqplus::utils::string_from_coolq(path_dirname(os_getmodulefilename(NULL)));
    cqplus::api::init();
    cqplus::settings::init();
    cqplus::script_engine::init();
}

CQPLUS_MAIN(HMODULE hModule) {
    cqplus::event::on_rpc_invoke = [](const Json::String& method, const Json::Value& params) -> Json::Value {
        Json::Value ret(Json::nullValue);

        const char* ret_s = cqplus::script_engine::on_rpc_invoke(method.c_str(), params.toStyledString().c_str());
        
        Json::Value ret_t = json_loads(ret_s);
        if (ret_t.get("code", -1).asInt() == 0)
        {
            ret = ret_t.get("data", Json::nullValue);
        }
        else
        {
            Json::Value env = params.get("env", Json::objectValue);
            cqplus::logging::error(env, ret_t.get("data", "unknown").asString());
        }

        return ret;
    };
}
