#include "../headers/ResourceManager.hpp"

void ResourceManager::loadResources()
{
    // Load the textures
    background.loadFromFile("resources/images/background.png");
}

sf::Texture ResourceManager::getBackgroundTexture()
{
    return background;
}
