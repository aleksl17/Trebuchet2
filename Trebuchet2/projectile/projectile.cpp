//
// Created by havar on 05.12.2018.
//

#include "projectile.h"


projectile::projectile(int x, int y, int s_y, int s_x, const std::string &imgDirectory){

    if (use_once)
        return;

    location_x = x;
 location_y = y;
 speed_x = s_x;
 speed_y = s_y;

    if (!pTexture.loadFromFile(imgDirectory)) {
        std::cerr << "Could not Load projectile Texture From File\n";
    }
    pSprite.setTexture(pTexture);
    pSprite.setPosition(50.0f, 200.0f);
}







// GETTER AND SETTERS


int projectile::getlocation_X() const {
    return location_x;
}

void projectile::setlocation_X(int x) {
    projectile::location_x = x;
}

int projectile::getlocation_Y() const {
    return location_y;
}

void projectile::setlocation_Y(int y) {
    projectile::location_y = y;
}

int projectile::getWidth() const {
    return width;
}

void projectile::setWidth(int width) {
    projectile::width = width;
}

int projectile::getHeight() const {
    return height;
}

void projectile::setHeight(int height) {
    projectile::height = height;
}

int projectile::getSpeed_x() const {
    return speed_x;
}

void projectile::setSpeed_x(int speed_x) {
    projectile::speed_x = speed_x;
}

int projectile::getSpeed_y() const {
    return speed_y;
}

void projectile::setSpeed_y(int speed_y) {
    projectile::speed_y = speed_y;
}
