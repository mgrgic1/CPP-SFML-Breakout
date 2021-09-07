#pragma once
#include <SFML/Audio.hpp>
#include <random> //getting a random song number

class Music {

public:
    Music();
    ~Music(){};

    void Update(); //checks if the song has finished so that it can be switched
    void setPlay(bool play);
    bool getPlay(){return playSong;};

    int getRandNum(int minRange, int maxRange);

private:
    bool playSong = false;
    int onSong; //what song are we currently listening to?
    sf::Music music;
};