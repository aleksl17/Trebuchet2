#ifndef MAP_H
#define MAP_H

#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>

#include <SFML/Graphics/Texture.hpp>

namespace sf
{
    class Sprite;
}

namespace Json
{
    class Value;
}

class Object;
class Sprite;
class Layer;

// Helper struct describing a tileset
struct Tileset
{
    unsigned int firstGid;
    int columns;
    int imageWidth;
    int imageHeight;
    int tileWidth;
    int tileHeight;
    int spacing;

    sf::Texture texture;
};

// Helper struct describing a frame of animation
struct AnimationFrame
{
    AnimationFrame(unsigned int gid, int duration) : gid(gid), duration(duration) {}

    unsigned int gid;
    int duration;
};

// Class containing the information in a Tiled map
class Map
{
public:
    // Load map from Tiled JSON file
    bool loadFromFile(const std::string& filename);

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getTileWidth() const { return tileWidth; }
    int getTileHeight() const { return tileHeight; }

    // Get layer by name. Use this to find the foreground layer for collision detection etc.
    std::shared_ptr<Layer> getLayer(const std::string& name);

    // Call this function after loadFromFile to get a list of layers that you can draw etc.
    std::list<std::shared_ptr<Layer>>& getLayers() { return layers; }

    // Call this function after loadFromFile to get a list of sprites that you can draw etc.
    std::list<std::shared_ptr<Sprite>>& getSprites() { return sprites; }

    // Gets animation for a specific global tile id
    const std::shared_ptr<std::vector<AnimationFrame>> getAnimation(unsigned int gid);

    // Sets sprite texture and texture coordinates based on global tile id
    void setSpriteTextureFromGid(sf::Sprite& sprite, unsigned int gid, int frame = 0);

protected:
    // Used in loadFromFile to load information from JSON
    void loadTileset(Json::Value& tileset);
    void loadTileLayer(Json::Value& layer);
    void loadObjectLayer(Json::Value& layer);

    int width;
    int height;
    int tileWidth;
    int tileHeight;

    // Map information
    std::list<std::shared_ptr<Tileset>> tilesets;
    std::map<int, std::shared_ptr<std::vector<AnimationFrame>>> animations;

    // Map content
    std::list<std::shared_ptr<Layer>> layers;
    std::list<std::shared_ptr<Sprite>> sprites;
};

#endif
