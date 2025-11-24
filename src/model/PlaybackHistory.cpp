#include "../../include/model/PlaybackHistory.hpp"

using namespace std;

optional<Song> PlaybackHistory::playPreviousSong() {
    if (history.empty()) return nullopt;
    Song previous = history.top();
    history.pop();
    return previous;
}
