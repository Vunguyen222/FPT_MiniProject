#pragma once
#include "../global.h"

struct Song {
    int id;
    std::string title;
    std::string artist;
    std::string album;
    int duration;
    
    Song()
        : id(0), duration(0) {}   
};