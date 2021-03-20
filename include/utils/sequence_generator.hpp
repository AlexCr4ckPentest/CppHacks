/* sequence_generator.hpp
 *
 * Simple implementation of similar range() object from Python
*/



#pragma once

#include <iterator>

#include "coroutine_helpers.hpp"



namespace alex::utils::coroutine_helpers
{
    namespace detail
    {
        template<typename T>
        struct sequence_generator_iterator
        {
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::input_iterator_tag;



            sequence_generator_iterator(generator<T>& generator)
                : generator_{generator}
            {}

            // Postfix increment
            sequence_generator_iterator operator++(int) noexcept
            {
                sequence_generator_iterator tmp{*this};
                generator_.next();
                return tmp;
            }

            // Prefix increment
            sequence_generator_iterator& operator++()
            {
                generator_.next();
                return *this;
            }

            bool operator!=(const sequence_generator_iterator& other) const noexcept
            { return generator_.current_value() != other.generator_.current_value(); }

            bool operator==(const sequence_generator_iterator& other) const noexcept
            { return !(*this != other); }

            value_type operator*() const noexcept
            { return generator_.current_value(); }

        private:
            generator<T>& generator_;
        };
    } // namespace alex::utils::coroutine_helpers::detail



    template<typename T>
    struct sequence_generator : public generator<T>
    {
        using iterator = detail::sequence_generator_iterator<T>;

        iterator begin() noexcept
        { return iterator{*this}; }

        iterator end() noexcept
        { return iterator{*this}; }
    };



    template<typename T>
    sequence_generator<T> sequence(T start, T stop, T step = 1)
    {
        for (T seq_index{start}; seq_index > stop; seq_index += step)
        {
            co_yield seq_index;
        }
    }
} // namespace alex::utils::coroutine_helpers

