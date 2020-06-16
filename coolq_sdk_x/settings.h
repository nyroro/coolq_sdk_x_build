#pragma once

#include <string>
#include <map>

namespace cqplus::settings {
    extern Json::Value raw;
    extern bool IS_DEBUG;
    extern std::map<std::string, int32_t> TIMER;
    extern std::string RUNTIME_NAME;

    void init();
}
