#include "MainMenuState.hpp"
#include "Level1State.hpp"

MainMenuState::MainMenuState(GameToolsPtr tools, StatsTrackerPtr statsTool) {
	this->gameTools = tools;
	this->stats = statsTool;

	//begins playing music when we are in main menu
	gameTools->music.setPlay(true);
}


void MainMenuState::Start() {

	gameTools->assetManager.LoadFont("titleFont","Resources/Fonts/titleFont.ttf");

	titleText.setFont(gameTools->assetManager.GetFont("titleFont"));
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color::White);
    titleText.setString("BREAKOUT");

	//get width and height of text area
    float width = titleText.getGlobalBounds().width;
    float height = titleText.getGlobalBounds().height;

	//sets the origin of the text to be in the exact center of its bounding area
    //(allows the text to always have a center origin regardless of char size)
    titleText.setOrigin(width/2, height/2);
    titleText.setPosition(1024/2, 768/4);

	gameTools->assetManager.LoadTexture("MainMenuBG","Resources/backgroundSheet.png");
	gameTools->assetManager.LoadTexture("PlayButton","Resources/Play Button.png");
	gameTools->assetManager.LoadTexture("ExitButton","Resources/Exit Button.png");
	gameTools->assetManager.LoadTexture("HoverPlay", "Resources/Hover Play Button.png");
	gameTools->assetManager.LoadTexture("HoverExit", "Resources/Hover Exit Button.png");

	
	sf::IntRect textureRect = sf::IntRect(0,0,1024,768);
	bgSprite.setTexture(this->gameTools->assetManager.GetTexture("MainMenuBG"));
	bgSprite.setTextureRect(textureRect);


	bgAnim.loadAnimInfo(&textureRect, sf::Vector2i(10,10),2);
	bgAnim.setLoop(true);

	playSprite.setTexture(this->gameTools->assetManager.GetTexture("PlayButton"));
	exitSprite.setTexture(this->gameTools->assetManager.GetTexture("ExitButton"));
	
	float buttonWidth = playSprite.getGlobalBounds().width;
	float buttonHeight = playSprite.getGlobalBounds().height;

	playSprite.setPosition((1024/2) - buttonWidth/2,(768/2) -buttonHeight/2);
	exitSprite.setPosition((1024/2) - buttonWidth/2,playSprite.getPosition().y + playSprite.getGlobalBounds().height + 10);
}

void MainMenuState::HandleInput(sf::Event ev) {
	
	//was the play button clicked?
	if(this->gameTools->inputManager.IsSpriteClicked(playSprite, 0, *this->gameTools->window,ev))
	{
		this->gameTools->stateManager.LoadState(std::unique_ptr<State>(new Level1State("Level1.xml",this->gameTools,this->stats)));
	}

	//was the exit button clicked?
	else if(this->gameTools->inputManager.IsSpriteClicked(exitSprite, 0, *this->gameTools->window,ev))
	{
		this->gameTools->window->close();
	}

	//was the play button hovered over?
	if(this->gameTools->inputManager.MouseHoverSprite(playSprite,*this->gameTools->window))
	{
		playSprite.setTexture(this->gameTools->assetManager.GetTexture("HoverPlay"));	
	}
	//else, if mouse button has left the play button sprite, change the texture back
	else
	{
		playSprite.setTexture(this->gameTools->assetManager.GetTexture("PlayButton"));
	}

	//was the exit button hovered over?
	if(this->gameTools->inputManager.MouseHoverSprite(exitSprite,*this->gameTools->window))
	{
		exitSprite.setTexture(this->gameTools->assetManager.GetTexture("HoverExit"));	
	}
	//else, if mouse button has left the exit button sprite, change the texture back
	else
	{
		exitSprite.setTexture(this->gameTools->assetManager.GetTexture("ExitButton"));
	}

}

void MainMenuState::Update(float dt) {
	

}

void MainMenuState::Draw(float dt) {
	gameTools->window->draw(this->bgSprite);
	bgAnim.RunAnim(&bgSprite, dt);

	gameTools->window->draw(this->playSprite);
	gameTools->window->draw(this->exitSprite);

	gameTools->window->draw(this->titleText);

	


}
