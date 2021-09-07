#include <SFML/Graphics.hpp>

struct BrickInfo {

std::string brickID;
sf::Texture* brickTexture;
std::string damagedTexturePath;
int hitPoints;
std::string hitSoundPath;
std::string breakSoundPath;
int breakScore;

};