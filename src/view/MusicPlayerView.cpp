#include "../../include/view/MusicPlayerView.hpp"

using namespace std;

namespace VIEW {
void MusicPlayerView::displayMainDashboard() {
    cout << "============= MAIN DASHBOARD ===============\n";
    cout << "0. Exit\n";
    cout << "1. Music Library Function\n";
    cout << "2. Add Song To Playback Queue\n";
    cout << "3. Music Player Menu\n";
    // cout << "4. Select And Play Song Immediately\n";
    cout << "Your choice : ";
}

void MusicPlayerView::displayMusicLibraryMenu() {
    cout << "\n====================== MUSIC LIBRARY MENU =======================\n";
    cout << "0. Exit\n";
    cout << "1. Add Song\n";
    cout << "2. Find By Artist\n";
    cout << "3. Find By Album\n";
    cout << "4. Print Library Songs\n";
    cout << "---> Your choice: ";
}

void MusicPlayerView::displayAddSongMusicLibrary() {
    cout << "======================= ADD SONG ======================\n";
    cout << "1. Please add song with following Template: Title - Artist - Album - Duration\n";
    cout << "2. Press q then enter to quit and save\n";
    cout << "Your song: \n";
}

void MusicPlayerView::displayFindSongByArtist() {
    cout << "======================= FIND SONG BY ARTIST ======================\n";
    cout << "Press 0 to exit\n";
    cout << "Enter your artist: ";
}

void MusicPlayerView::displayFindSongByAlbum() {
    cout << "======================= FIND SONG BY ALBUM ======================\n";
    cout << "Press 0 to exit\n";
    cout << "Enter your album: ";
}

void MusicPlayerView::displayAddSongsInstruction() {
    cout << "\n====================== GET SONG INSTRUCTION =======================\n";
    cout << "Please choose your song to put in Playback Queue\n";
    cout << "id_of_songA - id_of_songB: get from song A to song B\n";
    cout << "id_of_songA, id_of_songB: get song A and song B\n";
    cout << "---> Your songs: ";
}

void MusicPlayerView::displayMusicPlayerMenu() {
    cout << "================ MUSIC PLAYER MENU ================\n";
    cout << "[A] Play Previous Song (Playback)\n";
    cout << "[D] Play Next Song (Playnext)\n";
    cout << "[Space] Pause Current Song\n";
    cout << "[N] Choose Next Song\n";
    cout << "[P] Choose and Play Song Immediately\n";
    cout << "[E] Exit\n";
}
}  // namespace VIEW