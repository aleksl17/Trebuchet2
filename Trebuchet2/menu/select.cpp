#include "select.h"

#include <iostream>

select::select(float width, float height)
{
    if (!font.loadFromFile("data/ShadowsIntoLight.ttf"))
    {
        std::cout << "Failed to load font." << std::endl;
    }

    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString("Select Map");
    text.setPosition(240, 20);

    menuText[0].setFont(font);
    menuText[0].setFillColor(sf::Color::Red);
    menuText[0].setString("Map 1: Tundra");
    menuText[0].setPosition(sf::Vector2f(width / 4, height / (MAP_CHOICES + 6) * 1));

    menuText[1].setFont(font);
    menuText[1].setFillColor(sf::Color::White);
    menuText[1].setString("Map 2: Desert");
    menuText[1].setPosition(sf::Vector2f(width / 4, height / (MAP_CHOICES + 6) * 2));

    menuText[2].setFont(font);
    menuText[2].setFillColor(sf::Color::White);
    menuText[2].setString("Map 3: Forest");
    menuText[2].setPosition(sf::Vector2f(width / 4, height / (MAP_CHOICES + 6) * 3));

    menuText[3].setFont(font);
    menuText[3].setFillColor(sf::Color::White);
    menuText[3].setString("Back");
    menuText[3].setPosition(sf::Vector2f(width / 4, height / (MAP_CHOICES + 6) * 4));

    selectedItemIndex = 0;
}

select::~select()
{
}

void select::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < MAP_CHOICES; i++)
    {
        window.draw(menuText[i]);
        window.draw(text);
    }
}

void select::moveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menuText[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuText[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void select::moveDown()
{
    if (selectedItemIndex + 1 < MAP_CHOICES)
    {
        menuText[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuText[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
