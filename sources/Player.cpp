#include "../headers/Player.hpp"
#define PI 3.14159265

Player::Player(sf::Texture newTexture, sf::RenderWindow* newParentWindow)
:MovingObject(newTexture, newParentWindow)
{
    objAngVel = 1;
    objVel = 0.5;
}

sf::Vector2f Player::getShootPosition(float a, float b)
{
    double y = b - objSprite.getPosition().y;
    double x = a - objSprite.getPosition().x;

    double direction = atan2(y,x)*180/PI;

    objSprite.setRotation((float)direction);

    float distance = objTexture.getSize().x/2 + 1;

    return sf::Vector2f(objSprite.getPosition().x + (float)cos(direction)*distance, objSprite.getPosition().y + (float)sin(direction)*distance);
}
