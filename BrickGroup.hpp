#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "tinyxml2.h" //reading XML files
#include "Brick.hpp"
#include <vector>
#include "Game.hpp" //allows us to use items in gametoolsptr
#include "Ball.hpp"

//defines a group of bricks in each scene
//this class is responsible for managing all bricks in the scene
class BrickGroup {

public:
    //takes the xmlPath and reads all bricks present in the level
    BrickGroup(const char* pathToXml, GameToolsPtr tools, StatsTrackerPtr stats);
    ~BrickGroup();

    void Draw(sf::RenderWindow& window); //draws all bricks in the scene

    //updates bricks
    //passed ball pointer checks if any bricks in our group are colliding...
    //with our ball. if it is, change ball velocity
    void Update(Ball* ball); 

    bool allBricksDestroyed(){return isFinished;};

private:
    int rowCount;
    int columnCount;
    int rowPadding; //the amount of padding between each row
    int columnPadding; //the amount of padding between each column

    StatsTrackerPtr stats; //keeps track of stats (points, lives)

    //how many impenetrable bricks are there? will be used to calculate the end...
    //...of the game
    int impenBrickNum = 0; 

    //checks if we have destroyed all bricks
    bool isFinished;

    //stores brick types for each level
    std::map<std::string, BrickInfo> brickTypes;
    std::vector<Brick*> bricksInLevel;

    //after the brick has been hit, it is no longer drawn. however, this vector will...
    //...allow us to do things to the brick (ex: play a sound) after it has been destroyed
    //once all the behaviors we want to happen have happened, brick dtor is called
    std::vector<Brick*> brickWaitVector;

    //fixes bug where, if a ball hits two bricks at the same, velocity recalculations...
    //...to send the ball in the other direction are ignored. this bool checks if...
    //...the ball already hit a brick. if it did, it can't hit any others
    bool ballHitBrick;

    //sets the layout of the bricks based on the xml file
    void setupBricksFromFile(const char* pathToXml);

};