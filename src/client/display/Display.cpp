/*
** EPITECH PROJECT, 2023
** Display.cpp
** File description:
** Display
*/

#include "client/display/Display.hpp"
#include "GameEngine/Events.hpp"

#include <iostream>
Screen::Display::Display(GameState state) : _state(0), _gameState(state)
{
    const int fps = 60;
    int monitor = GetCurrentMonitor();

    InitWindow(480, 240, "R-Type");
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    ToggleFullscreen();
    SetTargetFPS(fps);
}

bool Screen::Display::isOpen()
{
    return !WindowShouldClose();
}

Screen::Display::GameState Screen::Display::getGameState() const
{
    return _gameState;
}

Screen::Display::MenuState Screen::Display::getMenuState() const
{
    return _menuState;
}

void Screen::Display::setMenuState(MenuState state)
{
    _menuState = state;
}

const std::string &Screen::Display::getHostName() const
{
    return _hostName;
}

int Screen::Display::getPort() const
{
    if (_port.empty()) {
        return -1;
    }
    return std::stoi(_port);
}

void Screen::Display::beginUpdate()
{
    this->detectActionMenu();
    this->update();
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void Screen::Display::endUpdate()
{
    EndDrawing();
}

void Screen::Display::update()
{
    if (_gameState == GameState::MENU) {
        if (_menuState == MenuState::CONNECTED) {
            _menuState = MenuState::WAITING_FOR_PLAYER_INPUT;
            _gameState = GameState::GAME;
        }
    }
}

///// Menu
static Rectangle getInputRect(int posX, int posY)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const int widthRect = 0.5 * screenWidth;
    const int heightRect = 0.05 * screenHeight;

    return { (float)posX, (float)posY, (float)widthRect, (float)heightRect };
}

void Screen::Display::displayHostNameInput()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const int posXRect = 0.25 * screenWidth;
    const int posYRect = 0.4 * screenHeight;
    _hostNameclickableZone = getInputRect(posXRect, posYRect);
    const int lineSize = std::max(1., 0.1 * _hostNameclickableZone.width);
    const int posXText = posXRect + 0.05 * _hostNameclickableZone.width;
    const int posYText = posYRect + 0.001 * _hostNameclickableZone.height;
    const int fontSizeText = _hostNameclickableZone.height;

    _hostNameclickableZone.x = posXRect;
    _hostNameclickableZone.y = posYRect;
    if (_hostName.empty()) {
        DrawRectangleLines(posXRect, posYRect, _hostNameclickableZone.width, _hostNameclickableZone.height, RED);
    } else {
        DrawRectangleLines(posXRect, posYRect, _hostNameclickableZone.width, _hostNameclickableZone.height, BLUE);
    }
    DrawText(_hostName.c_str(), posXText, posYText, fontSizeText, LIGHTGRAY);
}

void Screen::Display::displayPortInput()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const int posXRect = 0.25 * screenWidth;
    const int posYRect = 0.5 * screenHeight;
    _portclickableZone = getInputRect(posXRect, posYRect);
    const int lineSize = std::max(1., 0.1 * _portclickableZone.width);
    const int posXText = posXRect + 0.05 * _portclickableZone.width;
    const int posYText = posYRect + 0.001 * _portclickableZone.height;
    const int fontSizeText = _portclickableZone.height;

    _portclickableZone.x = posXRect;
    _portclickableZone.y = posYRect;
    if (_hostName.empty()) {
        DrawRectangleLines(posXRect, posYRect, _portclickableZone.width, _portclickableZone.height, RED);
    } else {
        DrawRectangleLines(posXRect, posYRect, _portclickableZone.width, _portclickableZone.height, BLUE);
    }
    DrawText(_port.c_str(), posXText, posYText, fontSizeText, LIGHTGRAY);
}

void Screen::Display::displayConnectionButton()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const int posXRect = 0.25 * screenWidth;
    const int posYRect = 0.75 * screenHeight;
    _connectionclickableZone = getInputRect(posXRect, posYRect);
    const int lineSize = std::max(1., 0.1 * _connectionclickableZone.width);
    const int posXText = posXRect + 0.05 * _connectionclickableZone.width;
    const int posYText = posYRect + 0.001 * _connectionclickableZone.height;
    const int fontSizeText = _connectionclickableZone.height;

    if (_hostName.empty() || _port.empty()) {
        DrawRectangleRec(_connectionclickableZone, RED);
    } else {
        DrawRectangleRec(_connectionclickableZone, BLUE);
    }
    DrawText("Connexion", posXText, posYText, fontSizeText, WHITE);
}

void Screen::Display::detectActionMenu()
{
    int keyPressed = 0;
    int key = 0;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        mouseClickedMenu();
    }
    keyPressed = GetCharPressed();
    if (keyPressed != 0) {
        keyPressededMenu(keyPressed, key);
    }
    keyPressed = GetCharPressed();
    key = GetKeyPressed();
    if (keyPressed != 0 || key != 0) {
        keyPressededMenu(keyPressed, key);
    }
}

void Screen::Display::mouseClickedMenu()
{
    float mouseX = GetMouseX();
    float mouseY = GetMouseY();
    const Vector2 mouse = { mouseX, mouseY };

    if (CheckCollisionPointRec(mouse, _hostNameclickableZone)) {
        _state = 1;
    } else if (CheckCollisionPointRec(mouse, _portclickableZone)) {
        _state = 2;
    } else {
        _state = 0;
    }
    if (CheckCollisionPointRec(mouse, _connectionclickableZone)) {
        std::cout << "\n Try Connexion\nwith:" << _hostName << " | " << _port << "\n\n";
        _menuState = MenuState::CONNECTING;
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


