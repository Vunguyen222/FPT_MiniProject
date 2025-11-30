#include "../../include/model/PlaybackQueue.hpp"
#include "../../include/model/MusicLibrary.hpp"
using namespace std;
namespace MODEL
{

	/*
		Queue() tạo list rỗng
		current(queue.end()) -> iterator chỉ vào cuối list (không trỏ tới bài nào)
		hasCurrent(false) -> chưa có bài hát hiện tại

		=> Hàng đợi bắt đầu trạng thái rỗng, chưa có bài hát nào được chọn
	*/
	PlaybackQueue::PlaybackQueue() : queue(), current(queue.end()), hasCurrent(false) {}

	/*
		//=======================================Add Song===================================================
		Check for duplicate ID
			Use unordered_set → O(1).
			If the ID exists → skip it.
		Add to the end of the queue
			This matches the behavior of a music playback queue.
		If the queue was previously empty
			Set current to the first newly added song.
			Mark hasCurrent = true.
		=> The function ensures that the queue contains no duplicate IDs and always has a current track when the first song is added.
	*/
	void PlaybackQueue ::addSong(const Song &song)
	{
		if (songIdInQueue.find(song.id) != songIdInQueue.end())
		{
			std::cout << "Song ID: " << song.id << " already in queue\n";
			return;
		}
		queue.push_back(song);
		songIdInQueue.insert(song.id);
		if (!hasCurrent)
		{
			current = queue.begin();
			hasCurrent = true;
		}
	}

	/*
	====================================================Remove Song=====================================================
		- If the queue is empty → do nothing.
		- Iterate through the entire list to find a song with a matching ID.
		- When found:
			Check if this song is currently pointed to by current.
			Remove the ID from the unordered_set.
			Erase the element using erase(it)
		-> erase() returns an iterator pointing to the next element.
	*/

	void PlaybackQueue::removeSong(int songId)
	{
		if (queue.empty())
		{
			return;
		}
		for (auto it = queue.begin(); it != queue.end();)
		{
			if (it->id == songId)
			{
				bool removingCurrent = hasCurrent && (it == current);
				// Xoa id khoi set
				songIdInQueue.erase(songId);
				// erase trả về iterator kế tiếp sau phần tử bị xóa
				auto nextIt = queue.erase(it);
				if (removingCurrent)
				{
					if (nextIt != queue.end())
					{
						current = nextIt;
						hasCurrent = true;
					}
					else if (!queue.empty())
					{
						// Không còn phía sau nhưng list vẫn còn phần tử
						// => quay về bài đầu
						current = queue.begin();
						hasCurrent = true;
					}
					else
					{
						// Queue rỗng
						current = queue.end();
						hasCurrent = false;
					}
				}
				it = nextIt;
			}
			else
			{
				++it;
			}
		}
	}

	Song PlaybackQueue::getCurrentSong() const
	{
		if (!hasCurrent || queue.empty())
		{
			return Song{}; // id = 0, title rỗng, v.v.
		}
		return *current;
	}
	Song *PlaybackQueue::playNext()
	{

		if (!hasCurrent || queue.empty())
		{
			return nullptr;
		}

		Song *result = new Song(*current);
		auto nextIt = current;
		++nextIt;
		if (nextIt != queue.end())
		{
			current = nextIt;
		}
		else
		{
			current = queue.begin();
		}

		return result;
	}

	bool PlaybackQueue::empty() const
	{
		return queue.empty();
	}
	std::size_t PlaybackQueue::size() const
	{
		return queue.size();
	}

	void PlaybackQueue::printQueueByPage(const MusicLibrary &library, int page, const int pageSize) const
	{
		int total = static_cast<int>(queue.size());
		if (total == 0)
		{
			std::cout << "[Queue] Hien tai khong co bai hat nao trong queue.\n";
			return;
		}
		int totalPages = (total + pageSize - 1) / pageSize;
		if (page < 1 || page > totalPages)
		{
			std::cout << "[Queue] Page khong hop le. Chi co " << totalPages << " trang.\n";
			return;
		}
		int startIndex = (page - 1) * pageSize;
		int endIndex = std::min(startIndex + pageSize, total);
		std::cout << "\n===== QUEUE	 Trang " << page << " / " << totalPages << " =====\n";
		library.printSongTableHeader();
		int index = 0;
		auto it = queue.begin();
		// Duyet list, in chỉ các phần tử thuộc [startIndex, endIndex)
		while (it != queue.end() && index < endIndex)
		{
			if (index >= startIndex)
			{
				library.printSongInfo(*it);
			}
			++it;
			++index;
		}
	}

	void addAlbumToQueue(const std::string &albumName, const MusicLibrary &library, PlaybackQueue &queue)
	{
		auto songsInAlbum = library.findByAlbum(albumName);
		for (auto *s : songsInAlbum)
		{
			if (s)
			{
				queue.addSong(*s);
			}
		}
	}
}