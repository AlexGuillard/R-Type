/*
** EPITECH PROJECT, 2023
** Display.hpp
** File description:
** Display
*/

#pragma once

#include <iostream>
#include <raylib.h>
#include "client/network/ClientNetwork.hpp"

namespace Screen {
    /**
     * @brief Display contain fonction for the graphic of the client
     *
     * */
    class Display {
    public:
        /**
         * @brief Init the window with raylib
         *
         */
        static void initWindow();
        /**
         * @brief loop display window with menu or game
         *
         */
        void displayWindow();

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
        void keyPressededMenu(int KeyPressed);
        /**
         * @brief draw the menu
         *
         */
        void drawMenu();

        /**
         * @brief draw the game
         *
         */
        void drawGame();


        Display();
        ~Display();

    protected:
    private:
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
        // Set game state 0=menu 1=game
        bool _gameState;
        // Client used to communicate with server (network)
        Network::ClientNetwork _client;
    };
}
