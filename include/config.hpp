#pragma once
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>
#endif
#include <type_traits>
#include <iostream>
#include "arts.hpp"

#define ARROW_UP (((DWORD)(0x8)<<3)|((0x32)>>2&(~0x4))) 
#define ARROW_DOWN (((0x8)<<3)|((DWORD)(0x32)>>1&(~(0x8 | 0x1))))
#define ENTER (((DWORD)0xF0>>4&(~(0x2))))

#define START 0 
#define OPTIONS 1 
#define EXIT 2

#define BOARD_SIZE 9

inline void map_move(int &move) {
    if( move >= 1 && move <= 9) {
        move -= 1;
    }
}

enum class GAMESTATE {
    MENU,
    PLAYING,
    AI_WON,
    PLAYER_WON,
    PLAYER_2_WON,
    TIE,
};

enum class OSType {
    WINDOWS_NT,
    LINUX,
    MAC_OS,
};

#ifdef _WIN32
    static constexpr OSType os = OSType::WINDOWS_NT;
#elif __linux__
    static constexpr OSType os = OSType::LINUX;
#elif __APPLE__
    static constexpr OSType os = OSType::MAC_OS;
#endif

struct OS {
    static constexpr inline OSType getType() {
        return os; 
    }
};

inline std::string OSTypeToString(OSType os) {
    switch(os) {
        case OSType::WINDOWS_NT: return "WINDOWS_NT";
        case OSType::LINUX: return "LINUX";
        case OSType::MAC_OS: return "MAC_OS";
        default: return "UNKNOWN";
    }
}
