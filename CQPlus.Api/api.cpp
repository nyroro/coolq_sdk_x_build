#include "stdafx.h"
#include "./api.h"


namespace cqplus::api {
    static std::vector<std::function<void(HMODULE)>> api_func_initializers;

    static bool add_func_initializer(const std::function<void(HMODULE)> &initializer) {
        api_func_initializers.push_back(initializer);
        return true;
    }

    void init() {
        const auto dll = GetModuleHandleW(L"CQP.dll");
        for (const auto &initializer : api_func_initializers) {
            initializer(dll);
        }
    }

    namespace raw {
#define FUNC(ReturnType, FuncName, ...)                                                              \
    typedef __declspec(dllimport) ReturnType(__stdcall *__CQ_##FuncName##_T)(__VA_ARGS__);           \
    __CQ_##FuncName##_T CQ_##FuncName;                                                               \
    static bool __dummy_CQ_##FuncName = add_func_initializer([](auto dll) {                          \
        CQ_##FuncName = reinterpret_cast<__CQ_##FuncName##_T>(GetProcAddress(dll, "CQ_" #FuncName)); \
    });

#include "./api_funcs.inl"
    }

    static std::map<std::string, std::function<Json::Value(const Json::String&, const Json::Value&)>> handlers;

    void route(const std::string& method, std::function<Json::Value(const Json::String&, const Json::Value&)> handler) {
        handlers[method] = handler;
    }

    Json::Value handle(const Json::String& method, const Json::Value& params) {
        Json::Value ret(Json::objectValue);
        if (handlers.find(method) != handlers.end()) {
            auto hander = handlers[method];
            ret = hander(method, params);
        }
        return ret;
    }
}
