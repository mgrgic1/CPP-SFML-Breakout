#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class InputManager{

public:
	InputManager(){};
	~InputManager(){};

	//if hold is true, this will return true for as long as the player is holding down the mouse button
	bool IsSpriteClicked(sf::Sprite sprite, int mouseKey, sf::RenderWindow& window, sf::Event ev);

	bool MouseHoverSprite(sf::Sprite sprite, sf::RenderWindow& window);

	sf::Vector2i GetMousePosition(sf::RenderWindow& window);

	//returns the exact frame that the mouseButton was clicked
	bool GetMouseButtonDown(float mouseButton, sf::Event ev);

	//is the mouse within the window's bounds?
	bool inWindowBounds(sf::RenderWindow& window);

private:
	bool wasSpriteClicked = false;

};