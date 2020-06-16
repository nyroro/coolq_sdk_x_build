#pragma once

#include <Windows.h>

namespace cqplus::script {
    void init();

    extern HMODULE cqplus_dll;

    namespace raw {
#include "./script_funcs.inl"
    }
}
