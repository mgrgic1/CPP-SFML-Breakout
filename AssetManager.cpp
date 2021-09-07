#include "AssetManager.hpp"

void AssetManager::LoadTexture(std::string name, std::string filePath) {
	sf::Texture tex;

	if(tex.loadFromFile(filePath)) {
		this->textureMap[name] = tex;
	}
}

void AssetManager::LoadFont(std::string name, std::string filePath) {
	sf::Font font;

	if(font.loadFromFile(filePath)) {
		this->fontMap[name] = font;
	}
}



sf::Texture &AssetManager::GetTexture(std::string name) {
	return this->textureMap.at(name);
}

sf::Font &AssetManager::GetFont(std::string name) {
	return this->fontMap.at(name);
}