#include "Paddle.hpp"
#include <iostream>


Paddle::Paddle(GameToolsPtr tools, StatsTrackerPtr stats) {
    gameTools = tools;
    this->stats = stats;
    ball = new Ball(gameTools);

    gameTools->assetManager.LoadTexture("Paddle","Resources/paddle.png");
    paddleSprite.setTexture(gameTools->assetManager.GetTexture("Paddle"));

    float paddleWidth = paddleSprite.getGlobalBounds().width;
    float paddleHeight = paddleSprite.getGlobalBounds().height;

    //sets paddle origin to be in the center bottom
    paddleSprite.setOrigin(paddleWidth/2,paddleHeight);

    //sets position to be in the center bottom of screen
    paddleSprite.setPosition(1024/2,768);

    //sets ball's initial position
    ball->setPosition(paddleSprite.getPosition().x, paddleSprite.getPosition().y - paddleSprite.getGlobalBounds().height);

    //on paddle creation, the ball will follow the paddle
    ballFollowPaddle = true;

    collideWithBall = false;

    if(!buffer.loadFromFile("Resources/Sounds/hitPaddle.wav")); 
    {
        std::cout << "Error loading paddle hit sound effect!" << std::endl;
    } 
    ballHitSound.setBuffer(buffer);

}

void Paddle::Update(float dt) {
    movePaddle();
    ball->Update(dt);

    if(ballFollowPaddle) 
    {
        ball->setPosition(paddleSprite.getPosition().x, ball->getPosition().y);
    }

    //checks if ball collides with paddle WHEN IT IS NOT following paddle
    if(!ballFollowPaddle && isCollidingWith(ball->getSprite())) 
    {
        ballHitSound.play();
        ball->changeVelocityOnHit(paddleSprite.getPosition().x);    
    }


    if(ball->isOutOfBounds() && !ballFollowPaddle) 
    {
        ball->setVelocity(0,0);
        ballFollowPaddle = true;
        ball->setPosition(paddleSprite.getPosition().x, paddleSprite.getPosition().y - paddleSprite.getGlobalBounds().height);
        stats->totalLives--;
        ball->resetBound();
    }



}

void Paddle::HandleInput(sf::Event ev) 
{
    //if the player clicked the left mouse key AND ball is following paddle...
    //...removes ball from paddle, ball starts moving
    if(gameTools->inputManager.GetMouseButtonDown(0,ev) && ballFollowPaddle) 
    {
        ballFollowPaddle = false;
        ball->setStartVelocity();
    }
}

void Paddle::Draw() {
    gameTools->window->draw(paddleSprite);
    ball->Draw();
}

void Paddle::movePaddle() {

    //if mouse is in the window bounds, allow the paddle to be moved (only on x axis!)
    if(gameTools->inputManager.inWindowBounds(*gameTools->window)) 
    {
        //if the paddle collides with left OR side of the screen...
        //...then stop it
        //(because the paddle's origin is in the middle of the sprite. player can move their mouse...
        //...off the screen and half of the paddle will disappear. these bools prevents that)
        bool inBoundsL = gameTools->inputManager.GetMousePosition(*gameTools->window).x - paddleSprite.getGlobalBounds().width/2 > 0;
        bool inBoundsR = gameTools->inputManager.GetMousePosition(*gameTools->window).x + paddleSprite.getGlobalBounds().width/2 < gameTools->window->getSize().x;
        
        if(inBoundsL && inBoundsR) 
        {
            paddleSprite.setPosition(gameTools->inputManager.GetMousePosition(*gameTools->window).x, paddleSprite.getPosition().y);
        }
    }
}//end move paddle


Paddle::~Paddle() {
    delete ball;
}

bool Paddle::isCollidingWith(sf::Sprite* ballSprite) 
{
    //sets bool true when paddle collides with ball
    if(!collideWithBall && paddleSprite.getGlobalBounds().intersects(ballSprite->getGlobalBounds())) 
    {
        collideWithBall = true;
        return true;
    }

    //sets bool false IF paddle is no longer colliding with ball
    else if(collideWithBall && paddleSprite.getGlobalBounds().intersects(ballSprite->getGlobalBounds())) 
    {
        collideWithBall = false;
        return false;
    }
    else return false; //default value
}