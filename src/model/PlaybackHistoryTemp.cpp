#include "../../include/model/PlaybackHistoryTemp.hpp"

using namespace std;

namespace MODEL {
PlaybackHistoryTemp::PlaybackHistoryTemp() {}

Song* PlaybackHistoryTemp::getSong() {
    if (historyTemp.empty()) return nullptr;
    Song* previous = new Song(historyTemp.top());
    historyTemp.pop();
    return previous;
}

void PlaybackHistoryTemp::addSong(const Song& song) { historyTemp.push(song); }
bool PlaybackHistoryTemp::isEmpty() { return historyTemp.empty(); }

PlaybackHistoryTemp::~PlaybackHistoryTemp() {
    while (!historyTemp.empty()) historyTemp.pop();
}
}  // namespace MODEL
