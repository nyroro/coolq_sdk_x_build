#pragma once

#include <functional>
#include "./json.h"

namespace cqplus::event {
    extern std::function<Json::Value(const Json::String&, const Json::Value&)> on_api_invoke;
}
