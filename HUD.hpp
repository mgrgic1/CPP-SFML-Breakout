#include <SFML/Graphics.hpp>
#include "Game.hpp"

class HUD {
    
public:
    HUD(GameToolsPtr tools, StatsTrackerPtr stats);
    ~HUD(){};

    void Draw(); //draws hud on the screen
    void Update(); //checks for variable changes

    void setLevel(int level); //sets level for level text

private:
    GameToolsPtr gameTools;
    StatsTrackerPtr stats;
    sf::Text levelText;
    sf::Text livesText;
    sf::Text pointsText; 

    int onLevel = 0;
    int points = 0;
    int lives = 0;




};