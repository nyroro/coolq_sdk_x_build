#pragma once

namespace cqplus::timer {
    extern void init();
    extern void fini();

    extern std::function<void(const std::string&)> on_timer;
}
