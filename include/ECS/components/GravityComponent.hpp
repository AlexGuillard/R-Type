/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GravityComponent
*/

#include <iostream>
#pragma once

namespace ECS::components {
	/**
	* @brief Component that contains the gravity details
	* @param gravity size_t for the gravity of the ship
	*/
	struct GravityComponent{
		std::size_t gravity;
	};
}