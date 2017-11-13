#include "../headers/Bullet.hpp"

Bullet::Bullet(sf::Texture newTexture, sf::RenderWindow* newParentWindow, sf::Vector2f bulletPosition, sf::Vector2f bulletTarget)
:MovingObject(newTexture, newParentWindow)
{
    objVel = 1.2f;
    objAngVel = 360;

    objSprite.setPosition(bulletPosition);
    moveTo(bulletTarget.x, bulletTarget.y);

    doesStop = false;
}
