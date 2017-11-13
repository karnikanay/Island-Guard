#include "MovingObject.hpp"

class Enemy
: public MovingObject
{
private:

    int totalHealth;
    int health;

public:

    Enemy(sf::Texture newTexture, sf::RenderWindow* newParentWindow);
    bool hit(int damage);
    sf::RectangleShape totalHealthBar;
    sf::RectangleShape healthBar;
    void move(int sign);
    void draw();
    void update();
};
