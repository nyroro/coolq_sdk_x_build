#pragma once

#include <string>

namespace cqplus::utils::base64 {
    std::string encode(const unsigned char *bytes, unsigned int len);
    std::string decode(const std::string &str);
}
