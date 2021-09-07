#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.hpp"
#include <string>


class EndScene : public State{

public:
    EndScene(GameToolsPtr tools, bool won);
    ~EndScene();

    void Start(){};
    void HandleInput(sf::Event ev){};
    void Update(float dt){};
    void Draw(float dt);


private:
	sf::Clock* clock; 
    GameToolsPtr gameTools;
    bool won;

    sf::Text mainText;

    sf::SoundBuffer buffer;
    sf::Sound sound;

};