//
// Created by havar on 05.12.2018.
//

#ifndef TREBUCHET2_PROJECTILE_H
#define TREBUCHET2_PROJECTILE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "map/map.h"
#include <queue>


class projectile {

public:
    projectile* p = nullptr;
    bool use_once = false;
    sf::Sprite pSprite;
    std::string canonball = "data/entities/cannonball.png"; 

    // Location on screen
    int location_x = 0;
    int location_y = 0;

    //Speed of projectile
    int speed_x = 0;
    int speed_y = 0;

    // Dimensions
    int width = 4;
    int height = 4;


    projectile( int x, int y, int s_y, int s_x, const std::string &imgDirectory);

    ~projectile() = default;

    void draw(sf::RenderWindow &window) {
        window.draw(pSprite);
    }


    void Update() {
        // int location_x = getlocation_X() + getSpeed_x();
        //int location_y = getlocation_Y() + getSpeed_y();
        //sf::Vector2f movement(0.0f, 0.0f);
        location_x += speed_x;
        location_y += speed_y;

        //pSprite.move(movement.x, movement.y);
    }


    int getx() { return static_cast<int>(pSprite.getPosition().x); }

    int gety() { return static_cast<int>(pSprite.getPosition().y); }

    void setPos(int x, int y) {
        pSprite.setPosition(x, y);
    }



    int getlocation_X() const;

    void setlocation_X(int x);

    int getlocation_Y() const;

    void setlocation_Y(int y);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    int getSpeed_x() const;

    void setSpeed_x(int speed_x);

    int getSpeed_y() const;

    void setSpeed_y(int speed_y);



private:
    sf::Texture pTexture;




};


#endif //TREBUCHET2_PROJECTILE_H
