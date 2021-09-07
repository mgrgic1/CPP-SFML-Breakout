#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "StateManager.hpp"
#include "InputManager.hpp"
#include "Music.hpp"

struct GameTools {
	AssetManager assetManager;
	StateManager stateManager;
	InputManager inputManager;
	Music music;

	std::shared_ptr<sf::RenderWindow> window;

	sf::Event ev;
};

struct StatsTracker {
	int totalPoints;
	int totalLives;
};

typedef std::shared_ptr<GameTools> GameToolsPtr;
typedef std::shared_ptr<StatsTracker> StatsTrackerPtr;

//main game manager
class Game {

public:
	Game();
	~Game(){};

	void CheckInput();
	void Update();
	void Render();

	const bool isRunning() const;

private:
	std::shared_ptr<sf::RenderWindow> mainWindow;

	GameToolsPtr gameTools;
	StatsTrackerPtr stats;
	sf::Clock clock;


};