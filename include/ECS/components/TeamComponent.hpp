/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TeamComponent
*/

#pragma once

namespace ECS::components {
	/**
	* @brief Component that contains the  type of team
	* @param team enum of the type of team of the component
	*/
	enum TeamGroup {
		ALLY,
		ENEMY
	};
	struct TeamComponent{
		TeamGroup team;
	};
}