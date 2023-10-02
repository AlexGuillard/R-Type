/*
** EPITECH PROJECT, 2023
** Error.hpp
** File description:
** Error
*/

#ifndef _ERROR_
#define _ERROR_
#include "ANetwork.hpp"
#include <iostream>

namespace Network {

	/**
	 * @brief Error class for ClientNetwork issues
	 *
	 */
	class Error : public std::runtime_error {

	public:
		/**
		 * @brief Construct a new Error object
		 *
		 * @param message This is the message the Error will receive for debug
		 */
		explicit Error(const std::string &message) : std::runtime_error(message) {}
	};
}

#endif /* !_ERROR_ */
