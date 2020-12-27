#include "StatePlaying.h"

#include "../GUI/Button.h"
#include "../GUI/Textbox.h"
#include "../Game.h"
#include "StateGame.h"
#include "StateSetting.h"
#include <iostream>

std::string test;

StatePlaying::StatePlaying(Game& game)
:   StateBase   (game)
//,   m_TestMenu  (game.getWindow(), 50)
,   testCard('H',12,true)
,   testDeck(sf::Vector2f(20,20),0,true)
,   testBuangDeck(sf::Vector2f(400,400),0,false)
,   buang_deck(((sf::Vector2f)m_pGame->getWindow().getSize()*0.5f), 0, true)
,   activePlayer(0)
{
    auto b = std::make_unique<gui::Button>();
    b->setText("SETTINGS");
    b->setFunction([this]() {
        std::cout << "Button 1 clicked!" << '\n';
//        m_pGame->pushState<StateSetting>(*m_pGame);
    });

//    testCard.setTexture(m_pGame->resHolder->textures.get("12H"),
//                        m_pGame->resHolder->textures.get("back"),
//                        m_pGame->resHolder->textures.get("highlight"));
//    testCard.setTargetPosition(0,0);
//    testCard.scale(0.25);
    for(int i=1;i<=13;i++)
    {
        Card* tmpCard = new Card('H',((i==1)?14:i),true);
        std::string texname = std::to_string(i)+tmpCard->getKind();
        tmpCard->setTexture(m_pGame->resHolder->textures.get(texname),
                            m_pGame->resHolder->textures.get("back"),
                            m_pGame->resHolder->textures.get("highlight"));
        tmpCard->scale(0.10);
        testDeck.addCard(std::move(*tmpCard));
    }
    for(int i=1;i<=13;i++)
    {
        Card* tmpCard = new Card('D',((i==1)?14:i),true);
        std::string texname = std::to_string(i)+tmpCard->getKind();
        tmpCard->setTexture(m_pGame->resHolder->textures.get(texname),
                            m_pGame->resHolder->textures.get("back"),
                            m_pGame->resHolder->textures.get("highlight"));
        tmpCard->scale(0.10);
        testDeck.addCard(std::move(*tmpCard));
    }
    testDeck.shuffle();
    testDeck.toggleOpen(true);
    testDeck.setSelectableKind(0);

    for(int i=1;i<=13;i++)
    {
        Card* tmpcard = new Card('C',i,false);
        std::string texname = std::to_string(i)+tmpcard->getKind();
        tmpcard->setTexture(m_pGame->resHolder->textures.get(texname),
                            m_pGame->resHolder->textures.get("back"),
                            m_pGame->resHolder->textures.get("highlight"));
        tmpcard->scale(0.10);
        testBuangDeck.addCard(std::move(*tmpcard));
    }
    testBuangDeck.toggleOpen(true);
    testBuangDeck.faceDown();

    testDeck.setBuangDeck(testBuangDeck);
//    m_TestMenu.addWidget(std::move(b));
}

void StatePlaying::handleEvent(sf::Event e)
{
//    m_TestMenu.handleEvent(e, m_pGame->getWindow());
    if(e.type==sf::Event::MouseButtonPressed)
    {
        ;
//        testDeck.faceDown();
    }
    testDeck.handleEvent(e,m_pGame->getWindow());
    if(e.type == sf::Event::KeyPressed)
        if(e.key.code == sf::Keyboard::Space)
        {
          testDeck.shuffle();
        }
}

void StatePlaying::handleInput()
{

}

void StatePlaying::update(sf::Time deltaTime)
{
    testCard.updatePosition();
    if(testDeck.isCardSelected())
    {
        testDeck.getSelectedCard().setPosition((sf::Vector2f)sf::Mouse::getPosition(m_pGame->getWindow()));
    }
    testDeck.update();
    testBuangDeck.update();

}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}

void StatePlaying::render(sf::RenderTarget& renderer)
{
//    m_TestMenu.render(renderer);
//    testCard.render(renderer);
    testDeck.render(renderer);
    testBuangDeck.render(renderer);
}
