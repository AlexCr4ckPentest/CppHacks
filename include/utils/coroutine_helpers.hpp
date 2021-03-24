/* coroutine_helpers.hpp
 *
 * Some simple coroutine helpers and awaitable objects
 * Such as generator
*/



#ifndef _COROUTINE_HELPERS_HPP_
#define _COROUTINE_HELPERS_HPP_

#include <coroutine>



namespace alex::utils::coroutine_helpers
{
    template<typename T>
    struct generator
    {
        struct promise_type
        {
            auto initial_suspend() noexcept
            { return std::suspend_always{}; }

            auto final_suspend() noexcept
            { return std::suspend_always{}; }

            void unhandled_exception()
            { std::terminate(); }

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



        using coro_handle = std::coroutine_handle<promise_type>;

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

#endif // _COROUTINE_HELPERS_HPP_