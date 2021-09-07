#pragma once
#include <string>
#include "tinyxml2.h" //reading XML files
#include "BrickGroup.hpp"
#include "HUD.hpp"
#include "EndScene.hpp"

class Level {

public:
    //will load all necessary information about a specific level GIVEN the path to the xml file
    Level(const char* xmlPath, GameToolsPtr tools, StatsTrackerPtr stats);
    ~Level();

//information that only derived classes can view/modify
protected:
    int spriteSheetRows; //rows in the sprite sheet
    int spriteSheetColumns;//columns in the sprite sheet
    int spriteSheetSeconds; //duration of how long the sprite sheet will play (in seconds)
    int onLevel;
    std::string pathToBackground; //path to background

    void goToEndScene(bool won);

    BrickGroup* brickGroup; //represents all bricks in the level
    HUD* headsUpDisplay;

private:
    GameToolsPtr gameTools;
};