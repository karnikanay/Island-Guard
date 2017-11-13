#include "../headers/MovingObject.hpp"
#define PI 3.14159265
#include <iostream>

MovingObject::MovingObject(sf::Texture newTexture, sf::RenderWindow* newParentWindow)
{
    objTexture = newTexture;
    objSprite.setTexture(objTexture);
    objSprite.setOrigin(objTexture.getSize().x/2, objTexture.getSize().y/2);

    parentWindow = newParentWindow;
}

void MovingObject::update()
{
    while(finalDir >= 360)
        finalDir -= 360;
    while(finalDir < 0)
        finalDir += 360;

    if(isRotating)
    {
        float difference = finalDir - objSprite.getRotation();

        if(abs((int)difference) > 178 || isForced)
        {
            objSprite.setRotation(finalDir);
        }
        else if(difference > 0)
        {
            if((finalDir - objSprite.getRotation()) > objAngVel)
                objSprite.rotate(objAngVel);
            else
            {
                objSprite.setRotation(finalDir);
                isRotating = false;
            }
        }
        else
        {
            if((objSprite.getRotation() - finalDir) > objAngVel)
            {
                objSprite.rotate(-objAngVel);
            }
            else
            {
                objSprite.setRotation(finalDir);
                isRotating = false;
            }
        }
    }

    if(isMoving)
    {
        if(doesStop)
            moveTo(finalPos.x, finalPos.y);
        if((abs((int)(finalPos.y - objSprite.getPosition().y)) >= 1) ||
           (abs((int)(finalPos.x - objSprite.getPosition().x)) >= 1) ||
           !doesStop)
        {
            move(+1);
        }
        else if(doesStop)
        {
            objSprite.setPosition(finalPos);
            isMoving = false;
        }
    }
}

void MovingObject::moveTo(float a, float b)
{
    finalPos.x = a;
    finalPos.y = b;

    double y = finalPos.y - objSprite.getPosition().y;
    double x = finalPos.x - objSprite.getPosition().x;

    finalDir = ((float)atan2(y,x)*180/PI);
    isRotating = true;
    isMoving = true;
}

void MovingObject::setDirection(float newDirection)
{
    objSprite.setRotation(newDirection);
}

void MovingObject::setPos(float a, float b)
{
    objSprite.setPosition(a, b);
}

void MovingObject::draw()
{
    parentWindow->draw(objSprite);
}

void MovingObject::move(int sign)
{
    if(sign < 0)
        isForced = true;
    else
        isForced = false;
    movement = sf::Vector2f(sign*cos(objSprite.getRotation()*PI/180.d)*objVel*dt/1000, sign*sin(objSprite.getRotation()*PI/180.d)*objVel*dt/1000);
    objSprite.move(movement);
}

sf::Vector2f MovingObject::getPosition()
{
    return objSprite.getPosition();
}

sf::FloatRect MovingObject::getBounds()
{
    return objSprite.getGlobalBounds();
}
