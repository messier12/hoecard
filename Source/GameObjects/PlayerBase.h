//
// Created by dion on 16/12/2020.
//

#ifndef SFML_FRAMEWORK_PLAYERBASE_H
#define SFML_FRAMEWORK_PLAYERBASE_H
#include "Card.h"
#include "Deck.h"

class PlayerBase {
protected:

public:

    PlayerBase(const PlayerBase& other) = delete;
    PlayerBase& operator=(const PlayerBase& other) = delete;
    Deck deck;
    virtual void handleEvent(sf::Event e,const sf::RenderWindow& window);
    void activate();
    void deactivate();
    bool isActive();
private:
    bool active;


};


#endif //SFML_FRAMEWORK_PLAYERBASE_H
