#include "InputManager.hpp"

//was the sprite CLICKED (not held)
//int mouseKey can be 0 or 1 --> 0 being left, 1 being right mouse button
bool InputManager::IsSpriteClicked(sf::Sprite sprite, int mouseKey, sf::RenderWindow& window, sf::Event ev) {
	
	sf::IntRect tempRect(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);


	/*
	if:
		the mouse is in the temporary rectangle box we created above (which represents the sprite) 
		the event type is a mouse button pressed
		the wasSpriteClicked bool is false (meaning we did not click L or R mouse button)
	*/
	if(tempRect.contains(sf::Mouse::getPosition(window)) && ev.type == sf::Event::MouseButtonPressed && !wasSpriteClicked) {
		if(mouseKey == 0 && ev.key.code == sf::Mouse::Left) {
			wasSpriteClicked = true;
			return true;
		}
		if(mouseKey == 1 && ev.key.code == sf::Mouse::Right) {
			wasSpriteClicked = true;
			return true;
		}
	}

	else if(wasSpriteClicked && ev.type == sf::Event::MouseButtonReleased) {
		wasSpriteClicked = false;
		return false;
	}

return false;
}//end isSpriteClicked function

bool InputManager::GetMouseButtonDown(float mouseButton, sf::Event ev) 
{
	bool leftClicked = mouseButton == 0 && ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Left;
	bool rightClicked =  mouseButton == 1 && ev.type == sf::Event::MouseButtonPressed && ev.key.code == sf::Mouse::Right;
	if(leftClicked || rightClicked) {
		return true;
	} 
	else return false;


	
}



//returns mouse position on the screen
sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window) {
	return sf::Mouse::getPosition(window);
}



bool InputManager::MouseHoverSprite(sf::Sprite sprite, sf::RenderWindow& window)
{
	sf::IntRect tempRect(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

	if(tempRect.contains(sf::Mouse::getPosition(window))) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool InputManager::inWindowBounds(sf::RenderWindow& window) {

	//is the mouse inside the window (x axis)
	bool insideX = sf::Mouse::getPosition(window).x > 0 && sf::Mouse::getPosition(window).x < window.getSize().x;
	bool insideY = sf::Mouse::getPosition(window).y > 0 && sf::Mouse::getPosition(window).y < window.getSize().y;

	if(insideX && insideY) 
	{
		return true;
	}
	else return false;
	
}