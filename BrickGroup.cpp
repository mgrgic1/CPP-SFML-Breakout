#include "BrickGroup.hpp"


BrickGroup::BrickGroup(const char* pathToXml, GameToolsPtr tools, StatsTrackerPtr statsTool) 
{
    GameToolsPtr gameTools = tools;
    stats = statsTool;

    tinyxml2::XMLDocument doc;
    doc.LoadFile(pathToXml);

    //get the "brickTypes" node in the xml file
    tinyxml2::XMLElement* xmlBrickTypes = doc.RootElement()->FirstChildElement("BrickTypes");

    //loops through all child brickTypes and stores relevant information in our brickTypes map
    for(tinyxml2::XMLElement* childElem = xmlBrickTypes->FirstChildElement(); childElem != NULL; childElem = childElem = childElem->NextSiblingElement())  
    {
         //these four elements are common among all of our bricks. all of our bricks have these attributes
            std::string brickID = childElem->Attribute("Id");

            //rather than passing a string of the texturePath, it is stored in our asset manager
            //since the struct holds a reference to this texture, the reference will be stored...
            //...instead of the actual file location
            gameTools->assetManager.LoadTexture(brickID, childElem->Attribute("Texture"));
            
            int hitPoints = std::stoi(childElem->Attribute("HitPoints"));
            std::string hitSoundPath = childElem->Attribute("HitSound");

            //some bricks have the following attributes, and some dont. therefore, i had to...
            //...implement error handling to see if the attribute existed in the xml file
            //by default, they are empty strings. if a value exists, the empty string will be rewritten
            std::string damagedTexturePath = "";
            std::string breakSoundPath = "";
            int breakScore = 0;

            if(childElem->Attribute("DamagedTexture")) 
            {
                damagedTexturePath = childElem->Attribute("DamagedTexture");
            }

            if(childElem->Attribute("BreakSound")) 
            {
                breakSoundPath = childElem->Attribute("BreakSound");
            }

            if(childElem->Attribute("BreakScore")) 
            {
                breakScore = std::stoi(childElem->Attribute("BreakScore"));
            }

            //sets up new brick information
            BrickInfo brickInfo;
            
            brickInfo.brickID = brickID;

            //the reference to a specific brick texture (in our asset manager) is assigned
            //faster and better because storing textures for every brick is very expensive
            brickInfo.brickTexture = &gameTools->assetManager.GetTexture(brickID);
            brickInfo.damagedTexturePath = damagedTexturePath;
            brickInfo.hitPoints = hitPoints;
            brickInfo.hitSoundPath =  hitSoundPath;
            brickInfo.breakSoundPath = breakSoundPath;
            brickInfo.breakScore = breakScore;

            brickTypes.insert({brickID,brickInfo});

    }//end for loop that goes through xml document

    isFinished = false;

    rowCount = std::stoi(doc.RootElement()->Attribute("RowCount"));
    columnCount = std::stoi(doc.RootElement()->Attribute("ColumnCount"));

    //allocates space for all bricks in the level
    //all bricks in the level can be defined as row * column
    bricksInLevel.reserve(rowCount * columnCount);

    //after space has been reserved and all brick types have been identified, set up all bricks
    setupBricksFromFile(pathToXml);
}//end ctor


//draws bricks on the scene (called in each individual level)
void BrickGroup::Draw(sf::RenderWindow& window) 
{
    for(Brick* brick : bricksInLevel) 
    {
        brick->Draw(window);
    }
}

//updates the entire brick group
void BrickGroup::Update(Ball* ball) 
{
    //checks for collision with the ball
    for(Brick* brick : bricksInLevel) 
    {   
        //if the ball sprite collided with the brick sprite
        if(!ballHitBrick && ball->getSprite()->getGlobalBounds().intersects(brick->getSprite()->getGlobalBounds())) 
        {
            //checks where the ball collided
            //in order to change the ball's velocity appropriately, we have to check if...
            //...the ball hit the brick to the top,bottom,left,right of it
            //(because all hits to the brick output a different velocity for the ball)
            bool bottomHit = brick->getSprite()->getPosition().y + brick->getSprite()->getGlobalBounds().height <= ball->getSprite()->getPosition().y - ball->getSprite()->getGlobalBounds().height;
            bool RHit = brick->getSprite()->getPosition().x + brick->getSprite()->getGlobalBounds().width <= ball->getSprite()->getPosition().x - ball->getSprite()->getGlobalBounds().width;
            bool LHit =  brick->getSprite()->getPosition().x <= ball->getSprite()->getPosition().x - ball->getSprite()->getGlobalBounds().width;
            bool topHit = brick->getSprite()->getPosition().y <= ball->getSprite()->getPosition().y;

            if(bottomHit || topHit)
            {
                ball->setVelocity(-ball->getVelocity().x, -ball->getVelocity().y);
            }

            if(RHit || LHit) 
            {
                ball->setVelocity(-ball->getVelocity().x, ball->getVelocity().y);
            }

            //this code is called when a collision happens on the brick. if there's one hit left...
            //...when a collision happens, this means the brick will be broken
            if(brick->getHits() == 1) {
                brick->takeHit();
                brick->playBrickBreak();
                brickWaitVector.push_back(brick);

                stats->totalPoints += brick->getPoints();
                
                //erases brick from vector
                //it will not be drawn BUT IT IS NOT ERASED FROM THE SCENE
                bricksInLevel.erase(std::remove(bricksInLevel.begin(), bricksInLevel.end(),brick), bricksInLevel.end());
            }
            else {
                brick->takeHit();

                //play the sound associated with the brick
                brick->playBrickHit();
            }
        }//end ball brick collision if statement

        ballHitBrick = false;

        //checks if the level has finished
        //(exludes impenetrable bricks because they can't be destroyed. we check all other bricks)
        if((bricksInLevel.size() - impenBrickNum) == 0) 
        {
            isFinished = true;
        }
    }//end for loop
    
    
    //lets brick play a sound, once sound has finished playing, brick dtor is called
    for(Brick* brick : brickWaitVector) 
    {  
        //if a sound has finished playing, finally destroy the brick
        if(brick->getBreakSound()->getStatus() == sf::SoundSource::Stopped)
        {
            brickWaitVector.erase(std::remove(brickWaitVector.begin(), brickWaitVector.end(),brick), brickWaitVector.end());
            brick->~Brick();
        }

    }
    
    
    
}

//creates all of the bricks to be drawn in the current level
void BrickGroup::setupBricksFromFile(const char* pathToXml) 
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile(pathToXml);


    //brick "design" from the XML file
    //tells us the sequence/order of bricks for each row and column
    std::string brickDesign = doc.RootElement()->FirstChildElement("BrickTypes")->NextSiblingElement()->GetText();

    int onRow = 0; //by default, we are starting on the first row
    int onColumn = 0; //by default, we are starting on the first column

    //to get size of an individual brick texture before we place it
    //this will help figure out spacing between bricks (since bricks are placed exactly next to each other)
    sf::Texture tex;
    std::string baseTexturePath = "Resources/Bricks/Soft.png";
    tex.loadFromFile(baseTexturePath);
    int brickWidth = tex.getSize().x;
    int brickHeight = tex.getSize().y;

    //padding for each row and column
    //values will be passed in when we are creating a new brick and setting its position
    int rowPadding = std::stoi(doc.RootElement()->Attribute("RowPadding"));
    int columnPadding = std::stoi(doc.RootElement()->Attribute("ColumnPadding"));


    for(char designChar : brickDesign) 
    {
        //STRICTLY following rowCount and columnCount attributes in XML
        //if there a mismatch between the BrickDesign attribute and rowCount/columnCount...
        //...we break out of the loop. everything stops
        if(onRow > rowCount || onColumn > columnCount) {
            break;
        } 

        //individual characters to deal with
        //checks if there is a line break or empty space
        if(designChar == '\n' || isspace(designChar)) 
        {
            continue;
        }

        //checks if the read brick is impenetrable
        if(designChar == 'I') 
        {
            impenBrickNum++;
        }

        //if a row break is read (comma), go to the next row
        else if(designChar == ',') 
        {   
            onRow++;
            onColumn = 0;
            continue;
        }

        //empty spot
        else if(designChar == '_') 
        {
            onColumn++; //skip over this column
            continue;
        }

        //the brick we are using (based on ID)
        std::string designStr(1,designChar);
        BrickInfo brickInfo = brickTypes.find(designStr)->second;
        
        //F I N A L L Y, add brick to vector, passing in a start position
        bricksInLevel.push_back(new Brick(brickInfo, sf::Vector2i((onColumn * brickWidth) + columnPadding, (onRow * brickHeight) + rowPadding)));
    
        //after reading every letter, the column we are placing a block on increases by one
        onColumn++;
    }

}//end setupBricksFromFile

//destructor
//since we allocated space in our vector of pointers, they must be deallocated
BrickGroup::~BrickGroup() 
{
    if(bricksInLevel.size() > 0) {
        for(Brick* brick : bricksInLevel) {
            delete brick;
        }
    }

    if(brickWaitVector.size() > 0)
    {
        for(Brick* brick : brickWaitVector) {
            delete brick;
        } 
    }


}