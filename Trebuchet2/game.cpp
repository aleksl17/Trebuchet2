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
#include "menu/menu.h"

const int screenWidth = 1280;
const int screenHeight = 720;

int mapnr = 0;
int screenModifier = 1;

player player;

menu menu(screenWidth, screenHeight);

bool isRunning = true;
bool isDrawn = false;
bool inMenu = true;

bool Game::init() {
    // Load map information from JSON into object list
    if (!map.loadFromFile("data/Desert.json")) {
        std::cout << "Failed to load map data." << std::endl;
        return false;
    }

    if (!font.loadFromFile("data/ShadowsIntoLight.ttf")) {
        std::cout << "Failed to load font." << std::endl;
        return false;
    }

    //Text properties
    text.setFont(font);
    text.setString("Paused");
    text.setCharacterSize(64);
    text.setFillColor(sf::Color::Red);
    //Text Position
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(screenWidth / 4.0f, screenHeight / 4.0f));

    // Copy layer references from map object to Game list
    std::copy(map.getLayers().begin(), map.getLayers().end(), std::back_inserter(objects));

    // Copy sprite references from map object to Game list
    //std::copy(map.getSprites().begin(), map.getSprites().end(), std::back_inserter(objects));

    // Standard SFML setup
    window.create(sf::VideoMode(screenWidth, screenHeight), "Trebuchet 2: Double Cannonaloo");

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
                //Menu keys
                if (event.key.code == sf::Keyboard::W) {
                    menu.moveUp();
                    break;
                }
                if (event.key.code == sf::Keyboard::S) {
                    menu.moveDown();
                    break;
                }
                if (event.key.code == sf::Keyboard::Return) {
                    switch (menu.getPressedItem()) {
                        case 0:
                            std::cout << "Play button has been pressed" << std::endl;
                            inMenu = false;
                            break;
                        case 1:
                            std::cout << "Option button has been pressed" << std::endl;
                            break;
                        case 2:
                            window.close();
                            break;
                        default:
                            // Ignore the other events
                            break;
                    }
                }

                //Pause game
                if (event.key.code == sf::Keyboard::P) {
                    isRunning = !isRunning;
                }

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
                //change map
                if (event.key.code == sf::Keyboard::M) {
                    if (mapnr == 0) {
                        map.loadFromFile("data/Forest.json");
                        std::copy(map.getLayers().begin(), map.getLayers().end(), std::back_inserter(objects));
                        mapnr++;
                    } else if (mapnr == 1) {
                        map.loadFromFile("data/Snow.json");
                        std::copy(map.getLayers().begin(), map.getLayers().end(), std::back_inserter(objects));
                        mapnr++;
                    } else if (mapnr == 2) {
                        map.loadFromFile("data/Desert.json");
                        std::copy(map.getLayers().begin(), map.getLayers().end(), std::back_inserter(objects));
                        mapnr = 0;
                    }
                }
                //respawn
                if (event.key.code == sf::Keyboard::R) {
                    player.pSprite.setPosition(30, 200);
                    player.dead = false;
                    player.pSprite.setTexture(player.pright);
                    view.move(-640 * (screenModifier - 1), 0);
                    screenModifier = 1;
                    window.setView(view);
                }

                //Displays current position of player
                if (event.key.code == sf::Keyboard::J) {
                    std::cout << "Player position: X = " << player.getx() << " , Y = " << player.gety()
                              << std::endl;
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

    if (isRunning) {
        isDrawn = false;

        window.clear();

        // Process and render each object
        if(!inMenu) {
            for (auto &object: objects) {
                object->process(deltaTime);
                object->draw(window);
            }
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
        if (player.grounded) {
            y = 0;
        }
        if (!player.grounded) {
            y = 1;
        }

        auto layer = map.getLayer("foreground");
        for (int i = 0; i < 26; i += 5) {
            for (int j = 0; j < 26; j += 5) {
                if (layer->getTilemap()[((player.getx() + i + x) / map.getTileWidth()) +
                                        ((player.gety() + j + y) / map.getTileHeight()) * layer->getWidth()] != 0) {
                    //collision
                    if (player.left) {
                        player.pSprite.move(1, 0);
                        player.jump = false;
                    }
                    if (player.right) {
                        player.pSprite.move(-1, 0);
                        player.jump = false;
                    }
                    if (player.up) {
                        player.pSprite.move(0, 1);
                        player.jump = false;
                    }
                    if (!player.grounded) {
                        player.grounded = true;
                        player.pSprite.move(0, -1);
                        player.i = 0;
                    }

                }
            }
        }

        //lava check
        for (int i = 0; i < 21; i += 5) {
            for (int j = 0; j < 21; j += 5) {
                if (layer->getTilemap()[((player.getx() + i) / map.getTileWidth()) +
                                        ((player.gety() + j + 7) / map.getTileHeight()) * layer->getWidth()] == 52) {
                    //dying
                    player.pSprite.setTexture(player.onflame);
                    player.dead = true;
                }
            }
        }

        //gravity check
        if (player.grounded) {
            int k = 0;
            for (int i = 0; i < 36; i += 5) {
                if (layer->getTilemap()[((player.getx() + i - 5) / map.getTileWidth()) +
                                        ((player.gety() + 27) / map.getTileHeight()) * layer->getWidth()] == 0) {
                    k += 1;
                }
                if (k == 7) {
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
        if (player.getx() > 640 * screenModifier) {
            view.getCenter();
            view.move(640, 0);
            window.setView(view);
            screenModifier++;
        }

<<<<<<< HEAD


    //draws player on screen
    player.Update(deltaTime);
    player.draw(window);

    //window.draw(text);


        // copy for auto        std::vector<projectile>::iterator

    for (auto it = bullets.begin(); it != bullets.end() ; it++) {
        it->Update();
        it->setPos(it->getlocation_X(),it->getlocation_Y());
        it->draw(window);
    }


=======
        if (inMenu) {
            menu.draw(window);
        }
        else {
            //draws player on screen
            player.Update(deltaTime);
            player.draw(window);
        }
>>>>>>> Added start menu

        window.display();
    }
    else {
        window.draw(text);
        if (!isDrawn) {
            window.display();
            isDrawn = true;
        }
    }
    return true;
}

