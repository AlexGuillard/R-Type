/*
** EPITECH PROJECT, 2023
** Display.cpp
** File description:
** Display
*/

#include "client/display/Display.hpp"

///// Window

void Screen::Display::initWindow()
{
	int monitor = GetCurrentMonitor();
    // const int screenWidth = GetMonitorWidth(monitor);
    // const int screenHeight = GetMonitorHeight(monitor);
    const int screenWidth = 700;
    const int screenHeight = 500;
	const int fps = 60;
	InitWindow(screenWidth, screenHeight, "R-Type");
	// ToggleFullscreen();
    SetTargetFPS(fps);
}

void Screen::Display::displayWindow()
{
	initWindow();
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
			if (!_gameState) {
				detectActionMenu();
				drawMenu();
			} else {
				drawGame();
			}
        EndDrawing();
    }
    CloseWindow();
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

	_hostNameclickableZone = {posXRect, posYRect, widthRect, heightRect};
	if (_hostName.empty()) {
		DrawRectangleLines(posXRect, posYRect, widthRect, heightRect, RED);
	} else {
		DrawRectangleLines(posXRect, posYRect, widthRect, heightRect, BLUE);
	}
	DrawText(_hostName.c_str(), posXText, posYText, fontSizeText, LIGHTGRAY);
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

	_portclickableZone = {posXRect, posYRect, widthRect, heightRect};
	if (_port.empty()) {
		DrawRectangleLines(posXRect, posYRect, widthRect, heightRect, RED);
	} else {
		DrawRectangleLines(posXRect, posYRect, widthRect, heightRect, BLUE);
	}
	DrawText(_port.c_str(), posXText, posYText, fontSizeText, LIGHTGRAY);
}

void Screen::Display::displayConnectionButton()
{
	const Rectangle defaultClickableZone = {100, 210, 110, 30};
	const int lineSize = 30;
	const int posXText = 105;
	const int posYText = 215;
	const int fontSizeText = 20;

	if (_hostName.empty() || _port.empty()) {
		_connectionclickableZone = defaultClickableZone;
		DrawRectangleRec(_connectionclickableZone, RED);
	} else {
		_connectionclickableZone = defaultClickableZone;
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
	key = GetKeyPressed();
	if (keyPressed != 0 || key != 0) {
		keyPressededMenu(keyPressed, key);
	}
}

void Screen::Display::mouseClickedMenu()
{
	float mouseX = GetMouseX();
	float mouseY = GetMouseY();
	const Vector2 mouse = {mouseX, mouseY};

    if (CheckCollisionPointRec(mouse, _hostNameclickableZone)) {
		_state = 1;
	} else if (CheckCollisionPointRec(mouse, _portclickableZone)) {
		_state = 2;
	} else {
		_state = 0;
	}
	if (CheckCollisionPointRec(mouse, _connectionclickableZone)) {
		std::cout << "\n Try Connexion\nwith:" << _hostName << " | " << _port << "\n\n";
		//TODO: handle basic error (empty hostname, empty port, invalid port (ex: chocolat instead of 8080)) on the graphic side
		//connect return a bool to let us know if the connection was successful or not
		_client.connect(_hostName, std::stoi(_port));
		_gameState = true;
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

void Screen::Display::detectActionGame()
{
	int keyPressed = 0;

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		mouseClickedGame();
    }
	keyPressed = GetKeyPressed();
	if (keyPressed != 0) {
		keyPressededGame(keyPressed);
	}
}

void Screen::Display::mouseClickedGame()
{

}

void Screen::Display::keyPressededGame(int KeyPressed)
{
	const int upKey = 87;
	const int downKey = 83;
	const int leftKey = 65;
	const int rightKey = 68;

	switch (KeyPressed) {
		case upKey:
			_client.sendMovement(Network::Movement::UP);
			break;
		case downKey:
			_client.sendMovement(Network::Movement::DOWN);
			break;
		case leftKey:
			_client.sendMovement(Network::Movement::LEFT);
			break;
		case rightKey:
			_client.sendMovement(Network::Movement::RIGHT);
			break;
		default:
			break;
	}
}

void Screen::Display::drawGame()
{
	detectActionGame();
}

Screen::Display::Display()
{
	_gameState = false;
}

Screen::Display::~Display() {}
