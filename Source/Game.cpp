#include "Game.h"

#include "States/StatePlaying.h"

#include <iostream>

Game::Game()
:   window    ({1000, 1000}, "Kartu Cangkul")
{
    resHolder = &ResourceHolder::get();
    window.setPosition({window.getPosition().x, 0});
    window.setFramerateLimit(60);
    pushState<StatePlaying>(*this);

}

//Runs the main loop
void Game::run()
{
    constexpr unsigned TPS = 30; //ticks per seconds
    const sf::Time     timePerUpdate = sf::seconds(1.0f / float(TPS));
    unsigned ticks = 0;

    sf::Clock timer;
    auto lastTime = sf::Time::Zero;
    auto lag      = sf::Time::Zero;

    //Main loop of the game
    while (window.isOpen() && !states.empty()) {
        auto& state = getCurrentState();

        //Get times
        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        lag += elapsed;

        //Real time update
        state.handleInput();
        state.update(elapsed);
        counter.update();

        //Fixed time update
        while (lag >= timePerUpdate)
        {
            ticks++;
            lag -= timePerUpdate;
            state.fixedUpdate(elapsed);
        }

        //Render
        window.clear();
        state.render(window);
        counter.draw(window);
        window.display();


        //Handle window events
        handleEvent();
        tryPop();
    }
}

//Tries to pop the current game state
void Game::tryPop()
{
    if (shouldPop) {
        shouldPop = false;
        if (shouldExit) {
            while(!states.empty())states.pop();
//            states.clear();
            return;
        }
        else if (shouldChageState) {
            shouldChageState = false;
            states.pop();
            pushState(std::move(change));
            return;
        }
        
        states.pop();
    }
}

//Handles window events, called every frame
void Game::handleEvent()
{
    sf::Event e;

    while (window.pollEvent(e)) {
        getCurrentState().handleEvent(e);
        switch (e.type) {
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;

        }
    }
}

//Returns a reference to the current game state
StateBase& Game::getCurrentState()
{
    return *states.top();
}

void Game::pushState(std::unique_ptr<StateBase> state)
{
    states.push(std::move(state));
}

//Flags a boolean for the game to pop state
void Game::popState()
{
    shouldPop = true;
}

void Game::exitGame()
{
    shouldPop = true;
    shouldExit = true;
}


//on tin
const sf::RenderWindow& Game::getWindow() const
{
    return window;
}
