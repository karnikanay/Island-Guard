#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../headers/Game.hpp"

class Menu
{
private:

    sf::RenderWindow* igWindow;
    Game* igGame;

public:

    Menu();

    void start();
    void processEvents();
    void update();
    void render();

};
