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
    Deck(sf::Vector2f position, float rotation, bool isFaceUp);
    std::vector<Card> cardlist;
    void shuffle();
    void moveTopCardToDeck(Deck& destination);
    void moveCardToDeck(Deck& destination, int index);
    sf::Vector2f getPosition();
    sf::Vector2f setPosition(sf::Vector2f pos);
    void addCard(Card&& card);
    void render(sf::RenderTarget& renderer);
    void openDeck();
    void closeDeck();
    void faceUp();
    void faceDown();

    void update();
    void handleEvent(sf::Event event, const sf::RenderWindow& window );
    void setSpacing(float spacing);
    void setBuangDeck(Deck& buangDeck);

    Card& getSelectedCard();
    bool isCardSelected();

    bool isAvailable(char kind);

    void toggleOpen(bool toggle);
    void setSelectableKind(char kind);
private:
    char selectable_kind;
    bool card_selected;
    Card* selected_card;
    std::list<std::reference_wrapper<Card>>::iterator selected_card_it;
    Deck* buang_deck;
    float rotation;
    sf::Vector2f position;
    bool is_face_up;
    bool open_toggled;
    float spacing;

};


#endif //SFML_FRAMEWORK_DECK_H
