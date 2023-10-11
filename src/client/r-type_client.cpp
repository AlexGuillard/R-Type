/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** r-type_client
*/

#include "client/r-type_client.hpp"
#include "client/display/Display.hpp"
#include "client/network.hpp"
#include "GameEngine/GameEngine.hpp"

static void menuLoop(Screen::Display &window)
{
    window.drawMenu();
    if (window.getMenuState() == Screen::Display::MenuState::CONNECTING) {
        if (Network::startClientNetwork(window.getHostName(), window.getPort(), 0, Network::ConnectionType::TCP)) {
            window.setMenuState(Screen::Display::MenuState::CONNECTED);
        } else {
            window.setMenuState(Screen::Display::MenuState::WAITING_FOR_PLAYER_INPUT);
        }
    }
}

static bool isConnected = false;

static void gameLoop([[maybe_unused]] Screen::Display &window, GameEngine::GameEngine &engine, Network::ConnectionType type)
{
    if (!isConnected) {
        Network::startClientNetwork(window.getHostName(), 0, 6084, type);
        isConnected = true;
    }
    Network::updateClientNetwork(type);
    Screen::Display::drawGame(engine);
}

int rtype_client()
{
    Screen::Display window;
    GameEngine::GameEngine engine = GameEngine::createEngine();
    while (Screen::Display::isOpen()) {
        window.beginUpdate();
        switch (window.getGameState()) {
        case Screen::Display::GameState::MENU:
            menuLoop(window);
            break;
        case Screen::Display::GameState::GAME:
            gameLoop(window, engine, Network::ConnectionType::UDP);
            break;
        }
        Screen::Display::endUpdate();
    }
    Network::stopClientNetwork();
    return 0;
}
