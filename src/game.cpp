#include "console_ui.hpp"
#include "game.hpp"
#include <random>

void TicTacToe::play() {
    populateBoard();
    ConsoleUI::GameMenu(state, running);

    while(running) {
        displayBoard();
        makeMove();
        if(!isTie())
            AIMove();
        victory(); 
    }
}

inline void TicTacToe::setPlayed(int move) {
    alreadyPlayed.at(move) = 1;
}

void TicTacToe::displayBoard()
{
    //TODO : Make the board bigger and  center it
    std::system("cls");
    std::cout << TicTacToeTexts::tictactoeText << "\n";
    for(std::size_t i = 0 ; i < BOARD_SIZE ; i+=3 )
    {
        std::cout << "          ██          ██     " << '\n';
        std::cout << "          ██          ██     " << '\n';
        std::cout << "    " << board[i] << "     ██    " << board[i + 1] << "     ██    " << board[i + 2] << "  " << '\n';
        std::cout << "          ██          ██     " << '\n';
        std::cout << "          ██          ██     " << '\n';
        std::cout << ((i < 6) ? "▇▇▇▇▇▇▇▇▇▇██▇▇▇▇▇▇▇▇▇▇██▇▇▇▇▇▇▇▇▇▇" : "" ) << '\n';    
    }
}

inline void TicTacToe::populateBoard() {
    for(std::size_t i = 0 ; i < BOARD_SIZE ; i++) {
        board.at(i) = ' ';
    }
}

inline bool TicTacToe::isWinningLine(const char &a, const char &b, const char &c, const char &who)
{
    return a == who && b == who && c == who;
}

bool TicTacToe::isTie() {
    for(std::size_t i = 0 ; i < BOARD_SIZE ; i++) {
        if(board.at(i) == ' ') {
            return false;
        }
    }
    return true;
}

bool TicTacToe::checkWin() {
    for(std::size_t row = 0 ; row < BOARD_SIZE ; row+=3) {
        if(isWinningLine(board.at(row), board.at(row + 1), board.at(row + 2), player) 
        || isWinningLine(board.at(row), board.at(row + 1), board.at(row + 2), ai))
          {
            winner = board.at(row);
            return true;
          }
    }
    for(std::size_t col = 0 ; col < BOARD_SIZE / 3 ; col++) {
        if(isWinningLine(board.at(col), board.at(col + 3), board.at(col + 6), player) 
        || isWinningLine(board.at(col), board.at(col + 3), board.at(col + 6), ai))
          {
            winner = board.at(col);
            return true;
          }
    }
    if( isWinningLine(board.at(2), board.at(4), board.at(6), player) || 
        isWinningLine(board.at(2), board.at(4), board.at(6), ai)     ||
        isWinningLine(board.at(0), board.at(4), board.at(8), player) || 
        isWinningLine(board.at(0), board.at(4), board.at(8), ai))
        {
            winner = board.at(4); //? index 4 is the common of all
            return true;
        }
    return false;
}

void TicTacToe::makeMove()
{
    int move = 0;
    bool validMove = false;
    while(!validMove)
    {
        std::cout << "Enter a number to play (1-9) : ";
        std::cin >> move;

        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //! dont uderstand this yet
            std::cout << "Invalid input. ";
        } 
        else
        {            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            validMove = move > 0 && move < 10;
            if (!validMove) {
                std::cout << "Invalid move. Number must be between 1 and 9.\n";
            }
            else
            {
                if(alreadyPlayed.at(static_cast<std::size_t>(move - 1)) == 1)
                {
                    std::cout << "That tile was already played on chose another tile!" << "\n";
                    validMove = false;
                }
            }
        }
    }
    map_move(move);
    board.at(move) = player;
    setPlayed(move);
}

void TicTacToe::AIMove()
{
    int move = 0;
    //! It needs some training
    while(move == 0)
    {
        move = getRandMinMax(1, 9);
        if(alreadyPlayed.at(static_cast<std::size_t>(move - 1)) == 1)
        {
            move = 0;
        }
    }
    map_move(move);
    board.at(move) = ai;
    setPlayed(move);
}

void TicTacToe::victory()
{
    int msg_index = getRandMinMax(0, 4);

    if (checkWin())  
    {
        displayBoard();
        switch (winner)
        {
            case 'O': state = GAMESTATE::AI_WON; break;
            case 'X': state = GAMESTATE::PLAYER_WON; break;
        }

        if (state == GAMESTATE::PLAYER_WON)
        {
            std::cout << TicTacToeTexts::victoryText << "\n";
            std::cout << "\n" << TicTacToeTexts::playerWinMessages[msg_index] << "\n";
            running = false;
        }
        else if (state == GAMESTATE::AI_WON)
        {
            std::cout << TicTacToeTexts::gameOverText << "\n";
            std::cout << "\n" << TicTacToeTexts::aiWinMessages[msg_index] << "\n";
            running = false;
        }
    } else {
        if(isTie()) {
            state = GAMESTATE::TIE;
        }
    }
    
    if (state == GAMESTATE::TIE)
    {
        displayBoard();
        
        std::cout << TicTacToeTexts::tieText << "\n";
        std::cout << "\n" << TicTacToeTexts::tieMessages[msg_index] << "\n";
        running = false;
    }
}

inline int TicTacToe::getRandMinMax(int min, int max)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distr(min, max);

    return distr(eng);
}


