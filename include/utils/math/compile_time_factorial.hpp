/* compile_time_factorial.hpp
 *
 * Calculating factorial at compile time using recursive templates instantiation
 * Requires Boost.Multiprecision library
*/



#ifndef _COMPILE_TIME_FACTORIAL_HPP_
#define _COMPILE_TIME_FACTORIAL_HPP_

#include <type_traits>

#include <boost/multiprecision/cpp_int.hpp>



#ifdef __RECURSIVE_TEMPLATE_INSTANTIATION_FACTORIAL_COMPUTING
#warning "Be careful when using large numbers!"
#warning "Add the -ftemplate-depth=N flag to increase the depth of template instantiation!"
#endif // __RECURSIVE_TEMPLATE_INSTANTIATION_FACTORIAL_COMPUTING



namespace alex::utils::math
{
    namespace concepts
    {
#if __cplusplus > 201703L && __cpp_concepts >= 201907L
    template<typename T>
    concept IntegerType =
#if defined(__RECURSIVE_TEMPLATE_INSTANTIATION_FACTORIAL_COMPUTING) || defined(__RECURSIVE_CONSTEXPR_FUNCTION_FACTORIAL_COMPUTING) ||   \
    defined(__CONSTEXPR_FUNCTION_FOR_LOOP_FACTORIAL_COMPUTING)
        std::is_integral_v<T> || boost::multiprecision::is_number<T>::value;
#else
        std::is_integral_v<T>;
#endif
#else
    template<typename T>
    struct IsIntegerType
    {
        static constexpr bool value {
#if defined(__RECURSIVE_TEMPLATE_INSTANTIATION_FACTORIAL_COMPUTING) || defined(__RECURSIVE_CONSTEXPR_FUNCTION_FACTORIAL_COMPUTING) ||   \
    defined(__CONSTEXPR_FUNCTION_FOR_LOOP_FACTORIAL_COMPUTING)
            std::is_integral_v<T> || boost::multiprecision::is_number<T>::value
#else
            std::is_integral_v<T>
#endif
        };
    };
#endif
    }; // namespace alex::utils::math::concepts



#if defined(__RECURSIVE_CONSTEXPR_FUNCTION_FACTORIAL_COMPUTING) || defined(__CONSTEXPR_FUNCTION_FOR_LOOP_FACTORIAL_COMPUTING)
    namespace detail
    {
        template<size_t N>
        constexpr size_t cached_factorial_value {
            [] {
                if constexpr (N <= 1)       return 1;
                else if constexpr (N == 2)  return 2;
                else if constexpr (N == 3)  return 6;
                else if constexpr (N == 4)  return 24;
                else if constexpr (N == 5)  return 120;
            }()
        };
    } // namespace alex::utils::math::ct_factorial::detail
#endif



#ifdef __RECURSIVE_TEMPLATE_INSTANTIATION_FACTORIAL_COMPUTING

    template<
#if __cplusplus > 201703L && __cpp_concepts >= 201907L
        concepts::IntegerType integer_type,
        size_t N
#else
        typename integer_type,
        size_t N,
        typename = std::enable_if_t<concepts::IsIntegerType<integer_type>::value>
#endif
    >
    struct ct_factorial { static constexpr integer_type value{N * ct_factorial<integer_type, N - 1>::value}; };

    template<
#if __cplusplus > 201703L && __cpp_concepts >= 201907L
        concepts::IntegerType integer_type
#else
        typename integer_type
#endif
    >
    struct ct_factorial<integer_type, 0> { static constexpr integer_type value{1}; };

#elif defined(__RECURSIVE_CONSTEXPR_FUNCTION_FACTORIAL_COMPUTING)

    template<
#if __cplusplus > 201703L && __cpp_concepts >= 201907L
        concepts::IntegerType integer_type,
        size_t N
#else
        typename integer_type,
        size_t N,
        typename = std::enable_if_t<concepts::IsIntegerType<integer_type>::value>
#endif
    >
    constexpr integer_type ct_factorial()
    {
        if constexpr (N <= 5) return detail::cached_factorial_value<N>;
        else return N * ct_factorial<integer_type, N - 1>();
    }

#elif defined(__CONSTEXPR_FUNCTION_FOR_LOOP_FACTORIAL_COMPUTING)

    template<
#if __cplusplus > 201703L && __cpp_concepts >= 201907L
        concepts::IntegerType integer_type,
        size_t N
#else
        typename integer_type,
        size_t N,
        typename = std::enable_if_t<concepts::IsIntegerType<integer_type>::value>
#endif
    >
    constexpr integer_type ct_factorial()
    {
        if constexpr (N <= 5) return detail::cached_factorial_value<N>;
        else {
            integer_type result{1};
            for (size_t i{1}; i <= N; ++i) {
                result *= i;
            }
            return result;
        }
    }

#elif defined(__SFINAE_TEMLATE_INSTANTIATION_FACTORIAL_COMPUTING)

    template<
#if __cplusplus > 201703L && __cpp_concepts >= 201907L
        concepts::IntegerType integer_type,
        size_t N
#else
        typename integer_type,
        size_t N,
        typename = std::enable_if_t<concepts::IsIntegerType<integer_type>::value>
#endif
    >
    struct ct_factorial : std::integral_constant<integer_type, N * ct_factorial<integer_type, N - 1>{}> {};

    template<
#if __cplusplus > 201703L && __cpp_concepts >= 201907L
        concepts::IntegerType integer_type
#else
        typename integer_type
#endif
    >
    struct ct_factorial<integer_type, 0> : std::integral_constant<integer_type, 1> {};

#endif

} // namespace alex::utils::math

#endif // _COMPILE_TIME_FACTORIAL_HPP_