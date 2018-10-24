#include <iostream>

#include <SFML/Window.hpp>

#include "game.h"
#include "layers/map.h"
#include "layers/layer.h"
#include "objects/object.h"

float y = 230;
float x = 0;

bool Game::init()
{
    // Load map information from JSON into object list
    if (!Map::load("data/map.json", objects))
    {
        std::cout << "Failed to load map data." << std::endl;
        return false;
    }

    // Standard SFML setup
    window.create(sf::VideoMode(1280, 720), "Trebuchet 2: Double Cannonaloo");

    // Double the size of the screen
    sf::View view = window.getDefaultView();
    view.setSize(view.getSize().x / 2, view.getSize().y / 2);
    view.setCenter(view.getCenter().x / 2, view.getCenter().y / 2);
    window.setView(view);


    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    return true;
}

void Game::run()
{
    float deltaTime = 0;
    clock.restart();

    // Game loop
    while (gameTick(window, objects, deltaTime))
    {
        deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
    }
}

// Process and draws one frame of the game
bool Game::gameTick(sf::RenderWindow& window, std::list<Object*>& objects, float deltaTime)
{
    sf::Event event;

    sf::Texture playerRollRight;
    playerRollRight.loadFromFile("data/playerRollRight.png");
    sf::Sprite player(playerRollRight);


    // Process events from the OS
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                return false;

            case sf::Event::KeyPressed:
                //player movment
                if (event.key.code == sf::Keyboard::W)
                {
                    y--;
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    y++;
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    x--;
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    y++;
                }

            case sf::Event::KeyReleased:
                // Reload map on F5
                if (event.key.code == sf::Keyboard::F5)
                {
                    objects.clear();

                    if (!Map::load("data/map.json", objects))
                    {
                        std::cout << "Failed to reload map data." << std::endl;
                        return false;
                    }
                }

                // Exit program on escape
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                    return false;
                }
                break;

            default:
                // Ignore the other events
                break;
        }
    }

    window.clear(sf::Color::Black);

    // Process and render each object
    for (Object* object : objects)
    {
        object->process(deltaTime);
        object->draw(window);
    }

    player.setPosition(x,y);
    window.draw(player);
    window.display();

    return true;
}