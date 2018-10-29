#ifndef GAME_H
#define GAME_H

#include <list>


#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

#include "map/map.h"

class Object;

class Game {
public:
    bool init();
    void run();

protected:
    bool gameTick(sf::RenderWindow& window, std::list<std::shared_ptr<Object>>& objects, float deltaTime);

    // List of game objects. Should of course be put somewhere else in a bigger game
    std::list<std::shared_ptr<Object>> objects;
    sf::Clock clock;

    sf::RenderWindow window;

    Map map;
};

#endif
