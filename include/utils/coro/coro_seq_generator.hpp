/* coro_seq_generator.hpp
 *
 * Simple implementation of similar range() object from Python
*/

#ifndef _CORO_SEQ_GENERATOR_HPP_
#define _CORO_SEQ_GENERATOR_HPP_

#include <iterator>

#include "coro_generator_object.hpp"

namespace alex::utils::coroutine_helpers
{
    template<typename T>
    struct coro_seq_generator_iterator
    {
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        coro_seq_generator_iterator()
            : generator_{}
        {}

        coro_seq_generator_iterator(generator<T>& generator)
            : generator_{generator}
        {}

        value_type operator*() const noexcept
        { return generator_.current_value(); }

        bool operator!=(const std::nullptr_t ptr) noexcept
        { return !generator_.handle().done(); }

        coro_seq_generator_iterator operator++(int) noexcept
        {
            coro_seq_generator_iterator tmp{generator_};
            generator_.next();
            return tmp;
        }

        coro_seq_generator_iterator& operator++() noexcept
        {
            generator_.next();
            return *this;
        }

    private:
        generator<T>& generator_;
    };

    template <typename T>
    struct coro_seq_generator : public generator<T>
    {
        using iterator = coro_seq_generator_iterator<T>;

        iterator begin() const noexcept
        { return iterator{*this}; }

        auto end() const noexcept
        { return nullptr; }
    };

    template <typename T = int>
        coro_seq_generator<T>
    seq_generator(T start, T stop, T step = 1) noexcept
    {
        for (T index{start}; index < stop; index += step)
        { co_yield index; }
    }
} // namespace alex::utils::coroutine_helpers

#endif // _CORO_SEQ_GENERATOR_HPP_