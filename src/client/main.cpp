/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include "client/display/Display.hpp"
#include "GameEngine/GameEngine.hpp"

int main()
{
    Screen::Display window;
    // Screen::Display window(Screen::Display::GameState::GAME); // Uncomment this line to start the game directly
    GameEngine::GameEngine engine = GameEngine::createEngine();
    window.displayWindow(engine);
}
