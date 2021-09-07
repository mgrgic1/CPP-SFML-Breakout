#include "Level2State.hpp"
#include "Level3State.hpp"

//Level2State xmlPath "gives" the information to the ctor in level, level does all the work
Level2State::Level2State(const char* xmlPath, GameToolsPtr tools, StatsTrackerPtr stats): Level(xmlPath, tools, stats) {
	this->gameTools = tools;
	paddle = new Paddle(gameTools, stats);
	this->stats = stats;
}

Level2State::~Level2State() {
	delete paddle;
}

void Level2State::Start() {
	gameTools->assetManager.LoadTexture("backgroundImg", pathToBackground);
	background.setTexture(gameTools->assetManager.GetTexture("backgroundImg"));

	sf::IntRect textureRect = sf::IntRect(0,0,1024,768);
	animation.loadAnimInfo(&textureRect, sf::Vector2i(spriteSheetRows,spriteSheetColumns),spriteSheetSeconds);
	
	animation.setLoop(true);

	headsUpDisplay->setLevel(onLevel);

}

void Level2State::HandleInput(sf::Event ev) {
	paddle->HandleInput(ev);

}

void Level2State::Update(float dt) {
	paddle->Update(dt);

	brickGroup->Update(paddle->getBall());

	if(brickGroup->allBricksDestroyed()) 
	{
		this->gameTools->stateManager.LoadState(std::unique_ptr<State>(new Level3State("Level3.xml",this->gameTools,this->stats)));
	}

	if(stats->totalLives == 0) 
	{
		goToEndScene(false);
	}


	headsUpDisplay->Update();
}

void Level2State::Draw(float dt) {

	gameTools->window->draw(background);
	animation.RunAnim(&background,dt);
	

	paddle->Draw();
	brickGroup->Draw(*gameTools->window);
	headsUpDisplay->Draw();
}
