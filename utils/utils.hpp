#pragma once

#include "../include/global.h"
#include "../include/model/Song.hpp"

inline void trim(std::string&);
void separateData(std::string, Song&);
std::string formatTime(int);
void moveCursor(int, int);
void clearLine();
void clearScreen();