//
// Created by dion on 16/12/2020.
//

#include "PlayerBase.h"

PlayerBase::PlayerBase(sf::Vector2f pos, float rot)
: deck(pos,rot,false)
, active(false)
{
    ;
}

void PlayerBase::activate()
{
    active = true;
}
void PlayerBase::deactivate() {
    active = false;
}
bool PlayerBase::isActive()
{
    return active;
}
