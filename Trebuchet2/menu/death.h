#ifndef TREBUCHET2_DEATH_H
#define TREBUCHET2_DEATH_H

#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS0 2

class death
{
public:
    death(float width, float height);
    ~death();

    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menuText[MAX_NUMBER_OF_ITEMS0];
    sf::Text text;
};

#endif
