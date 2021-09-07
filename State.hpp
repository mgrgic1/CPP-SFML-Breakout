#pragma once
#include <SFML/Graphics.hpp>

class State {

public:
	virtual void Start() = 0;
	virtual void HandleInput(sf::Event ev) = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(float dt) = 0;

	virtual void Pause(){};
	virtual void Resume(){};
};