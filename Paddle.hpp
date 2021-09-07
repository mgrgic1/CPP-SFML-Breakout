#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.hpp"
#include "Ball.hpp"

//defines the main paddle class to be used throughout the game
class Paddle { 

public:
    Paddle(GameToolsPtr tools, StatsTrackerPtr stats);
    ~Paddle();

    //update function for paddle
    //will be called in level's update function since paddle cannot update by itself
    //!!!!Delta time was intentionally not added because the paddle will follow the mouse's position...
    //...rather than move on its own logic
    void Update(float dt); 

    void Draw();

    //paddle will have input, therefore it must be handled appropriately in each scene
    void HandleInput(sf::Event ev); 

    Ball* getBall(){return ball;};

private:
    GameToolsPtr gameTools;
    StatsTrackerPtr stats;
    sf::Sprite paddleSprite; 
    sf::Sound ballHitSound;
    sf::SoundBuffer buffer;

    Ball* ball;

    //is the ball following the paddle?
    //used at the beginning of the game so that the ball follows where the paddle is going...
    //...(before player presses mouse)
    bool ballFollowPaddle;

    bool collideWithBall; //is paddle colliding with ball

    void movePaddle();

    //function to help get truly random AND equal numbers
    int getRandNum(int minRange, int maxRange);

    //checks collision with ball sprite
    bool isCollidingWith(sf::Sprite* ballSprite);
};
