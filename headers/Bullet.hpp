#include "MovingObject.hpp"

class Bullet
: public MovingObject
{
public:

    Bullet(sf::Texture newTexture, sf::RenderWindow* newParentWindow, sf::Vector2f bulletPosition, sf::Vector2f bulletTarget);
};
