#ifndef TREBUCHET2_MENU_H
#define TREBUCHET2_MENU_H

#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3

class menu
{
public:
    menu(float width, float height);
    ~menu();

    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menuText[MAX_NUMBER_OF_ITEMS];
};

#endif
