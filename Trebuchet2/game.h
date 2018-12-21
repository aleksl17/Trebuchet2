#ifndef GAME_H
#define GAME_H

#include <list>
#include <vector>
#include <iterator>
#include <memory>
#include <stack>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "map/map.h"
#include "projectile/projectile.h"
#include "objects/catapult.h"

class Object;

class Game {
public:
    bool init();

    void run();

    std::vector<projectile> bullets;

    std::vector<catapult> catapults;

protected:
    bool gameTick(sf::RenderWindow &window, std::list<std::shared_ptr<Object>> &objects, float deltaTime);

    // List of game objects
    std::list<std::shared_ptr<Object>> objects;

    sf::Clock clock;

    sf::Font font;

    sf::FloatRect textRect;

    sf::Text text;

    sf::Texture texture;

    sf::Texture victoryTexture;

    sf::Sprite background;

    sf::Sprite victoryBackground;

    sf::RenderWindow window;

    sf::View view;

    sf::View uiView;

    Map map;

};

#endif
