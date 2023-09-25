/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** GameEngine
*/

#include <algorithm>

#include "gameEngine/GameEngine.hpp"
#include "Errors/RegistryNotFound.hpp"

namespace gameEngine {

	using Registry = ECS::containers::Registry;

	Registry &GameEngine::operator[](const std::string &type)
	{
		return this->getRegistry(type);
	}
	const Registry &GameEngine::operator[](const std::string &type) const
	{
		return this->getRegistry(type);
	}

	Registry &GameEngine::createRegistry(const std::string &type)
	{
		m_registries.push_back(std::make_pair(type, Registry()));
		return m_registries.back().second;
	}

	Registry &GameEngine::getRegistry(const std::string &type)
	{
		auto it = std::find_if(m_registries.begin(), m_registries.end(),
			[&type](const auto &pair) {
				return pair.first == type;
			});
		if (it == m_registries.end())
			throw Errors::RegistryNotFound(type);
		return it->second;
	}

	const Registry &GameEngine::getRegistry(const std::string &type) const
	{
		auto it = std::find_if(m_registries.begin(), m_registries.end(),
			[&type](const auto &pair) {
				return pair.first == type;
			});
		if (it == m_registries.end())
			throw Errors::RegistryNotFound(type);
		return it->second;
	}

	void GameEngine::run()
	{
		for (auto &[_, registry] : m_registries) {
			registry.runSystems();
		}
	}

}; // namespace gameEngine
