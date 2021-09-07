#include "Game.hpp"
#include "SplashState.hpp"


Game::Game() {

    sf::VideoMode videoMode;
    videoMode.width = 1024;
    videoMode.height = 768;
    this->mainWindow = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(videoMode, "Breakout", sf::Style::Titlebar | sf::Style::Close));

    this->mainWindow->setFramerateLimit(60);


    gameTools = std::make_shared<GameTools>();
    stats = std::make_shared<StatsTracker>();
    this->gameTools->stateManager.LoadState(std::unique_ptr<State>(new SplashState(this->gameTools,this->stats)));
    this->gameTools->window = this->mainWindow;
}


void Game::Update() {

    //special separate case
    //since music is played throughout the game, it is unique from the other states
    //the most fundamental scene it can play on is the actual game window rather than other states
    if(gameTools->music.getPlay()) 
    {
        gameTools->music.Update();
    }

    this->gameTools->stateManager.ProcessStateChanges();

    this->gameTools->stateManager.CurrentState()->Update(clock.restart().asSeconds());

}

void Game::Render() {
	this->mainWindow->clear();

	//Draw active scene, giving delta seconds as parameter
    this->gameTools->stateManager.CurrentState()->Draw(clock.restart().asSeconds());
	this->mainWindow->display();

}


void Game::CheckInput() {

    //event polling
    while(this->gameTools->window->pollEvent(this->gameTools->ev)) {
            switch(this->gameTools->ev.type) 
            {
                case sf::Event::Closed:
                    this->mainWindow->close();
                    break;
                case sf::Event::KeyPressed:
                    if(this->gameTools->ev.key.code == sf::Keyboard::Escape) 
                    {
                        this->mainWindow->close();
                    }
                    else if(this->gameTools->ev.key.code == sf::Keyboard::M) 
                    {
                        this->gameTools->music.setPlay(!this->gameTools->music.getPlay());
                    }


                    break;
            }
        }



    this->gameTools->stateManager.CurrentState()->HandleInput(gameTools->ev);

}



const bool Game::isRunning() const {
	return this->mainWindow->isOpen();
}