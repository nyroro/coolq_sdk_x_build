#ifndef FUNC
#define DEFINED_FUNC_MACRO
#define FUNC(ReturnType, FuncName, ...)                                     \
    typedef ReturnType(__stdcall *__CQPLUS_##FuncName##_T)(__VA_ARGS__);    \
    extern __CQPLUS_##FuncName##_T CQPLUS_##FuncName;
#endif

#include <cstdint>

FUNC(const char *, rpc_invoke, const char *method, const char *params)
FUNC(void, rpc_free, void* p);

#ifdef DEFINED_FUNC_MACRO
#undef FUNC
#endif
