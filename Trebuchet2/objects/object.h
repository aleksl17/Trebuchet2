#ifndef OBJECT_H
#define OBJECT_H

namespace sf
{
    class RenderWindow;
    class Texture;
}

// Small helper struct that contains tile size information
struct TileSize
{
    int x; // Width
    int y; // Height
    int s; // Spacing
};

// Class representing any game object
class Object
{
    // Map needs to access protected/private data
    friend class Map;

public:
    explicit Object(TileSize tileSize) : tileSize(tileSize), texture(nullptr) { }
    virtual ~Object();

    virtual void process(float deltaTime) {}
    virtual void draw(sf::RenderWindow& window) {}

    // Calculate x and y position of given tile in the texture
    void getTileCoords(int tile, int& x, int& y);

    const TileSize tileSize;

protected:
    sf::Texture* texture;
};

#endif
