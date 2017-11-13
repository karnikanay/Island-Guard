#include "../headers/Enemy.hpp"
#include <time.h>
#include <random>
#include <iostream>

Enemy::Enemy(sf::Texture newTexture, sf::RenderWindow* newParentWindow)
:MovingObject(newTexture, newParentWindow)
{
    static std::random_device rd;
    srand(rd()+rand()+time(NULL));

    totalHealth = 100 + (rand()%50);
    health = totalHealth;

    if(rand() % 2 == 0)
    {
        int x;
        int y;

        x = rand() % (int)parentWindow->getSize().x;
        y = (rand() % 2)*(int)(parentWindow->getSize().y);

        objSprite.setPosition(x, y);
    }
    else
    {
        int x;
        int y;

        x = (rand() % 2)*(int)(parentWindow->getSize().x);
        if(x == (int)(parentWindow->getSize().x))
            objSprite.setRotation(180);
        y = rand() % (int)parentWindow->getSize().y;

        objSprite.setPosition(x, y);
    }

    objAngVel = 0.02;
    objVel = 0.03 + (rand()%5)/100;

    totalHealthBar.setSize(sf::Vector2f(30, 5));
    totalHealthBar.setPosition(objSprite.getPosition().x - totalHealthBar.getSize().x/2, objSprite.getPosition().y - objTexture.getSize().y/2 - 14);
    totalHealthBar.setFillColor(sf::Color::Red);
    totalHealthBar.setOutlineColor(sf::Color::Black);
    totalHealthBar.setOutlineThickness(0.5f);

    healthBar.setSize(sf::Vector2f(30, 5));
    healthBar.setPosition(totalHealthBar.getPosition());
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setOutlineColor(sf::Color::Black);
    healthBar.setOutlineThickness(0.2f);
}

bool Enemy::hit(int damage)
{
    health -= damage;
    healthBar.setSize(sf::Vector2f(totalHealthBar.getSize().x*health/totalHealth, totalHealthBar.getSize().y));
    if(health <= 0)
        return true;
    else
        return false;
}

void Enemy::move(int sign)
{
    MovingObject::move(sign);
    healthBar.move(movement);
    totalHealthBar.move(movement);
}

void Enemy::draw()
{
    MovingObject::draw();
    parentWindow->draw(totalHealthBar);
    parentWindow->draw(healthBar);
}

void Enemy::update()
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
