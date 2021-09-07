#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Paddle.hpp"
#include "Animation.hpp"
#include "Level.hpp"
#include "EndScene.hpp"

//multiple inheritance :O, this is because:
/*
	- ALL levels in our game are states, but not all states are levels. this type of state needs to be further defined
	- adds onto my existing logic for state manangement
	- further defines that this state will have level type attributes (rowCount, columnCount, etc)
	- allows me to use protected variables in the Level hpp while using Level's public functions to return these vars
*/
class Level3State : public State, public Level {

public:
	Level3State(const char* xmlPath, GameToolsPtr tools, StatsTrackerPtr stats);
	~Level3State();

	void Start();
	void Update(float dt);
	void HandleInput(sf::Event ev);
	void Draw(float dt);

private:
	GameToolsPtr gameTools;
	StatsTrackerPtr stats;
	Paddle* paddle;
	Animation animation;
	sf::Sprite background;

};