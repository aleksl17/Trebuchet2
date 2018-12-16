#ifndef GAME_H
#define GAME_H

#include <list>
#include "projectile/projectile.h"
#include <iterator>


#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

#include "map/map.h"

#include <vector>

class Object;

class Game {
public:
    bool init();
    void run();
    //std::queue<projectile> bullets;
    std::vector<projectile> bullets;



protected:
    bool gameTick(sf::RenderWindow& window, std::list<std::shared_ptr<Object>>& objects, float deltaTime);

    // List of game objects. Should of course be put somewhere else in a bigger game
    std::list<std::shared_ptr<Object>> objects;
    sf::Clock clock;

    sf::RenderWindow window;

    sf::View view;

    Map map;
};

#endif
