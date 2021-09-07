#include "Brick.hpp"

//default ctor to set up the brick

Brick::Brick(BrickInfo brickInfo, sf::Vector2i startPos) 
{
    ID = brickInfo.brickID;
    timesHit = brickInfo.hitPoints;
    breakScore = brickInfo.breakScore;

    brickSprite.setTexture(*brickInfo.brickTexture);

    //loading a brick's broken textures
    if(brickInfo.damagedTexturePath == "") {
         std::cout<<"No value given for brick broken texture, moving on..." << std::endl;
    }
    else if(!brokenTexture.loadFromFile(brickInfo.damagedTexturePath)) {
		std::cout<<"Unable to load broken brick texture!" << std::endl;
	}
    else 
    {
        brokenTexture.loadFromFile(brickInfo.damagedTexturePath);
    }
    
    if(brickInfo.hitSoundPath == "") 
    {
        std::cout<<"No value given for hit sound path, moving on..." << std::endl;
    }
    else if(!hitBuffer.loadFromFile(brickInfo.hitSoundPath)) 
    {
        std::cout << "Error loading hit sound effect!" << std::endl;
    } 
    else 
    {
        hitAudio.setBuffer(hitBuffer); 
        hitAudio.setLoop(false); //NEVER loop the sound
    }


    if(brickInfo.breakSoundPath == "") 
    {
        std::cout<<"No value given for break sound path, moving on..." << std::endl;  
    }
    else if(!breakBuffer.loadFromFile(brickInfo.breakSoundPath)) 
    {
        std::cout << "Error loading break sound effect!" << std::endl;
    }
    else {
        breakAudio.setBuffer(breakBuffer);
        breakAudio.setLoop(false); //NEVER loop the sound
    }

    brickSprite.setPosition(startPos.x, startPos.y);
}


void Brick::Draw(sf::RenderWindow& window) 
{
    window.draw(brickSprite);
}

void Brick::setPosition(float x, float y) 
{
    brickSprite.setPosition(x,y);
}

//makes brick "take a hit" -- removes 1 from the brick's hit points
//if the sprite has 1 hit on it left (close to being destroyed, changes its sprite to have...
//...a broken texture)
void Brick::takeHit() 
{
    timesHit--; 

    if(timesHit == 1) 
    {
        brickSprite.setTexture(brokenTexture);
    }
}

void Brick::playBrickBreak() 
{
    breakAudio.play();
}

void Brick::playBrickHit() 
{
    hitAudio.play();
}