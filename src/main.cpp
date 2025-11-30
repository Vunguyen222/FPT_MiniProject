#include "../include/controller/MusicPlayerController.hpp"
#include "../include/global.h"
#include "../include/model/MusicPlayer.hpp"
#include "../include/model/Song.hpp"
#include "../include/view/MusicPlayerView.hpp"
// #include "include/model/MusicLibrary.hpp"
// #include "include/model/PlaybackQueue.hpp"

using namespace std;
int main() {
    //    // 1. Khởi tạo thư viện nhạc
    //    MusicLibrary library;
    //    library.addSong({1, "Shape of You", "Ed Sheeran", "Divide", 240});
    //    library.addSong({2, "Perfect",      "Ed Sheeran", "Divide", 263});
    //    library.addSong({3, "Happy",        "Pharrell Williams", "G I R L", 233});
    //    library.addSong({4, "See You Again","Wiz Khalifa", "Furious 7", 230});
    //    // 2. Khởi tạo playback queue
    //    PlaybackQueue queue;
    //    // Thêm toàn bộ bài trong album "Divide" vào queue
    //    addAlbumToQueue("Divide", library, queue);
    //    std::cout << "Queue size after addAlbumToQueue: "
    // << queue.size() << "\n";
    //    // 3. Phát thử các bài trong queue
    //    if (!queue.empty()) {
    //        Song current = queue.getCurrentSong();
    //        std::cout << "Now playing: " << current.title
    // << " - " << current.artist << "\n";
    //    } else {
    //        std::cout << "Queue is empty\n";
    //    }
    //    // Play next
    //    queue.playNext();
    //    if (!queue.empty()) {
    //        Song current = queue.getCurrentSong();
    //        std::cout << "Next song: " << current.title
    // 		<< " - " << current.artist << "\n";
    //    }
    //    // 4. Thử remove theo id
    //    queue.removeSong(2); // ví dụ xóa bài có id = 2
    //    std::cout << "Queue size after removeSong(2): "
    // << queue.size() << "\n";

    unique_ptr<MODEL::MusicPlayer> model(new MODEL::MusicPlayer());
    unique_ptr<VIEW::MusicPlayerView> view(new VIEW::MusicPlayerView());
    unique_ptr<CONTROLLER::MusicPlayerController> controler(
        new CONTROLLER::MusicPlayerController(move(model), move(view)));

    controler->run();

    return 0;
}