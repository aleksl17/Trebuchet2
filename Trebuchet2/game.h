#ifndef GAME_H
#define GAME_H

#include <list>
#include <vector>
#include <iterator>
#include <memory>
#include <stack>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

#include "map/map.h"
#include "projectile/projectile.h"

class Object;

class Game {
public:
    bool init();
    void run();
    //std::queue<projectile> bullets;
    std::vector<projectile> bullets;

protected:
    bool gameTick(sf::RenderWindow& window, std::list<std::shared_ptr<Object>>& objects, float deltaTime);

    // List of game objects
    std::list<std::shared_ptr<Object>> objects;
    sf::Clock clock;

    sf::Font font;

    sf::FloatRect textRect;

    sf::Text text;

    sf::RenderWindow window;

    sf::View view;

    Map map;
};

#endif
