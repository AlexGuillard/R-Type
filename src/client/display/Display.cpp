/*
** EPITECH PROJECT, 2023
** Display.cpp
** File description:
** Display
*/

#include "client/display/Display.hpp"

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

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		mouseClickedMenu();
    }
	keyPressed = GetCharPressed();
	if (keyPressed != 0) {
		keyPressededMenu(keyPressed);
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

void Screen::Display::keyPressededMenu(int KeyPressed)
{
	if (_state == 1) {
		if (KeyPressed >= '0' && KeyPressed <= '9' || KeyPressed == '.') {
		_hostName += KeyPressed;
		} else if (KeyPressed == '-' && !_hostName.empty()) {
			 _hostName.erase(_hostName.size() - 1);
		}
	}

	if (_state == 2) {
		if (KeyPressed >= '0' && KeyPressed <= '9') {
			_port += KeyPressed;
		} else if (KeyPressed == '-' && !_port.empty()) {
			 _port.erase(_port.size() - 1);
		}
	}
}

void Screen::Display::drawMenu()
{
	displayHostNameInput();
	displayPortInput();
	displayConnectionButton();
}

void Screen::Display::drawGame()
{

}

Screen::Display::Display()
{
	_gameState = false;
}

Screen::Display::~Display() {}
