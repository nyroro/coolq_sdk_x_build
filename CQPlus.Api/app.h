#pragma once

#include <Windows.h>
#include <functional>

namespace cqplus::app {
    extern std::function<void(HMODULE)> app_init;
    extern std::function<void(HMODULE)> app_main;
}

#define CQPLUS_INIT \
    static void __cqplus_app_init(HMODULE); \
    static bool __cqplus_app_init_func() { \
        cqplus::app::app_init = __cqplus_app_init; \
        return true; \
    } \
    static bool __cqplus_app_init_flag = __cqplus_app_init_func(); \
    static void __cqplus_app_init

#define CQPLUS_MAIN \
    static void __cqplus_app_main(HMODULE); \
    static bool __cqplus_app_main_func() { \
        cqplus::app::app_main = __cqplus_app_main; \
        return true; \
    } \
    static bool __cqplus_app_main_flag = __cqplus_app_main_func(); \
    static void __cqplus_app_main
