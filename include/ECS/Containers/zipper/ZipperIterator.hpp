/*
** EPITECH PROJECT, 2023
** RType-bootstrap [WSL: Ubuntu]
** File description:
** ZipperIterator
*/

#pragma once

#include <tuple>
#include <utility>
#include <type_traits>
#include <iterator>
#include <optional>

#include "ECS/Containers/SparseArray.hpp"

namespace ECS::Containers {

    /**
     * @brief The iterator for the Zipper class.
     * @tparam ...SparseArrays The SparseArrays to zip together.
     * @tparam Zipper The Zipper class.
     */
    template <class Zipper, class... SparseArrays>
    class ZipperIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::tuple<typename SparseArrays::value_type &...>;
        using iterator_tuple = typename Zipper::iterator_tuple;
        ZipperIterator(iterator_tuple const &it_tuple, std::size_t size)
            : _current(it_tuple), _size(size)
        {
            if (!allSet(seq)) {
                nextIndex(seq);
            }
        }
        // prefix increment
        ZipperIterator operator++()
        {
            nextIndex(seq);
            return *this;
        }
        // postfix increment
        ZipperIterator &operator++(int)
        {
            ZipperIterator *tmp = this;
            ++(*this);
            return *tmp;
        }
        value_type operator*() { return toValue(seq); }
        value_type operator->() { return (*this); }
        friend bool operator==(
            ZipperIterator const &lhs,
            ZipperIterator const &rhs)
        {
            return lhs._current == rhs._current;
        }
        friend bool operator!=(
            ZipperIterator const &lhs,
            ZipperIterator const &rhs)
        {
            return !(lhs == rhs);
        }

    private:
        /**
         * @brief Goes to the next index where all std::optional are set.
         */
        template <size_t... Is>
        void nextIndex(std::index_sequence<Is...> /*unused*/)
        {
            if (_idx >= _size) { return; }
            do {
                ++_idx;
                (++(std::get<Is>(_current)), ...);
            } while (!allSet(seq) && _idx < _size);
        }
        /**
         * @brief Checks if all std::optional are set.
         * @tparam ...Is Indices of the std::optional to check
         * @return true if all std::optional are set
         */
        template <size_t... Is>
        bool allSet(std::index_sequence<Is...> /*unused*/)
        {
            if (_idx >= _size) { return true; }
            return ((std::get<Is>(_current)->has_value()) && ...);
        }
        /**
         * @brief Converts the current iterator_tuple to a value_type.
         * @tparam ...Is Indices of the std::optional to convert
         * @return the value_type
         */
        template <size_t... Is>
        value_type toValue(std::index_sequence<Is...> /*unused*/)
        {
            return std::tie(*std::get<Is>(_current)...);
        }

        iterator_tuple _current;
        std::size_t _size;
        static constexpr std::index_sequence_for<SparseArrays...> seq{};
        std::size_t _idx = 0;
    };

}; // namespace ECS::Containers
