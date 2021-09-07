#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include <iostream>

SplashState::SplashState(GameToolsPtr tools, StatsTrackerPtr stats) {
    this->gameTools = tools;
    this->stats = stats;
}

void SplashState::Start() {


	gameTools->assetManager.LoadFont("splashFont","Resources/Fonts/splashFont.ttf");

    logoText.setFont(gameTools->assetManager.GetFont("splashFont"));
    logoText.setCharacterSize(50);
    logoText.setFillColor(sf::Color::White);
    logoText.setStyle(sf::Text::Bold);
    logoText.setString("Demo");

    //get width and height of text area
    float width = logoText.getLocalBounds().width;
    float height = logoText.getLocalBounds().height;

    //sets the origin of the text to be in the exact center of its bounding area
    //(allows the text to always have a center origin regardless of char size)
    logoText.setOrigin(width/2, height/2);

    logoText.setPosition(1024/2, 768/4);

    goodBoyTex.loadFromFile("Resources/dogSplash.png");

    sf::IntRect textureRect = sf::IntRect(0,0,360,360);
    goodBoy.setTexture(goodBoyTex);
    goodBoy.setTextureRect(textureRect);

    //sets origin (center point) of sprite
	//regardless of scale or w/e the origin will always be in center of sprite
	sf::FloatRect rect = goodBoy.getGlobalBounds();

	goodBoy.setOrigin(sf::Vector2f(rect.width / 2, rect.height/2));
    goodBoy.setPosition(1024/2,768/1.5f);

    animation.loadAnimInfo(&textureRect, sf::Vector2i(4,3),1);

    if(effectBuffer.loadFromFile("Resources/Sounds/coin.wav")) 
    {
        std::cout << "Error loading sound effect!" << std::endl;
    }

    soundEffect.setBuffer(effectBuffer);
}

void SplashState::Update(float dt) 
{
    if(!played && clock.getElapsedTime().asSeconds() > 2) {
        played = true;
        soundEffect.play();
    }

    if(played && clock.getElapsedTime().asSeconds() > 5) {
        this->gameTools->stateManager.LoadState(std::unique_ptr<State>(new MainMenuState(this->gameTools,this->stats)));
    }

}

void SplashState::Draw(float dt) {

    this->gameTools->window->draw(this->logoText);
    this->gameTools->window->draw(this->goodBoy);


    if(!animation.IsCompleted() && clock.getElapsedTime().asSeconds() > 2) {
        animation.RunAnim(&goodBoy, dt);
    }



}