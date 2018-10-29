#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <list>
#include <map>

#include "layer/layer.h"

namespace Json
{
    class Value;
}

class Object;

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

    // Call this function after loadFromFile to get a list of objects that you can use to draw etc.
    std::list<std::shared_ptr<Object>>& getObjects() { return objects; }

    // Sets sprite texture and texture coordinates based on global tile id
    void setSpriteTextureFromGid(sf::Sprite& sprite, unsigned int gid, int frame = 0);

    // Gets animation for a specific global tile id
    const std::vector<std::shared_ptr<AnimationFrame>>& getAnimation(unsigned int gid);

private:
    // Used in loadFromFile to load information from JSON
    void loadTileset(Json::Value& tileset);
    void loadTileLayer(Json::Value& layer);
    void loadObjectLayer(Json::Value& layer);

    int width;
    int height;
    int tileWidth;
    int tileHeight;

    std::list<std::shared_ptr<Tileset>> tilesets;
    std::map<int, std::vector<std::shared_ptr<AnimationFrame>>> animations;

    std::list<std::shared_ptr<Object>> objects;
};

#endif
