#ifndef __MOVING_OBJECT__
#define __MOVING_OBJECT__

#include <SFML/Graphics.hpp>

class MovingObject
{
protected:

    sf::RenderWindow* parentWindow;

    sf::Texture objTexture;
    sf::Sprite objSprite;

    float objVel = 0.f;
    float objAngVel = 0.f;
    float finalDir = 0.f;
    sf::Vector2f finalPos = sf::Vector2f(0.f, 0.f);

    bool isMoving = false;
    bool isRotating = false;
    bool isForced = false;
    bool doesStop = true;

    float velocityX;
    float velocityY;

    sf::Vector2f movement = sf::Vector2f(0.f, 0.f);

public:

    MovingObject(sf::Texture newTexture, sf::RenderWindow* newParenWindow);
    void update();
    void moveTo(float a, float b);
    void move(int sign);
    void setDirection(float newDirection);
    void setPos(float a, float b);
    void draw();
    sf::Vector2f getPosition();
    sf::FloatRect getBounds();
    int dt = 1000;

};

#endif // __MOVING_OBJECT__
