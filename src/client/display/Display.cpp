/*
** EPITECH PROJECT, 2023
** Display.cpp
** File description:
** Display
*/

#include "client/display/Display.hpp"
#include "GameEngine/Events.hpp"

Screen::Display::Display(GameState state) : _state(0), _gameState(state)
{
    int monitor = Raylib::GetCurrentMonitor();
    const int screenWidth = Raylib::GetMonitorWidth(monitor);
    const int screenHeight = Raylib::GetMonitorHeight(monitor);
    const int fps = 60;
    Raylib::InitWindow(screenWidth, screenHeight, "R-Type");
    Raylib::ToggleFullscreen();
    Raylib::SetTargetFPS(fps);
}

void Screen::Display::displayWindow(GameEngine::GameEngine &engine)
{
    auto &clientNetwork = Network::ClientNetwork::getInstance();

    while (!Raylib::WindowShouldClose()) {
        Raylib::BeginDrawing();
        Raylib::ClearBackground(Raylib::RAYWHITE);
        if (_gameState == GameState::MENU) {
            detectActionMenu();
            drawMenu();
        } else if (_gameState == GameState::GAME) {
            GameEngine::Events::Type type;
            while (GameEngine::Events::poll(type)) {
                switch (type) {
                case GameEngine::Events::Type::PLAYER_UP:
                    clientNetwork.sendMovement(Network::Movement::UP);
                    break;
                case GameEngine::Events::Type::PLAYER_DOWN:
                    clientNetwork.sendMovement(Network::Movement::DOWN);
                    break;
                case GameEngine::Events::Type::PLAYER_LEFT:
                    clientNetwork.sendMovement(Network::Movement::LEFT);
                    break;
                case GameEngine::Events::Type::PLAYER_RIGHT:
                    clientNetwork.sendMovement(Network::Movement::RIGHT);
                    break;
                case GameEngine::Events::Type::PLAYER_SHOOT:
                    clientNetwork.sendAction(Network::Action::SHOOT);
                    break;
                case GameEngine::Events::Type::PLAYER_DROP:
                    clientNetwork.sendAction(Network::Action::DROP);
                    break;
                default:
                    break;
                }
            }
            drawGame(engine);
        }
        Raylib::EndDrawing();
    }
    Raylib::CloseWindow();
}

///// Menu
void Screen::Display::displayHostNameInput()
{
    const int posXRect = 100;
    const int posYRect = 100;
    const int widthRect = 500;
    const int heightRect = 30;
    const int lineSize = 30;
    const int posXText = 105;
    const int posYText = 105;
    const int fontSizeText = 20;

    _hostNameclickableZone = { posXRect, posYRect, widthRect, heightRect };
    if (_hostName.empty()) {
        Raylib::DrawRectangleLines(posXRect, posYRect, widthRect, heightRect, Raylib::RED);
    } else {
        Raylib::DrawRectangleLines(posXRect, posYRect, widthRect, heightRect, Raylib::BLUE);
    }
    Raylib::DrawText(_hostName.c_str(), posXText, posYText, fontSizeText, Raylib::LIGHTGRAY);
}

void Screen::Display::displayPortInput()
{
    const int posXRect = 100;
    const int posYRect = 150;
    const int widthRect = 500;
    const int heightRect = 30;
    const int lineSize = 30;
    const int posXText = 105;
    const int posYText = 155;
    const int fontSizeText = 20;

    _portclickableZone = { posXRect, posYRect, widthRect, heightRect };
    if (_port.empty()) {
        Raylib::DrawRectangleLines(posXRect, posYRect, widthRect, heightRect, Raylib::RED);
    } else {
        Raylib::DrawRectangleLines(posXRect, posYRect, widthRect, heightRect, Raylib::BLUE);
    }
    Raylib::DrawText(_port.c_str(), posXText, posYText, fontSizeText, Raylib::LIGHTGRAY);
}

void Screen::Display::displayConnectionButton()
{
    const Raylib::Rectangle defaultClickableZone = { 100, 210, 110, 30 };
    const int lineSize = 30;
    const int posXText = 105;
    const int posYText = 215;
    const int fontSizeText = 20;

    if (_hostName.empty() || _port.empty()) {
        _connectionclickableZone = defaultClickableZone;
        Raylib::DrawRectangleRec(_connectionclickableZone, Raylib::RED);
    } else {
        _connectionclickableZone = defaultClickableZone;
        Raylib::DrawRectangleRec(_connectionclickableZone, Raylib::BLUE);
    }
    Raylib::DrawText("Connexion", posXText, posYText, fontSizeText, Raylib::WHITE);
}

void Screen::Display::detectActionMenu()
{
    int keyPressed = 0;
    int key = 0;

    if (Raylib::IsMouseButtonPressed(Raylib::MOUSE_LEFT_BUTTON)) {
        mouseClickedMenu();
    }
    keyPressed = Raylib::GetCharPressed();
    if (keyPressed != 0) {
        keyPressededMenu(keyPressed, key);
    }
    keyPressed = Raylib::GetCharPressed();
    key = Raylib::GetKeyPressed();
    if (keyPressed != 0 || key != 0) {
        keyPressededMenu(keyPressed, key);
    }
}

void Screen::Display::mouseClickedMenu()
{
    float mouseX = Raylib::GetMouseX();
    float mouseY = Raylib::GetMouseY();
    const Raylib::Vector2 mouse = { mouseX, mouseY };

    if (Raylib::CheckCollisionPointRec(mouse, _hostNameclickableZone)) {
        _state = 1;
    } else if (Raylib::CheckCollisionPointRec(mouse, _portclickableZone)) {
        _state = 2;
    } else {
        _state = 0;
    }
    if (Raylib::CheckCollisionPointRec(mouse, _connectionclickableZone)) {
        std::cout << "\n Try Connexion\nwith:" << _hostName << " | " << _port << "\n\n";
        //TODO: handle basic error (empty hostname, empty port, invalid port (ex: chocolat instead of 8080)) on the graphic side
        //connect return a bool to let us know if the connection was successful or not
        _client.connect(_hostName, std::stoi(_port));
        _gameState = GameState::GAME;
    }
}

void Screen::Display::keyPressededMenu(int KeyPressed, int key)
{
    const int deleteKey = 259;

    if (key == deleteKey) {
        if (_state == 1) {
            _hostName.erase(_hostName.size() - 1);
        }
        if (_state == 2) {
            _port.erase(_port.size() - 1);
        }
    }
    if (KeyPressed == 0) {
        return;
    }
    if (_state == 1) {
        if (KeyPressed >= '0' && KeyPressed <= '9' || KeyPressed == '.') {
            _hostName += KeyPressed;
        }
    }

    if (_state == 2) {
        if (KeyPressed >= '0' && KeyPressed <= '9') {
            _port += KeyPressed;
        }
    }
}

void Screen::Display::drawMenu()
{
    displayHostNameInput();
    displayPortInput();
    displayConnectionButton();
}

///// Game

void Screen::Display::drawGame(GameEngine::GameEngine &engine)
{
    engine.run();
}


