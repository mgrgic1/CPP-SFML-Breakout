#pragma once

#include "SFML/Graphics.hpp"

//animation class
//all this implementation does is play through a loaded sprite sheet by changing the "frame"...
//...(frame being the intRect displaying the image), of an image in the sprite sheet
//as with movies, this displays movement
class Animation {

public:
    Animation(){};
    ~Animation(){};

    //number of rows and columns in the sprite sheet
    void loadAnimInfo(sf::IntRect* spriteRect, sf::Vector2i rowColumn, float playTime);
    void RunAnim(sf::Sprite* sprite,float dt);
    void setLoop(bool isLooping); //allows us to change whether or not the anim can loop

    bool IsCompleted(); //has the animation finished running?

    float currentTime();

private:
    float frameTimer = 0; //will track how many seconds we spend on each frame
    float totalPlaySeconds; //how many seconds will the entire animation be?
    float realTime; //what is the real playback position of the animation in seconds?
    bool loop;
    bool isFinished; 

    sf::Vector2i sprSheetRowCol;

    //used to track/move frames for the sprite sheet of a sprite
    //this rect will show the   "individual image" from the spritesheet 
    //will be assigned constantly in the update to give the illusion of frames moving...
    //...from the sprite sheet
    sf::IntRect frameRect;

    sf::Clock clock; //general clock for measuring time


};