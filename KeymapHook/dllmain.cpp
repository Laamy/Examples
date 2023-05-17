/*
ISO C++17 Standard (/std:c++17)
No Precompiled Headers
*/

#include <Windows.h>
#include <iostream>

#include "Util.h"
#include "Libs/minhook/minhook.h"

const uintptr_t BASE_ADDR = (uintptr_t)GetModuleHandleA("Minecraft.Windows.exe"); // v1.*.*

const uintptr_t KEYMAP_ADDR = BASE_ADDR + 0x1C7B30; // v1.19.81

void* __o__KeyPress; // pointer of the original keypress

void KeyPressDetour(int key, bool held)
{
    std::cout << key << " " << held << std::endl;

    Util::CallFunc<void*, int, bool>(
        __o__KeyPress,
        key,
        held
    );
}

void InitClient(HMODULE mod)
{
    Util::createConsole(); // Not essential, just debugging.

    if (MH_Initialize() == MH_OK)
    {
        if (MH_CreateHook((void*)KEYMAP_ADDR, &KeyPressDetour, &__o__KeyPress) == MH_OK)
        {
            MH_EnableHook((void*)KEYMAP_ADDR); // activate the detour
        }
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