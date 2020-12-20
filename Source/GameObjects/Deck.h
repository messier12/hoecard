//
// Created by dion on 17/12/2020.
//

#ifndef SFML_FRAMEWORK_DECK_H
#define SFML_FRAMEWORK_DECK_H

#include "Card.h"
#include <list>
#include <bits/stdc++.h>
#include <random>
#include <algorithm>
#include "../Util/NonCopyable.h"
class Deck : NonCopyable
{
public:
    Deck(sf::Vector2f position, float roation, bool isFaceUp);
    std::list<std::reference_wrapper<Card>> cardlist;
    void shuffle();
    void moveTopCardToDeck(Deck& destination);
    sf::Vector2f getPosition();
    sf::Vector2f setPosition(sf::Vector2f pos);
    void addCard(Card& card);
    void render(sf::RenderTarget& renderer);
    void openDeck();
    void closeDeck();
    void faceUp();
    void faceDown();

    void update();
    void handleEvent(sf::Event event, const sf::RenderWindow& window );
    void setSpacing(float spacing);
private:
    float rotation;
    sf::Vector2f position;
    bool isFaceUp;
    float spacing;

};


#endif //SFML_FRAMEWORK_DECK_H
