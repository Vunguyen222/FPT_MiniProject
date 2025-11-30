#include "../../include/controller/MusicPlayerController.hpp"

using namespace std;

namespace CONTROLLER {
MusicPlayerController::MusicPlayerController(
    unique_ptr<MODEL::MusicPlayer> model,
    unique_ptr<VIEW::MusicPlayerView> view)
    : musicPlayerView(move(view)),
      musicPlayerModel(move(model)),
      currentSong(nullptr),
      userCommand(NONE) {}

MusicPlayerController::MusicPlayerController()
    : musicPlayerView(nullptr),
      musicPlayerModel(nullptr),
      currentSong(nullptr),
      userCommand(NONE) {}

/*================================ HELPER FUNC
 * =================================*/

/*============================= MUSIC LIBRARY FUNC
 * ===============================*/

void MusicPlayerController::addSongToMusicLibrary() {
    // present view of add song
    clearScreen();
    musicPlayerView->displayAddSongMusicLibrary();

    // get and handle user input
    string strTemplate;
    Song newSong;
    cin.ignore();

    while (getline(cin, strTemplate)) {
        if (strTemplate == "q") break;

        // separate data
        separateData(strTemplate, newSong);

        // add song to music lib
        musicPlayerModel->addSongToMusicLibrary(newSong);
    }
}

void MusicPlayerController::findSongByArtist() {
    cin.ignore();
    while (true) {
        clearScreen();
        musicPlayerView->displayFindSongByArtist();

        string artist;
        getline(cin, artist);

        if (artist == "0") {
            break;
        }

        vector<Song*> songs = musicPlayerModel->findByArtist(artist);
        musicPlayerModel->printSongs(songs);

        cout << "\nDo you want to add songs to the Playback Queue [y/n]: ";
        char option;
        cin >> option;
        if (option == 'y') {
            for (const auto& song : songs) {
                musicPlayerModel->addSongToPlayback(*song);
            }
            cout << "Adding songs to Playback Queue successfully\n";
        }
        cin.ignore();
        system("pause");
    }
}

void MusicPlayerController::findSongByAlbum() {
    cin.ignore();
    while (true) {
        clearScreen();
        musicPlayerView->displayFindSongByAlbum();

        string album;
        getline(cin, album);

        if (album == "0") {
            break;
        }

        vector<Song*> songs = musicPlayerModel->findByArtist(album);
        musicPlayerModel->printSongs(songs);

        cout << "\nDo you want to add songs to the Playback Queue [y/n]: ";
        char option;
        cin >> option;
        if (option == 'y') {
            for (const auto& song : songs) {
                musicPlayerModel->addSongToPlayback(*song);
            }
            cout << "Adding songs to Playback Queue successfully\n";
        }
        cin.ignore();
        system("pause");
    }
}

void MusicPlayerController::musicLibraryFunction() {
    int choice;
    while (true) {
        clearScreen();
        musicPlayerView->displayMusicLibraryMenu();
        cin >> choice;
        switch (choice) {
            case 0:
                return;
            case 1:
                addSongToMusicLibrary();
                break;

            case 2:
                findSongByArtist();
                break;

            case 3:
                findSongByAlbum();
                break;

            default:

                break;
        }

        system("pause");
    }
}

/*============================================================================*/

/*============================== ADD SONG TO PLAYBACK QUEUE
 * ====================*/

vector<int> MusicPlayerController::handleSongIDString() {
    string line;
    cin.ignore();
    getline(cin, line);

    int start = 0;
    size_t pos = 0;

    vector<int> result;
    do {
        pos = line.find(',', start);
        string substr = (pos != string::npos) ? line.substr(start, pos - start)
                                              : line.substr(start);

        bool isFirstNum = true;
        int firstNum = 0;
        int secondNum = 0;
        // handle substr
        for (size_t i = 0; i < substr.length(); i++) {
            if (substr[i] == ' ') continue;

            if (substr[i] == '-') {
                isFirstNum = false;
                continue;
            }

            if (isdigit(substr[i])) {
                firstNum =
                    (isFirstNum) ? firstNum * 10 + (substr[i] - '0') : firstNum;
                secondNum = (!isFirstNum) ? secondNum * 10 + (substr[i] - '0')
                                          : secondNum;
            }
        }
        // cout << firstNum << " " << secondNum << endl;
        // system("pause");
        if ((firstNum > secondNum) && (secondNum != 0))
            swap(firstNum, secondNum);

        if (secondNum) {
            for (auto i = firstNum; i <= secondNum; i++) result.push_back(i);
        } else
            result.push_back(firstNum);

        start = pos + 1;
    } while (pos != string::npos);

    sort(result.begin(), result.end());
    return result;
}

void MusicPlayerController::addSongToPlaybackQueue() {
    // clear screen
    clearScreen();

    // print music lib songs
    musicPlayerModel->printMusicLibrarySongs();

    // print add song instructions
    musicPlayerView->displayAddSongsInstruction();

    // handle user input
    vector<int> songIDs = handleSongIDString();

    // get song from music lib and add to playback queue
    for (const auto& id : songIDs) {
        musicPlayerModel->addSongToPlayback(
            *(musicPlayerModel->getMusicLibrarySong(id)));
    }

    cout << "Add Song To Playback Queue succesffuly !\n";
}

/*===============================================================================*/
/*=============================== MUSIC PLAYER MENU
 * ========================================*/
void MusicPlayerController::playSong() {
    if (currentSong == nullptr) return;
    cout << currentSong->title << " " << currentSong->artist;

    string songTime = formatTime(currentSong->duration);
    for (int currentSecond = 0; currentSecond <= currentSong->duration;
         currentSecond += 5) {
        std::cout << currentSecond << " / " << songTime << "\r";
        std::cout.flush();
        // (pauseSong) ? sleep(INT32_MAX) : sleep(1);
        this_thread::sleep_for(chrono::seconds(1));
    }

    // playNextSong();
}

void MusicPlayerController::loadNextSong() {
    if (currentSong != nullptr) {
        // put current Song to PlaybackHistory
        musicPlayerModel->addSongToPlaybackHistory(*(currentSong));

        // free Song resource
        delete currentSong;
        currentSong = nullptr;
    }

    // Get new Song from playback | Next Queue | History Temp
    currentSong = musicPlayerModel->getNextSong();
    if (currentSong == nullptr) {
        cout << "No more history song to display\n";
        cout << "Please add song to Playback Queue\n";
    }
}

void MusicPlayerController::loadPreviousSong() {
    if (currentSong != nullptr) {
        // store current song to historyTemp stack
        musicPlayerModel->addSongToPlaybackHistoryTemp(*(currentSong));

        // free Song resource
        delete currentSong;
        currentSong = nullptr;
    }

    // get song from history stack
    currentSong = musicPlayerModel->getPreviousSong();
    if (currentSong == nullptr) {
        cout << "Playlist has no song\n";
    }
}

void MusicPlayerController::controlLoop() {
    while (true) {
        char key = _getch();
        if (key == 'd')
            userCommand = NEXT;
        else if (key == 'a')
            userCommand = PREVIOUS;
        else if (key == ' ')
            userCommand = (userCommand == PAUSE ? NONE : PAUSE);
        else if (key == 'n') {
        } else if (key == 'p') {
        } else if (key == 'e') {
            userCommand = EXIT;
            break;
        }
    }
}

void MusicPlayerController::playSongLoop() {
    loadNextSong();
    while (true) {
        if (currentSong == nullptr) {
            return;
        }

        if (userCommand == EXIT) break;

        moveCursor(10, 1);
        clearLine();
        cout << currentSong->title << " - " << currentSong->artist << endl;
        clearLine();

        string songTime = formatTime(currentSong->duration);
        for (int currentSecond = 0; currentSecond <= currentSong->duration;
             currentSecond += 5) {
            if (userCommand == NEXT || userCommand == PREVIOUS) {
                break;
            }

            if (userCommand == EXIT) return;

            if (userCommand == PAUSE) {
                while (userCommand == PAUSE) {
                    this_thread::sleep_for(chrono::milliseconds(100));
                }
            }
            cout << formatTime(currentSecond) << " / " << songTime << "\r";
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(500));
        }

        if (userCommand == NEXT) {
            loadNextSong();
            userCommand = NONE;
            continue;
        }

        if (userCommand == PREVIOUS) {
            userCommand = NONE;
            loadPreviousSong();
            continue;
        }
        loadNextSong();
    }
}

void MusicPlayerController::musicPlayerMenu() {
    clearScreen();
    // present view
    musicPlayerView->displayMusicPlayerMenu();

    system("pause");

    thread t1(&MusicPlayerController::controlLoop, this);
    thread t2(&MusicPlayerController::playSongLoop, this);

    t1.join();
    t2.join();
}

/*===============================================================================*/

/*============================== MAIN FUNC
 * ====================================*/
void MusicPlayerController::run() {
    int choice;
    while (true) {
        clearScreen();
        musicPlayerView->displayMainDashboard();
        cin >> choice;
        switch (choice) {
            case 0:
                return;
            case 1:
                musicLibraryFunction();
                break;
            case 2:
                addSongToPlaybackQueue();
                break;
            case 3:
                musicPlayerMenu();
                break;
            case 4:
                break;

            default:
                break;
        }
        system("pause");
    }
}

}  // namespace CONTROLLER