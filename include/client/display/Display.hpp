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
    class Display {
        public:
			static void initWindow();
			void displayWindow();

			void displayHostNameInput();
			void displayPortInput();
			void displayConnectionButton();
			void detectActionMenu();
			void mouseClickedMenu();
			void keyPressededMenu(int KeyPressed);
			void drawMenu();

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
