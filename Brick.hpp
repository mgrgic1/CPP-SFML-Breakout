#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "BrickInfoStruct.hpp"
#include <iostream>

//brick class
//defines the behavior of an individual brick
class Brick 
{
    
public:
    //default ctor to set up the brick
    Brick(BrickInfo brickInfo, sf::Vector2i startPos);
    ~Brick(){};

    void Draw(sf::RenderWindow& window); //draw brick

    void setPosition(float x, float y); //sets position of a brick

    sf::Vector2i getPosition() {return sf::Vector2i(brickSprite.getPosition().x, brickSprite.getPosition().y);};

    sf::Sprite* getSprite() {return &brickSprite;};

    //gets the amount of times a brick has been hit
    int getHits(){return timesHit;};

    //makes the brick take a hit
    void takeHit();

    //gets ID of the current brick
    std::string getID(){return ID;};

    //plays brick hit sound
    void playBrickHit();

    //plays brick break sound
    void playBrickBreak();

    //the amount of points a player gets when they break a brick
    int getPoints(){return breakScore;};

    sf::Sound* getBreakSound(){return &breakAudio;};

private:
    std::string ID; //id of the brick
    sf::Sprite brickSprite; //sprite of the brick
    sf::Texture brickTexture; //regular brick texture
    sf::Texture brokenTexture; //texture of broken brick

    sf::SoundBuffer hitBuffer;
    sf::SoundBuffer breakBuffer;

    //how many times brick needs to be hit to break
    //if this value is -1, infinite hits are assumed (meaning the brick cannot be broken)
    int timesHit;

    sf::Sound hitAudio; //sound that plays when brick is hit
    sf::Sound breakAudio; //sound that plays when brick is broken
    int breakScore = 0; //score player gets when brick is broken. default is 0


};