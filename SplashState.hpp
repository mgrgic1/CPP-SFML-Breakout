#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Animation.hpp"

class SplashState : public State {

public:
    SplashState(GameToolsPtr tools, StatsTrackerPtr stats);
	void Start();

	void HandleInput(sf::Event ev){};
	void Update(float dt);
	void Draw(float dt);

private:
    GameToolsPtr gameTools;
	StatsTrackerPtr stats;
	Animation animation;

	//was the sound effect played?
	//used for playing once in update function (since we want it to play at the same time as wink )
	bool played = false;

	sf::Text logoText;
	
	sf::Sprite goodBoy; // ;)
	sf::Texture goodBoyTex;

	//tracks when we get to see the good boy wink ::DDD
	//slight delay between start of scene and wink AND wink to switch scene
	sf::Clock clock; 

    sf::SoundBuffer effectBuffer;
	sf::Sound soundEffect; //coin sound effect

};