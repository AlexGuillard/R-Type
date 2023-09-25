/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** IndexedZipperIterator
*/

#pragma once

#include <tuple>
#include <utility>
#include <type_traits>
#include <iterator>
#include <optional>

#include "ECS/containers/SparseArray.hpp"

namespace ECS::containers {

	/**
	 * @brief The iterator for the IndexedZipper class.
	 * @tparam ...SparseArrays The SparseArrays to zip together.
	 * @tparam IndexedZipper The IndexedZipper class.
	 */
	template <class IndexedZipper, class... SparseArrays>
	class IndexedZipperIterator {
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = std::tuple<std::size_t, typename SparseArrays::value_type &...>;
		using iterator_tuple = typename IndexedZipper::iterator_tuple;
		IndexedZipperIterator(iterator_tuple const &it_tuple, std::size_t size)
			: _current(it_tuple), _size(size)
		{
			if (!allSet(_seq))
				nextIndex(_seq);
		}
		// prefix increment
		IndexedZipperIterator operator++()
		{
			nextIndex(_seq);
			return *this;
		}
		// postfix increment
		IndexedZipperIterator &operator++(int)
		{
			IndexedZipperIterator *tmp = this;
			++(*this);
			return *tmp;
		}
		value_type operator*() { return toValue(_seq); }
		value_type operator->() { return (*this); }
		friend bool operator==(
			IndexedZipperIterator const &lhs,
			IndexedZipperIterator const &rhs)
		{
			return lhs._current == rhs._current;
		}
		friend bool operator!=(
			IndexedZipperIterator const &lhs,
			IndexedZipperIterator const &rhs)
		{
			return !(lhs == rhs);
		}

	private:
		/**
		 * @brief Goes to the next index where all std::optional are set.
		 */
		template <size_t... Is>
		void nextIndex(std::index_sequence<Is...>)
		{
			if (_idx >= _size)
				return;
			do {
				++_idx;
				(++(std::get<Is>(_current)), ...);
			} while (!allSet(_seq) && _idx < _size);
		}
		/**
		 * @brief Checks if all std::optional are set.
		 * @tparam ...Is Indices of the std::optional to check
		 * @return true if all std::optional are set
		 */
		template <size_t... Is>
		bool allSet(std::index_sequence<Is...>)
		{
			if (_idx >= _size)
				return true;
			return ((std::get<Is>(_current)->has_value()) && ...);
		}
		/**
		 * @brief Converts the current iterator_tuple to a value_type.
		 * @tparam ...Is Indices of the std::optional to convert
		 * @return the value_type
		 */
		template <size_t... Is>
		value_type toValue(std::index_sequence<Is...>)
		{
			return std::tie(_idx, *std::get<Is>(_current)...);
		}

	private:
		iterator_tuple _current;
		std::size_t _size;
		static constexpr std::index_sequence_for<SparseArrays...> _seq{};
		std::size_t _idx = 0;
	};

}; // namespace ECS::containers
