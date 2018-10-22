#include <SFML/Graphics.hpp>

#include "layer.h"

void Layer::draw(sf::RenderWindow& window)
{
    // Render each tile
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int tileid = tilemap[x][y];

            // Skip empty tiles
            if (tilemap[x][y] == 0)
                continue;

            // Texture coordinates
            int tilex, tiley;
            getTileCoords(tileid, tilex, tiley);

            // Using vertex arrays or permanent sprites would be faster
            sf::Sprite sprite(*texture, sf::IntRect(tilex, tiley, tileSize.x, tileSize.y));
            sprite.setPosition((float)(x * tileSize.x), (float)(y * tileSize.y));

            window.draw(sprite);
        }
    }
}
