#include "arts.hpp"

const char* TicTacToeTexts::tictactoeText = R"(
    ██████╗ ██████╗ ███╗   ██╗███████╗ ██████╗ ██╗     ███████╗    ████████╗██╗ ██████╗████████╗ █████╗  ██████╗████████╗ ██████╗ ███████╗  
   ██╔════╝██╔═══██╗████╗  ██║██╔════╝██╔═══██╗██║     ██╔════╝    ╚══██╔══╝██║██╔════╝╚══██╔══╝██╔══██╗██╔════╝╚══██╔══╝██╔═══██╗██╔════╝
   ██║     ██║   ██║██╔██╗ ██║███████╗██║   ██║██║     █████╗         ██║   ██║██║        ██║   ███████║██║        ██║   ██║   ██║█████╗    
   ██║     ██║   ██║██║╚██╗██║╚════██║██║   ██║██║     ██╔══╝         ██║   ██║██║        ██║   ██╔══██║██║        ██║   ██║   ██║██╔══╝     
   ╚██████╗╚██████╔╝██║ ╚████║███████║╚██████╔╝███████╗███████╗       ██║   ██║╚██████╗   ██║   ██║  ██║╚██████╗   ██║   ╚██████╔╝███████╗  
    ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚══════╝╚══════╝       ╚═╝   ╚═╝ ╚═════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚══════╝  
   )";

const char* TicTacToeTexts::victoryText = R"(
▀████▀   ▀███▀████▀ ▄▄█▀▀▀█▄███▀▀██▀▀███ ▄▄█▀▀██▄ ▀███▀▀▀██▄ ▀███▀   ▀██▀
  ▀██     ▄█   ██ ▄██▀     ▀█▀   ██   ▀███▀    ▀██▄ ██   ▀██▄  ███   ▄█  
   ██▄   ▄█    ██ ██▀       ▀    ██    ██▀      ▀██ ██   ▄██    ███ ▄█   
    ██▄  █▀    ██ ██             ██    ██        ██ ███████      ████    
    ▀██ █▀     ██ ██▄            ██    ██▄      ▄██ ██  ██▄       ██     
     ▄██▄      ██ ▀██▄     ▄▀    ██    ▀██▄    ▄██▀ ██   ▀██▄     ██     
      ██     ▄████▄ ▀▀█████▀   ▄████▄    ▀▀████▀▀ ▄████▄ ▄███▄  ▄████▄   
    )";

const char* TicTacToeTexts::gameOverText = R"(
▀███▀   ▀██▀ ▄▄█▀▀██▄ ▀███▀   ▀███▀   ▀████▀     ▄▄█▀▀██▄  ▄█▀▀▀█▄███▀▀██▀▀███
  ███   ▄█ ▄██▀    ▀██▄██       █       ██     ▄██▀    ▀██▄██    ▀█▀   ██   ▀█
   ███ ▄█  ██▀      ▀████       █       ██     ██▀      ▀█████▄        ██     
    ████   ██        ████       █       ██     ██        ██ ▀█████▄    ██     
     ██    ██▄      ▄████       █       ██     ▄█▄      ▄██     ▀██    ██     
     ██    ▀██▄    ▄██▀██▄     ▄█       ██    ▄███▄    ▄██▀█     ██    ██     
   ▄████▄    ▀▀████▀▀   ▀██████▀▀     ██████████ ▀▀████▀▀ █▀█████▀   ▄████▄   
    )";

const char* TicTacToeTexts::tieText = R"(
 ______   __     __                ______       ________ ______ ________ 
|      \ |  \   |  \              /      \     |        \      \        \
 \▓▓▓▓▓▓_| ▓▓_  | ▓▓ _______     |  ▓▓▓▓▓▓\     \▓▓▓▓▓▓▓▓\▓▓▓▓▓▓ ▓▓▓▓▓▓▓▓
  | ▓▓ |   ▓▓ \  \▓ /       \    | ▓▓__| ▓▓       | ▓▓    | ▓▓ | ▓▓__    
  | ▓▓  \▓▓▓▓▓▓    |  ▓▓▓▓▓▓▓    | ▓▓    ▓▓       | ▓▓    | ▓▓ | ▓▓  \
  | ▓▓   | ▓▓ __    \▓▓    \     | ▓▓▓▓▓▓▓▓       | ▓▓    | ▓▓ | ▓▓▓▓▓   
 _| ▓▓_  | ▓▓|  \   _\▓▓▓▓▓▓\    | ▓▓  | ▓▓       | ▓▓   _| ▓▓_| ▓▓_____ 
|   ▓▓ \  \▓▓  ▓▓  |       ▓▓    | ▓▓  | ▓▓       | ▓▓  |   ▓▓ \ ▓▓     \
 \▓▓▓▓▓▓   \▓▓▓▓    \▓▓▓▓▓▓▓      \▓▓   \▓▓        \▓▓   \▓▓▓▓▓▓\▓▓▓▓▓▓▓▓
    )";
   

    const std::string TicTacToeTexts::playerWinMessages[] = {
        "Congratulations! You've outsmarted the AI with a brilliant move!",
        "You did it! You've won the game! Great job!",
        "Victory is yours! You’ve successfully lined up three in a row!",
        "Well played! You've triumphed over the challenge!",
        "Amazing! You’ve won against the AI!"
    };

    const std::string TicTacToeTexts::aiWinMessages[] = {
        "The AI has defeated you this time. Better luck next game!",
        "Oops! The AI made a clever move and claimed victory!",
        "The challenge was too tough this time. The AI is the winner!",
        "The AI has outplayed you! Don't worry; you can always try again!",
        "The AI stands victorious this time!"
    };

    const std::string TicTacToeTexts::tieMessages[] = {
        "It's a tie! No one wins this time, but great effort from both sides!",
        "Well played! The game ends in a draw. Neither player can claim victory.",
        "It’s a stalemate! Both you and the AI played to perfection.",
        "The game is a tie! Neither side could break the deadlock.",
        "What a thrilling match! The result is a tie!"
    };