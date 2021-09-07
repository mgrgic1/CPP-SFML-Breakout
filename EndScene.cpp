#include "EndScene.hpp"
#include <iostream>

EndScene::EndScene(GameToolsPtr tools, bool won) {
    gameTools = tools;
    this->won = won;

    if(won) 
    {
        if(!buffer.loadFromFile("Resources/Sounds/finishGame.wav")) 
        {
            std::cout<<"Unable to load finish game wav!" << std::endl;
        }
    }
    else 
    {
        if(!buffer.loadFromFile("Resources/Sounds/loseGame.wav")) 
        {
            std::cout<<"Unable to load lose game wav!" << std::endl;
        }
    }


    mainText.setFont(gameTools->assetManager.GetFont("splashFont"));
    mainText.setCharacterSize(50);
    mainText.setFillColor(sf::Color::White);
    mainText.setStyle(sf::Text::Bold);
    mainText.setString("You " + std::string(won ? "won!" : "lost!"));

    //get width and height of text area
    float width = mainText.getLocalBounds().width;
    float height = mainText.getLocalBounds().height;

    //sets the origin of the text to be in the exact center of its bounding area
    //(allows the text to always have a center origin regardless of char size)
    mainText.setOrigin(width/2, height/2);

    mainText.setPosition(1024/2, 768/4);

    sound.setBuffer(buffer);
    sound.setLoop(false);
    sound.play();

    clock = new sf::Clock();
}


void EndScene::Draw(float dt) 
{
    gameTools->window->draw(mainText);

    if(clock->getElapsedTime().asSeconds() > (won ? 10 : 3))
    {
        gameTools->window->close();
    }
}

EndScene::~EndScene() {
    delete clock;
}