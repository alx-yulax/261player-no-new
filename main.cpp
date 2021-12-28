#include <iostream>
#include <ctime>
#include <cassert>

class Track {
    std::string title;
    std::tm released;
    int duration_sec;
public:
    Track(std::string inTitle, std::tm inReleased, int inDuration_sec) :
            title(inTitle), released(inReleased), duration_sec(inDuration_sec) {
        assert(inDuration_sec >= 0);
    }

    std::string getTitle() {
        return title;
    }

    void show() {
        std::cout << " title: " << title << "  Released: " << asctime(&released) << "  Duration (sec): " << duration_sec
                  << std::endl;
    }
};

enum Status {
    STOPPED,
    PLAYING,
    PAUSED,
};

class Player {
    Status status;
    int currentTrack;
    int currentTrackTime;
    Track **availableRecords;
public:
    Player() : status(STOPPED) {
        availableRecords = new Track *[5];

        std::tm released{};
        released.tm_year = 119;
        released.tm_mon = 5;
        released.tm_mday = 1;

        availableRecords[0] = new Track("Just Like a Pill", released, 244);
        availableRecords[1] = new Track("Who Knew", released, 212);
        availableRecords[2] = new Track("Time After Time", released, 206);
        availableRecords[3] = new Track("Just Give Me a Reason", released, 278);
        availableRecords[4] = new Track("Walk Me Home", released, 177);

    }

    ~Player() {
        for (int i = 0; i < 5; ++i) {
            delete availableRecords[i];
        }
    }

    void play() {
        for (int i = 0; i < 5; ++i) {
            std::cout << i << " " << availableRecords[i]->getTitle() << std::endl;
        }
        std::cout << "Input number of track (0-4): ";
        int trackNumber;
        std::cin >> trackNumber;
        if (trackNumber <0 || trackNumber > 5) {
            std::cout << "Wrong number of track.";
        } else {
            status == PLAYING;
            currentTrack = trackNumber;

        }

    }

    void pause() {

    }

    void next() {

    }

    void stop() {

    }

};


int main() {
    Player *sony = new Player();

    std::string command;
    do {
        std::cin >> command;
        if (command == "play") {
            sony->play();
        } else if (command == "pause") {
        } else if (command == "next") {
        } else if (command == "stop") {

        }
    } while (command != "exit");

    return 0;
}
