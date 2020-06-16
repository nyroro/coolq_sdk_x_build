#include "stdafx.h"

#include "./app.h"
#include "./def.h"
#include "./api.h"
#include "./function.h"


namespace cqplus::app {
    int32_t auth_code;
    std::string app_id;
    std::string cq_home;

    std::function<void()> on_initialize;
    std::function<void()> on_enable;
    std::function<void()> on_disable;
    std::function<void()> on_coolq_start;
    std::function<void()> on_coolq_exit;

    std::function<void(HMODULE)> app_init;
    std::function<void(HMODULE)> app_main;
}

using namespace std;
using namespace cqplus;
using cqplus::utils::call_if_valid;

/**
 * Return app info.
 */
__CQ_EVENT(const char *, AppInfo, 0)
() {
    // CoolQ API version: 9
    static auto info = "9," + app::app_id;
    return info.c_str();
}

/**
 * Initialize SDK using the auth code given by CoolQ.
 */
__CQ_EVENT(int32_t, Initialize, 4)
(const int32_t auth_code) {
    app::auth_code = auth_code;
    api::init();
    call_if_valid(app::on_initialize);
    return 0;
}

/**
 * Event: Plugin is enabled.
 */
__CQ_EVENT(int32_t, cq_app_enable, 0)
() {
    call_if_valid(app::on_enable);
    return 0;
}

/**
 * Event: Plugin is disabled.
 */
__CQ_EVENT(int32_t, cq_app_disable, 0)
() {
    call_if_valid(app::on_disable);
    return 0;
}

/**
 * Event: CoolQ is starting.
 */
__CQ_EVENT(int32_t, cq_coolq_start, 0)
() {
    call_if_valid(app::on_coolq_start);
    return 0;
}

/**
 * Event: CoolQ is exiting.
 */
__CQ_EVENT(int32_t, cq_coolq_exit, 0)
() {
    call_if_valid(app::on_coolq_exit);
    return 0;
}
