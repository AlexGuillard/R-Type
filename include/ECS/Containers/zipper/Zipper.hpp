/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** Zipper
*/

#pragma once

#include "ECS/Containers/zipper/ZipperIterator.hpp"

namespace ECS::Containers {

	/**
	 * @brief A class that allows to iterate over multiple SparseArrays at once.
	 * @tparam ...SparseArrays The SparseArrays to zip together.
	 */
	template <class... SparseArrays>
	class Zipper {
	public:
		using iterator = ZipperIterator<Zipper<SparseArrays...>, SparseArrays...>;
		using iterator_tuple = std::tuple<decltype(std::declval<SparseArrays>().begin())...>;
		/**
		 * @brief Construct a new Zipper object
		 * @param ...arrays The containers to zip together.
		 */
		Zipper(SparseArrays &...arrays)
		{
			m_size = std::min({ arrays.size()... });
			m_begin = iterator_tuple(arrays.begin()...);
			this->calculateEnd();
		}

		/**
		 * @returns a read/write iterator that points to the first element
		 * in each of the containers.
		 */
		iterator begin() noexcept
		{
			return iterator(m_begin, m_size);
		}
		/**
		 * @returns a read/write iterator that points one past the last
		 * element in each of the containers.
		 */
		iterator end() noexcept
		{
			return iterator(m_end, 0);
		}
		/**
		 * @returns the number of elements in the smallest container.
		 */
		std::size_t size() const noexcept
		{
			return m_size;
		}

	private:
		void calculateEnd()
		{
			m_end = m_begin;
			std::apply([this](auto &&...args) { ((args += m_size), ...); },
				m_end);
		}

		std::size_t m_size;
		std::size_t m_idx;
		iterator_tuple m_begin;
		iterator_tuple m_end;
	};

}; // namespace ECS::Containers
