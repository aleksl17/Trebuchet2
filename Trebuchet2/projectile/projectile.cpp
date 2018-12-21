#include "projectile.h"

projectile::projectile(float x, float y, float s_y, float s_x, const std::string &imgDirectory, float start_Y,
                       float m_h) {

    if (use_once)
        return;

    location_x = x;
    location_y = y;
    speed_x = s_x;
    speed_y = s_y;
    start_y = start_Y;
    max_height = m_h;

    cannonball.loadFromFile("data/entities/cannonball.png");
    pSprite.setTexture(cannonball);
    pSprite.setPosition(50.0f, 200.0f);
}

void projectile::setZero() {
    location_y = 400;
    location_x = 0;
    speed_y = speed_x = 0;
}

// GETTER AND SETTERS

float projectile::getlocation_X() const {
    return location_x;
}

void projectile::setlocation_X(float x) {
    projectile::location_x = x;
}

float projectile::getlocation_Y() const {
    return location_y;
}

void projectile::setlocation_Y(float y) {
    projectile::location_y = y;
}

float projectile::getSpeed_x() const {
    return speed_x;
}

void projectile::setSpeed_x(float speed_x) {
    projectile::speed_x = speed_x;
}

float projectile::getSpeed_y() const {
    return speed_y;
}

void projectile::setSpeed_y(float speed_y) {
    projectile::speed_y = speed_y;
}

int projectile::get_int_X(float x) {
    return static_cast<int>(x);
}

int projectile::get_int_Y(float y) {
    return static_cast<int>(y);
}