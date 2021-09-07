#include "Level.hpp"

//ctor for level
//sets up a level based on its xmlPath
//the derived class (Level1State, Level2State, etc) can then access variables about itself (row count, column count)
Level::Level(const char* xmlPath, GameToolsPtr tools, StatsTrackerPtr statsTool)
{
    gameTools = tools;

    tinyxml2::XMLDocument doc;
    doc.LoadFile(xmlPath);

    //access root element (Level) in XML doc
    tinyxml2::XMLElement* rootElement = doc.RootElement();

    onLevel = std::stoi(rootElement->Attribute("Number"));

    //get information about the level from XML doc
    pathToBackground = rootElement->Attribute("BackgroundTexture"); 

    spriteSheetRows = std::stoi(rootElement->Attribute("SpriteSheetRows"));
    spriteSheetColumns = std::stoi(rootElement->Attribute("SpriteSheetColumns"));
    spriteSheetSeconds = std::stoi(rootElement->Attribute("SpriteSheetSeconds"));

    brickGroup = new BrickGroup(xmlPath, tools, statsTool);
    headsUpDisplay = new HUD(tools, statsTool);

}

//cleans up pointers
Level::~Level() {
    delete brickGroup;
    delete headsUpDisplay;
}

void Level::goToEndScene(bool won) 
{
    //stop playing music
    gameTools->music.setPlay(false);

    //load scene
    gameTools->stateManager.LoadState(std::unique_ptr<State>(new EndScene(gameTools, won)));
}