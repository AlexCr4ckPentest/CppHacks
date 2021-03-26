/* coro_NN_generator.hpp
 *
 * Simple natural nums generator
*/



#ifndef _CORO_NN_GENERATOR_HPP_
#define _CORO_NN_GENERATOR_HPP_

#include "coro_generator_object.hpp"



namespace alex::utils::coroutine_helpers
{
    template<typename T = int>
    generator<T> natural_nums_generator(T start = 0)
    {
        while (true)
        {
            co_yield start;
            start++;
        }
    }
} // namespace alex::utils::coroutine_helpers

#endif // _CORO_NN_GENERATOR_HPP_