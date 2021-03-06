#include "StatePlaying.h"


#include "../GUI/Button.h"
#include "../GUI/Textbox.h"
#include "../Game.h"
#include "StateGame.h"
//#include "StateSetting.h"
#include <iostream>

StatePlaying::StatePlaying(Game& game)
:   StateBase   (game)
,   buang_deck(((sf::Vector2f)m_pGame->getWindow().getSize()*0.45f), 0, true)
,   dealer_deck(((sf::Vector2f)m_pGame->getWindow().getSize()*0.35f),0,false)
,   active_player(0)
,   state_sequence(0)
,   turn(0)
,   buang_deck_size(0)
{
//    auto b = std::make_unique<gui::Button>();
//    b->setText("SETTINGS");
//    b->setFunction([this]() {
//        std::cout << "Button 1 clicked!" << '\n';
//    });

//    players.push_back(new PlayerHuman(sf::Vector2f(0,0),acosf(-1)));
    int window_width = m_pGame->getWindow().getSize().x;
    int window_height= m_pGame->getWindow().getSize().y;
    //players.push_back(new PlayerHuman(sf::Vector2f(window_width/2,window_height-150),0));
    //players.push_back(new PlayerHuman(sf::Vector2f(150,window_height/2),acosf(0)));
    //players.push_back(new PlayerComp(sf::Vector2f(window_width/2,150),acosf(-1)));
    //players.push_back(new PlayerHuman(sf::Vector2f(window_width-150,window_height/2),3*acosf(0)));
    players.push_back(new PlayerComp(sf::Vector2f(150,window_height-150),0));
    players.push_back(new PlayerHuman(sf::Vector2f(150,150),acosf(0)));
    players.push_back(new PlayerComp(sf::Vector2f(window_width-150,150),acosf(-1)));
    players.push_back(new PlayerHuman(sf::Vector2f(window_width-150,window_height-150),3*acosf(0)));

    for(auto player : players)
    {
        player->deck.toggleOpen(true);
        player->deck.faceUp();
        player->deck.setBuangDeck(this->buang_deck);
        player->activate();
    }

    char kindarray[] = {'C','D','H','S'};

    for(char i : kindarray)
    {
        for(int j=1;j<=13;j++)
        {
            int value = (j==1)?14:j;
            std::string texture_name = std::to_string(j)+i;
            Card* tmp_card = new Card(i,value,true);
            tmp_card->setTexture(m_pGame->resHolder->textures.get(texture_name)
                                ,m_pGame->resHolder->textures.get("back")
                                ,m_pGame->resHolder->textures.get("highlight")
            );
            tmp_card->scale(0.15);
            dealer_deck.addCard(std::move(*tmp_card));
        }
    }
    dealer_deck.shuffle();
    dealer_deck.closeDeck();
}

void StatePlaying::handleEvent(sf::Event e)
{
//    m_TestMenu.handleEvent(e, m_pGame->getWindow());
    switch(state_sequence)
    {
        case 0:
            break;
        case 1:
        {
            players[active_player]->handleEvent(e,m_pGame->getWindow());
        }
            break;
        case 2:
        {
            if(e.type == sf::Event::KeyPressed)
            {
                if(e.key.code == sf::Keyboard::Return)
                {
                    m_pGame->exitGame();
                }
            }
        }
            break;
        case 4:
            ;;;;
            break;
    }
}

void StatePlaying::handleInput()
{

}

void StatePlaying::update(sf::Time deltaTime)
{
    state_clock += deltaTime;
    switch(state_sequence)
    {
        case 0:
        {
            if(dealer_deck.cardlist.size()>=52-7*players.size())
            {
                if(state_clock >= sf::milliseconds(200))
                {
                    state_clock = sf::Time::Zero;
                    dealer_deck.moveTopCardToDeck(players[active_player]->deck);
                    active_player++;
                    active_player %= players.size();
                }
            }
            else
                state_sequence = 1;
        }
        break;
        case 1:
        {
            if(buang_deck_size != buang_deck.cardlist.size())
            {
                buang_deck_size = buang_deck.cardlist.size();
                players[active_player]->activate();
                nextTurn();
            }
        }
            break;
        case 2:
            break;
        case 4:
        {
            if(!dealer_deck.cardlist.empty())
            {

                if(players[active_player]->deck.selectableKindCount()==0)
                {
                    if(state_clock>=sf::milliseconds(200))
                    {
                        state_clock = sf::Time::Zero;
                        dealer_deck.moveTopCardToDeck(players[active_player]->deck);
                    }
                }
                else
                {
                    state_sequence = 1;
                }
            }
            else
            {
                if(!buang_deck.cardlist.empty())
                {
                    if(state_clock >= sf::milliseconds(200))
                    {
                        state_clock = sf::Time::Zero;
                        buang_deck.moveTopCardToDeck(players[active_player]->deck);
                    }
                }
                else{
                    players[active_player]->deck.setSelectableKind(0);
                    state_sequence = 1;
                }
            }
            buang_deck_size = buang_deck.cardlist.size();
        }
            break;
    }

    dealer_deck.update();
    buang_deck.update();
    for(auto player : players)
        player->update(deltaTime);

    std::cout<<state_sequence<<' '<<active_player<<std::endl;
}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}

void StatePlaying::render(sf::RenderTarget& renderer)
{
//    m_TestMenu.render(renderer);
//    testCard.render(renderer);
    dealer_deck.render(renderer);
    buang_deck.render(renderer);
    for(auto player : players)
    {
        player->deck.render(renderer);
    }
}

void StatePlaying::nextTurn()
{
    turn++;
    turn%=players.size();
    if(turn == 1&&!buang_deck.cardlist.empty())
    {
        for(auto player : players)
            player->deck.setSelectableKind(buang_deck.cardlist.back().getKind());
        active_player++;
        active_player%=players.size();
    }
    else if(turn==0&&buang_deck.cardlist.size()>=players.size())
    {
        auto max_card_it = std::max_element(buang_deck.cardlist.rbegin(),
                                            buang_deck.cardlist.rbegin()+players.size(),
                                            [](Card& a, Card& b){return a.getValue()<b.getValue();});
        int back_step = max_card_it - buang_deck.cardlist.rbegin();
        active_player -= back_step;
        active_player %= players.size();
        if(active_player<0)active_player+=players.size();

        players[active_player]->deck.setSelectableKind(0);
    }
    else
    {
        active_player++;
        active_player %= players.size();
    }


    if(players[active_player]->deck.selectableKindCount() == 0)
    {
        state_sequence = 4;
    }
    else
        state_sequence = 1;
}


void StatePlaying::nextRound()
{
    ;
}
