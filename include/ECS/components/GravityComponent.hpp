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
	* @param gravity in size_t (pixel per sec), gravity of entity
	*/
	struct GravityComponent{
		std::size_t gravity;
	};
}