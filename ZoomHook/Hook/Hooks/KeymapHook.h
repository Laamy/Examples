#pragma once

const uintptr_t KEYMAP_ADDR = BASE_ADDR + 0x1C7B30; // v1.19.81 (tutorial: https://www.youtube.com/watch?v=IEpvEjLhBcc)

void* __o__KeyPress; // pointer of the original keypress

std::map<int, bool> keymap;

void KeyPressDetour(int key, bool held)
{
    keymap[key] = held; // store keystates

    Util::CallFunc<void*, int, bool>(
        __o__KeyPress,
        key,
        held
    );
}

class KeymapHook : public FuncHook
{
public:
    bool Initialize() override
    {
        if (MH_CreateHook((void*)KEYMAP_ADDR, &KeyPressDetour, &__o__KeyPress) == MH_OK)
        {
            MH_EnableHook((void*)KEYMAP_ADDR); // activate the detour
        }
        else return false;

        return true;
    }

    static KeymapHook& Instance()
    {
        static KeymapHook instance;
        return instance;
    }
};