#pragma once
#include <string>

struct TicTacToeTexts final {
    static const char* tictactoeText;
    static const char* victoryText;
    static const char* gameOverText;
    static const char* tieText;

    static const std::string playerWinMessages[];
    static const std::string aiWinMessages[];
    static const std::string tieMessages[];
};