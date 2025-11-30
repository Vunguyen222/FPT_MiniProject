#pragma once
#include "../global.h"
#include "Song.hpp"

namespace MODEL {
class PlaybackHistoryTemp {
   private:
    std::stack<Song> historyTemp;

   public:
    PlaybackHistoryTemp();

    Song* getSong();
    void addSong(const Song&);
    bool isEmpty();

    ~PlaybackHistoryTemp();
};
}  // namespace MODEL