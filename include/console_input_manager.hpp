#pragma once
#include "config.hpp"

class ConsoleInputManager {
    private:

    public:
        ConsoleInputManager();
        ~ConsoleInputManager();
    public:
        bool    keyPressed(void) const;
        int     getKey() const;
    private:

        int     _unixKbhit();
        int     _unixGetch();
        void    reset_terminal(struct termios* oldt);
        void    set_conio_terminal_mode();
};