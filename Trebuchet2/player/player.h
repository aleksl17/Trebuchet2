#ifndef TREBUCHET2_PLAYER_H
#define TREBUCHET2_PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "map/map.h"
#include "game.h"

class player {
public:
    sf::Sprite pSprite;
    sf::Sprite liv;
    int life = 1;
    bool left = false;
    bool right = false;
    bool up = false;
    bool grounded = false;
    bool dead = false;
    bool jump = true;
    int i = 0,j = 0,k = 0;
    bool fliker = false;
    sf::Texture pleft;
    sf::Texture pright;
    sf::Texture pleft1;
    sf::Texture pright1;
    sf::Texture onflame;
    sf::Texture fullliv;
    sf::Texture tomliv;
    sf::Texture misteliv;

    player() {
        pright1.loadFromFile("data/entities/playerRollRight1.png");
        pleft1.loadFromFile("data/entities/playerRollLeft1.png");
        pright.loadFromFile("data/entities/playerRollRight.png");
        pleft.loadFromFile("data/entities/playerRollLeft.png");
        onflame.loadFromFile("data/entities/onflame_1.png");
        fullliv.loadFromFile("data/entities/full_hearth.png");
        tomliv.loadFromFile("data/entities/empty_hearth.png");
        misteliv.loadFromFile("data/entities/misteliv.png");
        liv.setTexture(fullliv);
        pSprite.setTexture(pright);
        pSprite.setPosition(30, 200);
    }

    ~player() = default;

    void Update(float deltaTime) {
        liv.setPosition(600,10);
        sf::Vector2f movement(0.0f, 0.0f);
        up = false;
        left = false;
        right = false;
        if(!dead) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                movement.x -= speed * deltaTime;
                left = true;
                if (j < 10) {
                    pSprite.setTexture(pleft);

                } else {
                    pSprite.setTexture(pleft1);
                }
                j++;
                if (j > 20) { j = 0; }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                movement.x += speed * deltaTime;
                right = true;
                if (j < 10) {
                    pSprite.setTexture(pright);

                } else {
                    pSprite.setTexture(pright1);
                }
                j++;
                if (j > 20) { j = 0; }
            }
            if (jump and i < 40) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    movement.y -= speed * deltaTime;
                    up = true;
                    grounded = false;
                    i++;
                } else {
                    jump = false;
                }
            }
        }
        //gravity
        if (!grounded and !up) {
            movement.y += speed * deltaTime;
        }else{jump = true;}

        pSprite.move(movement.x, movement.y);
    }

    void draw(sf::RenderWindow &window) {
        if(fliker){
            if(k < 10 or (k < 30 and k > 20)) {
                pSprite.setTexture(misteliv);
            }
            k++;
            if(k>40){
                life = 0;
                k=0;
                fliker = false;
            }
        }
        window.draw(pSprite);
        if (getx() > 322) {
            liv.setPosition(getx()+280,10);
        }

        window.draw(liv);
    }

    int getx() { return static_cast<int>(pSprite.getPosition().x); }

    int gety() { return static_cast<int>(pSprite.getPosition().y); }

    void setPos(int x, int y) {
        pSprite.setPosition(x, y);
    }

private:

    float speed = 100;
protected:
    Map map;
};

#endif
