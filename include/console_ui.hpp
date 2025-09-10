#pragma once
#include "config.hpp"

enum class ConsoleColor {
    Default,
    TextGray_BGBlue,
    TextBlack_BGWhite,
    RED,
    BLUE,
    YELLOW,
};

class ConsoleUI final {
    private:
    #ifdef _WIN32
        static const HANDLE hConsole;
        static WORD _w32getConsoleAttributes();
        static WORD _w32getWinColorAttribute(ConsoleColor color);
        static const WORD saved_attributes;
    #endif
        using ConsoleHandle = void *;
    public:
        ConsoleUI() { }
        ~ConsoleUI() { }
    public:
        static void GameMenu(GAMESTATE& state, bool& isRunning);
        static void showCursor();
        static void hideCursor();
        static void setColor(ConsoleColor color);
        static void resetColor();
        static void clearConsole();
    private:
        static std::string  getAnsiEscapeSequence(ConsoleColor color);
        static void         getConsoleMetrics(int &width, int &height);
        static void         setCursorPosition(short cx, short cy);
        static int          showMenu(int cx, int cy);
        static void         drawBox(int posx, int posy, int box_width, int box_height);
};
