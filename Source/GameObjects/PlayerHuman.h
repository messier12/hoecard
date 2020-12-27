//
// Created by dion on 16/12/2020.
//

#ifndef SFML_FRAMEWORK_PLAYERHUMAN_H
#define SFML_FRAMEWORK_PLAYERHUMAN_H

#include "PlayerBase.h"

class PlayerHuman : PlayerBase
{
    PlayerHuman(sf::Vector2f position, float rotation);
    void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
    void update(sf::Time deltaTime) override;

};


#endif //SFML_FRAMEWORK_PLAYERHUMAN_H
