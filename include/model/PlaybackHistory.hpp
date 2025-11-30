#pragma once
#include "../global.h"
#include "Song.hpp"

namespace MODEL {
class PlaybackHistory {
   private:
    std::stack<Song> history;
    int capacity;
    void cleanHistory();

   public:
    PlaybackHistory();
    PlaybackHistory(int);

    Song* getPreviousSong();
    void addSong(const Song&);

    bool isFull();
    bool isEmpty();
    ~PlaybackHistory();
};
}  // namespace MODEL