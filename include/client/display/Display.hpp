/*
** EPITECH PROJECT, 2023
** Display.hpp
** File description:
** Display
*/

#pragma once

#include <iostream>
#include <raylib.h>

#include "GameEngine/GameEngine.hpp"

namespace Screen {
    /**
     * @brief Display contain fonction for the graphic of the client
     *
     * */
    class Display {
    public:
        enum class GameState {
            MENU,
            GAME
        };
        enum class MenuState {
            WAITING_FOR_PLAYER_INPUT, // waiting for player input
            CONNECTING,               // waiting for connection to server to be established
            CONNECTED,                // connected to server
        };
        /**
         * @brief Init the window with raylib
         * @param state set the starting state of the game
         */
        Display(GameState state = GameState::MENU);

        /**
         * @returns True if the window is open
         */
        static bool isOpen();

        /**
         * @returns The current state of the game
         */
        GameState getGameState() const;
        /**
         * @returns The current state of the menu
         */
        MenuState getMenuState() const;
        /**
         * @brief Sets the state of the menu
         * @param state The new state of the menu
         */
        void setMenuState(MenuState state);
        /**
         * @returns The host name entered in the login menu
         */
        const std::string &getHostName() const;
        /**
         * @returns The port name entered in the login menu or -1 if
         * no port is entered
         */
        int getPort() const;

        /**
         * @brief Start updating the window
         */
        void beginUpdate();
        /**
         * @brief End updating the window
         */
        void endUpdate();

        // /**
        //  * @brief loop display window with menu or game
        //  * @param engine GameEngine
        //  */
        // void displayWindow(GameEngine::GameEngine &engine);

        /**
         * @brief display an input for hostname
         *
         */
        void displayHostNameInput();
        /**
         * @brief display an input for port
         *
         */
        void displayPortInput();
        /**
         * @brief display button for connection
         *
         */
        void displayConnectionButton();
        /**
         * @brief detect the action in menu
         *
         */
        void detectActionMenu();
        /**
         * @brief do when action is mouse clicked in menu
         *
         */
        void mouseClickedMenu();
        /**
         * @brief detect the key pressed for the input zone in menu
         *
         * @param KeyPressed send the key pressed to function
         */
        void keyPressededMenu(int KeyPressed, int key);
        /**
         * @brief draw the menu
         *
         */
        void drawMenu();

        /**
         * @brief draw the game
         * @param engine GameEngine
         */
        void drawGame(GameEngine::GameEngine &engine);

    private:
        /**
         * @brief Updates the window's states
         */
        void update();

        // Stock the Hostname in a string
        std::string _hostName;
        // Stock the Port in a string
        std::string _port;
        // Stock the state of the input in menu 0=none 1=hostname 2=port
        int _state = 0;
        // Set the rectangle clickable for hostname input
        Rectangle _hostNameclickableZone;
        // Set the rectangle clickable for port input
        Rectangle _portclickableZone;
        // Set the rectangle clickable for conection button
        Rectangle _connectionclickableZone;
        GameState _gameState = GameState::MENU;
        MenuState _menuState = MenuState::WAITING_FOR_PLAYER_INPUT;
    };
}
