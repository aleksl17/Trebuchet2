#ifndef TREBUCHET2_PLAYER_H
#define TREBUCHET2_PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Player{
public:
    Player() = default;

    explicit Player(const std::string &imgDirectory){
        if(!pTexture.loadFromFile(imgDirectory)){
            std::cerr << "Could not Load Player Texture From File\n";
        }
        pSprite.setTexture(pTexture);
    }

    void drawPlayer(sf::RenderWindow &window){
        window.draw(pSprite);
    }

    void movePlayer(char direction, float moveSpeed){
        if(direction == 'u'){
            pSprite.move(0, -moveSpeed);
        }
        else if(direction == 'd'){
            pSprite.move(0, moveSpeed);
        }
        else if(direction == 'l'){
            pSprite.move(-moveSpeed, 0);
        }
        else if(direction == 'r'){
            pSprite.move(moveSpeed, 0);
        }
    }

private:
    sf::Texture pTexture;
    sf::Sprite pSprite;
};

#endif
