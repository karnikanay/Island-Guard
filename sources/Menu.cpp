#include "../headers/Menu.hpp"

Menu::Menu()
{
    igWindow = new sf::RenderWindow(sf::VideoMode(Game::IG_WINDOW_WIDTH, Game::IG_WINDOW_HEIGHT), "Island Guard");
}

void Menu::start()
{
    igGame = new Game(igWindow);
    while(igWindow->isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Menu::processEvents()
{
    igGame->processEvents();
}

void Menu::update()
{
    if(igGame->getState() == Game::Running)
    {
        igGame->update();
    }
    else if(igGame->getState() == Game::Over)
    {

    }
}

void Menu::render()
{
    igGame->render();
}
