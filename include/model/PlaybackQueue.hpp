#pragma once
#include "MusicLibrary.hpp"
#include "Song.hpp"

namespace MODEL
{
	class PlaybackQueue
	{
	private:
		std::list<Song> queue;
		std::list<Song>::iterator current; // iterator trỏ tới bài hiện tại
		bool hasCurrent;				   // đánh dấu đã có current hợp lệ hay chưa
		std::unordered_set<int> songIdInQueue;

	public:
		PlaybackQueue();
		void addSong(const Song &song);
		void removeSong(int songID);
		Song getCurrentSong() const;
		Song* playNext();
		bool empty() const;
		std::size_t size() const;
		void printQueueByPage(const MusicLibrary &library, int page, const int pageSize) const;
	};
	void addAlbumToQueue(const std::string &albumName, const MusicLibrary &library,
						 PlaybackQueue &queue);
} // namespace MODEL
