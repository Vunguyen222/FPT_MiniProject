#pragma once
#include "../global.h"
#include "MusicLibrary.hpp"
#include "PlaybackHistory.hpp"
#include "PlaybackHistoryTemp.hpp"
#include "PlaybackQueue.hpp"
#include "PlaynextQueue.hpp"
#include "ShuffleManager.hpp"
#include "Song.hpp"

namespace MODEL {
class MusicPlayer {
   private:
    std::unique_ptr<MODEL::PlaybackHistory> playbackHistory;
    std::unique_ptr<MODEL::PlaybackHistoryTemp> playbackHistoryTemp;
    std::unique_ptr<MODEL::PlaynextQueue> playnextQueue;
    std::unique_ptr<MODEL::ShuffleManager> shuffleManager;
    std::unique_ptr<MODEL::PlaybackQueue> playbackQueue;
    std::unique_ptr<MODEL::MusicLibrary> musicLibrary;

   public:
    MusicPlayer();

    /*================ MUSIC LIBRARY UTILS ==============*/
    void printMusicLibrarySongs();

    Song* getMusicLibrarySong(int);
    void addSongToMusicLibrary(const Song&);

    void printSongs(const std::vector<Song*>&);
    std::vector<Song*> findByArtist(const std::string&);

    std::vector<Song*> findByAlbum(const std::string&);

    /*================ PLAYBACK QUEUE UTILS ==============*/
    void addSongToPlayback(const Song&);
    // void printPlaybackQueue();

    /*================ MUSIC PLAYER UTILS ==============*/
    Song* getPreviousSong();
    void addSongToPlaybackHistory(const Song&);
    Song* getNextSong();
    void addSongToPlaybackHistoryTemp(const Song&);
};

}  // namespace MODEL