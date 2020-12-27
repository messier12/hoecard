//
// Created by dion on 16/12/2020.
//

#ifndef SFML_FRAMEWORK_PLAYERBASE_H
#define SFML_FRAMEWORK_PLAYERBASE_H
#include "Card.h"
#include "Deck.h"

class PlayerBase
{
public:
    PlayerBase(sf::Vector2f,float);

    PlayerBase(const PlayerBase& other) = delete;
    PlayerBase& operator=(const PlayerBase& other) = delete;
    Deck deck;
    virtual void handleEvent(sf::Event e,const sf::RenderWindow& window) = 0;
    virtual void update(sf::Time deltaTime) = 0;
    void activate();
    void deactivate();
    bool isActive();
protected:
    bool active;


};


#endif //SFML_FRAMEWORK_PLAYERBASE_H
