#include <SFML/Graphics.hpp>

class ResourceManager
{
private:

    sf::Texture background;

public:

    void loadResources();

    sf::Texture getBackgroundTexture();
};
