#include "../../include/model/PlaynextQueue.hpp"

namespace MODEL {
PlaynextQueue::PlaynextQueue() {}

void PlaynextQueue::addSong(const Song& nextSong) { playnextQueue.push(nextSong); }
Song* PlaynextQueue::getNextSong() {
    if (playnextQueue.empty()) return nullptr;

    Song* nextSong = new Song(playnextQueue.front());
    playnextQueue.pop();
    return nextSong;
}

bool PlaynextQueue::isEmpty() { return playnextQueue.empty(); }

PlaynextQueue::~PlaynextQueue() {
    while (!playnextQueue.empty()) {
        playnextQueue.pop();
    }
}
}  // namespace MODEL