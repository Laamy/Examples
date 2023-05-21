#pragma once

const uintptr_t FIELD_HOOK = BASE_ADDR + 0xE69CB0; // v1.19.81 (tutorial: https://www.youtube.com/watch?v=IEpvEjLhBcc)

void* __o__FieldHook;

void* FieldDetour(void* a1, void* a2, void* a3, void* a4, float* a5)
{
    float* fieldMulti = reinterpret_cast<float*>((uintptr_t)a1 + 0x1350);

    if (keymap['C'])
    {
        *fieldMulti = 0.3f;
    }

    return Util::CallFunc<void*, void*, void*, void*, void*, float*>(
        __o__FieldHook,
        a1, a2, a3, a4,a5
    );
}

class FieldHook : public FuncHook
{
public:
    bool Initialize() override
    {
        if (MH_CreateHook((void*)FIELD_HOOK, &FieldDetour, &__o__FieldHook) == MH_OK)
        {
            MH_EnableHook((void*)FIELD_HOOK); // activate the detour
        }
        else return false;

        return true;
    }

    static FieldHook& Instance()
    {
        static FieldHook instance;
        return instance;
    }
};