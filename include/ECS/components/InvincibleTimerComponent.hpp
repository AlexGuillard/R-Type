/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** InvincibleTimerComponent
*/

#include <iostream>
#pragma once

namespace ECS::components {
	/**
	* @brief Component that contains the InvincibleTimer details
	* @param InvincibleTimer thos double displays the time we have left using the invincibility
	*/
	struct InvincibleTimerComponent{
		double timer;
	};
}