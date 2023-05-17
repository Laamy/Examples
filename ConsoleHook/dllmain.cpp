/*
ISO C++17 Standard (/std:c++17)
No Precompiled Headers
*/

#include <Windows.h>
#include <iostream>

#include "Util.h"

void InitClient(HMODULE mod)
{
    Util::createConsole();
    SetConsoleTitleA("Hello, world! (x2)");

    std::cout << "Hello, world!" << std::endl;
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