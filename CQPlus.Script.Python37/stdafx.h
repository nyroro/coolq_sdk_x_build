// stdafx.h: 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>



// 在此处引用程序需要的其他标头
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include <delayimp.h>
#pragma comment(lib, "Delayimp.lib")

#include <Windows.h>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cstdint>
#include <functional>
#include <list>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include "./json.h"
#include "./base64.h"
#include "./utils.h"
#include "./script_engine_def.h"
