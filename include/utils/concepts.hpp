/* concepts.hpp
 *
 * Just some concepts (C++20)
*/



#ifndef _CONCEPTS_HPP_
#define _CONCEPTS_HPP_

#include <type_traits>  // Legacy C++ SFINAE    :(
#include <concepts>     // Modern C++ "SFINAE"  :)



/* Declaration helpers for concepts like has_method_XXX<>
 */
#define __DECLARE_CONCEPT__HAS_METHOD(method_name)   \
template<typename T, typename RetValue, typename... Args>   \
concept has_method_##method_name = requires (T t, Args... args)  \
{    \
    { t.method_name(args...) } -> std::same_as<RetValue>;     \
}

#define __DECLARE_CONCEPT__HAS_METHOD_R(method_name, ret_value) \
template<typename T, typename... Args>   \
concept has_method_##method_name = requires (T t, Args... args)  \
{    \
    { t.method_name(args...) } -> std::same_as<ret_value>;     \
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



namespace alex::utils::concepts
{
} // namespace alex::utils::concepts

#endif // _CONCEPTS_HPP_