#pragma once
#include "../global.h"
#include "Song.hpp"

namespace MODEL {
class PlaynextQueue {
   private:
    std::queue<Song> playnextQueue;

   public:
    PlaynextQueue();

    void addSong(const Song&);
    Song* getNextSong();
    bool isEmpty();

    ~PlaynextQueue();
};

}  // namespace MODEL