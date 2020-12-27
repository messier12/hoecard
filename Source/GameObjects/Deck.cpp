//
// Created by dion on 17/12/2020.
//

#include "Deck.h"

Deck::Deck(sf::Vector2f position,float rotation, bool isFaceUp)
: position(position),rotation(rotation),is_face_up(isFaceUp),spacing(20),card_selected(false),open_toggled(false)
{
    ;
}
void Deck::addCard(Card&& card)
{
    if(is_face_up)
        card.faceUp();
    else
        card.faceDown();
    card.setRotation(rotation);
    card.setTargetPosition(position);
    cardlist.push_back(std::move(card));
    if(open_toggled)
        openDeck();
}

void Deck::moveTopCardToDeck( Deck &destination) {
    destination.addCard(std::move(cardlist.back()));
    cardlist.pop_back();
}

void Deck::shuffle()
{
    std::shuffle(cardlist.begin(),cardlist.end(),std::mt19937{std::random_device{}()});
}
sf::Vector2f Deck::getPosition(){
    return position;
}
sf::Vector2f Deck::setPosition(sf::Vector2f pos){
    position = pos;
}

void Deck::render(sf::RenderTarget& renderer)
{
//    if(!is_face_up)
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
    if(open_toggled)
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
    for(auto& card : cardlist)
    {
        card.setHighlight(false);
    }
    for(auto it = cardlist.rbegin();it!=cardlist.rend();it++)
    {
            if((*it).getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window)))
            {
                if((*it).isFaceUp()&&(selectable_kind == (*it).getKind() || selectable_kind == 0))
                (*it).setHighlight(true);
                break;
            }
    }
    if(event.type == sf::Event::MouseButtonPressed)
    {
        auto it = cardlist.rbegin();
        for(;it!=cardlist.rend();it++)
        {
            if(selectable_kind==0||selectable_kind==(*it).getKind())
            {
                if((*it).getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window)))
                {
                    (*it).setHighlight(true);
                    selected_card = &*it;
                    card_selected = true;
//                    selected_card_it = (++temp).base();
                    break;
                }
            }
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        if(!card_selected)return;
        card_selected = false;
        Card& tmp = *selected_card;
        if(EuclideanDistance(tmp.getPosition(),tmp.getTargetPosition())>=50)
        {
            tmp.setHighlight(false);
            buang_deck->addCard(std::move(*selected_card));
            cardlist.erase(std::find(cardlist.begin(),cardlist.end(),*selected_card));
//            cardlist.remove(*selected_card);
        }
        else
        {
            ;
        }
//        openDeck();
    }

}

void Deck::setBuangDeck(Deck& buang_deck)
{
    this->buang_deck = &buang_deck;
}

Card& Deck::getSelectedCard()
{
    return *selected_card;
}
bool Deck::isCardSelected()
{
    return card_selected;
}

void Deck::toggleOpen(bool toggle)
{
   open_toggled = toggle;
}

bool Deck::isAvailable(char kind)
{
   for(auto& card : cardlist)
   {
       if(card.getKind()==kind)
           return true;
   }
   return false;
}

void Deck::setSelectableKind(char kind)
{
    selectable_kind = kind;
}

void Deck::moveCardToDeck(Deck& destination, int index)
{
    if(index>=0&&index<cardlist.size())
    {
        destination.addCard(std::move(cardlist[index]));
        cardlist.erase(cardlist.begin()+index);
    }
}