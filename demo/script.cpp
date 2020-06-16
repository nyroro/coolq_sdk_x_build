#include "pch.h"

#include "./script.h"

using namespace std;

#include <vector>
#include <string>
#include <functional>

#include "../lib_utils/utils.h"

#pragma comment(lib, "../Release/lib_utils.lib")

namespace cqplus::script {
    static vector<function<void(HMODULE)>> api_func_initializers;

    static bool add_func_initializer(const function<void(HMODULE)> &initializer) {
        api_func_initializers.push_back(initializer);
        return true;
    }

    HMODULE cqplus_dll;

    void init() {
        std::string RUNTIME_NAME = "Python27";
        std::string dll_filename = path_join(str_list(os_getenv("CQ_HOME"), "bin", "CQPlus.Script." + RUNTIME_NAME + ".dll"));

        cqplus_dll = LoadLibraryA(dll_filename.c_str());
        if (cqplus_dll)
        {
            for (const auto &initializer : api_func_initializers) {
                initializer(cqplus_dll);
            }
        }
        else 
        {

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
