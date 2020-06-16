// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

#include "./app.h"
#include "./function.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        cqplus::utils::call_if_valid(cqplus::app::app_init, hModule);
        cqplus::utils::call_if_valid(cqplus::app::app_main, hModule);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

