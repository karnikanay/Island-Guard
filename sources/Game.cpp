#include "../headers/Game.hpp"
#include <iostream>
#include "../headers/MovingObject.hpp"

Game::Game()
{
    igWindow = new sf::RenderWindow(sf::VideoMode(IG_WINDOW_WIDTH, IG_WINDOW_HEIGHT), "Island Guard");

    // Load the game resources
    igBackgroundTexture.loadFromFile("resources/images/background.png");
    igPlayerTexture.loadFromFile("resources/images/player.png");
    igEnemyTexture.loadFromFile("resources/images/enemy.png");
    igBulletTexture.loadFromFile("resources/images/bullet.png");
    igReplayTexture.loadFromFile("resources/images/replay.png");
    igFont.loadFromFile("resources/Arctik 5.ttf");

    igBackground.setTexture(igBackgroundTexture);
    igReplay.setTexture(igReplayTexture);
    igReplay.setOrigin(igReplayTexture.getSize().x/2, igReplayTexture.getSize().y/2);
    igReplay.setPosition(IG_WINDOW_WIDTH/2, IG_WINDOW_HEIGHT/2);

    initialize();

    scoreText.setFont(igFont);
    scoreText.setColor(sf::Color(200, 20, 20, 120));
    scoreText.setCharacterSize(50);
    scoreText.setPosition(IG_WINDOW_WIDTH/2 - 70, 10);

    gameOverText.setFont(igFont);
    gameOverText.setColor(sf::Color(127, 13, 0, 255));
    gameOverText.setCharacterSize(100);
    gameOverText.setPosition(IG_WINDOW_WIDTH/2 - 200, 50);
    gameOverText.setString("GAME OVER");

}

void Game::processEvents()
{
    sf::Event e;
    while(igWindow->pollEvent(e))
    {
        switch(e.type)
        {
        case sf::Event::Closed:
            igWindow->close();
            break;
        case sf::Event::MouseButtonPressed:
            handleMouse(e.mouseButton.button, e.mouseButton.x, e.mouseButton.y);
        default:
            break;
        }
    }
}

void Game::start()
{
    while(igWindow->isOpen())
    {
        frameClock.restart();
        processEvents();
        update();
        render();
        deltaTime = frameClock.getElapsedTime().asMicroseconds();
    }
}

void Game::update()
{
    if(igState == gameStates::Running)
    {
        igPlayer->update();
        if(igIslandChecker.getPixel((int)igPlayer->getPosition().x, (int)igPlayer->getPosition().y) == igWaterColor)
        {
            igPlayer->move(-1);
        }

        for(std::list<Bullet>::iterator it = igBullets.begin(); it != igBullets.end(); it++)
        {
            it->update();
        }

        for(int i = 0; i < enemyQuota; i++)
        {
            igEnemy[i]->moveTo(igPlayer->getPosition().x, igPlayer->getPosition().y);
            igEnemy[i]->update();
            if(igIslandChecker.getPixel((int)igEnemy[i]->getPosition().x, (int)igEnemy[i]->getPosition().y) != igWaterColor)
            {
                sf::CircleShape blast;
                blast.setRadius(40.f);
                blast.setOrigin(blast.getRadius(), blast.getRadius());
                blast.setFillColor(igWaterColor);
                igEnemy[i]->move(-1);
                blast.setPosition(igEnemy[i]->getPosition());
                igBlasts.push_back(blast);
                for(int i = (int)(blast.getPosition().x - blast.getRadius()); i < blast.getPosition().x + blast.getRadius(); i++)
                {
                    for(int j = (int)(blast.getPosition().y - blast.getRadius()); j < blast.getPosition().y + blast.getRadius(); j++)
                    {
                        if(distanceBetween(blast.getPosition(), sf::Vector2f((float)i,(float)j)) <= blast.getRadius())
                            igIslandChecker.setPixel(i, j, igWaterColor);
                    }
                }
                delete igEnemy[i];
                igEnemy[i] = new Enemy(igEnemyTexture, igWindow);
                if(distanceBetween(blast.getPosition(), igPlayer->getPosition()) <= blast.getRadius())
                    igState = Game::Over;
            }

            for(std::list<Bullet>::iterator it = igBullets.begin(); it != igBullets.end(); it++)
            {
                if(igEnemy[i]->getBounds().intersects(it->getBounds()))
                {
                    if(igEnemy[i]->hit(bulletDamage))
                    {
                        delete igEnemy[i];
                        igEnemy[i] = new Enemy(igEnemyTexture, igWindow);
                        score += 20;
                    }
                    delete &it;
                    it = igBullets.erase(it);
                    it--;
                }
            }
        }

        int oldEnemyQuota = enemyQuota;
        enemyQuota = 2 + (int)(score/100);
        std::cout << enemyQuota << std::endl;
        for(int i = 0; i < enemyQuota - oldEnemyQuota; i++)
        {
            if(enemyQuota < 10)
            {
                igEnemy[i+oldEnemyQuota] = new Enemy(igEnemyTexture, igWindow);
            }
        }

        for(std::list<Bullet>::iterator it = igBullets.begin(); it != igBullets.end(); it++)
        {
            if(it->getPosition().x < 0 ||
               it->getPosition().x > igWindow->getSize().x ||
               it->getPosition().y < 0 ||
               it->getPosition().y > igWindow->getSize().y)
            {
                delete &it;
                it = igBullets.erase(it);
                it--;
            }
        }
    }
    else if(igState = gameStates::Over)
    {

    }
    igPlayer->dt = deltaTime;
    for(std::list<Bullet>::iterator it = igBullets.begin(); it != igBullets.end(); it++)
    {
        it->dt = deltaTime;
    }
    for(int i = 0; i < enemyQuota; i++)
    {
        igEnemy[i]->dt = deltaTime;
    }

    intToString << "Score: " << score;
    scoreText.setString(intToString.str());
    intToString.str("");
}

void Game::render()
{
    igWindow->clear(sf::Color(128, 128, 128));

    igWindow->draw(igBackground);

    for(std::list<sf::CircleShape>::iterator it = igBlasts.begin(); it != igBlasts.end(); it++)
    {
        igWindow->draw(*it);
    }

    for(std::list<Bullet>::iterator it = igBullets.begin(); it != igBullets.end(); it++)
    {
        it->draw();
    }

    igPlayer->draw();
    for(int i = 0; i < enemyQuota; i++)
    {
        igEnemy[i]->draw();
    }

    igWindow->draw(scoreText);

    if(igState == gameStates::Over)
    {
        igWindow->draw(gameOverText);
        igWindow->draw(igReplay);
    }

    igWindow->display();
}

void Game::handleMouse(sf::Mouse::Button button, int x, int y)
{
    Bullet* bullet;
    switch(button)
    {
    case sf::Mouse::Left:
        igPlayer->moveTo((float)x, (float)y);
        if(igState == gameStates::Over)
        {
            if(igReplay.getGlobalBounds().contains(x, y))
            {
                initialize();
            }
        }
        break;
    case sf::Mouse::Right:
        bullet = new Bullet(igBulletTexture, igWindow, igPlayer->getShootPosition(x, y), sf::Vector2f(x, y));
        igBullets.push_back(*bullet);
        break;
    default:
        break;
    }
}

float Game::distanceBetween(sf::Vector2f p1, sf::Vector2f p2)
{
    int distance = sqrt((double)((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y)));
    return distance;
}

void Game::initialize()
{
    igState = Game::Running;

    igPlayer = new Player(igPlayerTexture, igWindow);
    igPlayer->setPos(IG_WINDOW_WIDTH/2, IG_WINDOW_HEIGHT/2);

    enemyQuota = 2;

    for(int i = 0; i < enemyQuota; i++)
    {
        igEnemy[i] = new Enemy(igEnemyTexture, igWindow);
    }

    igBullets.clear();
    igBlasts.clear();
    igIslandChecker = igBackgroundTexture.copyToImage();
    igWaterColor = igIslandChecker.getPixel(1, 1);
}
