#include "stdafx.h"

#include "./script_engine.h"
#include "./api.h"
#include "./app.h"
#include "./logging.h"
#include "./utils.h"
#include "./settings.h"

#define CQPLUS_MODULE_NAME "_cqplus"

static std::string PYOBJECT_TO_STR(PyObject* o) {
    std::string ret;

    if (PyBytes_Check(o))
    {
        ret = PyBytes_AsString(o);
    }
    else if (PyUnicode_Check(o))
    {
        ret = PyBytes_AsString(PyUnicode_AsUTF8String(o));
    }

    return ret;
}

static PyObject* CQPLUS_PYTHON_api_invoke(PyObject* self, PyObject* args) {
    PyObject* ret = NULL;

    PyObject* method_t = PyTuple_GetItem(args, 0);
    PyObject* params_t = PyTuple_GetItem(args, 1);

    std::string method = PYOBJECT_TO_STR(method_t);
    std::string params = PYOBJECT_TO_STR(params_t);

    const char* ret_s = cqplus::api::raw::CQPLUS_api_invoke(method.c_str(), params.c_str());
    ret = Py_BuildValue("s", ret_s);
    cqplus::api::raw::CQPLUS_api_free((void*)ret_s);

    return ret;
}

static struct PyMethodDef CQPLUS_funcs[] = {
    { "api_invoke", (PyCFunction)CQPLUS_PYTHON_api_invoke, 0x0001, NULL },
    { NULL, NULL, 0, NULL }
};

#if defined(USE_PYTHON37)
PyObject* PyInit__cqplus(void) {
    PyObject* m = NULL;

    static struct PyModuleDef CQPLUS_module = {
        PyModuleDef_HEAD_INIT,
        CQPLUS_MODULE_NAME,
        NULL,
        -1,
        CQPLUS_funcs,
        NULL,
        NULL,
        NULL,
        NULL
    };

    m = PyModule_Create(&CQPLUS_module);

    return m;
}
#endif

#if defined(USE_PYTHON27)
static void CQPLUS_PYTHON27_module_init() {
    Py_InitModule3(CQPLUS_MODULE_NAME, CQPLUS_funcs, NULL);
}
#elif defined(USE_PYTHON37)
static void CQPLUS_PYTHON37_module_init() {
    PyImport_AppendInittab(CQPLUS_MODULE_NAME, PyInit__cqplus);
}
#endif

std::string reg_read(HKEY hKey, LPCSTR lpSubKey, LPCSTR lpValueName = "") {
    HKEY hKeyOut;
    DWORD type = 0;
    CHAR buffer[1024];
    DWORD len = 1024;

    memset(buffer, 0, sizeof(buffer));

    if (::RegOpenKeyExA(hKey, lpSubKey, 0, KEY_QUERY_VALUE, &hKeyOut) == ERROR_SUCCESS) {
        ::RegQueryValueExA(hKeyOut, lpValueName, 0, NULL, (BYTE*)buffer, &len);
        ::RegCloseKey(hKeyOut);
    }

    return std::string(buffer);
}

namespace cqplus::script_engine {
    bool is_initialized = false;
    std::string dll_filename;
    std::string zip_filename;
    PyObject* cqplus_ptr = NULL;
}

namespace cqplus::script_engine {
    void init() {
        if (is_initialized)
        {
            return;
        }

        std::string RUNTIME_NAME = cqplus::settings::RUNTIME_NAME;
        std::string RUNTIME_HOME = cqplus::settings::RUNTIME_HOME;

        do {
            os_delenv("PYTHONDEBUG");
            os_delenv("PYTHONHOME");
            os_delenv("PYTHONOPTIMIZE");
            os_delenv("PYTHONPATH");
            os_delenv("PYTHONVERBOSE");

            dll_filename = str_tolower(RUNTIME_NAME) + ".dll";
            zip_filename = str_tolower(RUNTIME_NAME) + ".zip";

            if (RUNTIME_HOME.empty()) {
                if (RUNTIME_NAME == "Python27") {
                    RUNTIME_HOME = reg_read(HKEY_CURRENT_USER, "Software\\Python\\PythonCore\\2.7\\InstallPath", "");
                }
                else if (RUNTIME_NAME == "Python37") {
                    RUNTIME_HOME = reg_read(HKEY_CURRENT_USER, "Software\\Python\\PythonCore\\3.7-32\\InstallPath", "");
                }
            }

            const static std::string PATH = os_getenv("PATH");

            std::vector<std::string> sys_path_list;
            sys_path_list.push_back(RUNTIME_HOME);
            sys_path_list.push_back(path_join(str_list(RUNTIME_HOME, "DLLs")));
            sys_path_list.push_back(PATH);
            os_putenv("PATH", str_join(";", sys_path_list));

            sys_path_list = str_split(os_getenv("PATH"), ";");
            bool is_python_dll_exists = false;
            std::string python_dll_basename = RUNTIME_NAME + ".dll";
            for (auto it = sys_path_list.cbegin(); it != sys_path_list.cend(); it++)
            {
                std::string python_dll_filename = path_join(str_list(*it, python_dll_basename));
                if (path_isfile(python_dll_filename)) {
                    is_python_dll_exists = true;
                    break;
                }
            }
            if (!is_python_dll_exists) {
                ALERT("找不到" + RUNTIME_NAME + "环境");
                break;
            }

            std::vector<std::string> python_path_list;

            std::string cq_home = cqplus::utils::string_to_coolq(cqplus::app::cq_home);
            std::string plugin_home = path_join(str_list(cq_home, "bin"));

            std::string cqplus_pysdk_dev_home = os_getenv("CQPLUS_PYSDK_DEV_HOME");
            if (!cqplus_pysdk_dev_home.empty())
            {
                python_path_list.push_back(cqplus_pysdk_dev_home);
            }
            python_path_list.push_back(path_join(str_list(plugin_home, "CQPlus.Script.Python")));
            python_path_list.push_back(path_join(str_list(plugin_home, "CQPlus.Script.Python.zip")));
            python_path_list.push_back(path_join(str_list(plugin_home, "CQPlus.Script." + RUNTIME_NAME)));
            python_path_list.push_back(path_join(str_list(plugin_home, "CQPlus.Script." + RUNTIME_NAME + ".zip")));
            python_path_list.push_back(RUNTIME_HOME);
            python_path_list.push_back(path_join(str_list(RUNTIME_HOME, zip_filename)));
            python_path_list.push_back(path_join(str_list(RUNTIME_HOME, "Lib")));
            python_path_list.push_back(path_join(str_list(RUNTIME_HOME, "DLLs")));
            if (RUNTIME_NAME == "Python27") {
                python_path_list.push_back(path_join(str_list(RUNTIME_HOME, "Lib", "lib-tk")));
            }

            os_putenv("PYTHONHOME", RUNTIME_HOME);
            os_putenv("PYTHONPATH", str_join(";", python_path_list));

            if (FAILED(__HrLoadAllImportsForDll(dll_filename.c_str()))) {
                std::stringstream ss;
                ss << ::GetLastError();
                auto msg = str_join(str_list("加载", RUNTIME_NAME, "运行时失败，ErrCode=", ss.str(), "\n", dll_filename));
                ALERT(msg);
                break;
            }

#if defined(USE_PYTHON37)
            CQPLUS_PYTHON37_module_init();
#endif

            Py_InitializeEx(0);
            if (!Py_IsInitialized()) {
                break;
            }

#if defined(USE_PYTHON27)
            CQPLUS_PYTHON27_module_init();
#endif

            PyObject* m = NULL;
            PyObject* d = NULL;
            PyObject* c = NULL;

            do {
#define BREAK_IF_NULL(var, msg) if (NULL == var) { ALERT(msg); break; }

                m = PyImport_ImportModule("cqplus._handler");
                BREAK_IF_NULL(m, "加载cqplus._handler模块失败");

                d = PyModule_GetDict(m);
                BREAK_IF_NULL(d, "获取cqplus._handler字典失败");

                c = PyDict_GetItemString(d, "CQPlusGlobalHandler");
                BREAK_IF_NULL(c, "加载cqplus._handler.CQPlusGlobalHandler类失败");

                cqplus_ptr = PyObject_CallObject(c, NULL);
                BREAK_IF_NULL(cqplus_ptr, "创建cqplus._handler.CQPlusGlobalHandler类示例失败");

                is_initialized = true;
            } while (false);

            Py_XDECREF(c);
            Py_XDECREF(d);
            Py_XDECREF(m);

         } while (false);

         if (!is_initialized)
         {
             ALERT("运行时" + RUNTIME_NAME + "初始化失败");
         }
    }

    const char* on_rpc_invoke(const char* method, const char* params) {
        const char* ret = "{\"code\":0, \"data\":0}";
        if (cqplus_ptr != NULL) {
            PyObject* f = PyObject_GetAttrString(cqplus_ptr, "_handle_event");
            if (f != NULL) {
                PyObject* args = PyTuple_New(2);
                PyTuple_SetItem(args, 0, PyUnicode_FromString(method));
                PyTuple_SetItem(args, 1, PyUnicode_FromString(params));

                PyObject* r = PyObject_CallObject(f, args);
                if (r != NULL) {
                    if (PyBytes_Check(r))
                    {
                        ret = PyBytes_AsString(r);
                    }
                    else if (PyUnicode_Check(r))
                    {
                        ret = PyBytes_AsString(PyUnicode_AsUTF8String(r));
                    }
                    Py_XDECREF(r);
                }
                else {
                    PyObject *exc = NULL;
                    PyObject *val = NULL;
                    PyObject *traceback = NULL;
                    PyErr_Fetch(&exc, &val, &traceback);
                    PyErr_NormalizeException(&exc, &val, &traceback);
                    
                    std::stringstream ss;

                    if (exc)
                    {
                        if (PyType_Check(exc))
                        {
                            ss << (const char*)(((PyTypeObject*)exc)->tp_name);
                        }
#if defined(USE_PYTHON27)
                        else
                        {
                            ss << (const char*)(((PyClassObject*)exc)->cl_name);
                        }
#endif
                        ss << ": ";
                    }

                    if (val)
                    {
                        PyObject *line = PyObject_Str(val);
                        if (line)
                        {
                            ss << PYOBJECT_TO_STR(line);
                        }
                        Py_XDECREF(line);
                    }

                    ss << std::endl;

                    for (PyTracebackObject *tb = (PyTracebackObject*)traceback; NULL != tb; tb = tb->tb_next)
                    {
                        PyFrameObject* tb_frame = (PyFrameObject*)tb->tb_frame;
                        PyObject *co_filename = PyObject_Str(tb_frame->f_code->co_filename);
                        PyObject *co_name = PyObject_Str(tb_frame->f_code->co_name);

                        ss << "  File \"" << PYOBJECT_TO_STR(co_filename) << "\", line " << tb->tb_lineno << ", in " << PYOBJECT_TO_STR(co_name) << "\"" << std::endl;

                        Py_XDECREF(co_name);
                        Py_XDECREF(co_filename);
                    }

                    std::string err = ss.str();
                    ALERT(err);

                    Py_XDECREF(traceback);
                    Py_XDECREF(val);
                    Py_XDECREF(exc);
                }

                Py_XDECREF(args);
                Py_XDECREF(f);
            }
            else {
                ALERT("调用PYTHON方法失败");
            }
        }
        return ret;
    }
}
