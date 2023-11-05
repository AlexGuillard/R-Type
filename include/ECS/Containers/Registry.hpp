/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** Registry
*/

#pragma once

#include <unordered_map>
#include <string>
#include <any>
#include <typeindex>
#include <functional>
#include <utility>
#include <tuple>

#include "ECS/Containers/SparseArray.hpp"
#include "ECS/Entity.hpp"
#include "Errors/ComponentNotRegisteredException.hpp"
#include "ECS/Components/ImmortalComponent.hpp"
#include "ECS/Components/ScoreComponent.hpp"

namespace ECS::Containers {
    class Registry {
    public:
        Registry() = default;
        Registry(std::size_t reservedIds) : m_nbEntities(reservedIds) {};
        /**
         * @brief Adds a new component array to our associative container
         * @tparam Component type of the component to register
         * @return Reference to the SparseArray of the component type
         */
        template <class Component>
        SparseArray<Component> &registerComponent()
        {
            const auto index = std::type_index(typeid(Component));

            m_componentsArrays[index] =
                std::make_pair(
                    std::make_any<SparseArray<Component>>(),
                    [](Registry &registry, Entity const &entity) {
                        registry.getComponents<Component>().erase(entity);
                    });
            return std::any_cast<SparseArray<Component> &>(
                m_componentsArrays[index].first);
        }
        /**
         * @brief Get the SparseArray of a component type
         * @tparam Component type of the component to get
         * @return Reference to the SparseArray of the component type
         */
        template <class Component>
        SparseArray<Component> &getComponents()
        {
            const auto index = std::type_index(typeid(Component));

            if (!m_componentsArrays.contains(index)) {
                throw Errors::ComponentNotRegisteredException(index.name());
            }
            try {
                return std::any_cast<SparseArray<Component> &>(
                    m_componentsArrays[index].first);
            } catch (const std::bad_any_cast &e) {
                throw Errors::ComponentNotRegisteredException(index.name());
            }
        }
        /**
         * @brief Get the SparseArray of a component type
         * @tparam Component type of the component to get
         * @return Reference to the SparseArray of the component type
         */
        template <class Component>
        SparseArray<Component> const &getComponents() const
        {
            const auto index = std::type_index(typeid(Component));

            if (!m_componentsArrays.contains(index)) {
                throw Errors::ComponentNotRegisteredException(index.name());
            }
            try {
                return std::any_cast<SparseArray<Component> const &>(
                    m_componentsArrays.at(index).first);
            } catch (const std::bad_any_cast &e) {
                throw Errors::ComponentNotRegisteredException(index.name());
            }
        }

        /**
         * @brief Get the component of an entity
         * @tparam Component type of the component to get
         * @param entity entity to get the component from
         * @return Reference to the component of the entity
         */
        template <class Component>
        std::optional<Component> &getComponent(Entity const &entity)
        {
            SparseArray<Component> &components = this->getComponents<Component>();

            return components.at(entity);
        }
        /**
         * @brief Get the component of an entity
         * @tparam Component type of the component to get
         * @param entity entity to get the component from
         * @return Reference to the component of the entity
         */
        template <class Component>
        const std::optional<Component> &getComponent(Entity const &entity) const
        {
            SparseArray<Component> const &components = this->getComponents<Component>();

            return components.at(entity);
        }

        /**
         * @brief Get the SparseArray of one or more component types
         * @tparam ...Component types of the components to get
         * @return Tuple of references to the SparseArrays of the component types
         */
        template <class... Component>
        std::tuple<SparseArray<Component> &...> getComponentsTuple()
        {
            return std::tuple<SparseArray<Component> &...>(
                this->getComponents<Component>()...);
        }

        // ENTITY MANAGER
        Entity spawnEntity()
        {
            std::size_t entityId = m_nbEntities;

            m_nbEntities++;
            return Entity(entityId);
        }

        Entity entityFromIndex(std::size_t idx)
        {
            m_nbEntities = std::max(m_nbEntities, idx + 1);
            return Entity(idx);
        }
        void killEntity(Entity const &entity)
        {
            if (this->getComponent<Components::ImmortalComponent>(entity)) {
                return;
            }
            if (this->getComponent<Components::ScoreComponent>(entity)) {
                _score += this->getComponent<Components::ScoreComponent>(entity)->score;
            }
            for (auto &[_, pair] : m_componentsArrays) {
                auto &deleter = pair.second;
                deleter(*this, entity);
            }
        }
        std::size_t size() const
        {
            return m_nbEntities;
        }

        template <typename Component>
        typename SparseArray<Component>::reference_type addComponent(
            Entity const &target, Component &&component)
        {
            SparseArray<Component> &components = this->getComponents<Component>();

            return components.insertAt(target, std::forward<Component>(component));
        }
        template <typename Component, typename... Params>
        typename SparseArray<Component>::reference_type emplaceComponent(
            Entity const &target, Params &&...params)
        {
            SparseArray<Component> &components = this->getComponents<Component>();

            return components.emplaceAt(target, std::forward<Params>(params)...);
        }
        template <typename Component>
        void removeComponent(Entity const &from)
        {
            SparseArray<Component> &components = this->getComponents<Component>();

            components.erase(from);
        }

        // SYSTEM MANAGER
        /**
         * @brief Add a system to the registry
         * @param f system to add to add
         */
        template <class... Components, typename Function>
        void addSystem(Function &&system)
        {
            m_systems.push_back(
                [system = std::forward<Function>(system), this]() {
                    system(*this, this->getComponents<Components>()...);
                });
        }
        /**
         * @brief Run all the systems
         */
        void runSystems()
        {
            for (auto &system : m_systems) {
                system();
            }
        }
        int _score = 0;
    private:
        // type_index.hash_code() -> Pair<SparseArray<Component>, deleteComponent>
        // where deleteComponent erase the component from the entity
        std::unordered_map<
            std::type_index,
            std::pair<std::any, std::function<void(Registry &, Entity const &)>>>
            m_componentsArrays;

        // ENTITY MANAGER

        std::size_t m_nbEntities = 0;

        // SYSTEM MANAGER
        std::vector<std::function<void()>> m_systems;
    };

}; // namespace ECS::Containers
