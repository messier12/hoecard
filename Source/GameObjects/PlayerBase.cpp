//
// Created by dion on 16/12/2020.
//

#include "PlayerBase.h"


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
