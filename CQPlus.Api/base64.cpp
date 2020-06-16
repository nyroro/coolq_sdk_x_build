#include "stdafx.h"

#include "./base64.h"
#include "../lib_base64/base64.h"

#ifdef _DEBUG
#pragma comment(lib, "../Debug/lib_base64.lib")
#else
#pragma comment(lib, "../Release/lib_base64.lib")
#endif

namespace cqplus::utils::base64 {
    std::string encode(const unsigned char *bytes, const unsigned int len) { return base64_encode(bytes, len); }
    std::string decode(const std::string &str) { return base64_decode(str); }
}
