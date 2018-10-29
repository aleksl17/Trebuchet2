#include <SFML/Graphics.hpp>

#include "layer.h"
#include "map/map.h"

void Layer::draw(sf::RenderWindow& window)
{
    // Render each tile
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            unsigned int gid = tilemap[x + y * width];

            // Skip empty tiles
            if (gid == 0)
                continue;

            sf::Sprite sprite;

            // Set source texture and position
            map.setSpriteTextureFromGid(sprite, gid);
            sprite.setPosition((float)(x * map.getTileWidth()), (float)(y * map.getTileHeight()));

            window.draw(sprite);
        }
    }
}
