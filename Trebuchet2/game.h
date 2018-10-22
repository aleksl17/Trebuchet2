#ifndef TREBUCHET2_GAME_H
#define TREBUCHET2_GAME_H

#include <list>


#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

class Object;

class Game {
public:
    bool init();
    void run();

protected:
    bool gameTick(sf::RenderWindow& window, std::list<Object*>& objects, float deltaTime);

    // List of game objects. Should of course be put somewhere else in a bigger game
    std::list<Object*> objects;
    sf::Clock clock;

    sf::RenderWindow window;
};

#endif
