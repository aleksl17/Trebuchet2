#ifndef TREBUCHET2_SELECT_H
#define TREBUCHET2_SELECT_H

#include "SFML/Graphics.hpp"

#define MAP_CHOICES 4

class select
{
public:
    select(float width, float height);
    ~select();

    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menuText[MAP_CHOICES];
    sf::Text text;
};

#endif
