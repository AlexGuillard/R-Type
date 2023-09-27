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
    const int screenWidth = GetMonitorWidth(monitor);
    const int screenHeight = GetMonitorHeight(monitor);
	const int fps = 60;
	InitWindow(screenWidth, screenHeight, "R-Type");
	ToggleFullscreen();
    SetTargetFPS(fps);
}

void Screen::Display::displayWindow()
{
	initWindow();
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
			if (!_GameState) {
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

	_HostNameclickableZone = {posXRect, posYRect, widthRect, heightRect};
	DrawRectangleLines(posXRect, posYRect, widthRect, heightRect, BLUE);
	DrawText(_HostName.c_str(), posXText, posYText, fontSizeText, LIGHTGRAY);
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

	_PortclickableZone = {posXRect, posYRect, widthRect, heightRect};
	DrawRectangleLines(posXRect, posYRect, widthRect, heightRect, BLUE);
	DrawText(_Port.c_str(), posXText, posYText, fontSizeText, LIGHTGRAY);
}

void Screen::Display::displayConnectionButton()
{
	const Rectangle defaultClickableZone = {100, 210, 110, 30};
	const int lineSize = 30;
	const int posXText = 105;
	const int posYText = 215;
	const int fontSizeText = 20;
	_ConnectionclickableZone = defaultClickableZone;
	DrawRectangleRec(_ConnectionclickableZone, BLUE);
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

    if (CheckCollisionPointRec(mouse, _HostNameclickableZone)) {
		_State = 1;
	} else if (CheckCollisionPointRec(mouse, _PortclickableZone)) {
		_State = 2;
	} else {
		_State = 0;
	}
	if (CheckCollisionPointRec(mouse, _ConnectionclickableZone)) {
		std::cout << "\n Try Connexion\nwith:" << _HostName << " | " << _Port << "\n\n";
		_GameState = true;
	}
}

void Screen::Display::keyPressededMenu(int KeyPressed)
{
	if (_State == 1) {
		_HostName += KeyPressed;
	}
	if (_State == 2) {
		_Port += KeyPressed;
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
	_GameState = false;
}

Screen::Display::~Display() {}
