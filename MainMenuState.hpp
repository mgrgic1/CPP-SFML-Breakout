#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Animation.hpp"

class MainMenuState : public State {

public:
	MainMenuState(GameToolsPtr tools, StatsTrackerPtr stats);

	void Start();

	void HandleInput(sf::Event ev);
	void Update(float dt);
	void Draw(float dt);


private:
	GameToolsPtr gameTools;
	StatsTrackerPtr stats;
	Animation bgAnim; //animating background

	sf::Sprite bgSprite;
	sf::Sprite playSprite;
	sf::Sprite exitSprite;

	sf::Text titleText;

};
