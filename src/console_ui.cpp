#include "console_ui.hpp"

const HANDLE ConsoleUI::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const WORD ConsoleUI::saved_attributes = ConsoleUI::_w32getConsoleAttributes();

WORD ConsoleUI::_w32getConsoleAttributes()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(ConsoleUI::hConsole, &csbi);
    return csbi.wAttributes;
}

void ConsoleUI::GameMenu(GAMESTATE &state, bool& isRunning)
 {
    ConsoleUI::clearConsole();
    int flag = -1;
    ConsoleUI::hideCursor();
    int x, y;
    x = y = 0;
    ConsoleUI::getConsoleMetrics(x, y);
    if(state == GAMESTATE::MENU){
        std::cout << TicTacToeTexts::tictactoeText << "\n";
        flag = ConsoleUI::showMenu(x/2, y/2);
        switch(flag)
        {
            case START:
                state = GAMESTATE::PLAYING; break;
            case EXIT: {
                ConsoleUI::clearConsole();
                ConsoleUI::showCursor();
                isRunning = false;
            }break;
        }
    }
}

void ConsoleUI::showCursor() 
{
    std::cout << "\e[?25h\n";
}

void ConsoleUI::hideCursor() 
{
    std::cout << "\e[?25l\n";
}

//TODO: refactor into branching code using constexpr
void ConsoleUI::getConsoleMetrics(int &width, int &height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;  
    if(GetConsoleScreenBufferInfo(ConsoleUI::hConsole, &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left - 1; 
        height = csbi.srWindow.Bottom - csbi.srWindow.Top - 1; 
    }
}

void ConsoleUI::setColor(ConsoleColor color) {
    if constexpr(OS::getType() == OSType::WINDOWS_NT) {
        switch(color) {
            case ConsoleColor::Default: 
                //! No default color yet
            break;
            case ConsoleColor::TextGray_BGBlue:
                SetConsoleTextAttribute(ConsoleUI::hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
            case ConsoleColor::TextBlack_BGWhite:
                SetConsoleTextAttribute(ConsoleUI::hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | 0);
            break;
            case ConsoleColor::RED:
                SetConsoleTextAttribute(ConsoleUI::hConsole, FOREGROUND_RED);
            break;
            case ConsoleColor::BLUE:
                SetConsoleTextAttribute(ConsoleUI::hConsole, FOREGROUND_BLUE);
            break;
        }
    }
    else if constexpr(OS::getType() == OSType::LINUX || OS::getType() == OSType::MAC_OS) {
        switch(color) {
            case ConsoleColor::Default: 
                //! No default color yet
            break;
            case ConsoleColor::TextGray_BGBlue:
                std::cout << "\033[38;5;15m\033[48;5;75m";    
            break;
            case ConsoleColor::TextBlack_BGWhite:
                std::cout << "\033[38;5;0m\033[48;5;15m";
            break;
            case ConsoleColor::RED:
                std::cout << "\033[1;31m";
            break;
            case ConsoleColor::BLUE:
                std::cout << "\033[1;34m";
            break;
        }
    }
}

void ConsoleUI::resetColor()
{
    if constexpr(OS::getType() == OSType::WINDOWS_NT) {
        SetConsoleTextAttribute(ConsoleUI::hConsole, ConsoleUI::saved_attributes);
    }
    else if constexpr(OS::getType() == OSType::LINUX || OS::getType() == OSType::MAC_OS) {
        std::cout << "\033[0m\n";
    }
}

void ConsoleUI::clearConsole()
{
    if constexpr(OS::getType() == OSType::WINDOWS_NT) {
        std::system("cls");
    }
    else if constexpr(OS::getType() == OSType::LINUX || OS::getType() == OSType::MAC_OS) {
        std::system("clear");
    }
}

//TODO: add Unix support
void ConsoleUI::setCursorPosition(short cx, short cy)
{
    COORD coord {cx, cy};
    SetConsoleCursorPosition(ConsoleUI::hConsole, coord);
}

int ConsoleUI::showMenu(int cx, int cy)
{
    const char *options[] = {
        "Start",
        "Options",
        "Exit"
    };
    std::size_t num_options = sizeof(options) / sizeof(options[0]);

    int highlight = 0;
    BOOL show_menu_flag = TRUE;
    char input;

    // Menu box dimensions
    int box_width = 30;
    int box_height = num_options * 2 + 2;
    
    ConsoleUI::drawBox(cx, cy, box_width, box_height);

    while (show_menu_flag) { 
        for (std::size_t i = 0; i < num_options; i++) {
            ConsoleUI::setCursorPosition(cx - box_width / 2 + 2, cy - num_options + i * 2);
            if (highlight == static_cast<int>(i)) {
                ConsoleUI::setColor(ConsoleColor::TextGray_BGBlue);
                printf(" > %-*s <", box_width - 8, options[i]);
                ConsoleUI::resetColor();
            } else {
                printf("   %-*s  ", box_width - 8, options[i]);
            }
        }
        //TODO: add console input support for Unix by creating an input class + branching code
        if (_kbhit()) {
            input = _getch();
            switch (input) {
                case ARROW_UP:
                    highlight = (highlight - 1 + num_options) % num_options;
                    break;
                case ARROW_DOWN:
                    highlight = (highlight + 1) % num_options;
                    break;
                case ENTER:
                    return highlight;
            }
        }

        Sleep(35); // small delay for smoother experience
    }
    return 0;
}
void ConsoleUI::drawBox(int posx, int posy, int box_width, int box_height)
{
    
    std::cout << "\033[38;5;75m";
    for (int y = 0; y <= box_height; y++) {
        for (int x = 0; x <= box_width; x++) {
            ConsoleUI::setCursorPosition(posx - box_width / 2 + x, posy - box_height / 2 + y);
            if (y == 0 && x == 0) std::cout << ("╔");
            else if (y == 0 && x == box_width) std::cout << ("╗");
            else if (y == box_height && x == 0) std::cout << ("╚");
            else if (y == box_height && x == box_width) std::cout << ("╝");
            else if (y == 0 || y == box_height) std::cout << ("═");
            else if (x == 0 || x == box_width) std::cout << ("║");
            else std::cout << (" ");
        }
    }
    ConsoleUI::resetColor();
}
