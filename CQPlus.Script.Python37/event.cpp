#include "stdafx.h"
#include "./event.h"

#include "./def.h"
#include "./utils.h"

namespace cqplus::event {
    std::function<Json::Value(const Json::String&, const Json::Value&)> on_rpc_invoke;
} // namespace cqplus::event

__CQPLUS_EVENT(const char*, rpc_invoke, 8)
(const char* method, const char* params) {
    Json::String _method(method);
    Json::Value _params(Json::objectValue);

    json_loads(params, &_params);

    Json::Value ret(Json::objectValue);
    ret = cqplus::utils::call_if_valid(cqplus::event::on_rpc_invoke, _method, _params);

    auto ret_s = ret.toStyledString();

    int32_t ret_buffer_size = ret_s.size() + 1;
    char* ret_buffer = (char*)malloc(ret_buffer_size);
    if (ret_buffer)
    {
        memset(ret_buffer, 0, ret_buffer_size);
        memcpy(ret_buffer, ret_s.c_str(), ret_s.size());
    }
    else
    {
        ALERT("ƒ⁄¥Ê∑÷≈‰ ß∞‹");
    }

    return (const char*)ret_buffer;
}

__CQPLUS_EVENT(void, rpc_free, 4)
(void* p) {
    if (p)
    {
        free(p);
    }
}
