#pragma once
#include "config.hpp"
#include <vector>
#include <array>
#include <limits>

class TicTacToe {
    private:
        GAMESTATE state = GAMESTATE::MENU;
        const char player = 'X';
        const char ai = 'O';
        std::array<char, BOARD_SIZE> board;
        std::array<int, BOARD_SIZE> alreadyPlayed;
        bool running = true;
        char winner = ' ';

    public:
        TicTacToe() {
            SetConsoleOutputCP(CP_UTF8);
            alreadyPlayed.fill(0);
         }
        ~TicTacToe() { }

    public:
        void play();

    private:
        bool isTie();
        bool checkWin();
        void makeMove();
        void AIMove();
        void victory();
        void displayBoard();
        inline void populateBoard();
        inline void setPlayed(int move);
        inline int getRandMinMax(int min, int max);
        static inline bool isWinningLine(const char& a, const char& b, const char& c, const char& who);
};