#include "Level1State.hpp"
#include "Level2State.hpp"

//Level1State xmlPath "gives" the information to the ctor in level, level does all the work
Level1State::Level1State(const char* xmlPath, GameToolsPtr tools, StatsTrackerPtr stats): Level(xmlPath, tools, stats) {
	this->gameTools = tools;
	stats->totalLives = 3; //setting initial lives when first level is first created
	paddle = new Paddle(gameTools, stats);
	this->stats = stats;
}

Level1State::~Level1State() {
	delete paddle;
}

void Level1State::Start() {
	gameTools->assetManager.LoadTexture("backgroundImg", pathToBackground);
	background.setTexture(gameTools->assetManager.GetTexture("backgroundImg"));

	sf::IntRect textureRect = sf::IntRect(0,0,1024,768);
	animation.loadAnimInfo(&textureRect, sf::Vector2i(spriteSheetRows,spriteSheetColumns),spriteSheetSeconds);
	
	animation.setLoop(true);

	headsUpDisplay->setLevel(onLevel);

}

void Level1State::HandleInput(sf::Event ev) {
	paddle->HandleInput(ev);

}

void Level1State::Update(float dt) {
	paddle->Update(dt);

	brickGroup->Update(paddle->getBall());

	if(brickGroup->allBricksDestroyed()) 
	{
		this->gameTools->stateManager.LoadState(std::unique_ptr<State>(new Level2State("Level2.xml",this->gameTools,this->stats)));
	}

	if(stats->totalLives == 0) 
	{
		goToEndScene(false);
	}


	headsUpDisplay->Update();
}

void Level1State::Draw(float dt) {

	gameTools->window->draw(background);
	animation.RunAnim(&background,dt);
	

	paddle->Draw();
	brickGroup->Draw(*gameTools->window);
	headsUpDisplay->Draw();
}
