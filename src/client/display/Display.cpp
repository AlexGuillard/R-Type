/*
** EPITECH PROJECT, 2023
** Display.cpp
** File description:
** Display
*/

#include <cmath>

#include "GameEngine/Events.hpp"
#include "client/display/Display.hpp"

uint16_t Screen::Display::cameraWidth = Screen::Display::defaultCameraWidth;
uint16_t Screen::Display::cameraHeight = Screen::Display::defaultCameraHeight;
Camera2D Screen::Display::camera = {
    .offset = {0, 0},
    .target = {0, 0},
    .rotation = 0.F,
    .zoom = 1
};

Screen::Display::Display(GameState state) : _gameState(state)
{
    InitWindow(0, 0, "R-Type");
    const int fps = 60;

    this->toggleFullScreen();
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

void Screen::Display::updateShake()
{
    const double divisor = 10.F;
    const int minHighTremor = 50;
    const int maxHighTremor = 150;
    const int minLowTremor = 1;
    const int maxLowTremor = 50;
    static int xTremor1 = GetRandomValue(minHighTremor, maxHighTremor) / divisor;
    static int xTremor2 = GetRandomValue(minLowTremor, maxLowTremor) / divisor;
    static int yTremor1 = GetRandomValue(minHighTremor, maxHighTremor) / divisor;
    static int yTremor2 = GetRandomValue(minLowTremor, maxLowTremor) / divisor;

    if (_cameraShake.t > 0) {
        _cameraShake.t = std::max(0.F, _cameraShake.t - GetFrameTime());
        Screen::Display::camera.offset.x =
            (
                std::sin(_cameraShake.t * xTremor1 * static_cast<int>(_cameraShake.intensity)) +
                std::cos(_cameraShake.t * xTremor2 * static_cast<int>(_cameraShake.intensity))) *
            _cameraShake.xRange * Screen::Display::cameraWidth;
        Screen::Display::camera.offset.y =
            (
                std::cos(_cameraShake.t * yTremor1 * static_cast<int>(_cameraShake.intensity)) +
                std::sin(_cameraShake.t * yTremor2 * static_cast<int>(_cameraShake.intensity))) *
            _cameraShake.yRange * Screen::Display::cameraHeight;
    } else {
        xTremor1 = GetRandomValue(minHighTremor, maxHighTremor) / divisor;
        xTremor2 = GetRandomValue(minLowTremor, maxLowTremor) / divisor;
        yTremor1 = GetRandomValue(minHighTremor, maxHighTremor) / divisor;
        yTremor2 = GetRandomValue(minLowTremor, maxLowTremor) / divisor;
        const float drag = 0.9;

        if (Screen::Display::camera.offset.x != 0) {
            Screen::Display::camera.offset.x *= drag;
        }
        if (Screen::Display::camera.offset.y != 0) {
            Screen::Display::camera.offset.y *= drag;
        }
        _cameraShake.t = 0;
    }
}

void Screen::Display::update()
{
    if (_gameState == GameState::MENU) {
        if (_menuState == MenuState::CONNECTED) {
            _menuState = MenuState::WAITING_FOR_PLAYER_INPUT;
            _gameState = GameState::GAME;
        }
    }
    for (auto it = GameEngine::Events::begin(); it != GameEngine::Events::end(); ++it) {
        GameEngine::Events::Type type = *it;
        if (type == GameEngine::Events::Type::PLAYER_SHOOT) {
            this->shake();
        }
    }
    this->updateShake();
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
    Color color = _buttonFocusedKO;

    _hostNameclickableZone.x = posXRect;
    _hostNameclickableZone.y = posYRect;
    if (_hostName.empty()) {
        if (_state == InputState::HOSTNAME) {
            color = _buttonFocusedKO;
        } else {
            color = _buttonUnfocusedKO;
        }
    } else {
        if (_state == InputState::HOSTNAME) {
            color = _buttonFocusedOK;
        } else {
            color = _buttonUnfocusedOK;
        }
    }
    DrawRectangleLines(posXRect, posYRect, _hostNameclickableZone.width, _hostNameclickableZone.height, color);
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
    Color color = _buttonFocusedKO;

    _portclickableZone.x = posXRect;
    _portclickableZone.y = posYRect;
    if (_port.empty()) {
        if (_state == InputState::PORT) {
            color = _buttonFocusedKO;
        } else {
            color = _buttonUnfocusedKO;
        }
    } else {
        if (_state == InputState::PORT) {
            color = _buttonFocusedOK;
        } else {
            color = _buttonUnfocusedOK;
        }
    }
    DrawRectangleLines(posXRect, posYRect, _portclickableZone.width, _portclickableZone.height, color);
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
        DrawRectangleRec(_connectionclickableZone, _buttonFocusedKO);
    } else {
        DrawRectangleRec(_connectionclickableZone, _buttonFocusedOK);
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
        _state = InputState::HOSTNAME;
    } else if (CheckCollisionPointRec(mouse, _portclickableZone)) {
        _state = InputState::PORT;
    } else {
        _state = InputState::NONE;
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
        if (_state == InputState::HOSTNAME && !_hostName.empty()) {
            _hostName.erase(_hostName.size() - 1);
        }
        if (_state == InputState::PORT && !_port.empty()) {
            _port.erase(_port.size() - 1);
        }
    }
    if (KeyPressed == 0) {
        return;
    }
    if (_state == InputState::HOSTNAME) {
        if (KeyPressed >= '0' && KeyPressed <= '9' || KeyPressed == '.') {
            _hostName += KeyPressed;
        }
    }

    if (_state == InputState::PORT) {
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


Screen::Display &Screen::Display::center()
{
    int monitor = GetCurrentMonitor();
    int hMonitorWidth = GetMonitorWidth(monitor) / 2;
    int hMonitorHeight = GetMonitorHeight(monitor) / 2;
    int hWindowWidth = _windowSize.x / 2;
    int hWindowHeight = _windowSize.y / 2;

    SetWindowPosition(hMonitorWidth - hWindowWidth, hMonitorHeight - hWindowHeight);
    return *this;
}

Screen::Display &Screen::Display::resizeWindow(
    uint16_t width, uint16_t height)
{
    SetWindowSize(width, height);
    _windowSize = Vector2(static_cast<float>(width), static_cast<float>(height));
    this->resizeCamera(Screen::Display::cameraWidth, Screen::Display::cameraHeight);
    return *this;
}

Screen::Display &Screen::Display::resizeCamera(
    uint16_t width, uint16_t height)
{
    const int windowWidth = _windowSize.x;
    const int windowHeight = _windowSize.y;
    const float windowRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    const float cameraRatio = static_cast<float>(width) / static_cast<float>(height);
    const float windowToCameraRatio = static_cast<float>(windowWidth) / static_cast<float>(width);
    const float epsilon = 0.01;
    const float ratioDiff = (windowRatio - cameraRatio) * (static_cast<int>((windowRatio - cameraRatio) >= 0) * 2 - 1);

    Screen::Display::cameraWidth = width;
    Screen::Display::cameraHeight = height;
    if (ratioDiff > epsilon) {
        Screen::Display::cameraHeight = width / windowRatio;
        std::cout << Screen::Display::cameraHeight << std::endl;
        return this->resizeCamera(Screen::Display::cameraWidth, Screen::Display::cameraHeight);
    }
    Screen::Display::camera.zoom = windowToCameraRatio;
    return *this;
}

Screen::Display &Screen::Display::moveCamera(int16_t posX, int16_t posY)
{
    Screen::Display::camera.target.x += posX;
    Screen::Display::camera.target.y += posY;
    return *this;
}

Screen::Display &Screen::Display::setCameraPosition(int16_t posX, int16_t posY)
{
    Screen::Display::camera.target.x = posX;
    Screen::Display::camera.target.y = posY;
    return *this;
}

Screen::Display &Screen::Display::shake(
    float time,
    enum CameraShakeIntensity intensity,
    float xRange,
    float yRange
)
{
    _cameraShake = {
        .t = time,
        .xRange = xRange,
        .yRange = yRange,
        .intensity = intensity,
        ._startTime = GetTime()
    };
    return *this;
}

bool Screen::Display::toggleFullScreen()
{
    const int monitor = GetCurrentMonitor();
    const int width = GetMonitorWidth(monitor);
    const int height = GetMonitorHeight(monitor);

    if (!IsWindowFullscreen()) {
        this->resizeWindow(width, height);
    }
    ToggleFullscreen();
    return IsWindowFullscreen();
}

void Screen::Display::beginDrawCamera()
{
    BeginMode2D(Screen::Display::camera);
}

void Screen::Display::endDrawCamera()
{
    EndMode2D();
}

Vector2 Screen::Display::getCameraSize()
{
    return Vector2(Screen::Display::cameraWidth, Screen::Display::cameraHeight);
}
