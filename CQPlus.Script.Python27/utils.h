#pragma once

#include "./string.h"
#include "./function.h"
#include "./memory.h"

#include "../lib_utils/utils.h"

#ifdef _DEBUG
#pragma comment(lib, "../Debug/lib_utils.lib")
#else
#pragma comment(lib, "../Release/lib_utils.lib")
#endif
