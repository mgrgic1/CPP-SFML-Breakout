#include "Animation.hpp"
#include <iostream>

void Animation::loadAnimInfo(sf::IntRect* spriteRect, sf::Vector2i rowColumn, float playTime)
{
    sprSheetRowCol = rowColumn;
    totalPlaySeconds = playTime;  

    //by default, the rect will be focused on the first image in the sprite sheet 
    frameRect.left = 0;
    frameRect.top = 0;

    //variables we wont change. how wide/tall is the current sprite's rect?
    frameRect.width = spriteRect->width;
    frameRect.height = spriteRect->height;

    realTime = 0;
    isFinished = false;
    loop = false;
}

void Animation::setLoop(bool isLooping) {
    loop = isLooping;
}

bool Animation::IsCompleted() {
    return isFinished;
}

float Animation::currentTime() {
    return realTime;
}

void Animation::RunAnim(sf::Sprite* sprite,float dt) {
    
    frameTimer += clock.restart().asSeconds();


     //if we have spent enough time on one image/frame in the sprite sheet, move to the next frame
    if(!isFinished && frameTimer >= (totalPlaySeconds/(sprSheetRowCol.x*sprSheetRowCol.y))) 
    {
        realTime += frameTimer;
        //if the next frame DOES NOT leave the bounds of the sprite sheet's columns
        if(frameRect.left + frameRect.width < sprSheetRowCol.y * frameRect.width) 
        {
            frameRect.left += frameRect.width;
        }
        
        //if the next frame LEAVES the sprite sheet's columns bounds...
        else 
        {

            //if the next frame DOES NOT leave the bounds of the sprite sheet's rows
            if(frameRect.top + frameRect.height < sprSheetRowCol.x * frameRect.height) 
            {
                //...go to the next column
                frameRect.left = 0;
                frameRect.top += frameRect.height;
            }

            //if the next frame both leaves the column and row bounds...
            else 
            {
                //if looping is true, starts everything from beginning
                if(loop) 
                {
                    frameRect.left = 0;
                    frameRect.top = 0;
                    realTime = 0;
                }
                else 
                {
                    isFinished = true;
                }
            }
        }

        frameTimer = 0; //reset the frame timer
    }


    sprite->setTextureRect(frameRect);
}