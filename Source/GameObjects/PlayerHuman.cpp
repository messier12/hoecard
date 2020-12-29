//
// Created by dion on 16/12/2020.
//

#include "PlayerHuman.h"

PlayerHuman::PlayerHuman(sf::Vector2f position, float rotation)
:PlayerBase(position,rotation)
{
    ;
}

void PlayerHuman::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    deck.handleEvent(e,window);
}

void PlayerHuman::update(sf::Time deltaTime)
{
    deck.update();
}