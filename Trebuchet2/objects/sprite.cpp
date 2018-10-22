#include <SFML/Graphics.hpp>

#include "sprite.h"

void Sprite::process(float deltaTime)
{
    // Go to next animation frame if required
    if (clock.getElapsedTime().asMilliseconds() < frameDuration)
        return;

    if (++frame >= frameCount)
        frame = 0;

    clock.restart();
}

void Sprite::draw(sf::RenderWindow& window)
{
    int tilex, tiley;
    getTileCoords(id, tilex, tiley);

    // Using vertex arrays or permanent sprites would be faster
    sf::Sprite sprite(*texture, sf::IntRect(tilex + frame * (tileSize.x + tileSize.s), tiley, tileSize.x, tileSize.y));
    sprite.setPosition((float)x, (float)y);

    window.draw(sprite);
}
