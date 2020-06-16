#pragma once

#include <string>
#include <regex>
#include <functional>

namespace cqplus::utils {
    std::string string_to_coolq(const std::string &str);
    std::string string_from_coolq(const std::string &str);
}
