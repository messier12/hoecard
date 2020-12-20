//
// Created by dion on 17/12/2020.
//

#include "Deck.h"

Deck::Deck(sf::Vector2f position,float rotation, bool isFaceUp)
: position(position),rotation(rotation),isFaceUp(isFaceUp),spacing(20),cardSelected(false)
{
    ;
}
void Deck::addCard(Card& card)
{
    card.setRotation(rotation);
    card.setTargetPosition(position);
    cardlist.push_back(card);
}

void Deck::moveTopCardToDeck( Deck &destination) {
    Card& topCard = (cardlist.back());
    cardlist.pop_back();
    destination.addCard(topCard);
}

void Deck::shuffle()
{
//    std::shuffle(cardlist.begin(),cardlist.end(),std::mt19937{std::random_device{}()});
}
sf::Vector2f Deck::getPosition(){
    return position;
}
sf::Vector2f Deck::setPosition(sf::Vector2f pos){
    position = pos;
}

void Deck::render(sf::RenderTarget& renderer)
{
    if(!isFaceUp)
    {
        Card& card = cardlist.back();
        card.render(renderer);
        return;
    }
    for(Card& card : cardlist){
        card.render(renderer);
    }
}
void Deck::openDeck()
{
    int i = 0;
    for(Card& card : cardlist)
    {
       sf::Vector2f openDistance = sf::Vector2f(cos(rotation),sin(rotation))*((float)spacing*i);
       card.setTargetPosition(position+openDistance);
       i++;
    }
}
void Deck::closeDeck()
{
    for(Card& card : cardlist)
    {
        card.setTargetPosition(position);
    }
}

void Deck::faceUp()
{
    for(Card& card : cardlist)
    {
        card.faceUp();
    }
}
void Deck::faceDown()
{
    for(Card& card : cardlist)
    {
        card.faceDown();
    }
}

void Deck::setSpacing(float spacing)
{
    this->spacing = spacing;
}

void Deck::update()
{
    for(Card& card : cardlist)
    {
        card.updatePosition();
    }
}
void Deck::handleEvent(sf::Event event, const sf::RenderWindow& window)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        auto it = cardlist.rbegin();
        for(;it!=cardlist.rend();it++)
        {
            Card& tmp = *it;
            if(tmp.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window)))
            {
                tmp.setHighlight(true);
                selected_card = &tmp;
                cardSelected = true;
                auto tmp = it;
                selected_card_it = (++tmp).base();
                break;
            }
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        if(!cardSelected)return;
        cardSelected = false;
        Card& tmp = *selected_card;
        if(EuclideanDistance(tmp.getPosition(),tmp.getTargetPosition())>=50)
        {
            tmp.setHighlight(false);
            buangDeck->addCard(*selected_card);
//            cardlist.erase(selected_card_it);
        }
        else
        {
            ;
        }
//        openDeck();
    }

}

void Deck::setBuangDeck(Deck& buangDeck)
{
    this->buangDeck = &buangDeck;
}

Card& Deck::getSelectedCard()
{
    return *selected_card;
}
bool Deck::isCardSelected()
{
    return cardSelected;
}