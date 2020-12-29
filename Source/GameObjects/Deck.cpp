//
// Created by dion on 17/12/2020.
//

#include "Deck.h"
Deck::Deck(sf::Vector2f position,float rotation, bool isFaceUp)
: position(position),rotation(rotation),is_face_up(isFaceUp),spacing(20),card_selected(false),open_toggled(false),selectable_kind(0)
{
    ;
}
void Deck::addCard(Card&& card)
{
    if(is_face_up)
        card.faceUp();
    else
        card.faceDown();

    card.setTargetRotation(this->rotation);
    card.setTargetPosition(position);
    cardlist.push_back(std::move(card));
    if(open_toggled)
        openDeck();
}

void Deck::moveTopCardToDeck( Deck &destination)
{
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
    float radian_rot = rotation*acosf(-1)/180.f;
    for(Card& card : cardlist)
    {
        sf::Vector2f openDistance = sf::Vector2f(cos(radian_rot),sin(radian_rot))*((float)spacing*i);
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
    is_face_up = true;
    for(Card& card : cardlist)
    {
        card.faceUp();
    }
}
void Deck::faceDown()
{
    is_face_up = false;
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
        if(card_selected)
        {
            if(&getSelectedCard() != &card)
                card.updatePosition();
        }
        else
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
        for(int i = cardlist.size()-1;i>=0;i--)
        {
            if(selectable_kind==0||selectable_kind==cardlist[i].getKind())
            {
                if(cardlist[i].getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window)))
                {
                    cardlist[i].setHighlight(true);
                    card_selected = true;
                    selected_card_index = i;
                    break;
                }
            }
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        if(!card_selected)return;
        card_selected = false;
        Card& tmp = cardlist[selected_card_index];
        if(EuclideanDistance(tmp.getPosition(),tmp.getTargetPosition())>=50)
        {
            tmp.setHighlight(false);
            buang_deck->addCard(std::move(cardlist[selected_card_index]));
//            cardlist.erase(std::find(cardlist.begin(),cardlist.end(),*selected_card));
//            cardlist.remove(*selected_card);
//            cardlist.erase(selected_card_it);
            cardlist.erase(cardlist.begin()+selected_card_index);
        }
        else
        {
            ;
        }
//        openDeck();
    }

    if(card_selected)
        cardlist[selected_card_index].setPosition((sf::Vector2f)sf::Mouse::getPosition(window));

}

void Deck::setBuangDeck(Deck& deck)
{
    this->buang_deck = &deck;
}

Card& Deck::getSelectedCard()
{
    return cardlist[selected_card_index];
}
bool Deck::isCardSelected() const
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

void Deck::buangCardOfIndex(int index)
{
    if(index>=0&&index<cardlist.size())
    {
        buang_deck->addCard(std::move(cardlist[index]));
        cardlist.erase(cardlist.begin()+index);
    }
}

sf::Vector2f Deck::getBoundingBox() {
    sf::Vector2f cardsize(cardlist.back().getGlobalBounds().width,cardlist.back().getGlobalBounds().height);
    return cardlist.back().getPosition() + cardsize - cardlist.front().getPosition();
}

float Deck::getRotation(){
    return rotation;
}

int Deck::selectableKindCount() {
    if(selectable_kind == 0)
        return cardlist.size();

    return std::count_if(cardlist.begin(),cardlist.end(),[this](Card& a){return a.getKind()==selectable_kind;});
}

std::vector<int> Deck::getSelectableCardIndices()
{
    if(selectable_kind == 0)
    {
            std::vector<int> ret(cardlist.size());
            std::iota(ret.begin(),ret.end(),0);
            return ret;
    }
    std::vector<int> ret;
    for(int i=0;i<cardlist.size();i++)
        if(cardlist[i].getKind() == selectable_kind)
            ret.push_back(i);

    return ret;

}