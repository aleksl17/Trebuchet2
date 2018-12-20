#include <memory>
#include <iostream>
#include <chrono>

#include <SFML/Window.hpp>
#include <menu/death.h>
//#include <commctrl.h>

#include "game.h"
#include "map/map.h"
#include "layer/layer.h"
#include "objects/object.h"
#include "player/player.h"
#include "objects/catapult.h"
#include "projectile/projectile.h"
#include "menu/menu.h"

const int screenWidth = 1280;
const int screenHeight = 720;

int mapnr = 0;
int screenModifier = 1;

player player;
catapult cat(210,208,100,0);
catapult cat1(1834,80,200,0);
catapult cat2(1588,305,100,0);


menu menu(screenWidth, screenHeight);
death death(screenWidth,screenHeight);

bool isRunning = true;
bool isDrawn = false;
bool inMenu = true;
bool inDeath = false;

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

    if (!texture.loadFromFile("data/menuBackground.png")) {
        std::cout << "Failed to load texture: menu background." << std::endl;
        return false;
    }

    background.setTexture(texture);
    //push catapults in a list
    catapults.push_back(cat);
    catapults.push_back(cat1);
    catapults.push_back(cat2);

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
                if (event.key.code == sf::Keyboard::W) {
                    menu.moveUp();
                    death.moveUp();
                    break;
                }
                if (event.key.code == sf::Keyboard::S) {
                    menu.moveDown();
                    death.moveDown();
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
                    switch(death.getPressedItem()){
                        case 0:
                            inDeath = false;
                            player.pSprite.setPosition(30, 200);
                            player.dead = false;
                            player.pSprite.setTexture(player.pright);
                            view.move(-640 * (screenModifier - 1), 0);
                            screenModifier = 1;
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
                    }
                    else if (mapnr == 1) {
                        map.loadFromFile("data/Snow.json");
                        std::copy(map.getLayers().begin(), map.getLayers().end(), std::back_inserter(objects));
                        mapnr++;
                    }
                    else if (mapnr == 2) {
                        map.loadFromFile("data/Desert.json");
                        std::copy(map.getLayers().begin(), map.getLayers().end(), std::back_inserter(objects));
                        mapnr = 0;
                    }
                }
                //respawn
                if (event.key.code == sf::Keyboard::R) {
                    player.pSprite.setPosition(30, 200);
                    player.dead = false;
                    player.life = 1;
                    player.liv.setTexture(player.fullliv);
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

        window.setView(view);

        // Process and render each object
        if(!inMenu and !inDeath) {
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

        //player lava check
        for (int i = 0; i < 21; i += 5) {
            for (int j = 0; j < 21; j += 5) {
                if (layer->getTilemap()[((player.getx() + i) / map.getTileWidth()) +
                                        ((player.gety() + j +7) / map.getTileHeight()) * layer->getWidth()] == 52) {
                    //dying
                    player.pSprite.setTexture(player.onflame);
                    inDeath = true;
                }
            }
        }


        //Gravity check
        if (player.grounded) {
            int k = 0;
            for(int i= 0;i<36;i+=5){
                if (layer->getTilemap()[((player.getx()+i-5) / map.getTileWidth()) +
                                        ((player.gety()+27) / map.getTileHeight()) * layer->getWidth()] == 0) {
                    k+=1;
                }
                if(k==7){
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
        if (player.gety() > 335 && player.gety() < 338) {
            player.setPos(player.getx(), 335);
        }


        //Camera moevement logic
        if (player.getx() < 322) {
            view.setCenter(320, 180);
            window.setView(view);
        }
        else {
            view.setCenter(player.getx(), 180);
            window.setView(view);
        }

        if (inMenu) {
            menu.draw(window);
        }
        else {
            for (auto it = bullets.begin(); it != bullets.end(); it++) {
                it->Update();
                it->setPos(it->getlocation_X(), it->getlocation_Y());
                it->draw(window);

            }
        }

        //catapult and player collision
        for (auto it = catapults.begin(); it != catapults.end(); it++) {
            if(it->map == mapnr) {
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

        //Draw main menu
        if (inMenu) {
            window.draw(background);
            menu.draw(window);
        }else if(inDeath){
            window.setView(uiView);
            death.draw(window);
        }
        else {
            //draws player and enemies on screen

            player.Update(deltaTime);
            player.draw(window,uiView);
            window.setView(view);
            for (auto it = catapults.begin(); it != catapults.end(); it++) {
                if(it->map == mapnr) {
                    it->Update(deltaTime);
                    it->draw(window);
                }
            }
        }
        window.display();

    }
    else {
        window.setView(uiView);
        window.draw(text);
        if (!isDrawn) {
            window.display();
            isDrawn = true;
        }
    }

    return true;
}

