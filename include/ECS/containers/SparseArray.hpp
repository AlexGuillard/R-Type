/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** SparseArray
*/

#pragma once

#include <vector>
#include <optional>

#include "Errors/ValueNotFound.hpp"

namespace ECS::containers {

	/**
	 * @brief SparseArray is a vector of std::optional<T>.
	 * @tparam T Type of the values stored in the vector
	 * @tparam N Initial size of the vector
	 */
	template <typename T>
	class SparseArray : private std::vector<std::optional<T>> {
	public:
		using value_type = std::optional<T>;
		using reference_type = value_type &;
		using const_reference_type = value_type const &;
		using container_t = std::vector<value_type>;
		using size_type = typename container_t::size_type;
		using iterator = typename container_t::iterator;
		using const_iterator = typename container_t::const_iterator;

		/**
		 * @brief Construct a new empty SparseArray object
		 */
		SparseArray() = default;
		SparseArray(SparseArray const &) = default;
		SparseArray(SparseArray &&) noexcept = default;
		/**
		 * @brief Construct a new SparseArray object
		 * @param n Initial size of the vector
		 */
		SparseArray(std::size_t n) : std::vector<value_type>(n) {}

		using std::vector<value_type>::operator=;
		using std::vector<value_type>::begin;
		using std::vector<value_type>::cbegin;
		using std::vector<value_type>::end;
		using std::vector<value_type>::cend;
		using std::vector<value_type>::size;

		reference_type operator[](size_type index) { return this->at(index); }
		const_reference_type operator[](size_type index) const { return this->at(index); }

		/**
		 * @brief Get the value at a specific index.
		 * If the index is out of range, returns an empty optional.
		 * @param index index of the value to get
		 * @return reference to the value
		 */
		reference_type at(size_type index)
		{
			if (index >= this->size())
				this->resize(index + 1);
			return this->std::vector<value_type>::operator[](index);
		}
		/**
		 * @brief Get the value at a specific index.
		 * @param index index of the value to get
		 * @return reference to the value
		 */
		const_reference_type at(size_type index) const { return this->std::vector<value_type>::at(index); }

		/**
		 * @brief insert T at a specific index, erasing the old value and resizing
		 * the vector if needed.
		 * @param index index to insert at
		 * @param value reference to the value to insert
		 * @return reference to the inserted value
		 */
		reference_type insertAt(size_type index, const T &value)
		{
			if (this->size() <= index) {
				this->resize(index + 1);
			}
			this->at(index) = value;
			return this->at(index);
		}

		/**
		 * @brief insert T at a specific index, erasing the old value and resizing
		 * the vector if needed.
		 * @param index index to insert at
		 * @param value rvalue reference to the value to insert
		 * @return reference to the inserted value
		 */
		reference_type insertAt(size_type index, T &&value)
		{
			if (this->size() <= index)
				this->resize(index + 1);
			this->at(index) = std::move(value);
			return this->at(index);
		}

		/**
		 * @brief emplace T at a specific index, erasing the old value and resizing
		 * the vector if needed.
		 * @tparam ...Args types of the arguments to forward to the constructor of
		 * T
		 * @param index index to insert at
		 * @param ...args arguments used to construct T
		 * @return reference to the inserted value
		 */
		template <typename... Args>
		reference_type emplaceAt(size_type index, Args &&...args)
		{
			if (this->size() <= index)
				this->resize(index + 1);
			this->at(index) = T(std::forward<Args>(args)...);
			return this->at(index);
		}

		/**
		 * @brief erase the value at a specific index.
		 * Does not resize the vector.
		 * @param index index to erase at
		 */
		void erase(size_type index)
		{
			if (index >= this->size())
				return;
			this->at(index).reset();
		}

		/**
		 * @brief get the index of a value.
		 * @param value value to get the index of
		 * @return index of the value
		 * @throw ValueNotFound if the value is not found
		 */
		size_type getIndex(value_type const &value) const
		{
			for (SparseArray<T>::size_type i = 0; i < this->size(); i++) {
				if (!(*this)[i].has_value() || !value.has_value())
					continue;
				if (std::addressof(this->at(i).value()) == std::addressof(value.value()))
					return i;
			}
			throw Errors::ValueNotFound("Value not found in SparseArray");
		}
	};

} // namespace ECS::containers
