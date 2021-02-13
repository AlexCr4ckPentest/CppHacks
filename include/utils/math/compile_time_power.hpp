/* compile_time_power.hpp
 *
*/



#include <type_traits>

#include <boost/multiprecision/cpp_int.hpp>



#ifndef COMPILE_TIME_POWER_HPP
#define COMPILE_TIME_POWER_HPP

namespace alex::utils::math::ct_power {
namespace concepts {

template<typename T>
concept NumberType = requires
{ requires std::is_integral_v<T> || std::is_floating_point_v<T> || boost::multiprecision::is_number<T>::value; };

} // namespace alex::utils::math::ct_power::concepts



#if 1
template<concepts::NumberType number_type, number_type number, size_t pow>
struct ct_power
{ static constexpr number_type value{number * ct_power<number_type, number, pow - 1>::value}; };

template<concepts::NumberType number_type, number_type number>
struct ct_power<number_type, number, 1> { static constexpr number_type value{number}; };

template<concepts::NumberType number_type, number_type number>
struct ct_power<number_type, number, 0> { static constexpr number_type value{static_cast<number_type>(1)}; };
#endif



template<concepts::NumberType number_type>
constexpr number_type ct_power_func(number_type number, size_t pow)
{
    if (pow == 0) return 1;
    if (pow == 1) return number;
    return number * ct_power_func(number, pow - 1);
}

} // namespace alex::utils::math::ct_power

#endif // COMPILE_TIME_POWER_HPP
