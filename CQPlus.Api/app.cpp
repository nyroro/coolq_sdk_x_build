#include "stdafx.h"

#include "./app.h"
#include "./function.h"


namespace cqplus::app {
    std::function<void(HMODULE)> app_init;
    std::function<void(HMODULE)> app_main;
}
