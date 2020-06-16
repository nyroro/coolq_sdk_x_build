#pragma once

#include "./def.h"

#define CQPLUS_MENU(MenuName) \
    static void __cqplus_menu_##MenuName(); \
    __CQ_EVENT(int32_t, MenuName, 0)() { \
        __cqplus_menu_##MenuName(); \
        return 0; \
    } \
    static void __cqplus_menu_##MenuName()
