#include "MovingObject.hpp"

class Player
:public MovingObject
{
public:

    Player(sf::Texture newTexture, sf::RenderWindow* newParenWindow);
    sf::Vector2f getShootPosition(float a, float b);
};
