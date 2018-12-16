#include <memory>
#include <iostream>

#include <SFML/Window.hpp>
//#include <commctrl.h>

#include "game.h"
#include "map/map.h"
#include "layer/layer.h"
#include "objects/object.h"
#include "player/player.h"
#include "projectile/projectile.h"

player player("data/playerRollRight.png");

int screenModifier = 1;

bool Game::init() {
    // Load map information from JSON into object list
    if (!map.loadFromFile("data/Desert.json")) {
        std::cout << "Failed to load map data." << std::endl;
        return false;
    }

    // Copy layer references from map object to Game list
    std::copy(map.getLayers().begin(), map.getLayers().end(), std::back_inserter(objects));

    // Copy sprite references from map object to Game list
    //std::copy(map.getSprites().begin(), map.getSprites().end(), std::back_inserter(objects));

    // Standard SFML setup
    window.create(sf::VideoMode(1280, 720), "Trebuchet 2: Double Cannonaloo");

    // Double the size of the screen
    view = window.getDefaultView();
    view.setSize(view.getSize().x / 2, view.getSize().y / 2);
    view.setCenter(view.getCenter().x / 2, view.getCenter().y / 2);
    window.setView(view);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // Makes sure player moves continually when key is held down
    window.setKeyRepeatEnabled(true);



    return true;
}

void Game::run() {
    float deltaTime = 0;
    clock.restart();

    // Game loop
    while (gameTick(window, objects, deltaTime)) {
        deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
    }
}

// Process and draws one frame of the game
bool Game::gameTick(sf::RenderWindow &window, std::list<std::shared_ptr<Object>> &objects, float deltaTime) {
    sf::Event event{};


    // Process events from the OS
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                return false;

            case sf::Event::KeyReleased:
                // Reload map on F5
                if (event.key.code == sf::Keyboard::F5) {
                    objects.clear();

                    if (!map.loadFromFile("data/Desert.json")) {
                        std::cout << "Failed to reload map data." << std::endl;
                        return false;
                    }
                    std::copy(map.getLayers().begin(), map.getLayers().end(), std::back_inserter(objects));
                    //std::copy(map.getSprites().begin(), map.getSprites().end(), std::back_inserter(objects));
                }

                // Exit program on escape
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return false;
                }

                //Displays current position of player
                if (event.key.code == sf::Keyboard::J) {
                    std::cout << "Player position: X = " << player.getx() << " , Y = " << player.gety() << std::endl;
                }

                if (event.key.code == sf::Keyboard::Space) {
                    projectile bullet(player.getx(), player.gety() , 0 , 1, "data/entities/cannonball.png");
                    //p = &bullet;
                    bullets.push_back(bullet);
                }
                break;

            default:
                // Ignore the other events
                break;
        }
    }

    window.clear(sf::Color::Black);

    // Process and render each object
    for (auto &object: objects) {
        object->process(deltaTime);
        object->draw(window);
    }
    //predict movement

    int x = 0;
    int y = 0;

    if (player.left) {
        x = -1;
    }
    if (player.right) {
        x = 1;
    }
    if (player.up) {
        y = -1;
    }
    if(player.grounded){
        y = 0;
    }
    if(!player.grounded){
        y = 1;
    }

    auto layer = map.getLayer("foreground");
    for (int i = 0; i < 26; i += 5) {
        for (int j = 0; j < 26; j += 5) {
            if (layer->getTilemap()[((player.getx() + i + x) / map.getTileWidth()) +
                                    ((player.gety() + j + y) / map.getTileHeight()) * layer->getWidth()] != 0) {
                //collision
                if (player.left) {
                    player.pSprite.move(1,0);
                }
                if (player.right) {
                    player.pSprite.move(-1,0);
                }
                if (player.up) {
                    player.pSprite.move(0,1);
                }
                if (!player.grounded){
                    player.grounded = true;
                    player.pSprite.move(0,-1);
                }

            }
        }
    }
    //gravity check
    if (player.grounded){
        int k = 0;
        for(int i= 0;i<26;i+=5){
            if (layer->getTilemap()[((player.getx()+i) / map.getTileWidth()) +
                                ((player.gety()+27) / map.getTileHeight()) * layer->getWidth()] == 0) {
                k+=1;
            }
            if(k==5){
                player.grounded = false;
            }
        }
    }

    //Edge collision and camera movement logic
    if (player.getx() > -3 && player.getx() < 0) {
        player.setPos(0, player.gety());
    }
    if (player.gety() > -3 && player.gety() < 0) {
        player.setPos(player.getx(), 0);
    }
    if (player.gety() > 335 && player.gety() < 338) {
        player.setPos(player.getx(), 335);
    }
    if (player.getx() > 637 * screenModifier) {
        view.getCenter();
        view.move(320.f * (screenModifier + 1), 0.f);
        window.setView(view);
        screenModifier++;
    }



    //draws player on screen
    player.Update(deltaTime);
    player.draw(window);

    // copy for auto        std::vector<projectile>::iterator

    for (auto it = bullets.begin(); it != bullets.end() ; it++) {
        it->Update();
        it->setPos(it->getlocation_X(),it->getlocation_Y());
        it->draw(window);
    }



    window.display();

    return true;
}
