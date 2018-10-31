#ifndef TREBUCHET2_PLAYER_H
#define TREBUCHET2_PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>

class player{
public:
    explicit player(const std::string &imgDirectory){
        if(!pTexture.loadFromFile(imgDirectory)){
            std::cerr << "Could not Load Player Texture From File\n";
        }
        pSprite.setTexture(pTexture);
        pSprite.setPosition(50.0f,200.0f);
    }
    ~player() = default;

    void Update(float deltaTime)
    {
        sf::Vector2f movement(0.0f, 0.0f);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            movement.x -= speed * deltaTime;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            movement.x+= speed * deltaTime;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            movement.y -= speed * deltaTime;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            movement.y += speed * deltaTime;

        pSprite.move(movement.x,movement.y);
    }

    void draw(sf::RenderWindow &window){
        window.draw(pSprite);
    }


private:
    sf::Texture pTexture;
    sf::Sprite pSprite;
    float speed = 100;
};

#endif
