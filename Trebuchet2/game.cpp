#include <memory>
#include <iostream>

#include <SFML/Window.hpp>

#include "game.h"
#include "map/map.h"
#include "layer/layer.h"
#include "objects/object.h"
#include "player/player.h"

//Note to Aleks:
//You should make a class that checks for and handles collisions and derive every "solid" class from it (Player, Platforms, Walls, Enemies, etc).
//That will make handling collisions in the future much easier.
//https://en.sfml-dev.org/forums/index.php?topic=13358.0

float movementSpeed = 1.0;

Player player("data/playerRollRight.png");

bool Game::init()
{
    // Load map information from JSON into object list
    if (!map.loadFromFile("data/map.json"))
    {
        std::cout << "Failed to load map data." << std::endl;
        return false;
    }

    // Move objects from map object to Game list
    objects.splice(objects.begin(), map.getObjects());

    // Standard SFML setup
    window.create(sf::VideoMode(1280, 720), "Trebuchet 2: Double Cannonaloo");

    // Double the size of the screen
    sf::View view = window.getDefaultView();
    view.setSize(view.getSize().x / 2, view.getSize().y / 2);
    view.setCenter(view.getCenter().x / 2, view.getCenter().y / 2);
    window.setView(view);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // Makes sure player moves continually when key is held down
    window.setKeyRepeatEnabled(true);

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
bool Game::gameTick(sf::RenderWindow& window, std::list<std::shared_ptr<Object>>& objects, float deltaTime)
{
    sf::Event event;

    // Process events from the OS
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                return false;

            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                    player.movePlayer('u', movementSpeed);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    player.movePlayer('d', movementSpeed);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    player.movePlayer('l', movementSpeed);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    player.movePlayer('r', movementSpeed);
                }

            case sf::Event::KeyReleased:
                // Reload map on F5
                if (event.key.code == sf::Keyboard::F5)
                {
                    objects.clear();

                    if (!map.loadFromFile("data/map.json"))
                    {
                        std::cout << "Failed to reload map data." << std::endl;
                        return false;
                    }

                    objects.splice(objects.begin(), map.getObjects());
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
    for (auto& object: objects)
    {
        object->process(deltaTime);
        object->draw(window);
    }

    //draws player on screen
    player.drawPlayer(window);

    window.display();

    return true;
}
