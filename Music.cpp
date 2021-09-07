#include "Music.hpp"
#include <iostream>

Music::Music() 
{
    //tests to see if there is an issue with loading a song
    if(!music.openFromFile("Resources/Music/song1.ogg")) 
    {
        std::cout<<"Error loading song 1" << std::endl;
    }
    if(!music.openFromFile("Resources/Music/song2.ogg")) 
    {
        std::cout<<"Error loading song 2" << std::endl;
    }

    //gives us a random song to play
    onSong = getRandNum(1,3);
    music.openFromFile("Resources/Music/song"+std::to_string(onSong)+".ogg");

    playSong = false;
}

void Music::setPlay(bool play) 
{
    if(play) 
    {
        music.play();
    }
    else 
    {
        music.pause();
    }

    playSong = play;
}

void Music::Update() 
{
    if(music.getStatus() == sf::SoundSource::Stopped) 
    {
        onSong = (++onSong)%4;
        music.openFromFile("Resources/Music/song"+std::to_string(onSong)+".ogg");
        music.play();
    }
}

//generates a random number between a certain range
//ideal for setting ball velocity when ball is attached to paddle
int Music::getRandNum(int minRange, int maxRange) {
    std::random_device rd; //get random number
    std::mt19937 gen(rd()); //seed RNG
    std::uniform_int_distribution<int> distr(minRange, maxRange); // define the range

    return distr(gen);
}