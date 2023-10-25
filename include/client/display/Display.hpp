/*
** EPITECH PROJECT, 2023
** Display.hpp
** File description:
** Display
*/

#pragma once

#include <iostream>
#include <raylib.h>
#include <cstdint>

#include "GameEngine/GameEngine.hpp"
#include "constants.hpp"

namespace Screen {
    /**
     * @brief Display contain fonction for the graphic of the client
     *
     * */
    class Display {
    public:
        enum class GameState {
            MENU,
            GAME,
            WAITINGROOM,             // play button waiting room
        };
        enum class MenuState {
            WAITING_FOR_PLAYER_INPUT, // waiting for player input
            CONNECTING,               // waiting for connection to server to be established
            CONNECTED,                // connected to server
        };
        enum class CameraShakeIntensity {
            RUMBLE = 3,
            EARTHQUAKE = 5,
            END_OF_THE_WORLD = 8
        };
        static bool _playButton;
        /**
         * @brief Get the Play Button object
         *
         * @return true need to connect udp
         * @return false tcp connection
         */
        static bool getPlayButton();
        /**
         * @brief Init the window with raylib
         * @param state set the starting state of the game
         */
        Display(GameState state = GameState::MENU);
        /**
         * @brief Destroy the Display object
         *
         */
        ~Display();
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

        void updateShake();

        /**
         * @brief Start updating the window
         */
        void beginUpdate();
        /**
         * @brief End updating the window
         */
        static void endUpdate();

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
        static void drawGame(GameEngine::GameEngine &engine);

        /**
         * @brief draw the waitingRoom
         */
        static void drawWaitingRoom(Rectangle playButtonRect);

        /**
         * @brief Centers the window on screen
         * @return (*this) to allow chain calls
         */
        Display &center();
        /**
         * @brief Resizes the window
         * @return (*this) to allow chain calls
         */
        Display &resizeWindow(uint16_t width, uint16_t height);
        /**
         * @brief Resizes the camera
         * @return (*this) to allow chain calls
         */
        Display &resizeCamera(uint16_t width, uint16_t height);
        /**
         * @brief Moves the camera by some amount
         * @param x Distance to move camera on X axis
         * @param y Distance to move camera on Y axis
         * @return (*this) to allow chain calls
         */
        Display &moveCamera(int16_t posX, int16_t posY);
        /**
         * @brief Sets the position of the camera
         * @return (*this) to allow chain calls
         */
        Display &setCameraPosition(int16_t posX, int16_t posY);

        /**
         * @brief Camera shake option
         * @param t Time (in sec.) left until shake end
         * @param intensity The intensity at which the camera shakes
         * @param xRange How much (in %) does the screen shake on x axis
         * @param yRange How much (in %) does the screen shake on x axis
         * @returns (*this) to allow chain calls
         */
        Display &shake(
            float time = 0.2,
            enum CameraShakeIntensity intensity = CameraShakeIntensity::EARTHQUAKE,
            float xRange = 0.01,
            float yRange = 0.01
        );

        static void beginDrawCamera();
        static void endDrawCamera();

        /**
         * @returns The size of the camera view
         */
        static Vector2 getCameraSize();

        /**
         * @brief Set the Game State object
         *
         * @param state
         */
        void setGameState(GameState state);
        /**
         * @brief detect the action in waiting room
         *
         * @param playButtonRect
         */
        void detectActionWaitingRoom(Rectangle playButtonRect);

    private:
        /**
         * @brief Toggles between fullscreen and windowed
         * @returns True if switched to fullscreen, false otherwise
        */
        bool toggleFullScreen();
        Color _buttonFocusedOK = BLUE;
        Color _buttonFocusedKO = RED;
        Color _buttonUnfocusedOK = DARKBLUE;
        Color _buttonUnfocusedKO = { 150, 75, 0, 255 };
        /**
         * @brief Updates the window's states
         */
        void update();

        // Stock the Hostname in a string
        std::string _hostName;
        // Stock the Port in a string
        std::string _port;
        // Stock the state of the input in menu 0=none 1=hostname 2=port
        // int _state = 0;
        enum class InputState {
            NONE,
            HOSTNAME,
            PORT
        } _state = InputState::NONE;
        // Set the rectangle clickable for hostname input
        Rectangle _hostNameclickableZone;
        // Set the rectangle clickable for port input
        Rectangle _portclickableZone;
        // Set the rectangle clickable for conection button
        Rectangle _connectionclickableZone;
        GameState _gameState = GameState::MENU;
        MenuState _menuState = MenuState::WAITING_FOR_PLAYER_INPUT;

        // Camera
        Vector2 _windowSize = { 0, 0 };
        const float _defaultWidthRatio = 0.5;
        const float _defaultHeightRatio = 0.5;
        static const uint16_t defaultCameraWidth = Constants::cameraDefaultWidth;
        static const uint16_t defaultCameraHeight = Constants::cameraDefaultHeight;
        static uint16_t cameraWidth;
        static uint16_t cameraHeight;
        float aspectRatio;
        static Camera2D camera;
        /**
         * @brief Camera shake option
         * @struct
         * @property t Time (in sec.) left until shake end
         * @property xRange How much (in %) does the screen shake on x axis
         * @property yRange How much (in %) does the screen shake on x axis
         * @property intensity The intensity at which the camera shakes
         * @property _startTime Used for internal processing, do not edit
         */
        struct {
            float t = 0;
            float xRange = 0.01;
            float yRange = 0.01;
            enum CameraShakeIntensity intensity = CameraShakeIntensity::EARTHQUAKE;
            double _startTime = 0;
        } _cameraShake;
    };
}
