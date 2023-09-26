/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** ComponentNotRegisteredException
*/

#pragma once

#include <stdexcept>

namespace Errors {

	/**
	 * @brief Exception thrown when trying to access a component that is not registered
	 */
	class ComponentNotRegisteredException : public std::runtime_error {
	public:
		explicit ComponentNotRegisteredException(const std::string &componentName)
			: std::runtime_error(std::string("ComponentNotRegisteredException: '") + componentName + "' is not registered") {};
	};

}; // namespace Errors
