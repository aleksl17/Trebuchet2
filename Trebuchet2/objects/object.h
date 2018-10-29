#ifndef OBJECT_H
#define OBJECT_H

#include <memory>

namespace sf
{
    class RenderWindow;
    class Texture;
}

class Map;

// Base class representing any game object, including tile layers and sprites
class Object
{
public:
    explicit Object(Map& map) : map(map) {}
    virtual ~Object() = default;

    virtual void process(float deltaTime) {}
    virtual void draw(sf::RenderWindow& window) {}

protected:
    // Reference to map class so objects can use the map to set textures for drawing
    Map& map;
};

#endif
