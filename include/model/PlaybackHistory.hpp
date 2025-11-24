#pragma once
#include "../global.hpp"
#include "Song.hpp"

namespace MODEL {
class PlaybackHistory {
   private:
    std::stack<Song> history;

   public:
    std::optional<Song> playPreviousSong();
};
}  // namespace MODEL