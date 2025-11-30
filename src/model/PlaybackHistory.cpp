#include "../../include/model/PlaybackHistory.hpp"

using namespace std;

#define MAX_HISTORY_SONG 100

namespace MODEL {
/** @in : history stack
 * @out : history stack with 1/4 size of stack remaining
 * use : use to reduce Song inside stack when history full capacity.
 */
void PlaybackHistory::cleanHistory() {
    if (!isFull()) {
        cout << "Can't clean history cause it is not full yet\n";
        return;
    }

    int remainingSong = history.size() / 4;

    // hold remaining songs to temporary stack
    stack<Song> tempHolder;
    while (remainingSong--) {
        tempHolder.push(history.top());
        history.pop();
    }

    // clear 3/4 old songs from history
    while (!history.empty()) {
        history.pop();
    }

    // restore remaining songs to history
    while (!tempHolder.empty()) {
        history.push(tempHolder.top());
        tempHolder.pop();
    }
}

PlaybackHistory::PlaybackHistory() : capacity(MAX_HISTORY_SONG) {}

PlaybackHistory::PlaybackHistory(int capacity) : capacity(capacity) {}

Song* PlaybackHistory::getPreviousSong() {
    if (history.empty()) return nullptr;
    Song* previous = new Song(history.top());
    history.pop();
    return previous;
}

void PlaybackHistory::addSong(const Song& song) {
    if (isFull()) {
        cleanHistory();
    }

    history.push(song);
}

bool PlaybackHistory::isFull() { return history.size() == capacity; }
bool PlaybackHistory::isEmpty() { return history.empty(); }

PlaybackHistory::~PlaybackHistory() {
    capacity = 0;
    while (!history.empty()) history.pop();
}
}  // namespace MODEL
