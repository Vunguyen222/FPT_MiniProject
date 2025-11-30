#include "../../include/model/MusicPlayer.hpp"

using namespace std;

namespace MODEL {
MusicPlayer::MusicPlayer() {
    playbackHistory = make_unique<PlaybackHistory>();
    playbackHistoryTemp = make_unique<PlaybackHistoryTemp>();
    playnextQueue = make_unique<PlaynextQueue>();
    playbackQueue = make_unique<PlaybackQueue>();
    shuffleManager = make_unique<ShuffleManager>();
    musicLibrary = make_unique<MusicLibrary>();
}

/*================ MUSIC LIBRARY UTILS ==============*/
void MusicPlayer::printMusicLibrarySongs() {
    // musicLibrary -> printSongsByPage()
    musicLibrary->printAllSongs();
}

Song* MusicPlayer::getMusicLibrarySong(int id) { return musicLibrary->findByID(id); }

void MusicPlayer::addSongToMusicLibrary(const Song& song) {
    musicLibrary->addSongFromUserAndSave(song);
}

void MusicPlayer::printSongs(const vector<Song*>& songs) {
    musicLibrary->printSongTableHeader();
    for (const auto& song : songs) {
        musicLibrary->printSongInfo(*song);
    }
}

vector<Song*> MusicPlayer::findByArtist(const string& artist) {
    return musicLibrary->findByArtist(artist);
}

vector<Song*> MusicPlayer::findByAlbum(const string& album) {
    return musicLibrary->findByAlbum(album);
}

/*================ PLAYBACK QUEUE UTILS ==============*/
void MusicPlayer::addSongToPlayback(const Song& song) { playbackQueue->addSong(song); }

// void MusicPlayer::printPlaybackQueue() {
//     for (const auto& i : playbackQueue->queue_) {
//         cout << i.title << endl;
//     }
// }

/*================ MUSIC PLAYER UTILS ==============*/
Song* MusicPlayer::getPreviousSong() { return playbackHistory->getPreviousSong(); }

void MusicPlayer::addSongToPlaybackHistory(const Song& song) {
    return playbackHistory->addSong(song);
}

Song* MusicPlayer::getNextSong() {
    if (!playbackHistoryTemp->isEmpty()) {
        return playbackHistoryTemp->getSong();
    }

    if (!playnextQueue->isEmpty()) {
        return playnextQueue->getNextSong();
    }

    return playbackQueue->playNext();
}

void MusicPlayer::addSongToPlaybackHistoryTemp(const Song& song) {
    playbackHistoryTemp->addSong(song);
}

}  // namespace MODEL