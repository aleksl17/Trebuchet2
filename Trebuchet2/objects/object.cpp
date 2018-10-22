#include <SFML/Graphics.hpp>

#include "object.h"

Object::~Object()
{
    delete texture;
    texture = nullptr;
}

void Object::getTileCoords(int tile, int& x, int& y)
{
    // Tileid 0 means no tile, so the ids actually start from 1
    tile--;

    int tileXcount = texture->getSize().x / (tileSize.x + tileSize.s);

    x = (tile % tileXcount) * (tileSize.x + tileSize.s);
    y = (tile / tileXcount) * (tileSize.x + tileSize.s);
}
