#pragma once
#include "../global.hpp"
#include "Song.hpp"

class PlaybackHistory {
   private:
    std::stack<Song> history;

   public:
    std::optional<Song> playPreviousSong();
};