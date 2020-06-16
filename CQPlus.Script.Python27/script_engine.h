#pragma once

#include <string>
#include "./script_engine_def.h"

namespace cqplus::script_engine {
    extern void init();
    extern const char* on_rpc_invoke(const char* method, const char* params);
}
