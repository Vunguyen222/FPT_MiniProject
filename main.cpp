#include "include/global.h"
#include "include/model/Song.hpp"
#include "include/model/MusicLibrary.hpp"
#include "include/model/PlaybackQueue.hpp"
using namespace MODEL;

void test_addSong()
{
	std::cout << "[TEST] addSong()\n";

	MusicLibrary lib;

	Song s1;
	s1.title = "Song A";
	s1.artist = "Artist A";
	s1.album = "Album A";
	s1.duration = 210;

	lib.addSong(s1);

	const auto &all = lib.getAllSongs();
}

void test_loadFromJson()
{
	std::cout << "[TEST] loadFromJsonFile()\n";

	MusicLibrary lib;

	bool ok = lib.loadFromJsonFile("include/music_library.json");
	if (!ok)
	{
		std::cout << " -> FAILED (cannot load JSON)\n\n";
		return;
	}

	const auto &all = lib.getAllSongs();

	std::cout << " Loaded songs = " << all.size() << "\n";
	if (!all.empty())
	{
		std::cout << " Example first song: ";
		lib.printSongInfo(all[0]);
	}
	std::cout << " -> PASSED\n\n";
}

void test_print_functions()
{
	std::cout << "[TEST] printSongTableHeader & printSongInfo\n";

	MusicLibrary lib;

	Song s2;
	s2.title = "Song B";
	s2.artist = "Artist B";
	s2.album = "Album B";
	s2.duration = 210;
	lib.addSongFromUserAndSave(s2);

	lib.printSongTableHeader();

	for (const auto &song : lib.getAllSongs())
	{
		lib.printSongInfo(song);
	}

	std::cout << " -> PASSED (please verify visually)\n\n";
}

int main()
{

	std::cout << "===== MUSIC LIBRARY TESTS =====\n\n";

	test_addSong();
	test_loadFromJson();
	test_print_functions();

	std::cout << "===== END TEST =====\n";

	return 0;
}