#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include "../headers/Player.hpp"
#include "../headers/Enemy.hpp"
#include "../headers/Bullet.hpp"
#include <sstream>

class Game
{
private:

    static constexpr float IG_WINDOW_WIDTH = 960.f;
    static constexpr float IG_WINDOW_HEIGHT = 600.f;

    std::stringstream intToString;

    sf::RenderWindow* igWindow;

    sf::Image igIslandChecker;
    sf::Color igWaterColor;

    sf::Texture igBackgroundTexture;
    sf::Sprite igBackground;

    sf::Texture igPlayerTexture;
    Player* igPlayer;

    sf::Texture igEnemyTexture;
    Enemy* igEnemy[10];
    int enemyQuota = 2;

    sf::Texture igReplayTexture;
    sf::Sprite igReplay;

    std::list<sf::CircleShape> igBlasts;

    sf::Texture igBulletTexture;
    std::list<Bullet> igBullets;
    int bulletDamage = 35;

    enum gameStates {Over, Running};

    gameStates igState;
    int score = 0;

    sf::Font igFont;
    sf::Text scoreText;
    sf::Text gameOverText;

    int deltaTime = 1000;
    sf::Clock frameClock;

public:

    Game();
    void start();

private:

    void initialize();
    void processEvents();
    void update();
    void render();
    void handleMouse(sf::Mouse::Button button, int x, int y);

    float distanceBetween(sf::Vector2f p1, sf::Vector2f p2);
};
