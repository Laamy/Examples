#pragma once

class FuncHook
{
public:
    virtual bool Initialize() = 0;
    std::string FuncName;
};

const uintptr_t BASE_ADDR = (uintptr_t)GetModuleHandleA("Minecraft.Windows.exe"); // v1.*.*

#include "Hooks/KeymapHook.h"
#include "Hooks/FieldOfViewHook.h"

void InitializeHooks()
{
    static FuncHook* hooks[] = {
        &KeymapHook::Instance(),
        &FieldHook::Instance()
    };

    for (std::size_t i = 0; i < std::size(hooks); ++i)
    {
        if (not hooks[i]->Initialize())
        {
            std::cout << "Failed to hook something!" << std::endl;
        }
    }
}