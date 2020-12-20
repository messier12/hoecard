
#ifndef SFML_FRAMEWORK_STATESETTING_H
#define SFML_FRAMEWORK_STATESETTING_H

#include "StateBase.h"
#include "../GUI/StackMenu.h"

class StateSetting : public StateBase
{
public:
    StateSetting(Game& game);

    void handleEvent    (sf::Event e)                   override;
    void handleInput    ()                              override;
    void update         (sf::Time deltaTime)            override;
    void fixedUpdate    (sf::Time deltaTime)            override;
    void render         (sf::RenderTarget& renderer)    override;

private:
    gui::StackMenu settings_menu;
};


#endif //SFML_FRAMEWORK_STATESETTING_H
