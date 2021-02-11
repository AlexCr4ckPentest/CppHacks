/* concepts.hpp
 *
 * Just some concepts (C++20)
*/



#include <type_traits>  // Legacy C++ SFINAE    :(

#include <concepts>     // Modern C++ "SFINAE"  :)

#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

/* Declaration helpers for concepts like has_method_XXX<>
 */
#define __DECLARE_CONCEPT__HAS_METHOD(method_name)   \
template<typename T, typename RetValue, typename... Args>   \
concept has_method_##method_name = requires (T t, Args... args)  \
{    \
    { t.method_name(args...) } -> std::same_as<RetValue>;     \
    std::is_invocable_r_v<RetValue, decltype(&T::method_name), Args...>;    \
}

#define __DECLARE_CONCEPT__HAS_METHOD_R(method_name, ret_value) \
template<typename T, typename... Args>   \
concept has_method_##method_name = requires (T t, Args... args)  \
{    \
    { t.method_name(args...) } -> std::same_as<ret_value>;     \
    std::is_invocable_r_v<ret_value, decltype(&T::method_name), Args...>;    \
}



/* Declaration helpers for concepts like has_field_XXX<>
 */
#define __DECLARE_CONCEPT__HAS_FIELD(field_name)    \
template<typename T, typename U>    \
concept has_field_##field_name = requires (T t) \
{ { t.field_name } -> std::same_as<U>; }

#define __DECLARE_CONCEPT__HAS_FIELD_T(field_name, field_type)  \
template<typename T>    \
concept has_field_##field_name = requires (T t) \
{ { t.field_name } -> std::same_as<field_type>; }



namespace alex::utils::concepts {

// Here will be concepts. But it`s empty here :(

} // namespace alex::utils::concepts

#endif // CONCEPTS_HPP
