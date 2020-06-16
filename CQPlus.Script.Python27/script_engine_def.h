#pragma once

#if defined(USE_PYTHON27)

#   define SCRIPT_ENGINE_NAME "Python27"
#   include "../lib_python27/include/Python.h"
#   include "../lib_python27/include/frameobject.h"

#elif defined(USE_PYTHON37)

#   define SCRIPT_ENGINE_NAME "Python37"
#   include "../lib_python37/include/Python.h"
#   include "../lib_python37/include/frameobject.h"

#else

#   error 未指定PYTHON版本，请使用预处理宏USE_PYTHON27或者USE_PYTHON37

#endif
