#include <memory>
#include <iostream>
#include <chrono>

#include <SFML/Window.hpp>
#include <menu/death.h>

#include "game.h"
#include "map/map.h"
#include "layer/layer.h"
#include "objects/object.h"
#include "player/player.h"
#include "objects/catapult.h"
#include "projectile/projectile.h"
#include "menu/menu.h"
#include "menu/select.h"
#include "menu/victory.h"

const int screenWidth = 1280;
const int screenHeight = 720;

int mapnr = 0;
int teller = 0;

player player;
catapult cat(210, 208, 100, 0);
catapult cat1(1804, 80, 300, 0);
catapult cat2(1588, 304, 100, 0);
catapult cat3(286, 241, 100, 2);
catapult cat4(945, 241, 100, 2);
catapult cat5(1133, 336, 100, 2);
catapult cat6(1244, 273, 200, 2);
catapult cat7(1090, 240, 300, 1);
catapult cat8(1350, 240, 300, 1);
catapult cat9(1785, 241, 200, 1);

menu menu(screenWidth, screenHeight);
death death(screenWidth, screenHeight);
select select(screenWidth, screenHeight);
victory victory(screenWidth, screenHeight);

bool isRunning = true;
bool isDrawn = false;
bool inMenu = true;
bool inSelect = false;
bool inDeath = false;
bool loopOnce = false;
bool inVictory = false;

bool Game::init() {
    // Load map information from JSON into object list
    if (!map.loadFromFile("data/Snow.json")) {
        std::cout << "Failed to load map data." << std::endl;
        return false;
    }

    if (!font.loadFromFile("data/ShadowsIntoLight.ttf")) {
        std::cout << "Failed to load font." << std::endl;
        return false;
    }

    if (!texture.loadFromFile("data/menuBackground.png")) {
        std::cout << "Failed to load texture: menu background." << std::endl;
        return false;
    }

    if (!victoryTexture.loadFromFile("data/victoryBackground.png")) {
        std::cout << "Failed to load texture: menu background." << std::endl;
        return false;
    }

    background.setTexture(texture);

    victoryBackground.setTexture(victoryTexture);

    //push catapults in a list
    catapults.push_back(cat);
    catapults.push_back(cat1);
    catapults.push_back(cat2);
    catapults.push_back(cat3);
    catapults.push_back(cat4);
    catapults.push_back(cat5);
    catapults.push_back(cat6);
    catapults.push_back(cat7);
    catapults.push_back(cat8);
    catapults.push_back(cat9);

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

    // Standard SFML setup
    window.create(sf::VideoMode(screenWidth, screenHeight), "Trebuchet 2: Double Cannonaloo");

    //Init uiView
    uiView = window.getDefaultView();
    uiView.setSize(uiView.getSize().x / 2, uiView.getSize().y / 2);
    uiView.setCenter(uiView.getCenter().x / 2, uiView.getCenter().y / 2);

    // Double the size of the screen
    view = window.getDefaultView();
    view.setSize(view.getSize().x / 2, view.getSize().y / 2);
    view.setCenter(view.getCenter().x / 2, view.getCenter().y / 2);
    window.setView(view);

    //Enable VSYNC
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
                if (event.key.code == sf::Keyboard::W && (inMenu || inDeath || inSelect || inVictory)) {
                    menu.moveUp();
                    death.moveUp();
                    select.moveUp();
                    victory.moveUp();
                    break;
                }

                if (event.key.code == sf::Keyboard::S && (inMenu || inDeath || inSelect || inVictory)) {
                    menu.moveDown();
                    death.moveDown();
                    select.moveDown();
                    victory.moveDown();
                    break;
                }

                if (event.key.code == sf::Keyboard::Return && (inMenu || inDeath || inSelect || inVictory)) {
                    if (inMenu) {
                        switch (menu.getPressedItem()) {
                            case 0:
                                inMenu = false;
                                inSelect = true;
                                isRunning = true;
                                break;
                            case 1:
                                break;
                            case 2:
                                window.close();
                                break;
                            default:
                                // Ignore the other events
                                break;
                        }
                    }

                    if (inDeath) {
                        switch (death.getPressedItem()) {
                            case 0:
                                inDeath = false;
                                player.pSprite.setPosition(30, 200);
                                player.dead = false;
                                player.pSprite.setTexture(player.pright);
                                view.setCenter(320, 180);
                                player.liv.setTexture(player.fullliv);
                                player.life = 1;
                                window.setView(view);
                                break;
                            case 1:
                                window.close();
                                break;
                            default:
                                // Ignore the other events
                                break;
                        }
                    }

                    if (inVictory) {
                        switch (victory.getPressedItem()) {
                            case 0:
                                inMenu = false;
                                inVictory = false;
                                inSelect = true;
                                isRunning = true;
                                player.pSprite.setPosition(30, 200);
                                player.dead = false;
                                player.life = 1;
                                player.liv.setTexture(player.fullliv);
                                player.pSprite.setTexture(player.pright);
                                view.setCenter(320, 180);
                                window.setView(view);
                                break;
                            case 1:
                                window.close();
                                break;
                            default:
                                // Ignore the other events
                                break;
                        }
                    }

                    if (loopOnce && inSelect) {
                        switch (select.getPressedItem()) {
                            case 0:
                                mapnr = 2;
                                objects.clear();
                                if (!map.loadFromFile("data/Snow.json")) {
                                    std::cout << "Failed to load map data." << std::endl;
                                    return false;
                                }
                                std::copy(map.getLayers().begin(), map.getLayers().end(), std::back_inserter(objects));
                                inSelect = false;
                                loopOnce = false;
                                break;
                            case 1:
                                mapnr = 0;
                                objects.clear();
                                if (!map.loadFromFile("data/Desert.json")) {
                                    std::cout << "Failed to load map data." << std::endl;
                                    return false;
                                }
                                std::copy(map.getLayers().begin(), map.getLayers().end(), std::back_inserter(objects));
                                inSelect = false;
                                loopOnce = false;
                                break;
                            case 2:
                                mapnr = 1;
                                objects.clear();
                                if (!map.loadFromFile("data/Forest.json")) {
                                    std::cout << "Failed to load map data." << std::endl;
                                    return false;
                                }
                                std::copy(map.getLayers().begin(), map.getLayers().end(), std::back_inserter(objects));
                                inSelect = false;
                                loopOnce = false;
                                break;
                            case 3:
                                inSelect = false;
                                loopOnce = false;
                                inMenu = true;
                                break;
                            default:
                                // Ignore the other events
                                break;
                        }
                    }
                }

                //Pause game
                if (event.key.code == sf::Keyboard::P) {
                    isRunning = !isRunning;
                }

                // Reload map on F5
                if (event.key.code == sf::Keyboard::F5) {
                    objects.clear();

                    if (mapnr == 0) {
                        if (!map.loadFromFile("data/Desert.json")) {
                            std::cout << "Failed to load map data." << std::endl;
                            return false;
                        }
                    } else if (mapnr == 1) {
                        if (!map.loadFromFile("data/Forest.json")) {
                            std::cout << "Failed to load map data." << std::endl;
                            return false;
                        }
                    } else if (mapnr == 2) {
                        if (!map.loadFromFile("data/Snow.json")) {
                            std::cout << "Failed to load map data." << std::endl;
                            return false;
                        }
                    }
                    std::copy(map.getLayers().begin(), map.getLayers().end(), std::back_inserter(objects));
                    //std::copy(map.getSprites().begin(), map.getSprites().end(), std::back_inserter(objects));
                }

                // Exit program on escape
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return false;
                }

                //respawn
                if (event.key.code == sf::Keyboard::R) {
                    player.pSprite.setPosition(30, 200);
                    player.dead = false;
                    player.life = 1;
                    player.liv.setTexture(player.fullliv);
                    player.pSprite.setTexture(player.pright);
                    view.setCenter(320, 180);
                    window.setView(view);
                }

                //Displays current position of player
                if (event.key.code == sf::Keyboard::J) {
                    std::cout << "Player position: X = " << player.getx() << " , Y = " << player.gety()
                              << std::endl;
                }

                //Shoot projectile
                if (event.key.code == sf::Keyboard::Right) {
                    projectile bullet(player.getx(), player.gety() + 10, -1, 1.5, "data/entities/cannonball.png",
                                      player.gety(), 35);
                    bullets.push_back(bullet);
                }
                if (event.key.code == sf::Keyboard::Left) {
                    projectile bullet(player.getx(), player.gety() + 10, -1, -1.5, "data/entities/cannonball.png",
                                      player.gety(), 35);
                    bullets.push_back(bullet);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    float direction_ball = 2;

                    if (player.left)
                        direction_ball = -2;

                    projectile bullet(player.getx(), player.gety() + 10, -1, direction_ball,
                                      "data/entities/cannonball.png", player.gety(), 50);
                    bullets.push_back(bullet);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    float direction_ball = 3.5;

                    if (player.left)
                        direction_ball = -3.5;

                    projectile bullet(player.getx(), player.gety() + 10, -1, direction_ball,
                                      "data/entities/cannonball.png", player.gety(), 5);
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

        window.setView(view);

        // Process and render each object
        if (!inMenu && !inDeath && !inSelect) {
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

                for (auto bull = bullets.begin(); bull != bullets.end(); bull++) {
                    if (layer->getTilemap()[((bull->get_int_X(bull->getlocation_X()) + i) / map.getTileWidth()) +
                                            ((bull->get_int_X(bull->getlocation_Y()) + j) / map.getTileHeight()) *
                                            layer->getWidth()] != 0) {
                        // bull->setSpeed_x(0);
                        //bull->setSpeed_y(0);
                        //bullets.erase(it);
                    }
                }
            }
        }

        //player lava check
        for (int i = 0; i < 21; i += 5) {
            for (int j = 0; j < 21; j += 5) {
                if (layer->getTilemap()[((player.getx() + i) / map.getTileWidth()) +
                                        ((player.gety() + j + 7) / map.getTileHeight()) * layer->getWidth()] == 52) {
                    //dying
                    player.pSprite.setTexture(player.onflame);
                    player.dead = true;
                    if (teller > 200) {
                        inDeath = true;
                        teller = 0;
                    }
                    teller++;
                }
            }
        }

        //Gravity check
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

        //Edge collision
        if (player.getx() > -3 && player.getx() < 0) {
            player.setPos(0, player.gety());
        }
        if (player.gety() > -3 && player.gety() < 0) {
            player.setPos(player.getx(), 0);
        }
        if (player.getx() > 2507 && player.getx() < 2510) {
            inVictory = true;
        }
        if (player.gety() > 335 && player.gety() < 338) {
            player.setPos(player.getx(), 335);
            inDeath = true;
        }

        //Camera moevement logic
        if (player.getx() < 322) {
            view.setCenter(320, 180);
            window.setView(view);
        } else {
            view.setCenter(player.getx(), 180);
            window.setView(view);
        }

        //catapult and player collision
        for (auto it = catapults.begin(); it != catapults.end(); it++) {
            if (it->map == mapnr) {
                for (int i = 0; i < 26; i += 3) {
                    if (player.getx() + i > it->getx() && player.getx() + i < it->getx() + 26 &&
                        player.gety() + i > it->gety() && player.gety() + i < it->gety() + 16) {
                        if (player.life == 1) {
                            player.liv.setTexture(player.tomliv);
                            player.fliker = true;
                        } else if (player.life == 0) {
                            inDeath = true;
                        }
                    }
                }
            }
        }

        //Draw main menu, death screen and map select screen
        if (inMenu) {
            window.draw(background);
            menu.draw(window);
        } else if (inDeath) {
            window.setView(uiView);
            death.draw(window);
        } else if (inSelect) {
            select.draw(window);
            loopOnce = true;
        } else if (inVictory) {
            window.setView(uiView);
            window.draw(victoryBackground);
            victory.draw(window);
        }
        else {
            //draws player and enemies on screen
            player.Update(deltaTime);
            player.draw(window, uiView);
            window.setView(view);
            for (auto it = catapults.begin(); it != catapults.end(); it++) {
                if (it->map == mapnr) {
                    it->Update(deltaTime);
                    it->draw(window);
                }
            }

            for (auto it = bullets.begin(); it != bullets.end(); it++) {
                for (auto cat = catapults.begin(); cat != catapults.end(); cat++) {
                    if (cat->map == mapnr) {
                        for (int i = 0; i < 26; i += 3) {
                            if (it->getlocation_X() > cat->getx() && it->getlocation_X() < cat->getx() + 26 &&
                                it->getlocation_Y() > cat->gety() && it->getlocation_Y() < cat->gety() + 16) {
                                std::cout << "HIT!" << std::endl;
                                catapults.erase(cat);
                                bullets.erase(it);
                            }
                        }
                    }
                }

                it->Update();
                it->setPos(it->getlocation_X(), it->getlocation_Y());
                it->draw(window);
            }
        }

        window.display();
    } else {
        window.setView(uiView);
        window.draw(text);
        if (!isDrawn) {
            window.display();
            isDrawn = true;
        }
    }

    return true;
}

