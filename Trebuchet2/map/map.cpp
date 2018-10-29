#include <memory>
#include <fstream>
#include <cstring>
#include <vector>

#include <jsoncpp/json/json.h>
#include <SFML/Graphics.hpp>

#include "map.h"
#include "objects/object.h"
#include "objects/sprite.h"
#include "layer/layer.h"

bool Map::loadFromFile(const std::string& filename)
{
    // Clear existing data
    tilesets.clear();
    animations.clear();
    objects.clear();

    // Will contain the data we read in
    Json::Value root;

    // Parses the file
    Json::Reader reader;

    // Stream used for reading the data file. The data file has been saved as JSON in Tiled
    std::ifstream file(filename);

    // Read data from file into root object
    bool parsingSuccessful = reader.parse(file, root);

    // Check for success
    if (!parsingSuccessful)
        return false;

    // Map properties
    width = root["width"].asInt();
    height = root["height"].asInt();
    tileWidth = root["tilewidth"].asInt();
    tileHeight = root["tileheight"].asInt();

    // Load all tilesets
    for (Json::Value& tileset: root["tilesets"])
        loadTileset(tileset);

        // Read in each layer
    for (Json::Value& layer: root["layers"])
    {
        if (layer["name"].asString() != "objects")
            loadTileLayer(layer);
        else
            loadObjectLayer(layer);
    }

    return true;
}

void Map::setSpriteTextureFromGid(sf::Sprite &sprite, unsigned int gid, int frame)
{
    // Extract flip flags
    unsigned int flipFlags = gid >> 29;

    // Remove flip flags
    gid &= ~(0b111 << 29);

    auto& animation = animations[gid];

    // Lookup the right animation gid frame, if any
    if (frame > 0 && frame < (int)animation.size())
        gid = animation[frame]->gid;

    // Find the correct tileset for this gid
    auto tileset = *std::find_if(tilesets.rbegin(), tilesets.rend(), [gid](auto ts) { return gid >= ts->firstGid; } );

    // Calculate x and y positions in the tileset
    int tileid = gid - tileset->firstGid;
    int x = (tileid % tileset->columns) * (tileset->tileWidth + tileset->spacing);
    int y = (tileid / tileset->columns) * (tileset->tileWidth + tileset->spacing);

    int textureRectWidth = tileset->tileWidth;
    int textureRectHeight = tileset->tileHeight;

    // Vertical flip
    if (flipFlags & 2)
    {
        textureRectHeight *= -1;
        y += tileset->tileHeight;
    }

    // Horizontal flip
    if (flipFlags & 4)
    {
        textureRectWidth *= -1;
        x += tileset->tileWidth;
    }

    // Set the texture and texture source rectangle
    sprite.setTexture(tileset->texture);
    sprite.setTextureRect(sf::IntRect(x, y, textureRectWidth, textureRectHeight));
}

const std::vector<std::shared_ptr<AnimationFrame>>& Map::getAnimation(unsigned int gid)
{
    return animations[gid];
}

void Map::loadTileset(Json::Value& tileset)
{
    auto ts = std::make_shared<Tileset>();

    ts->firstGid  = tileset["firstgid"].asUInt();
    ts->columns  = tileset["columns"].asInt();
    ts->imageWidth  = tileset["imagewidth"].asInt();
    ts->imageHeight  = tileset["imageheight"].asInt();
    ts->tileWidth  = tileset["tilewidth"].asInt();
    ts->tileHeight  = tileset["tileheight"].asInt();
    ts->spacing  = tileset["spacing"].asInt();

    ts->texture.loadFromFile("data/" + tileset["image"].asString());

    tilesets.push_back(ts);

    // Load all animations
    for (Json::Value& tile: tileset["tiles"])
    {
        int animationId = ts->firstGid + tile["id"].asInt();

        for (Json::Value& animation: tile["animation"]) {
            unsigned int gid = ts->firstGid + animation["tileid"].asUInt();
            int duration = animation["duration"].asInt();
            animations[animationId].push_back(std::make_shared<AnimationFrame>(gid, duration));
        }
    }
}

void Map::loadTileLayer(Json::Value& layer)
{
    auto tmp = std::make_shared<Layer>(*this);

    // Store info on layer
    tmp->id = layer["id"].asInt();
    tmp->name = layer["name"].asString();
    tmp->visible = layer["visible"].asBool();
    tmp->width = layer["width"].asInt();
    tmp->height = layer["height"].asInt();
    tmp->tilemap = new unsigned int[tmp->width * tmp->height];

    // Read in tilemap
    for (size_t i = 0; i < layer["data"].size(); i++)
        tmp->tilemap[i] = layer["data"][(int) i].asUInt();

    objects.push_back(tmp);
}

void Map::loadObjectLayer(Json::Value& layer)
{
    // Get all objects from layer
    for (Json::Value& object: layer["objects"])
    {
        auto sprite = std::make_shared<Sprite>(*this);

        // Load basic object info
        sprite->id = object["id"].asInt();
        sprite->gid = object["gid"].asInt();
        sprite->x = object["x"].asInt();
        sprite->y = object["y"].asInt();
        sprite->width = object["width"].asInt();
        sprite->height = object["height"].asInt();
        sprite->y -= sprite->height; // Not sure why Tiled anchor in the bottom left...

        objects.push_back(sprite);
    }
}
