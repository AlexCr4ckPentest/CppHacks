#ifndef _CPP_ASSERT_HPP_
#define _CPP_ASSERT_HPP_

#include <iostream> // std::cerr
#include <type_traits> // std::enable_if_t<>, std::is_convertible_v<>, std::is_invocable_r_v<>
#include <exception> // std::terminate()
#include <functional> // std::bind()



namespace alex::utils::assert
{
    namespace impl
    {
        void __default_assertion_handler(const char* filename, int line, const char* function, const char* expression, std::ostream& out) noexcept
        {
            out << "### In file: " << filename << "\n"
                << "### On line: " << line << "\n"
                << "### In function: " << function << "\n"
                << "### Assertion failed: '" << expression << "'\n";
        }

        template<typename Expression, typename Handler,
                typename = std::enable_if_t<
                    std::is_convertible_v<Expression, bool> &&
                    std::is_invocable_r_v<void, Handler, const char*, int, const char*, const char*, std::ostream&>
                    >
        >
        constexpr void __assert_base(Expression expr, const char* filename, int line, Handler&& handler) noexcept
        {
            if (!expr) {
                handler(filename, line);
                std::terminate();
            }
        }
    } // namespace alex::utils::assert::impl

    using Handler = void(*)(const char*, int, const char*, const char*, std::ostream&);
} // namespace alex::utils::assert



#define UTILS_CPPASSERT_DEFAULT(expression)  \
    alex::utils::assert::impl::__assert_base(expression, __FILE__, __LINE__,    \
                                std::bind(alex::utils::assert::impl::__default_assertion_handler, std::placeholders::_1, std::placeholders::_2, __PRETTY_FUNCTION__, #expression, std::ref(std::cerr)))

#define UTILS_CPPASSERT_CUSTOM(expression, handler, stream)  \
    alex::utils::assert::impl::__assert_base(expression, __FILE__, __LINE__,    \
                                std::bind(handler, std::placeholders::_1, std::placeholders::_2, __PRETTY_FUNCTION__, #expression, std::ref(stream)))

#endif // _CPP_ASSERT_HPP_