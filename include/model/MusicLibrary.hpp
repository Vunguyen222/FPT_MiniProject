#pragma once
#include "../global.h"
#include "Song.hpp"
namespace MODEL
{
	class MusicLibrary
	{
	private:
		std::vector<Song> songs;
		std::unordered_map<int, Song *> songIndexByID;
		std::map<std::string, Song *> songIndexByTitle;
		const int maxSize;
		std::unordered_map<std::string, std::vector<Song *>> artistIndex;
		std::unordered_map<std::string, std::vector<Song *>> albumIndex;
		const std::string jsonPath;
		int nextID ;

	public:

		// Add new songs
		void addSong(const Song &songInput);
		bool addSongFromUserAndSave(const Song &newSong);

		//lookup function
		Song *findByID(int songId);
		Song *findByTitle(const std::string &title);
		std::vector<Song *> findByArtist(const std::string &artist);
		std::vector<Song *> findByAlbum(const std::string &albumName) const;

		// load and save data from JSON file
		bool loadFromJsonFile(const std::string &filePath);
		bool savetoJsonFile(const std::string &filePath) const;

		// display
		void printSongTableHeader() const;
		void printSongInfo(const Song &s) const;
		void printSongsByPage(int page, const int pageSize) const;
		const std::vector<Song> &getAllSongs() const;

	public:
		MusicLibrary();
		void printAllSongs();
	};
} // namespace MODEL