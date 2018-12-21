#include "victory.h"
#include <iostream>

victory::victory(float width, float height) {
    if (!font.loadFromFile("data/ShadowsIntoLight.ttf")) {
        std::cout << "Failed to load font." << std::endl;
    }

    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString("Trebuchet won");
    text.setPosition(width / 4, 20);

    menuText[0].setFont(font);
    menuText[0].setFillColor(sf::Color::Red);
    menuText[0].setString("new map");
    menuText[0].setPosition(sf::Vector2f(width / 4, height / (MAX_NUMBER_OF_ITEMS1 + 4) * 1));

    menuText[1].setFont(font);
    menuText[1].setFillColor(sf::Color::White);
    menuText[1].setString("Exit");
    menuText[1].setPosition(sf::Vector2f(width / 4, height / (MAX_NUMBER_OF_ITEMS1 + 4) * 2));

    selectedItemIndex = 0;
}

victory::~victory() {
}

void victory::draw(sf::RenderWindow &window) {
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS1; i++) {
        window.draw(menuText[i]);
        window.draw(text);
    }
}

void victory::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuText[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuText[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void victory::moveDown() {
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS1) {
        menuText[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuText[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
