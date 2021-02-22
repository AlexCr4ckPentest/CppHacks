/* compile_time_power.hpp
 *
*/



#include <type_traits>

#include <boost/multiprecision/cpp_int.hpp>


#ifndef COMPILE_TIME_POWER_HPP
#define COMPILE_TIME_POWER_HPP

namespace alex::utils::math::ct_power
{
namespace concepts
{
#if __cplusplus > 201703L && __cpp_concepts >= 201907L
template<typename T>
concept NumberType = std::is_integral_v<T> ||
                    std::is_floating_point_v<T> ||
                    boost::multiprecision::is_number<T>::value;
#else
// Legacy SFINAE
template<typename T> struct IsNumberType
{ static constexpr bool value{std::is_integral<T>::value || std::is_floating_point<T>::value}; };
#endif
} // namespace alex::utils::math::ct_power::concepts



// Recursive template instantiation
#if 0
template<
#if __cplusplus > 201703L && __cpp_concepts >= 201907L
    concepts::NumberType number_type,
    number_type number,
    size_t pow
#else
    typename number_type,
    number_type number,
    size_t pow,
    typename = std::enable_if_t<concepts::IsNumberType<number_type>::value>
#endif
>
struct ct_power
{ static constexpr number_type value{number * ct_power<number_type, number, pow - 1>::value}; };

template<
#if __cplusplus > 201703L && __cpp_concepts >= 201907L
    concepts::NumberType number_type,
    number_type number
#else
    typename number_type,
    number_type number
#endif
> struct ct_power<number_type, number, 1> { static constexpr number_type value{number}; };

template<
#if __cplusplus > 201703L && __cpp_concepts >= 201907L
    concepts::NumberType number_type,
    number_type number
#else
    typename number_type,
    number_type number
#endif
> struct ct_power<number_type, number, 0> { static constexpr number_type value{static_cast<number_type>(1)}; };
#else
template<
#if __cplusplus > 201703L && __cpp_concepts >= 201907L
    concepts::NumberType number_type
#else
    typename number_type, typename = std::enable_if_t<concepts::IsNumberType<number_type>::value>
#endif
>
constexpr number_type ct_power(number_type number, size_t pow)
{
    if (pow == 0) return 1;
    if (pow == 1) return number;
    if (number == 2) return 1 << pow;
    return number * ct_power(number, pow - 1);
}
#endif

} // namespace alex::utils::math::ct_power
#endif // COMPILE_TIME_POWER_HPP
