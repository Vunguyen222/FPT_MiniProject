#pragma once
#include "../../utils/utils.hpp"
#include "../global.h"
#include "../model/MusicPlayer.hpp"
#include "../view/MusicPlayerView.hpp"

namespace CONTROLLER {
class MusicPlayerController {
   private:
    std::unique_ptr<MODEL::MusicPlayer> musicPlayerModel;
    std::unique_ptr<VIEW::MusicPlayerView> musicPlayerView;
    Song* currentSong;

    enum Command { NONE, NEXT, PREVIOUS, PAUSE, EXIT };
    std::atomic<Command> userCommand;

   public:
    MusicPlayerController(std::unique_ptr<MODEL::MusicPlayer>,
                          std::unique_ptr<VIEW::MusicPlayerView>);
    MusicPlayerController();

    /*================= MAIN FUNCTION =================*/
    void run();

    /*================= HELPER FUNCTION =================*/
    /*================= MUSIC LIBRARY FUNC =================*/
    void addSongToMusicLibrary();
    void findSongByID();
    void findSongByArtist();
    void findSongByAlbum();

    void musicLibraryFunction();

    /*================= ADD SONG TO PLAYBACK QUEUE =================*/
    std::vector<int> handleSongIDString();
    void addSongToPlaybackQueue();

    /*================== MUSICPLAYER MENU ===================*/
    void playSong();
    void loadNextSong();
    void loadPreviousSong();

    void controlLoop();
    void playSongLoop();
    void musicPlayerMenu();
};
}  // namespace CONTROLLER