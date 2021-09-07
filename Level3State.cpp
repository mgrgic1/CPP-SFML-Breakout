#include "Level3State.hpp"
#include "EndScene.hpp"

//Level3State xmlPath "gives" the information to the ctor in level, level does all the work
Level3State::Level3State(const char* xmlPath, GameToolsPtr tools, StatsTrackerPtr stats): Level(xmlPath, tools, stats) {
	this->gameTools = tools;
	paddle = new Paddle(gameTools, stats);
	this->stats = stats;
}

Level3State::~Level3State() {
	delete paddle;
}

void Level3State::Start() {
	gameTools->assetManager.LoadTexture("backgroundImg", pathToBackground);
	background.setTexture(gameTools->assetManager.GetTexture("backgroundImg"));

	sf::IntRect textureRect = sf::IntRect(0,0,1024,768);
	animation.loadAnimInfo(&textureRect, sf::Vector2i(spriteSheetRows,spriteSheetColumns),spriteSheetSeconds);
	
	animation.setLoop(true);

	headsUpDisplay->setLevel(onLevel);

}

void Level3State::HandleInput(sf::Event ev) {
	paddle->HandleInput(ev);

}

void Level3State::Update(float dt) {
	paddle->Update(dt);

	brickGroup->Update(paddle->getBall());

	if(brickGroup->allBricksDestroyed()) 
	{
		this->gameTools->music.setPlay(false);
		this->gameTools->stateManager.LoadState(std::unique_ptr<State>(new EndScene(gameTools, true)));
	}

	if(stats->totalLives == 0) 
	{
		goToEndScene(false);
	}


	headsUpDisplay->Update();
}

void Level3State::Draw(float dt) {

	gameTools->window->draw(background);
	animation.RunAnim(&background,dt);
	

	paddle->Draw();
	brickGroup->Draw(*gameTools->window);
	headsUpDisplay->Draw();
}
