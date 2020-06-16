#include "stdafx.h"

#include "./string.h"
#include "./_utils.h"

#include <codecvt>
#include <Windows.h>

using namespace std;

namespace cqplus::utils {
    string sregex_replace(const string &str, const regex &re, const function<string(const smatch &)> fmt_func) {
        string result;
        auto last_end_pos = 0;
        for (sregex_iterator it(str.begin(), str.end(), re), end; it != end; ++it) {
            result += it->prefix().str() + fmt_func(*it);
            last_end_pos = it->position() + it->length();
        }
        result += str.substr(last_end_pos);
        return result;
    }

    const UINT ENCODING_UTF8 = 65001;
    const UINT ENCODING_GB18030 = 54936;

    std::string ws2s(const std::wstring& s, UINT code_page)
    {
        std::string ret;
        
        auto len = ::WideCharToMultiByte(code_page, 0, s.c_str(), -1, NULL, 0, NULL, NULL);
        if (len > 0)
        {
            auto buffer_size = sizeof(char) * (len + 1);
            char* buffer = (char*)malloc(buffer_size);
            memset(buffer, 0, buffer_size);
            if (buffer)
            {
                ::WideCharToMultiByte(code_page, 0, s.c_str(), -1, buffer, len, NULL, NULL);
                ret = std::string(buffer);
                free(buffer);
            }
        }

        return ret;
    }

    std::wstring s2ws(const std::string& s, UINT code_page)
    {
        std::wstring ret;

        auto len = ::MultiByteToWideChar(code_page, 0, s.c_str(), -1, NULL, 0);
        if (len > 0)
        {
            auto buffer_size = sizeof(wchar_t) * (len + 1);
            wchar_t* buffer = (wchar_t*)malloc(buffer_size);
            memset(buffer, 0, buffer_size);
            if (buffer)
            {
                ::MultiByteToWideChar(code_page, 0, s.c_str(), -1, buffer, len);
                ret = std::wstring(buffer);
                free(buffer);
            }
        }

        return ret;
    }

    std::string string_convert_encoding(const std::string& s, UINT from_encoding_cp, UINT to_encoding_cp)
    {
        return ws2s(s2ws(s, from_encoding_cp), to_encoding_cp);
    }

    string string_to_coolq(const string &str) {
        std::string ret = string_convert_encoding(str, ENCODING_UTF8, ENCODING_GB18030);
        return ret;
    }

    string string_from_coolq(const string &str) {
        auto result = string_convert_encoding(str, ENCODING_GB18030, ENCODING_UTF8);
        if (false) {
            result = sregex_replace(result, regex(R"(\[CQ:emoji,\s*id=(\d+)\])"), [](const smatch &m) {
                const auto codepoint_str = m.str(1);
                u32string u32_str;

                if (str_starts_with(codepoint_str, "100000")) {
                    // keycap # to keycap 9
                    const auto codepoint = static_cast<char32_t>(stoul(codepoint_str.substr(strlen("100000"))));
                    u32_str.append({codepoint, 0xFE0F, 0x20E3});
                } else {
                    const auto codepoint = static_cast<char32_t>(stoul(codepoint_str));
                    u32_str.append({codepoint});
                }

                const auto p = reinterpret_cast<const uint32_t *>(u32_str.data());
                wstring_convert<codecvt_utf8<uint32_t>, uint32_t> conv;
                return conv.to_bytes(p, p + u32_str.size());
            });

            // CoolQ sometimes use "#\uFE0F" to represent "#\uFE0F\u20E3"
            // we should convert them into correct emoji codepoints here
            //     \uFE0F == \xef\xb8\x8f
            //     \u20E3 == \xe2\x83\xa3
            result = sregex_replace(result, regex("([#*0-9]\xef\xb8\x8f)(\xe2\x83\xa3)?"), [](const smatch &m) {
                return m.str(1) + "\xe2\x83\xa3";
            });
        }

        return result;
    }

} // namespace cqplus::utils
