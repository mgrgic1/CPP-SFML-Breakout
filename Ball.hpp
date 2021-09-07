#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <random> //setting initial ball velocity in random direction

//class defining ball and ball related logic
class Ball {

public:
    Ball(GameToolsPtr tools);
    ~Ball(){};
    
    void Update(float dt);

    void Draw();

    //sets position of the ball
    //(ideally used to put the ball back on top of the paddle when player dies OR at beginning of level)
    void setPosition(float x, float y);

    //sets initial velocity of the ball (when it is released from paddle)
    void setStartVelocity();

    void setVelocity(float x, float y);

    //changes velocity of the ball BASED ON THE POSITION of where it hit the paddle
    void changeVelocityOnHit(float paddleX);

    //gets velocity of the ball
    sf::Vector2i getVelocity(); 

    //get position of the ball
    sf::Vector2i getPosition();

    sf::Sprite* getSprite(){return &ballSprite;};

    bool isOutOfBounds(){return outofBounds;};

    void resetBound(){outofBounds = false;};

private:
    GameToolsPtr gameTools;

    //moveBall defines logic that makes the ball move based on its velocity
    void moveBall(float dt);

    //checks bounds to make sure ball is still in the game window
    void checkBounds(sf::RenderWindow& window);   

    //in what two directions is the ball moving?
    //ex: (0,1) means that the ball is moving upwards, (0,-1) downwards
    //similar to velocity vector in unity :)
    sf::Vector2i ballVelocity;

    sf::Sprite ballSprite;

    //PREDETERMINED NUMBER. what's the ball's minimum/base velocity
    float baseVelocity = 400; 

    //gets random number (commonly used for force)
    int getRandNum(int minRange, int maxRange);

    bool outofBounds;

};