#include <memory>
#include <fstream>

#include <jsoncpp/json/json.h>

#include <SFML/Graphics/Sprite.hpp>

#include "map.h"
#include "objects/object.h"
#include "layer/layer.h"
#include "objects/sprite.h"

// Public functions

bool Map::loadFromFile(const std::string &filename) {
    // Clear existing data
    tilesets.clear();
    animations.clear();
    layers.clear();
    sprites.clear();

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
    for (Json::Value &tileset: root["tilesets"])
        loadTileset(tileset);

    // Read in each layer
    for (Json::Value &layer: root["layers"]) {
        if (layer["name"].asString() != "objects")
            loadTileLayer(layer);
        else
            loadObjectLayer(layer);
    }

    return true;
}

std::shared_ptr<Layer> Map::getLayer(const std::string &name) {
    for (auto &layer: layers) {
        if (layer->name == name)
            return layer;
    }

    return std::shared_ptr<Layer>();
}

const std::shared_ptr<std::vector<AnimationFrame>> Map::getAnimation(unsigned int gid) {
    auto animationIt = animations.find(gid);

    if (animationIt != animations.end())
        return animationIt->second;

    return std::shared_ptr<std::vector<AnimationFrame>>();
}

void Map::setSpriteTextureFromGid(sf::Sprite &sprite, unsigned int gid, int frame) {
    // Extract flip flags
    unsigned int flipFlags = gid >> 29;

    // Remove flip flags
    gid &= ~(0b111 << 29);

    // Look for an animation for this gid
    auto animationIt = animations.find(gid);

    if (animationIt != animations.end()) {
        auto &animation = *animationIt->second;

        if (frame >= 0 && frame < (int) animation.size())
            gid = animation[frame].gid;
    }

    // Find the correct tileset for this gid
    auto tileset = *std::find_if(tilesets.rbegin(), tilesets.rend(), [gid](auto ts) { return gid >= ts->firstGid; });

    // Calculate x and y positions in the tileset
    int tileid = gid - tileset->firstGid;
    int x = (tileid % tileset->columns) * (tileset->tileWidth + tileset->spacing);
    int y = (tileid / tileset->columns) * (tileset->tileWidth + tileset->spacing);

    int textureRectWidth = tileset->tileWidth;
    int textureRectHeight = tileset->tileHeight;

    // Vertical flip
    if (flipFlags & 2) {
        textureRectHeight *= -1;
        y += tileset->tileHeight;
    }

    // Horizontal flip
    if (flipFlags & 4) {
        textureRectWidth *= -1;
        x += tileset->tileWidth;
    }

    // Set the texture and texture source rectangle
    sprite.setTexture(tileset->texture);
    sprite.setTextureRect(sf::IntRect(x, y, textureRectWidth, textureRectHeight));
}

// Protected functions

void Map::loadTileset(Json::Value &tileset) {
    auto ts = std::make_shared<Tileset>();

    ts->firstGid = tileset["firstgid"].asUInt();
    ts->columns = tileset["columns"].asInt();
    ts->imageWidth = tileset["imagewidth"].asInt();
    ts->imageHeight = tileset["imageheight"].asInt();
    ts->tileWidth = tileset["tilewidth"].asInt();
    ts->tileHeight = tileset["tileheight"].asInt();
    ts->spacing = tileset["spacing"].asInt();

    ts->texture.loadFromFile("data/" + tileset["image"].asString());

    tilesets.push_back(ts);

    // Load all animations
    for (Json::Value &tile: tileset["tiles"]) {
        int animationId = ts->firstGid + tile["id"].asInt();

        for (Json::Value &animation: tile["animation"]) {
            unsigned int gid = ts->firstGid + animation["tileid"].asUInt();
            int duration = animation["duration"].asInt();

            if (animations.find(animationId) == animations.end())
                animations[animationId] = std::make_shared<std::vector<AnimationFrame>>();

            animations[animationId]->push_back(AnimationFrame(gid, duration));
        }
    }
}

void Map::loadTileLayer(Json::Value &layer) {
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

    layers.push_back(tmp);
}

void Map::loadObjectLayer(Json::Value &layer) {
    // Get all objects from layer
    for (Json::Value &object: layer["objects"]) {
        auto sprite = std::make_shared<Sprite>(*this);

        // Load basic object info
        sprite->id = object["id"].asInt();
        sprite->gid = object["gid"].asUInt();
        sprite->x = object["x"].asInt();
        sprite->y = object["y"].asInt();
        sprite->width = object["width"].asInt();
        sprite->height = object["height"].asInt();
        sprite->y -= sprite->height; // Not sure why Tiled anchor in the bottom left...

        sprites.push_back(sprite);
    }
}
