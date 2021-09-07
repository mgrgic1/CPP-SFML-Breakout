#include "HUD.hpp"


HUD::HUD(GameToolsPtr tools, StatsTrackerPtr stats) 
{
    gameTools = tools;
    this->stats = stats;
    
    levelText.setFont(tools->assetManager.GetFont("splashFont"));
    livesText.setFont(tools->assetManager.GetFont("splashFont"));
    pointsText.setFont(tools->assetManager.GetFont("splashFont"));

    livesText.setCharacterSize(30);
    livesText.setFillColor(sf::Color::White);

    livesText.setPosition(10,0);

    levelText.setCharacterSize(30);
    levelText.setFillColor(sf::Color::White);

    pointsText.setCharacterSize(30);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition(1024 - pointsText.getGlobalBounds().width - 10,0); 
}


void HUD::Update() 
{
    livesText.setString("Lives: " + std::to_string(stats->totalLives));
    levelText.setString("Level: " + std::to_string(onLevel));
    pointsText.setString("Points: " + std::to_string(stats->totalPoints));

    //changes position based on how long the string is
    pointsText.setPosition(1024 - pointsText.getGlobalBounds().width - 10,0); 
    levelText.setPosition(1024/2 - levelText.getGlobalBounds().width/2,0);
}

void HUD::Draw() 
{
    gameTools->window->draw(livesText);
    gameTools->window->draw(pointsText);
    gameTools->window->draw(levelText);

}

void HUD::setLevel(int level) 
{
    onLevel = level;

    levelText.setPosition(1024/2 - levelText.getGlobalBounds().width/2,0);
}