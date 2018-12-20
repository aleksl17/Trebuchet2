#include "menu.h"

#include <iostream>

menu::menu(float width, float height) {
    if (!font.loadFromFile("data/ShadowsIntoLight.ttf")) {
        std::cout << "Failed to load font." << std::endl;
    }

    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString("Trebuchet 2");
    text.setPosition(240, 20);

    menuText[0].setFont(font);
    menuText[0].setFillColor(sf::Color::Red);
    menuText[0].setString("Play");
    menuText[0].setPosition(sf::Vector2f(width / 4, height / (MAX_NUMBER_OF_ITEMS + 4) * 1));

    menuText[1].setFont(font);
    menuText[1].setFillColor(sf::Color::White);
    menuText[1].setString("Options");
    menuText[1].setPosition(sf::Vector2f(width / 4, height / (MAX_NUMBER_OF_ITEMS + 4) * 2));

    menuText[2].setFont(font);
    menuText[2].setFillColor(sf::Color::White);
    menuText[2].setString("Exit");
    menuText[2].setPosition(sf::Vector2f(width / 4, height / (MAX_NUMBER_OF_ITEMS + 4) * 3));

    selectedItemIndex = 0;
}

void menu::draw(sf::RenderWindow &window) {
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menuText[i]);
        window.draw(text);
    }
}

void menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuText[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuText[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void menu::moveDown() {
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menuText[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuText[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

