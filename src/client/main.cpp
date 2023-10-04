/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include "client/display/Display.hpp"
#include "client/network.hpp"
#include "GameEngine/GameEngine.hpp"

static void menuLoop(Screen::Display &window)
{
    window.drawMenu();
    if (window.getMenuState() == Screen::Display::MenuState::CONNECTING) {
        if (Network::startClientNetwork(window.getHostName(), window.getPort())) {
            window.setMenuState(Screen::Display::MenuState::CONNECTED);
        } else {
            window.setMenuState(Screen::Display::MenuState::WAITING_FOR_PLAYER_INPUT);
        }
    }
}

static void gameLoop(Screen::Display &window, GameEngine::GameEngine &engine)
{
    Network::updateClientNetwork();
    window.drawGame(engine);
}

int main()
{
    Screen::Display window;
    // // Screen::Display window(Screen::Display::GameState::GAME); // Uncomment this line to start the game directly
    GameEngine::GameEngine engine = GameEngine::createEngine();
    while (Screen::Display::isOpen()) {
        window.beginUpdate();
        switch (window.getGameState()) {
        case Screen::Display::GameState::MENU:
            menuLoop(window);
            break;
        case Screen::Display::GameState::GAME:
            gameLoop(window, engine);
            break;
        }
        window.endUpdate();
    }
    Network::stopClientNetwork();
    return 0;
}
