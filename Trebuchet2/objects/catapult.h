#ifndef TREBUCHET2_CATAPULT_H
#define TREBUCHET2_CATAPULT_H

#include <iostream>
#include <SFML/Graphics.hpp>

class catapult {
public:
    sf::Sprite Sprite;
    sf::Texture right;
    sf::Texture left;
    int speed = 15;
    int i = 0;
    int lengde = 0;
    int map = 0;

    catapult(float x, float y, int len, int mapnr) {
        right.loadFromFile("data/entities/enemyCatapultRight.png");
        left.loadFromFile("data/entities/enemyCatapultLeft.png");
        Sprite.setTexture(left);
        Sprite.setPosition(x, y);
        lengde = len;
        map = mapnr;
    }

    ~catapult() = default;

    void draw(sf::RenderWindow &window) {
        window.draw(Sprite);
    }

    void Update(float deltaTime) {
        sf::Vector2f movement(0.0f, 0.0f);
        if (i < lengde) {
            Sprite.setTexture(right);
            movement.x += speed * deltaTime;
        } else {
            Sprite.setTexture(left);
            movement.x -= speed * deltaTime;
        }
        i++;
        if (i > (lengde * 2)) { i = 0; }
        Sprite.move(movement.x, movement.y);
    }

    int getx() { return static_cast<int>(Sprite.getPosition().x); }

    int gety() { return static_cast<int>(Sprite.getPosition().y); }
};

#endif
