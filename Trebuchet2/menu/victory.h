#ifndef TREBUCHET2_VICTORY_H
#define TREBUCHET2_VICTORY_H

#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS1 2

class victory {
public:
    victory(float width, float height);

    ~victory();

    void draw(sf::RenderWindow &window);

    void moveUp();

    void moveDown();

    int getPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menuText[MAX_NUMBER_OF_ITEMS1];
    sf::Text text;
};

#endif
