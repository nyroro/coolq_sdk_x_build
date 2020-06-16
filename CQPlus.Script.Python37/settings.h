#pragma once

namespace cqplus::settings {
    extern Json::Value raw;
    extern std::string RUNTIME_NAME;
    extern std::string RUNTIME_HOME;

    void init();
}
