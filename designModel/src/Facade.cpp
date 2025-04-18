#include <iostream>
#include <string>

// 子系统1：投影仪
class Projector {
public:
    void on() {
        std::cout << "Projector is turned on." << std::endl;
    }

    void off() {
        std::cout << "Projector is turned off." << std::endl;
    }

    void setInput(const std::string& input) {
        std::cout << "Projector input set to: " << input << std::endl;
    }
};

// 子系统2：音响
class SoundSystem {
public:
    void on() {
        std::cout << "Sound system is turned on." << std::endl;
    }

    void off() {
        std::cout << "Sound system is turned off." << std::endl;
    }

    void setVolume(int level) {
        std::cout << "Sound system volume set to: " << level << std::endl;
    }
};

// 子系统3：蓝光播放器
class BluRayPlayer {
public:
    void on() {
        std::cout << "Blu-ray player is turned on." << std::endl;
    }

    void off() {
        std::cout << "Blu-ray player is turned off." << std::endl;
    }

    void play(const std::string& movie) {
        std::cout << "Playing movie: " << movie << std::endl;
    }
};

// 门面类：家庭影院
class HomeTheaterFacade {
private:
    Projector projector;
    SoundSystem soundSystem;
    BluRayPlayer bluRayPlayer;

public:
    void watchMovie(const std::string& movie) {
        std::cout << "Setting up the home theater to watch a movie..." << std::endl;
        projector.on();
        projector.setInput("Blu-ray Player");
        soundSystem.on();
        soundSystem.setVolume(10);
        bluRayPlayer.on();
        bluRayPlayer.play(movie);
        std::cout << "Enjoy your movie!" << std::endl;
    }

    void endMovie() {
        std::cout << "Shutting down the home theater..." << std::endl;
        bluRayPlayer.off();
        soundSystem.off();
        projector.off();
        std::cout << "Goodbye!" << std::endl;
    }
};

// 客户端代码
int main() {
    HomeTheaterFacade homeTheater;

    homeTheater.watchMovie("Inception");
    std::cout << std::endl;
    homeTheater.endMovie();

    return 0;
}