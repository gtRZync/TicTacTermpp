#include "console_ui.hpp"

const HANDLE ConsoleUI::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void ConsoleUI::GameMenu(GAMESTATE &state, bool& isRunning)
 {
    ConsoleUI::clearConsole();
    int flag = -1;
    hide_cursor();
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
                show_cursor();
                isRunning = false;
            }break;
        }
    }
}

void ConsoleUI::setMenuColors(WORD flag)
{
    SetConsoleTextAttribute(ConsoleUI::hConsole, flag);
}

void ConsoleUI::getConsoleMetrics(int &width, int &height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;  
    if(GetConsoleScreenBufferInfo(ConsoleUI::hConsole, &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left - 1; 
        height = csbi.srWindow.Bottom - csbi.srWindow.Top - 1; 
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
    
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(ConsoleUI::hConsole, &csbi);
    WORD saved_attributes = csbi.wAttributes;

    int highlight = 0;
    BOOL show_menu_flag = TRUE;
    char input;

    // Menu box dimensions
    int box_width = 30;
    int box_height = num_options * 2 + 2;

    // Draw frame once
    for (int y = 0; y <= box_height; y++) {
        for (int x = 0; x <= box_width; x++) {
            setCursorPosition(cx - box_width / 2 + x, cy - box_height / 2 + y);
            if (y == 0 && x == 0) printf("╔");
            else if (y == 0 && x == box_width) printf("╗");
            else if (y == box_height && x == 0) printf("╚");
            else if (y == box_height && x == box_width) printf("╝");
            else if (y == 0 || y == box_height) printf("═");
            else if (x == 0 || x == box_width) printf("║");
            else printf(" ");
        }
    }

    while (show_menu_flag) {
        for (std::size_t i = 0; i < num_options; i++) {
            setCursorPosition(cx - box_width / 2 + 2, cy - num_options + i * 2);
            if (highlight == static_cast<int>(i)) {
                setMenuColors(flags);
                printf(" > %-*s <", box_width - 6, options[i]);
                setMenuColors(saved_attributes);
            } else {
                printf("   %-*s  ", box_width - 6, options[i]);
            }
        }

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