/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** GameEngine
*/

#include <algorithm>
#include <iostream>
#include <chrono>

#include "GameEngine/GameEngine.hpp"
#include "Errors/RegistryNotFound.hpp"

namespace GameEngine {

    using Registry = ECS::Containers::Registry;
    double GameEngine::mDeltaTime = 0.;

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
        auto registryIterator = std::find_if(m_registries.begin(), m_registries.end(),
            [&type](const auto &pair) {
                return pair.first == type;
            });
        if (registryIterator == m_registries.end()) {
            throw Errors::RegistryNotFound(type);
        }
        return registryIterator->second;
    }

    const Registry &GameEngine::getRegistry(const std::string &type) const
    {
        auto registryIterator = std::find_if(m_registries.begin(), m_registries.end(),
            [&type](const auto &pair) {
                return pair.first == type;
            });
        if (registryIterator == m_registries.end()) {
            throw Errors::RegistryNotFound(type);
        }
        return registryIterator->second;
    }

    void GameEngine::run()
    {
        static auto lastTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(
            currentTime - lastTime).count() / 1000000.0F;
        lastTime = currentTime;

        mDeltaTime = deltaTime;
        for (auto &[_, registry] : m_registries) {
            registry.runSystems();
        }
    }

    double GameEngine::getDeltaTime()
    {
        return GameEngine::mDeltaTime;
    }

}; // namespace GameEngine
