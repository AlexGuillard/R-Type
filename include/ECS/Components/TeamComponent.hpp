/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TeamComponent
*/

#pragma once
#include "enums.hpp"

namespace ECS::Components {
	/**
	* @brief Component that contains the  type of team
	* @param team enum of the type of team of the component
	*/
	struct TeamComponent{
		Enums::TeamGroup team;
	};
}
