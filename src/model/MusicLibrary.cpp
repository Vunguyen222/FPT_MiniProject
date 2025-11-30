#include "../../include/model/MusicLibrary.hpp"
using json = nlohmann::json;
using namespace std;
namespace MODEL {
MusicLibrary::MusicLibrary() : maxSize(1000), jsonPath("../include/music_library.json"), nextID(0) {
    songs.reserve(maxSize);
    loadFromJsonFile(jsonPath);

    for (auto& s : songs) {
        if (s.id >= nextID) {
            nextID = s.id + 1;
        }
    }
}

void MusicLibrary::addSong(const Song& songInput) {
    Song song = songInput;

    // User did not enter ID
    if (song.id == 0) {
        song.id = nextID++;
    }

    // Check for duplicate IDs
    if (songIndexByID.find(song.id) != songIndexByID.end()) {
        std::cout << "[MusicLibrary] ID \"" << song.id << "\" da ton tai. Khong them.\n";
        return;
    }

    // Check for duplicate Titles
    if (songIndexByTitle.find(song.title) != songIndexByTitle.end()) {
        std::cout << "[MusicLibrary] Title \"" << song.title << "\" da ton tai. Khong them.\n";
        return;
    }

    songs.push_back(song);

    // Get the address of the element just pushed
    Song* ptr = &songs.back();
    // update index
    songIndexByID[song.id] = ptr;
    songIndexByTitle[song.title] = ptr;
    artistIndex[song.artist].push_back(ptr);
    albumIndex[song.album].push_back(ptr);
}

const std::vector<Song>& MusicLibrary::getAllSongs() const { return songs; }

// ========== Search for information==================
/*
- findByID / findByTitle: use a map to search in O(1)/O(logN), return a Song* or nullptr.
- findByArtist / findByAlbum:
        + Because one artist/album can have many songs -> the value type is vector<Song*>.
        + If nothing is found → return an empty vector {}.
*/
Song* MusicLibrary::findByID(int songId) {
    auto it = songIndexByID.find(songId);
    if (it != songIndexByID.end()) {
        return it->second;
    }
    return nullptr;
}

Song* MusicLibrary::findByTitle(const string& title) {
    auto it = songIndexByTitle.find(title);
    if (it != songIndexByTitle.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<Song*> MusicLibrary::findByArtist(const string& artist) {
    auto it = artistIndex.find(artist);
    if (it != artistIndex.end()) {
        return it->second;
    }
    return {};
}

std::vector<Song*> MusicLibrary::findByAlbum(const std::string& albumName) const {
    auto it = albumIndex.find(albumName);
    if (it != albumIndex.end()) {
        return it->second;
    }
    return {};
}

// ===========================End Search for information=================================

/**
         ==================================Load from JSON=========================================
         * Workflow
         * 1. Open the JSON file - if it fails -> return false.
         * 2. Parse using nlohmann::json - if the format is invalid -> catch exception and return
   false.
         * 3. Check whether the "songs" field exists and is an array.
         * 4. Clear old data (vector + index).
         * 5. Iterate over each element inside "songs":
         *    - Skip entries that are missing required fields.
         *    - Convert the JSON entry into a Song struct.
         *    - Call addSong(s) to insert the song and update indexing.
         * 6. Log the operation and return true if there is at least one song.
 */

bool MusicLibrary::loadFromJsonFile(const string& filePath) {
    ifstream ifs;
    ifs.open(filePath);
    if (!ifs) {
        cerr << "[MusicLibrary] Error: cannot opne JSON file: " << filePath << "\n";
        return false;
    }

    json j;
    try {
        ifs >> j;
    } catch (const exception& e) {
        cerr << "[MusicLibrary] Error: invalid JSON: " << e.what() << "\n";
        return false;
    }
    if (!j.contains("songs") || !j["songs"].is_array()) {
        std::cerr << "[MusicLibrary] Error: JSON does not contain 'songs' array\n";
        return false;
    }

    songs.clear();
    songIndexByID.clear();
    songIndexByTitle.clear();
    artistIndex.clear();
    albumIndex.clear();

    for (const auto& item : j["songs"]) {
        if (!item.contains("id") || !item.contains("title") || !item.contains("artist") ||
            !item.contains("album") || !item.contains("duration")) {
            continue;
        }

        Song s;
        s.id = item["id"].get<int>();
        s.title = item["title"].get<std::string>();
        s.artist = item["artist"].get<std::string>();
        s.album = item["album"].get<std::string>();
        s.duration = item["duration"].get<int>();
        addSong(s);
    }

    std::cout << "                  [MusicLibrary] Loaded " << songs.size() << " songs from "
              << filePath << "\n\n";
    return !songs.empty();
}

/**
 * ================================Save to JSON file======================================
 * - Create a new JSON object and rebuild the "songs" array from the songs vector.
 *
 * - Open the output file and write the JSON.
 *
 * - If opening or writing fails → return false.
 *    Check if the file stream is valid before writing; if any error occurs,
 *    report failure by returning false from the function.
 */

bool MusicLibrary::savetoJsonFile(const std::string& filePath) const {
    json j;
    j["songs"] = json::array();
    for (const auto& s : songs) {
        json item;
        item["id"] = s.id;
        item["title"] = s.title;
        item["artist"] = s.artist;
        item["album"] = s.album;
        item["duration"] = s.duration;
        j["songs"].push_back(item);
    }

    ofstream ofs;
    ofs.open(filePath);
    if (!ofs) {
        cerr << "[MusicLibrary] Error: cannot open JSON file for writing: " << filePath << "\n";
        return false;
    }
    ofs << setw(4) << j;
    if (!ofs.good()) {
        cerr << "[MusicLibrary] Error: write JSON failed \n ";
        return false;
    }
    return true;
}

/**
 * ================================ Add song from user and save===========================
 * - Check for duplicate titles.
 * - If everything is OK → call addSong.
 * - Then call savetoJsonFile(jsonPath) to overwrite the original JSON file.
 * - Return true/false depending on the result.
 *    If saving to JSON (or adding) fails -> return false; otherwise return true.
 */
bool MusicLibrary::addSongFromUserAndSave(const Song& newSong) {
    if (findByTitle(newSong.title) != nullptr) {
        cout << "[Error] Title " << newSong.title << " da ton tai trong thu vien.\n";
        return false;
    }

    addSong(newSong);
    if (!savetoJsonFile(jsonPath)) {
        cerr << "[MusicLibrary] Error: cannot save JSON file after adding song\n";
        return false;
    }
    cout << "Da them bai hat moi va luu vao file: " << jsonPath << "\n";
    return true;
}

/**
 *  =================================Print table======================================
 * - printSongTableHeader: print the header row (ID, Title, Artist, Album) and use setw to align
 * columns.
 * - printSongInfo: print a single song using the same format as the header.
 * - printAllSongs: print the header, then loop with for over the entire songs vector
 *   to print each song.
 */

void MusicLibrary::printSongTableHeader() const {
    using std::left;
    using std::setw;
    cout << left << setw(5) << "ID"
         << " | " << setw(30) << "Title"
         << " | " << setw(35) << "Artist"
         << " | " << setw(20) << "Album" << '\n';
    cout << "--------------------------------------------------------------------------------------"
            "---------------"
         << '\n';
}
void MusicLibrary::printSongInfo(const Song& s) const {
    using std::left;
    using std::setw;
    cout << left << setw(5) << s.id << " | " << setw(30) << s.title << " | " << setw(35) << s.artist
         << " | " << setw(20) << s.album << '\n';
}

void MusicLibrary::printAllSongs() {
    printSongTableHeader();
    const auto& all = getAllSongs();
    for (const auto& song : all) {
        printSongInfo(song);
    }
}

//  =================================End print table======================================

void MusicLibrary::printSongsByPage(int page, const int pageSize) const {
    const auto& all = getAllSongs();
    int total = all.size();
    if (total == 0) {
        std::cout << "Thu vien khong co bai hat nao.\n";
        return;
    }
    int totalPages = (total + pageSize - 1) / pageSize;
    if (page < 1 || page > totalPages) {
        std::cout << "Page khong hop le. Chi co " << totalPages << " trang.\n";
        return;
    }

    int startIndex = (page - 1) * pageSize;
    int endIndex = std::min(startIndex + pageSize, total);
    std::cout << "\n===== Page " << page << " / " << totalPages << " =====\n";
    printSongTableHeader();
    for (int i = startIndex; i < endIndex; ++i) {
        printSongInfo(all[i]);
    }
}

}  // namespace MODEL
