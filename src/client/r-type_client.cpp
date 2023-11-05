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
        if (Network::startClientNetwork(window.getHostName(), window.getPort(),Network::ConnectionType::TCP, window.getMultiState(), window.getModeState(), engine)) {
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
    if (Network::getLoosingCondition()) {
        window.setGameState(Screen::Display::GameState::LOOSING);
    }
    if (Network::getWinningCondition()) {
        window.setGameState(Screen::Display::GameState::WINNING);
    }
    if (Network::getLeftWinningCondition()) {
        window.setGameState(Screen::Display::GameState::LEFT_WINNING);
    }
    if (Network::getRightWinningCondition()) {
        window.setGameState(Screen::Display::GameState::RIGHT_WINNING);
    }

}

static void looseLoop([[maybe_unused]] Screen::Display &window, GameEngine::GameEngine &engine)
{
    Screen::Display::drawLoose(window, engine);
}

static void winLoop([[maybe_unused]] Screen::Display &window, GameEngine::GameEngine &engine)
{
    Screen::Display::drawWin(window, engine);
}

static void leftWinLoop([[maybe_unused]] Screen::Display &window, GameEngine::GameEngine &engine)
{
    Screen::Display::drawLeftRightWin(window, engine, true);
}

static void rightWinLoop([[maybe_unused]] Screen::Display &window, GameEngine::GameEngine &engine)
{
    Screen::Display::drawLeftRightWin(window, engine, false);
}

static void waitRoomLoop([[maybe_unused]] Screen::Display &window, GameEngine::GameEngine &engine, Network::ConnectionType type)
{
    Network::updateClientNetworkTCP(Screen::Display::getPlayButton(), window.getModeState());

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
        case Screen::Display::GameState::LOOSING:
            looseLoop(window, engine);
            break;
        case Screen::Display::GameState::WINNING:
            winLoop(window, engine);
            break;
        case Screen::Display::GameState::LEFT_WINNING:
            leftWinLoop(window, engine);
            break;
        case Screen::Display::GameState::RIGHT_WINNING:
            rightWinLoop(window, engine);
            break;
        }
        Screen::Display::endUpdate();
    }
    //actually make the client crash on Windows
    // Network::stopClientNetwork();
    return 0;
}
