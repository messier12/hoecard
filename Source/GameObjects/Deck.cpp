//
// Created by dion on 17/12/2020.
//

#include "Deck.h"

Deck::Deck(sf::Vector2f position,float rotation, bool isFaceUp)
: position(position),rotation(rotation),isFaceUp(isFaceUp),spacing(20),cardSelected(false),openToggled(false)
{
    ;
}
void Deck::addCard(Card&& card)
{
    if(isFaceUp)
        card.faceUp();
    else
        card.faceDown();
    card.setRotation(rotation);
    card.setTargetPosition(position);
    cardlist.push_back(std::move(card));
}

void Deck::moveTopCardToDeck( Deck &destination) {
    destination.addCard(std::move(cardlist.back()));
    cardlist.pop_back();
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
//    if(!isFaceUp)
//    {
//        cardlist.back().render(renderer);
//        return;
//    }
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
    if(openToggled)
    {
        openDeck();
    }
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
            if((*it).getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window)))
            {
                (*it).setHighlight(true);
                selected_card = &*it;
                cardSelected = true;
                auto temp = it;
//                selected_card_it = (++temp).base();
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
            buangDeck->addCard(std::move(*selected_card));
//            cardlist.erase(std::find(cardlist.begin(),cardlist.end(),*selected_card));
            cardlist.remove(*selected_card);
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

void Deck::toggleOpen(bool toggle)
{
   openToggled = toggle;
}