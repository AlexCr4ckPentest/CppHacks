/* coro_generator_object.hpp
 *
 * Simple generator object for coroutines
*/

#ifndef _CORO_GENERATOR_OBJECT_HPP_
#define _CORO_GENERATOR_OBJECT_HPP_

#include <coroutine>



namespace alex::utils::coroutine_helpers
{
    namespace impl::generator_obj
    {
        template<typename T>
        struct promise_type
        {
            auto initial_suspend() noexcept { return std::suspend_never{}; }
            auto final_suspend() noexcept { return std::suspend_always{}; }

            void unhandled_exception() { std::terminate(); }

            auto get_return_object()
            { return std::coroutine_handle<promise_type>::from_promise(*this); }

            void return_void() {}

            auto yield_value(T value)
            {
                value_ = value;
                return std::suspend_always{};
            }

            T value_;
        };
    } // namespace alex::utils::coroutine_helpers::impl::generator_obj

    template<typename T>
    struct generator
    {
        using promise_type = impl::generator_obj::promise_type<T>;
        using coro_handle = std::coroutine_handle<promise_type>;

        generator() = default;

        generator(coro_handle handle) : handle_{handle} {}

        ~generator() noexcept
        {
            if (handle_)
            {
                handle_.destroy();
            }
        }

        bool next() noexcept
        {
            if (handle_)
            {
                handle_.resume();
                return !handle_.done();
            }
            return false;
        }

        T current_value() const noexcept
        { return handle_.promise().value_; }

    private:
        coro_handle handle_;
    };
} // namespace alex::utils::coroutine_helpers

#endif // _CORO_GENERATOR_OBJECT_HPP_