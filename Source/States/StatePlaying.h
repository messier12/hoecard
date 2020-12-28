#pragma once

#include <vector>
#include <algorithm>

#include "StateBase.h"
#include "../GUI/StackMenu.h"
#include "../GameObjects/Card.h"
#include "../GameObjects/Deck.h"
#include "../GameObjects/PlayerBase.h"
#include "../GameObjects/PlayerHuman.h"
//#include "../GameObjects/PlayerComp.h"
/**
    Game state for the main part of the game
*/
class StatePlaying : public StateBase
{
    public:
        StatePlaying(Game& game);

        void handleEvent    (sf::Event e)                   override;
        void handleInput    ()                              override;
        void update         (sf::Time deltaTime)            override;
        void fixedUpdate    (sf::Time deltaTime)            override;
        void render         (sf::RenderTarget& renderer)    override;

    private:
//        gui::StackMenu m_TestMenu;
        void nextTurn();
        void nextRound();
        int turn;

        Deck buang_deck;
        int buang_deck_size;
        Deck dealer_deck;
        int active_player;
        int state_sequence;
        sf::Time state_clock;

        std::vector<PlayerBase*> players;


};
