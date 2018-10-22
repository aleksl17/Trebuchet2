#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/System/Clock.hpp>

#include "object.h"

class Sprite : public Object
{
    // Map needs to access protected/private data
    friend class Map;

public:
    explicit Sprite(const TileSize& tileSize) : Object(tileSize)
    {
        id = x = y = frame = frameCount = frameDuration = 0;
    }

    void process(float time) override;
    void draw(sf::RenderWindow& window) override;

protected:
    // Id of first tile
    int id;

    // Location on screen
    int x, y;

    // Current animation frame
    int frame;

    //Frame count (duh)
    int frameCount;

    // Length of one frame in ms
    int frameDuration;

    // Times the animation
    sf::Clock clock;
};

#endif
