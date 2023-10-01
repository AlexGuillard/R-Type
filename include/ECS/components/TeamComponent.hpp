/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TeamComponent
*/

#pragma once

namespace ECS::components {
	enum TeamGroup {
		ALLY,
		ENEMY
	};
	/**
	* @brief Component that contains the  type of team
	* @param team enum of the type of team of the component
	*/
	struct TeamComponent{
		TeamGroup team;
	};
}