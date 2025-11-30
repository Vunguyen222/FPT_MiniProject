#include "utils.hpp"

using namespace std;

inline void ltrim(string& s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(),
                               [](unsigned char ch) { return !isspace(ch); }));
}

inline void rtrim(string& s) {
    s.erase(find_if(s.rbegin(), s.rend(),
                    [](unsigned char ch) { return !isspace(ch); })
                .base(),
            s.end());
}

inline void trim(string& s) {
    rtrim(s);
    ltrim(s);
}

void separateData(string dataStream, Song& target) {
    vector<string> parts;
    stringstream ss(dataStream);
    string item;

    while (std::getline(ss, item, '-')) {
        trim(item);
        parts.push_back(item);
    }

    if (parts.size() == 4) {
        target.title = parts[0];
        target.artist = parts[1];
        target.album = parts[2];
        target.duration = stoi(parts[3]);
    } else {
        cerr << "Invalid format: expected 4 parts\n";
    }
}

string formatTime(int songDuration) {
    int minutes = songDuration / 60;
    int seconds = songDuration % 60;
    ostringstream oss;
    oss << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}

void moveCursor(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

void clearLine() { std::cout << "\033[K"; }

void clearScreen() { cout << "\033[3J\033[2J\033[1;1H"; }
