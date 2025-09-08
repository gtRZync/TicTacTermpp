#pragma once
#include "config.hpp"

class ConsoleUI final {
    private:
        static const WORD flags = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        static const HANDLE hConsole;
    public:
        ConsoleUI() { }
        ~ConsoleUI() { }
    public:
        static void GameMenu(GAMESTATE& state, bool& isRunning);
        static void showCursor();
        static void hideCursor();
    private:
        static void setMenuColors(WORD flag);
        static void getConsoleMetrics(int &width, int &height);
        static void clearConsole();
        static void setCursorPosition(short cx, short cy);
        static int showMenu(int cx, int cy);
};
