/*
** EPITECH PROJECT, 2023
** Display.hpp
** File description:
** Display
*/

#ifndef DISPLAY_HPP_
    #define DISPLAY_HPP_

	#include <iostream>
	#include <raylib.h>

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
			 * @param KeyPressed
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
			std::string _HostName;
			std::string _Port;
			int _State = 0;
			Rectangle _HostNameclickableZone;
			Rectangle _PortclickableZone;
			Rectangle _ConnectionclickableZone;
			bool _GameState;
    };
}

#endif /* !DISPLAY_HPP_ */
