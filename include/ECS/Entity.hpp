/*
** EPITECH PROJECT, 2023
** Entity.hpp
** File description:
** Entity
*/

#pragma once

#include <cstddef>

namespace ECS {
	namespace containers {
		class Registry;
	}
	class Entity {
	public:
		operator std::size_t() const;

	private:
		friend class containers::Registry;
		explicit Entity(std::size_t entity);
		std::size_t _entity;
	};
}
