#include "Ball.hpp"
#include <cmath> //for absolute value

Ball::Ball(GameToolsPtr tools) {
    gameTools = tools;

    gameTools->assetManager.LoadTexture("Ball","Resources/ball.png");

    ballSprite.setTexture(gameTools->assetManager.GetTexture("Ball"));

    float ballWidth = ballSprite.getGlobalBounds().width;
    float ballHeight = ballSprite.getGlobalBounds().height;

    //sets the origin to be in the CENTER BOTTOM of the sprite
    ballSprite.setOrigin(ballWidth/2, ballHeight);

    ballVelocity = sf::Vector2i(0,0); //default velocity when ball is created (0,0 -- not moving)
}

void Ball::Update(float dt) {
    moveBall(dt);
    checkBounds(*gameTools->window);
}

void Ball::Draw() {
    gameTools->window->draw(ballSprite);
}

sf::Vector2i Ball::getVelocity() {
    return ballVelocity;
}

void Ball::setVelocity(float x, float y) 
{
    ballVelocity.x = x;
    ballVelocity.y = y;
}

void Ball::setPosition(float x, float y) {
    ballSprite.setPosition(x, y);
}

void Ball::setStartVelocity() 
{
    ballVelocity.x = getRandNum(-baseVelocity,baseVelocity);   
    ballVelocity.y = -baseVelocity; 
}

//this changes the ball's direction based on where the ball hit the paddle 
//???why is this here? --> (a hit on the very very very tip of the paddle SHOULD NOT be calculated the same as a hit in the center)
void Ball::changeVelocityOnHit(float paddleX) {

    //difference between where the ball hit and where the X was (will help us see how far off the ball was from the center)
    float paddleBallDifference = (ballSprite.getPosition().x - paddleX);

    //velocity of x based on where the ball hit the paddle
    //the speed multiplier is randomized because variety is the spice of life
    ballVelocity.x = paddleBallDifference * getRandNum(3,6);

    ballVelocity.y = -ballVelocity.y;
}


sf::Vector2i Ball::getPosition() {
    return sf::Vector2i(ballSprite.getPosition().x, ballSprite.getPosition().y);
}

void Ball::moveBall(float dt) {

    if(abs(ballVelocity.x) > 0 || abs(ballVelocity.y) > 0) 
    {
        ballSprite.move(ballVelocity.x * dt, ballVelocity.y * dt);
    }
}

//checks bounds to make sure ball is still on the screen
//IF the ball is trying to leave the screen on any axis, changes its velocity to keep it on the screen
void Ball::checkBounds(sf::RenderWindow& window) 
{
    //these floats are adjusted for the x axis
    //because i changed the ball's origin (see ctor), i have to adjust its real position...
    //...so that when the REAL edge of the ball hits the screen, the ball turns
    //(if i didn't have this, half of the ball would disappear off the screen, THEN the velocity would reverse)
    float adjustedBallPosL = ballSprite.getPosition().x - ballSprite.getGlobalBounds().width/2;
    float adjustedBallPosR = ballSprite.getPosition().x + ballSprite.getGlobalBounds().width/2;

    //float adjusted for y axis, same reason as above
    float adjustedBallPosTop = ballSprite.getPosition().y - ballSprite.getGlobalBounds().height;


    //left AND right screen bound
    //if the ball is trying to leave the window, reverse its velocity
    if(adjustedBallPosL <= 0 || adjustedBallPosR >= window.getSize().x) 
    {
        ballVelocity.x = -ballVelocity.x;
    }

    //top screen bound
    //if ball istrying to leave the top bound, reverse its y velocity
    if(adjustedBallPosTop < 0) 
    {
        ballVelocity.y = -ballVelocity.y;
    }

    //if ball leaves the scene altogether, it is out of bounds
    if(ballSprite.getPosition().y > window.getSize().y) 
    {
        outofBounds = true;
    }


}//end ball checkBounds

//generates a random number between a certain range
//ideal for setting ball velocity when ball is attached to paddle
int Ball::getRandNum(int minRange, int maxRange) {
    std::random_device rd; //get random number
    std::mt19937 gen(rd()); //seed RNG
    std::uniform_int_distribution<int> distr(minRange, maxRange); // define the range

    return distr(gen);
}