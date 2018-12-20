#include "death.h"

#include <iostream>

death::death(float width, float height)
{
    if (!font.loadFromFile("data/ShadowsIntoLight.ttf"))
    {
        std::cout << "Failed to load font." << std::endl;
    }
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString("Catapult won");
    text.setPosition(width/4,20);

    menuText[0].setFont(font);
    menuText[0].setFillColor(sf::Color::Red);
    menuText[0].setString("Play Again");
    menuText[0].setPosition(sf::Vector2f(width / 4, height / (MAX_NUMBER_OF_ITEMS0 + 4) * 1));

    menuText[1].setFont(font);
    menuText[1].setFillColor(sf::Color::White);
    menuText[1].setString("Exit");
    menuText[1].setPosition(sf::Vector2f(width / 4, height / (MAX_NUMBER_OF_ITEMS0 + 4) * 2));

    selectedItemIndex = 0;
}

death::~death()
{
}

void death::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS0; i++)
    {
        window.draw(menuText[i]);
        window.draw(text);
    }
}

void death::moveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menuText[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuText[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void death::moveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS0)
    {
        menuText[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuText[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

