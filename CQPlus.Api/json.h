#pragma once

#include "../lib_json/json.h"

#ifdef _DEBUG
#pragma comment(lib, "../Debug/lib_json.lib")
#else
#pragma comment(lib, "../Release/lib_json.lib")
#endif
