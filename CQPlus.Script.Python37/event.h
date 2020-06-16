#pragma once

namespace cqplus::event {
    extern std::function<Json::Value(const Json::String&, const Json::Value&)> on_rpc_invoke;
} // namespace cq::event
