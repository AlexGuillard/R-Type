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
            window.setGameState(Screen::Display::GameState::WAITINGROOM);
            window.setMenuState(Screen::Display::MenuState::CONNECTED);
        } else {
            window.setMenuState(Screen::Display::MenuState::WAITING_FOR_PLAYER_INPUT);
        }
    }
}

static bool isConnected = false;

static void gameLoop([[maybe_unused]] Screen::Display &window, GameEngine::GameEngine &engine, Network::ConnectionType type)
{
    // if (Network::returnIsCoUDP()) {
    //     Screen::Display::setGameState(Screen::Display::GameState::GAME);
    // }

    Network::updateClientNetworkUDP();
    Screen::Display::drawGame(engine);
}

//Sizes of the button Play dont want to put it on the function caus its a loop
Rectangle playButtonRect = { 320, 240, 160, 60 };

static void waitRoomLoop([[maybe_unused]] Screen::Display &window, GameEngine::GameEngine &engine, Network::ConnectionType type)
{
    Network::updateClientNetworkTCP(Screen::Display::getPlayButton());
    Screen::Display::drawWaitingRoom(playButtonRect);
}

int rtype_client()
{
    Screen::Display window(Screen::Display::GameState::GAME);
    GameEngine::GameEngine engine = GameEngine::createClientEngine();
    while (Screen::Display::isOpen()) {
        window.beginUpdate();
        switch (window.getGameState()) {
        case Screen::Display::GameState::MENU:
            menuLoop(window);
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
    Network::stopClientNetwork();
    return 0;
}
