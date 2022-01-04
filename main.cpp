#include <iostream>
#include <ctime>
#include <cassert>
#include <iomanip>
#include <vector>

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

    int getDuration_sec() {
        return duration_sec;
    }

    void show() {

        std::cout << " title: " << title << "  Released: " << std::put_time(&released, "%d/%m/%Y")
                  << "  Duration (sec): " << duration_sec << std::endl;
    }
};

enum Status {
    STOPPED,
    PLAYING,
    PAUSED,
};

class Player {
    Status status;
    int track_number;
    int track_start;
    std::time_t track_time_left;
    //Track **available_records;
    std::vector<Track> available_records_v;


public:
    Player() : status(STOPPED), track_number(-1) {
        //available_records = new Track *[5];

        std::tm released{};
        released.tm_year = 119;
        released.tm_mon = 5;
        released.tm_mday = 1;


        available_records_v.push_back(Track("Just Like a Pill", released, 244));
        available_records_v.push_back(Track("Who Knew", released, 212));
        available_records_v.push_back(Track("Time After Time", released, 206));
        available_records_v.push_back(Track("Just Give Me a Reason", released, 278));
        available_records_v.push_back(Track("Walk Me Home", released, 177));

    }

    ~Player() {
        for (int i = 0; i < available_records_v.size(); ++i) {
            //delete available_records[i];
        }
    }

    void update_status_PLAYING() {
        if (status == PLAYING) {
            track_time_left -= (std::time(nullptr) - track_start);
            if (track_time_left < 1) {
                stop(false);
            }
        }
    }

    void play(int in_track_number = -1) {
        update_status_PLAYING();
        if (status == STOPPED) {
            if (in_track_number == -1) {
                for (int i = 0; i < available_records_v.size(); ++i) {
                    std::cout << i << " " << available_records_v[i].getTitle() << std::endl;
                }
                std::cout << "Input number of track (0-4): ";
                std::cin >> in_track_number;
            }
            if (in_track_number < 0 || in_track_number > 5) {
                std::cout << "Wrong number of track." << std::endl;;
            } else {
                track_number = in_track_number;
                track_start = std::time(nullptr);
                track_time_left = available_records_v[in_track_number].getDuration_sec();
                status = PLAYING;

                std::cout << "PLAYING: " << std::endl;
                available_records_v[in_track_number].show();
            }
        } else if (status == PLAYING) {
            std::cout << "NOW playing: " << std::endl;
            available_records_v[track_number].show();
        } else if (status == PAUSED) {
            track_start = std::time(nullptr);
            status = PLAYING;
            std::cout << "Continue playing: " << std::endl;
            available_records_v[track_number].show();
        }
    }

    void pause() {
        update_status_PLAYING();
        if (status == PLAYING) {
            status = PAUSED;
            std::cout << "PAUSED: " << std::endl;
            available_records_v[track_number].show();
        }
    }

    void next() {
        stop(false);
        play(std::rand() % 5);
    }

    void stop(bool update_status_PLAY = true) {
        if (update_status_PLAY) {
            update_status_PLAYING();
        }
        if (status != STOPPED) {
            if (update_status_PLAY) {
                std::cout << "STOPPED: " << std::endl;
                available_records_v[track_number].show();
            }
            track_start = 0;
            track_time_left = 0;
            track_number = -1;
            status = STOPPED;
        }
    }
};


int main() {
    std::srand(std::time(nullptr));
    Player *sony = new Player();

    std::string command;
    do {
        std::cout << "Input command: ";
        std::cin >> command;
        if (command == "play") {
            sony->play();
        } else if (command == "pause") {
            sony->pause();
        } else if (command == "next") {
            sony->next();
        } else if (command == "stop") {
            sony->stop();
        }
    } while (command != "exit");

    delete sony;
    return 0;
}
