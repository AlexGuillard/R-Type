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

static void menuLoop(Screen::Display &window, GameEngine::GameEngine &engine)
{
    window.drawMenu();
    if (window.getMenuState() == Screen::Display::MenuState::CONNECTING) {
        if (Network::startClientNetwork(window.getHostName(), window.getPort(), 0, Network::ConnectionType::TCP, engine)) {
            window.setGameState(Screen::Display::GameState::WAITINGROOM);
            window.setMenuState(Screen::Display::MenuState::CONNECTED);
            window.setErrorConnection(false);
        } else {
            window.setMenuState(Screen::Display::MenuState::WAITING_FOR_PLAYER_INPUT);
            window.setErrorConnection(true);
        }
    }

    if (window.getErrorConnection())
        window.displayErrorConnection();
}

static bool isConnected = false;

static void gameLoop([[maybe_unused]] Screen::Display &window, GameEngine::GameEngine &engine, Network::ConnectionType type)
{

    Network::updateClientNetworkUDP();
    Screen::Display::drawGame(engine);
}

static void waitRoomLoop([[maybe_unused]] Screen::Display &window, GameEngine::GameEngine &engine, Network::ConnectionType type)
{
    Network::updateClientNetworkTCP(Screen::Display::getPlayButton());

    if (!Network::check401Error()) {
        window.drawWaitingRoom();
    } else {
        window.displayError401();
    }

    if (Network::returnIsCoUDP()) {
        window.setGameState(Screen::Display::GameState::GAME);
    }

}

int rtype_client()
{
    Screen::Display window(Screen::Display::GameState::MENU);
    GameEngine::GameEngine engine = GameEngine::createClientEngine();

    while (Screen::Display::isOpen()) {
        window.beginUpdate();
        switch (window.getGameState()) {
        case Screen::Display::GameState::MENU:
            menuLoop(window, engine);
            break;
        case Screen::Display::GameState::WAITINGROOM:
            waitRoomLoop(window, engine, Network::ConnectionType::TCP);
            break;
        case Screen::Display::GameState::GAME:
            gameLoop(window, engine, Network::ConnectionType::UDP);
            break;
        }
        Screen::Display::endUpdate();
    }
    //actually make the client crash on Windows
    // Network::stopClientNetwork();
    return 0;
}
