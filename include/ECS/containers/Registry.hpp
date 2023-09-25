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
#include <stdexcept>
#include <typeindex>
#include <functional>
#include <utility>
#include <tuple>

#include "ECS/containers/SparseArray.hpp"
#include "ECS/Entity.hpp"

namespace ECS::containers {

	class Registry {
	public:
		Registry() = default;
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

			if (m_componentsArrays.contains(index) == false) {
				throw ComponentNotRegisteredException(index.name());
			}
			try {
				return std::any_cast<SparseArray<Component> &>(
					m_componentsArrays[index].first);
			} catch (const std::bad_any_cast &e) {
				throw ComponentNotRegisteredException(index.name());
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

			if (m_componentsArrays.contains(index) == false) {
				throw ComponentNotRegisteredException(index.name());
			}
			try {
				return std::any_cast<SparseArray<Component> const &>(
					m_componentsArrays.at(index).first);
			} catch (const std::bad_any_cast &e) {
				throw ComponentNotRegisteredException(index.name());
			}
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

		class ComponentNotRegisteredException : public std::runtime_error {
		public:
			explicit ComponentNotRegisteredException(const std::string &componentName)
				: std::runtime_error(std::string("ComponentNotRegisteredException: '") + componentName + "' is not registered") {};
		};

		// ENTITY MANAGER
		Entity spawnEntity()
		{
			std::size_t id = m_nbEntities;

			m_nbEntities++;
			return Entity(id);
		}
		Entity entityFromIndex(std::size_t idx)
		{
			return Entity(idx);
		}
		void killEntity(Entity const &e)
		{
			for (auto &[_, pair] : m_componentsArrays) {
				auto &deleter = pair.second;
				deleter(*this, e);
			}
		}
		std::size_t size() const
		{
			return m_nbEntities;
		}

		template <typename Component>
		typename SparseArray<Component>::reference_type addComponent(
			Entity const &to, Component &&c)
		{
			SparseArray<Component> &components = this->getComponents<Component>();

			return components.insertAt(to, std::forward<Component>(c));
		}
		template <typename Component, typename... Params>
		typename SparseArray<Component>::reference_type emplaceComponent(
			Entity const &to, Params &&...p)
		{
			SparseArray<Component> &components = this->getComponents<Component>();

			return components.emplaceAt(to, std::forward<Params>(p)...);
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
		void addSystem(Function &&f)
		{
			m_systems.push_back(
				[f = std::forward<Function>(f), this]() {
					f(*this, this->getComponents<Components>()...);
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

}; // namespace ECS::containers
