#ifndef LAYER_H
#define LAYER_H

#include "../objects/object.h"

// Class representing a tile layer
class Layer : public Object
{
    // Map needs to access protected/private data
    friend class Map;

public:
    explicit Layer(TileSize tileSize) : Object(tileSize) { width = height = 0; }

    void draw(sf::RenderWindow& window) override;

protected:
    // Size in tiles
    int width, height;

    // Lazy, but ram is cheap!
    int tilemap[100][100] = { 0 };
};

#endif
