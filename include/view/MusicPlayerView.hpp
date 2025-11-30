#pragma once
#include "../global.h"

namespace VIEW {
class MusicPlayerView {
   private:
   public:
    void displayMainDashboard();

    // Music Library Function
    void displayMusicLibraryMenu();
    void displayAddSongMusicLibrary();
    void displayFindSongByArtist();
    void displayFindSongByAlbum();

    // Add Song to PlaybackQueue
    void displayAddSongsInstruction();

    // Music Player Menu
    void displayMusicPlayerMenu();
};
}  // namespace VIEW