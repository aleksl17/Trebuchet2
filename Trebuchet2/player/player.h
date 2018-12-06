#ifndef TREBUCHET2_PLAYER_H
#define TREBUCHET2_PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "map/map.h"

class player {
public:
    sf::Sprite pSprite;
    bool left = false;
    bool right = false;
    bool up = false;
    bool grounded = false;
    bool jump = true;
    int i = 0;

    explicit player(const std::string &imgDirectory) {
        if (!pTexture.loadFromFile(imgDirectory)) {
            std::cerr << "Could not Load Player Texture From File\n";
        }
        pSprite.setTexture(pTexture);
        pSprite.setPosition(50.0f, 200.0f);
    }

    ~player() = default;

    void Update(float deltaTime) {
        sf::Vector2f movement(0.0f, 0.0f);
        up = false;
        left = false;
        right = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movement.x -= speed * deltaTime;
            left = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.x += speed * deltaTime;
            right = true;
        }
        if (jump and i<40) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                movement.y -= speed * deltaTime;
                up = true;
                grounded = false;
                i++;
            }else{
                jump = false;
            }
        }
        //gravity
        if (!grounded and !up) {
            movement.y += speed * deltaTime;
        }else{jump = true;}

        pSprite.move(movement.x, movement.y);
    }

    void draw(sf::RenderWindow &window) {
        window.draw(pSprite);
    }

    int getx() { return static_cast<int>(pSprite.getPosition().x); }

    int gety() { return static_cast<int>(pSprite.getPosition().y); }

    void setPos(int x, int y) {
        pSprite.setPosition(x, y);
    }

private:
    sf::Texture pTexture;

    float speed = 100;
protected:
    Map map;
};

#endif
