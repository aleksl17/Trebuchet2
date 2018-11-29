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
    bool cantleft = false;
    bool cantright = false;
    bool cantup = false;
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and !cantleft) {
            movement.x -= speed * deltaTime;
            left = true;
            cantleft = false;
            cantright = false;
            cantup = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and !cantright) {
            movement.x += speed * deltaTime;
            right = true;
            cantleft = false;
            cantright = false;
            cantup = false;
        }
        if (jump and i<40) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and !cantup) {
                movement.y -= speed * deltaTime;
                up = true;
                cantleft = false;
                cantright = false;
                cantup = false;
                grounded = false;
                i++;
            }
        }else{
            i=0;
            jump = false;
        }
        //gravity
        if (!grounded and !up) {
            movement.y += speed * deltaTime;
        }else{jump = true;}

        pSprite.move(movement.x, movement.y);

        /*
        //collision til edge MOVED TO GAME.CPP
        if (getx() > -3 && getx() < 0) {
            pSprite.setPosition(0, gety());
        }
        if (getx() > 615 && getx() < 618) {
            pSprite.setPosition(615, gety());
        }
        if (gety() > -3 && gety() < 0) {
            pSprite.setPosition(getx(), 0);
        }
        if (gety() > 335 && gety() < 338) {
            pSprite.setPosition(getx(), 335);
        }
        */
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
