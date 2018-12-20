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
    float location_x = 0;
    float location_y = 0;

    float start_y;
    float max_height;

    //Speed of projectile
    float speed_x = 0;
    float speed_y = 0;

    // Dimensions
    int width = 4;
    int height = 4;

    projectile( float x, float y, float s_y, float s_x, const std::string &imgDirectory, float start_Y, float m_h);

    ~projectile() = default;

    void draw(sf::RenderWindow &window) {
        window.draw(pSprite);
    }

    void Update() {
        // int location_x = getlocation_X() + getSpeed_x();
        //int location_y = getlocation_Y() + getSpeed_y();
        //sf::Vector2f movement(0.0f, 0.0f);
        if (location_y <= start_y - max_height)
            speed_y = -speed_y;

        location_x += speed_x;
        location_y += speed_y;

        //pSprite.move(movement.x, movement.y);
    }

    int getx() { return static_cast<int>(pSprite.getPosition().x); }

    int gety() { return static_cast<int>(pSprite.getPosition().y); }

    void setPos(int x, int y) {
        pSprite.setPosition(x, y);
    }

    float getlocation_X() const;

    void setlocation_X(int x);

    float getlocation_Y() const;

    void setlocation_Y(int y);

    int get_int_X(float x);

    int get_int_Y(float y);

    float getWidth() const;

    void setWidth(int width);

    float getHeight() const;

    void setHeight(int height);

    float getSpeed_x() const;

    void setSpeed_x(int speed_x);

    float getSpeed_y() const;

    void setSpeed_y(int speed_y);

private:
    sf::Texture pTexture;
};

#endif
