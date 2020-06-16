#include "stdafx.h"

#include "./app.h"
#include "./def.h"
#include "./api.h"
#include "./function.h"


namespace cqplus::app {
    std::string cq_home;

    std::function<void(HMODULE)> app_init;
    std::function<void(HMODULE)> app_main;
}