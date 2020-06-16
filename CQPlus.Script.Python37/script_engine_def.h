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

#   error δָ��PYTHON�汾����ʹ��Ԥ�����USE_PYTHON27����USE_PYTHON37

#endif
