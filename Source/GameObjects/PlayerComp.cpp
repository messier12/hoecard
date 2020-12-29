//
// Created by dion on 16/12/2020.
//

#include "PlayerComp.h"
#include <algorithm>
#include <random>

PlayerComp::PlayerComp(sf::Vector2f pos, float rot)
    :PlayerBase(pos,rot)
{
   ;
}
void PlayerComp::handleEvent(sf::Event e, const sf::RenderWindow &window)
{
    pickCard();
}
void PlayerComp::update(sf::Time deltaTime) {
    deck.update();
}

void PlayerComp::pickCard()
{
    if(!active)return;
    std::vector<int> selectables = deck.getSelectableCardIndices();
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0,selectables.size()-1);
    deck.buangCardOfIndex(selectables[dist(rd)]);
    deactivate();
}