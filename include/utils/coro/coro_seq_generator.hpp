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
    template <typename T>
    struct coro_seq_generator : public generator<T>
    {
        auto begin() noexcept
        {}

        auto end() noexcept
        {}

        auto begin() const noexcept
        {}

        auto end() const noexcept
        {}
    };

    template <typename T = int>
        coro_seq_generator<T>
    seq_generator(T start, T stop, T step = 1) noexcept
    {
        for (T index{start}; index < stop; index++)
        {
            co_yield index;
        }
    }
} // namespace alex::utils::coroutine_helpers

#endif // _CORO_SEQ_GENERATOR_HPP_