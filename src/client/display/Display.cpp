/*
** EPITECH PROJECT, 2023
** Display.cpp
** File description:
** Display
*/

#include <cmath>

#include "GameEngine/Events.hpp"
#include "client/display/Display.hpp"
#include <cstring>

uint16_t Screen::Display::cameraWidth = Screen::Display::defaultCameraWidth;
uint16_t Screen::Display::cameraHeight = Screen::Display::defaultCameraHeight;
Camera2D Screen::Display::camera = {
    .offset = {0, 0},
    .target = {0, 0},
    .rotation = 0.F,
    .zoom = 1
};

bool Screen::Display::_playButton = false;

Color GetRandomColor() {
    return Color(
        (unsigned char)GetRandomValue(0, 255),
        (unsigned char)GetRandomValue(0, 255),
        (unsigned char)GetRandomValue(0, 255),
        255
    );
}

Screen::Display::Display(GameState state) : _gameState(state)
{
    InitWindow(0, 0, "R-Type");
    InitAudioDevice();
    _sound.playMusic(Assets::AssetsIndex::MUSIC_WAV, ".wav");
    //This is for developing caus its anoying to switch between fullscreen and windowed and it make crash my linux
    // We will remove this when the game will be finished or for presentation
    this->resizeWindow(1920, 1080).center();
    // this->toggleFullScreen();
    SetTargetFPS(Constants::frameRate);
    _errorConnection = false;
    for (int i = 0; i < MAX_DUST_PARTICLES; i++) {
        _dustParticles[i].position.x = GetRandomValue(20, GetScreenWidth() - 20);
        _dustParticles[i].position.y = GetRandomValue(-20, 0);
        _dustParticles[i].speed = static_cast<float>(GetRandomValue(5, 50));
        _dustParticles[i].color = {
            static_cast<unsigned char>(GetRandomValue(50, 200)),
            static_cast<unsigned char>(GetRandomValue(50, 200)),
            static_cast<unsigned char>(GetRandomValue(150, 255)),
            static_cast<unsigned char>(GetRandomValue(50, 200))
        };
    }
    for (int i = 0; i < MAX_NEBULA_PARTICLES; i++) {
        _nebulaParticles[i].position.x = GetRandomValue(20, GetScreenWidth() - 20);
        _nebulaParticles[i].position.y = GetRandomValue(-20, 0);
        _nebulaParticles[i].speed = static_cast<float>(GetRandomValue(5, 50));
        _nebulaParticles[i].color = {
            static_cast<unsigned char>(GetRandomValue(50, 200)),
            static_cast<unsigned char>(GetRandomValue(50, 200)),
            static_cast<unsigned char>(GetRandomValue(150, 255)),
            static_cast<unsigned char>(GetRandomValue(50, 200))
        };
    }
}

Screen::Display::~Display()
{
    Screen::Display::camera.zoom = 1;
    BeginDrawing();
    BeginMode2D(Screen::Display::camera);
    EndMode2D();
    EndDrawing();
    CloseAudioDevice();
    CloseWindow();
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

void Screen::Display::setGameState(GameState state)
{
    _gameState = state;
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
    _sound.updateMusicStream();
    this->detectActionMenu();
    this->update();
    BeginDrawing();
    if (_errorConnection)
        ClearBackground(ORANGE);
    else if (_gameState == Screen::Display::GameState::LOOSING)
        ClearBackground(BLACK);
    else
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
    this->updateShake();
}

bool Screen::Display::getPlayButton()
{
    return _playButton;
}

///// Menu

void Screen::Display::setErrorConnection(bool error)
{
    _errorConnection = error;
}

bool Screen::Display::getErrorConnection()const
{
    return _errorConnection;
}

Enums::MultiState Screen::Display::getMultiState() const
{
    return _multiState;
}

Enums::ModeSelect Screen::Display::getModeState() const
{
    return _modeState;
}

void Screen::Display::displayErrorConnection()
{
    DrawText("Error while the connection with server, try again", 150, 100, 64, RAYWHITE);
}

void Screen::Display::displayError401()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    ClearBackground(BLACK);
    const int maxParticles = 100;
    static std::vector<Particle> particles(maxParticles);

    for (int i = 0; i < maxParticles; i++) {
        if (particles[i].active) {
            particles[i].position.y += particles[i].speed;
            if (particles[i].position.y > screenHeight) {
                particles[i].position = Vector2(static_cast<float>(GetRandomValue(0, screenWidth)), -10.0);
                particles[i].speed = static_cast<float>(GetRandomValue(1, 5));
            }
            DrawCircleV(particles[i].position, particles[i].radius, particles[i].color);
        } else {
            particles[i].position = Vector2(static_cast<float>(GetRandomValue(0, screenWidth)), -10.0);
            particles[i].color = GetRandomColor();
            particles[i].radius = static_cast<float>(GetRandomValue(1, 3));
            particles[i].speed = static_cast<float>(GetRandomValue(1, 5));
            particles[i].active = true;
        }
    }
    const char* text = "Error :\nRoom already full or is already running,\nthe server can handle only one room at a time,\nplease wait the game end to restart the server...";
    Vector2 textPosition = {(float)(screenWidth - MeasureText(text, 20)) / 4.5f, (float)(screenHeight / 2 - 300)};
    Color textColor = WHITE;
    float letterSpacing = 10.0f;
    DrawTextEx(GetFontDefault(), text, textPosition, 40, letterSpacing, textColor);
    static float spinnerAngle = 0.0f;
    Vector2 spinnerPosition = {(float)(screenWidth / 2), (float)(screenHeight / 2 + 50)};
    float spinnerRadius = 30.0f;
    spinnerAngle += 5.0f;

    if (spinnerAngle >= 360.0f)
        spinnerAngle = 0.0f;

    DrawCircleLines(spinnerPosition.x, spinnerPosition.y, spinnerRadius, RAYWHITE);
    DrawCircleSector(spinnerPosition, spinnerRadius, 90, 90 + spinnerAngle, 24, GREEN);
    EndDrawing();
}

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
            DrawText("Host Name", posXText - 30, posYText + 0.08 * _hostNameclickableZone.height, fontSizeText, LIGHTGRAY);
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
            DrawText("Port", posXText - 30, posYText + 0.08 * _portclickableZone.height, fontSizeText, LIGHTGRAY);
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

void Screen::Display::displayConnectionStateButton()
{
    _soloclickableZone = { 700, 675, 160, 60 };
    _multiclickableZone = { 1000, 675, 160, 60 };


    DrawRectangleRec({ 690, 665, 180, 80 }, SKYBLUE);
    DrawRectangleRec({ 990, 665, 180, 80 }, SKYBLUE);

    if (_multiState == Enums::MultiState::SOLO)
        DrawRectangleRec(_soloclickableZone, SKYBLUE);
    else
        DrawRectangleRec(_soloclickableZone, LIGHTGRAY);
    DrawText("Solo", _soloclickableZone.x + 45, _soloclickableZone.y + 15, 32, RAYWHITE);

    if (_multiState == Enums::MultiState::MULTI)
        DrawRectangleRec(_multiclickableZone, SKYBLUE);
    else
        DrawRectangleRec(_multiclickableZone, LIGHTGRAY);
    DrawText("Multi", _multiclickableZone.x + 40, _multiclickableZone.y + 15, 32, RAYWHITE);
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

    if (IsKeyPressed(KEY_SPACE) && getGameState() == GameState::GAME) {
        this->_sound.playSound(Assets::AssetsIndex::SPACESHIP_SHOTTING_OGG, ".ogg");
    }

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
    if (_gameState == Display::GameState::WAITINGROOM) {
        detectActionWaitingRoom();
    }
}

void Screen::Display::detectActionWaitingRoom()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), _playclickableZone) && !_playButton) {
            _playButton = true;
        }
        if (CheckCollisionPointRec(GetMousePosition(), _regularclickableZone)) {
            _modeState = Enums::ModeSelect::REGULAR;
        }
        if (CheckCollisionPointRec(GetMousePosition(), _pvpclickableZone)) {
            _modeState = Enums::ModeSelect::PVP;
        }
        if (CheckCollisionPointRec(GetMousePosition(), _friendlyFireclickableZone)) {
            _modeState = Enums::ModeSelect::FRIENDLYFIRE;
        }
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
    if (CheckCollisionPointRec(mouse, _soloclickableZone)) {
        _multiState = Enums::MultiState::SOLO;
    }
    if (CheckCollisionPointRec(mouse, _multiclickableZone)) {
        _multiState = Enums::MultiState::MULTI;
    }
    if (CheckCollisionPointRec(mouse, _connectionclickableZone)) {
        if (_port != "" && _hostName != "") {
            std::cout << "\n Try Connexion\nwith:" << _hostName << " | " << _port << "\n\n";
            _menuState = MenuState::CONNECTING;
        }
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

void Screen::Display::setSpaceBackground(bool menu)
{
    ClearBackground(BLACK);

    for (int i = 0; i < MAX_DUST_PARTICLES; i++) {
        if (_dustParticles[i].position.x <= 0) {
            _dustParticles[i].position.x = GetScreenWidth();
            _dustParticles[i].position.y = GetRandomValue(20, GetScreenHeight() - 20);
            _dustParticles[i].speed = static_cast<float>(GetRandomValue(1, 5) * 5);
            _dustParticles[i].color = {
                static_cast<unsigned char>(GetRandomValue(200, 255)),
                static_cast<unsigned char>(GetRandomValue(200, 255)),
                static_cast<unsigned char>(GetRandomValue(200, 255)),
                static_cast<unsigned char>(GetRandomValue(50, 100))
            };
        } else {
            _dustParticles[i].position.x -= _dustParticles[i].speed;

            if (_dustParticles[i].position.x + 20 < 0) {
                _dustParticles[i].position.x = GetScreenWidth();
                _dustParticles[i].position.y = GetRandomValue(20, GetScreenHeight() - 20);
                _dustParticles[i].speed = static_cast<float>(GetRandomValue(1, 5) * 5);
                _dustParticles[i].color = {
                    static_cast<unsigned char>(GetRandomValue(200, 255)),
                    static_cast<unsigned char>(GetRandomValue(200, 255)),
                    static_cast<unsigned char>(GetRandomValue(200, 255)),
                    static_cast<unsigned char>(GetRandomValue(50, 100))
                };
            }
        }

        DrawRectangleV(_dustParticles[i].position, {40, 10}, _dustParticles[i].color);
    }

    for (int i = 0; i < MAX_NEBULA_PARTICLES; i++) {
        if (_nebulaParticles[i].position.y >= GetScreenHeight()) {
            _nebulaParticles[i].position.x = GetRandomValue(20, GetScreenWidth() - 20);
            _nebulaParticles[i].position.y = 0;
            _nebulaParticles[i].speed = static_cast<float>(GetRandomValue(1, 5) * 5);
            _nebulaParticles[i].color = {
                static_cast<unsigned char>(GetRandomValue(50, 200)),
                static_cast<unsigned char>(GetRandomValue(50, 200)),
                static_cast<unsigned char>(GetRandomValue(150, 255)),
                static_cast<unsigned char>(GetRandomValue(50, 200))
            };
        } else {
            _nebulaParticles[i].position.y += _nebulaParticles[i].speed;

            if (_nebulaParticles[i].position.y - 60 > GetScreenHeight()) {
                _nebulaParticles[i].position.x = GetRandomValue(20, GetScreenWidth() - 20);
                _nebulaParticles[i].position.y = 0;
                _nebulaParticles[i].speed = static_cast<float>(GetRandomValue(1, 5) * 5);
                _nebulaParticles[i].color = {
                    static_cast<unsigned char>(GetRandomValue(50, 200)),
                    static_cast<unsigned char>(GetRandomValue(50, 200)),
                    static_cast<unsigned char>(GetRandomValue(150, 255)),
                    static_cast<unsigned char>(GetRandomValue(50, 200))
                };
            }
        }

        DrawRectangleV(_nebulaParticles[i].position, {10, 40}, _nebulaParticles[i].color);
    }

    if (menu)
        DrawText("R-Type", 730, 250, 120, WHITE);
}


void Screen::Display::drawMenu()
{
    setSpaceBackground(true);
    displayHostNameInput();
    displayPortInput();
    displayConnectionStateButton();
    displayConnectionButton();
}

///// Game

void Screen::Display::drawGame(GameEngine::GameEngine &engine)
{
    engine.run();

}

void Screen::Display::drawWaitingRoom()
{
    _playclickableZone = { 850, 450, 160, 60 };
    _regularclickableZone = { 600, 275, 160, 60 };
    _pvpclickableZone = { 850, 275, 160, 60 };
    _friendlyFireclickableZone = { 1100, 275, 220, 60 };

    setSpaceBackground(false);

    DrawRectangleRec({ 590, 265, 180, 80 }, SKYBLUE);
    DrawRectangleRec({ 840, 265, 180, 80 }, SKYBLUE);
    DrawRectangleRec({ 1090, 265, 240, 80 }, SKYBLUE);

    DrawRectangleRec(_playclickableZone, SKYBLUE);
    DrawText("Play", _playclickableZone.x + 45, _playclickableZone.y + 10, 32, RAYWHITE);

    if (_modeState == Enums::ModeSelect::REGULAR)
        DrawRectangleRec(_regularclickableZone, SKYBLUE);
    else
        DrawRectangleRec(_regularclickableZone, LIGHTGRAY);
    DrawText("Regular", _regularclickableZone.x + 20, _regularclickableZone.y + 15, 32, RAYWHITE);

    if (_modeState == Enums::ModeSelect::PVP)
        DrawRectangleRec(_pvpclickableZone, SKYBLUE);
    else
        DrawRectangleRec(_pvpclickableZone, LIGHTGRAY);
    DrawText("PVP", _pvpclickableZone.x + 45, _pvpclickableZone.y + 15, 32, RAYWHITE);

    if (_modeState == Enums::ModeSelect::FRIENDLYFIRE)
        DrawRectangleRec(_friendlyFireclickableZone, SKYBLUE);
    else
        DrawRectangleRec(_friendlyFireclickableZone, LIGHTGRAY);
    DrawText("Friendly fire", _friendlyFireclickableZone.x + 10, _friendlyFireclickableZone.y + 15, 32, RAYWHITE);
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

///// End Game


void Screen::Display::drawBackToMenu(GameEngine::GameEngine &engine)
{
    _backToMenuClickableZone = { 1660, 900, 230, 60 };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, _backToMenuClickableZone)) {
            std::cout << "Back to menu" << std::endl;
        }
    }

    DrawRectangleRec(_backToMenuClickableZone, _buttonFocusedOK);
    DrawText("Back to menu", _backToMenuClickableZone.x + 10, _backToMenuClickableZone.y + 15, 32, RAYWHITE);
}

void Screen::Display::drawLoose([[maybe_unused]] Screen::Display &window, GameEngine::GameEngine &engine)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    float animationDuration = 2.0f;
    float elapsedTime = 0.0f;
    Color textColor = BLANK;

    while (elapsedTime < animationDuration) {
        elapsedTime += GetFrameTime();
        float alpha = (elapsedTime / animationDuration);
        textColor = Color{static_cast<unsigned char>(RAYWHITE.r), static_cast<unsigned char>(RAYWHITE.g), static_cast<unsigned char>(RAYWHITE.b), static_cast<unsigned char>(alpha * 255)};
        float yOffset = sin(2 * PI * (elapsedTime / animationDuration));
        float scale = 1.0f + sin(2 * PI * (elapsedTime / animationDuration));
        float rotation = 360.0f * (elapsedTime / animationDuration);
        ClearBackground(BLACK);
        window.drawBackToMenu(engine);

        Vector2 startPosition = {(float)((screenWidth - MeasureText("GAME OVER", 20)) / 2.4), (float)(screenHeight / 2.5 + 50 * yOffset)};
        Vector2 textPosition = startPosition;

        const char* text = "GAME OVER";
        int letterSpacing = 30;

        for (int i = 0; i < strlen(text); i++) {
            char character[2] = {text[i], '\0'};
            DrawTextEx(GetFontDefault(), character, textPosition, 30 * scale, rotation, textColor);
            textPosition.x += MeasureText(character, 30) + letterSpacing;
        }

        EndDrawing();
    }
}

void Screen::Display::drawWin([[maybe_unused]] Screen::Display &window, GameEngine::GameEngine &engine)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    float animationDuration = 2.0f;
    float elapsedTime = 0.0f;
    Color textColor = BLANK;
    const int maxParticles = 200;
    Particle fireworks[maxParticles];

    for (int i = 0; i < maxParticles; i++) {
        fireworks[i].active = false;
    }

    while (elapsedTime < animationDuration) {
        elapsedTime += GetFrameTime();
        float alpha = (elapsedTime / animationDuration);
        textColor = Color{static_cast<unsigned char>(GREEN.r), static_cast<unsigned char>(GREEN.g), static_cast<unsigned char>(GREEN.b), static_cast<unsigned char>(alpha * 255)};
        ClearBackground(BLACK);
        window.drawBackToMenu(engine);

        for (int i = 0; i < maxParticles; i++) {

            if (!fireworks[i].active) {
                fireworks[i].position = Vector2{static_cast<float>(GetRandomValue(0, screenWidth)), static_cast<float>(GetRandomValue(0, screenHeight))};
                fireworks[i].color = GetRandomColor();
                fireworks[i].radius = GetRandomValue(2, 4);
                fireworks[i].speed = GetRandomValue(5, 15);
                fireworks[i].active = true;
            }

            if (fireworks[i].active) {
                fireworks[i].position.y -= fireworks[i].speed;
                fireworks[i].position.x += GetRandomValue(-2, 2);

                if (fireworks[i].position.y < 0) {
                    fireworks[i].active = false;
                }

                DrawCircleV(fireworks[i].position, fireworks[i].radius, fireworks[i].color);
            }
        }

        const char* text = "Y O U   W I N";
        Vector2 textPosition = {(float)((screenWidth - MeasureText(text, 20)) / 2.25), (float)(screenHeight / 2.5)};
        DrawTextEx(GetFontDefault(), text, textPosition, 60, 0, textColor);

        EndDrawing();
    }
}

void Screen::Display::drawLeftRightWin([[maybe_unused]] Screen::Display &window, GameEngine::GameEngine &engine, bool left)
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    float animationDuration = 2.0f;
    float elapsedTime = 0.0f;
    Color textColor = BLANK;
    const int maxParticles = 200;
    Particle fireworks[maxParticles];

    for (int i = 0; i < maxParticles; i++) {
        fireworks[i].active = false;
    }

    while (elapsedTime < animationDuration) {
        elapsedTime += GetFrameTime();
        float alpha = (elapsedTime / animationDuration);
        textColor = Color{static_cast<unsigned char>(GREEN.r), static_cast<unsigned char>(GREEN.g), static_cast<unsigned char>(GREEN.b), static_cast<unsigned char>(alpha * 255)};
        ClearBackground(BLACK);
        window.drawBackToMenu(engine);

        for (int i = 0; i < maxParticles; i++) {

            if (!fireworks[i].active) {
                fireworks[i].position = Vector2{static_cast<float>(GetRandomValue(0, screenWidth)), static_cast<float>(GetRandomValue(0, screenHeight))};
                fireworks[i].color = GetRandomColor();
                fireworks[i].radius = GetRandomValue(2, 4);
                fireworks[i].speed = GetRandomValue(5, 15);
                fireworks[i].active = true;
            }

            if (fireworks[i].active) {
                fireworks[i].position.y -= fireworks[i].speed;
                fireworks[i].position.x += GetRandomValue(-2, 2);

                if (fireworks[i].position.y < 0) {
                    fireworks[i].active = false;
                }

                DrawCircleV(fireworks[i].position, fireworks[i].radius, fireworks[i].color);
            }
        }

        const char* text;

        if (left)
            text = "L E F T  W I N";
        else
            text = "R I G H T  W I N";

        Vector2 textPosition = {(float)((screenWidth - MeasureText(text, 20)) / 2.25), (float)(screenHeight / 2.5)};
        DrawTextEx(GetFontDefault(), text, textPosition, 60, 0, textColor);

        EndDrawing();
    }
}
