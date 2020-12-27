//
// Created by dion on 16/12/2020.
//

#ifndef SFML_FRAMEWORK_PLAYERCOMP_H
#define SFML_FRAMEWORK_PLAYERCOMP_H
#include "PlayerBase.h"


class PlayerComp : PlayerBase
{
public:
    PlayerComp(sf::Vector2f, float);
    void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
    void update(sf::Time deltaTime) override;
private:
    bool unavailableCards[4][13];
    void pickCard();
};


#endif //SFML_FRAMEWORK_PLAYERCOMP_H
