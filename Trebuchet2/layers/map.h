#ifndef MAP_H
#define MAP_H

#include <string>
#include <list>

#include "../objects/object.h"

namespace Json
{
    class Value;
}

// Class with a single public static function that loads a map into an object list
class Map
{
public:
    // Load map from Tiled JSON file
    static bool load(const std::string& filename, std::list<Object*>& objects);

private:
    // Handles regular layers
    static void loadLayer(Json::Value& layer, std::list<Object*>& objects, TileSize tileSize);

    // Handles object layers
    static void loadObjects(Json::Value& root, Json::Value& layer, std::list<Object*>& objects, TileSize tileSize);
};

#endif
