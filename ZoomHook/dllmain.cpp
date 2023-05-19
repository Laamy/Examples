/*
ISO C++17 Standard (/std:c++17)
No Precompiled Headers
*/

#include <Windows.h>
#include <iostream>
#include <map>

#include "Util.h"
#include "Libs/minhook/minhook.h"

#include "Hook/Hooks.h"

void InitClient(HMODULE mod)
{
    Util::createConsole(); // Not essential, just debugging.

    if (MH_Initialize() == MH_OK)
    {
        InitializeHooks();
    }
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(module); // stops multiple injections
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitClient, module, 0, 0);
    }
    return TRUE;
}