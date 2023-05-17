#pragma once

#include <stdio.h>

class Util {
public:
    static void createConsole()
    {
        HWND consoleWnd = GetConsoleWindow();
        if (!consoleWnd)
        {
            AllocConsole();

            freopen_s(&f, "CONOUT$", "w", stdout);
            freopen_s(&f, "CONIN$", "r", stdin);
            SetConsoleTitleA("Internal Console");
        }
        else
        {
            ShowWindow(GetConsoleWindow(), SW_SHOW);
        }
    }

    static void closeConsole()
    {
        // actually deallocating consoles in UWP will cause crashes
        // so we can reuse the console we just hide and clear it for the next "createConsole" call
        ShowWindow(GetConsoleWindow(), SW_HIDE);
        clearConsole();
    }

    static void clearConsole()
    {
        system("cls");
    }

private:
    inline static FILE* f;
};