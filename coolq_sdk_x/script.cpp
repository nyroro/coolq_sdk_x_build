#include "stdafx.h"

#include "./script.h"
#include "./utils.h"
#include "./settings.h"
#include "./logging.h"

using namespace std;

namespace cqplus::script {
    static vector<function<void(HMODULE)>> api_func_initializers;

    static bool add_func_initializer(const function<void(HMODULE)> &initializer) {
        api_func_initializers.push_back(initializer);
        return true;
    }

    HMODULE cqplus_dll;

    void init() {
        std::string dll_filename = path_join(str_list(cqplus::utils::string_to_coolq(cqplus::app::cq_home), "bin", "CQPlus.Script." + cqplus::settings::RUNTIME_NAME + ".dll"));
        std::string dll_filename_t = cqplus::utils::string_from_coolq(dll_filename);

        cqplus_dll = LoadLibraryA(dll_filename.c_str());
        if (cqplus_dll)
        {
            cqplus::logging::debug(u8"加载成功：" + dll_filename_t);
            for (const auto &initializer : api_func_initializers) {
                initializer(cqplus_dll);
            }
        }
        else 
        {
            cqplus::logging::error(u8"加载失败：" + dll_filename_t);
        }
    }

    namespace raw {
#define FUNC(ReturnType, FuncName, ...) \
    typedef __declspec(dllimport) ReturnType(__stdcall *__CQPLUS_##FuncName##_T)(__VA_ARGS__); \
    __CQPLUS_##FuncName##_T CQPLUS_##FuncName; \
    static bool __dummy_CQPLUS_##FuncName = add_func_initializer([](auto dll) { \
        if (dll != NULL) { \
            CQPLUS_##FuncName = reinterpret_cast<__CQPLUS_##FuncName##_T>(GetProcAddress(dll, "CQPLUS_" #FuncName)); \
        } else { \
            CQPLUS_##FuncName = reinterpret_cast<__CQPLUS_##FuncName##_T>(0); \
        } \
    });

#include "./script_funcs.inl"
    }
}
