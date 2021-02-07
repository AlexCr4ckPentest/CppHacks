#include <type_traits>

#include "../serialization.hpp"

#ifndef SERIALIZATION_TYPE_TRAITS_HPP
#define SERIALIZATION_TYPE_TRAITS_HPP

namespace alex::serialization::type_traits {
namespace detail {

template<typename T>
using is_derived_from_MainObject = std::is_base_of<MainObject, T>;

template<typename T>
struct has_getObjectName_method
{
    template<typename U> static constexpr char check(decltype(&U::getObjectName));
    template<typename...> static constexpr int check(...);

    static constexpr bool value{sizeof(check<T>(nullptr)) == sizeof(char)};
};

template<typename T>
struct has_setObjectName_method
{
    template<typename U> static constexpr char check(decltype(&U::setObjectName));
    template<typename...> static constexpr int check(...);

    static constexpr bool value{sizeof(check<T>(nullptr)) == sizeof(char)};
};

template<typename T>
struct has_getObjectName_setObjectName_methods
{ static constexpr bool value{has_getObjectName_method<T>::value && has_setObjectName_method<T>::value}; };

template<typename T>
struct has_valid_getObjectName_method
{
    template<typename U, typename Base,
             typename = std::enable_if_t<
                 has_getObjectName_method<T>::value &&
                 std::is_same_v<decltype(&U::getObjectName), decltype(&Base::getObjectName)>
                 >
    > static constexpr char check(std::nullptr_t);

    template<typename...> static constexpr int check(...);

    static constexpr bool value{sizeof(check<T, MainObject>(nullptr)) == sizeof(char)};
};

template<typename T>
struct has_valid_setObjectName_method
{
    template<typename U, typename Base,
             typename = std::enable_if_t<
                 has_setObjectName_method<T>::value &&
                 std::is_same_v<decltype(&U::setObjectName), decltype(&Base::setObjectName)>
                 >
    > static constexpr char check(std::nullptr_t);

    template<typename...> static constexpr int check(...);

    static constexpr bool value{sizeof(check<T, MainObject>(nullptr)) == sizeof(char)};
};

template<typename T>
struct has_valid_getObjectName_setObjectName_methods
{ static constexpr bool value{has_valid_getObjectName_method<T>::value && has_valid_setObjectName_method<T>::value}; };

template<typename T>
struct is_valid_object
{ static constexpr bool value{is_derived_from_MainObject<T>::value && has_valid_getObjectName_setObjectName_methods<T>::value}; };

} // namespace alex::serialization::type_traits::detail



template<typename T>
struct is_serializable
{
    template<typename U> static char check(decltype(&U::toJson));
    template<typename...> static int check(...);

    static constexpr bool value{sizeof(check<T>(nullptr)) == sizeof(char)};
};

template<typename T>
struct is_deserializable
{
    template<typename U> static char check(decltype(&U::fromJson));
    template<typename...> static int check(...);

    static constexpr bool value{sizeof(check<T>(nullptr)) == sizeof(char)};
};

template<typename T>
struct is_serializable_deserializable
{ static constexpr bool value{is_serializable<T>::value && is_deserializable<T>::value}; };



template<typename T>
struct is_serializable_object
{ static constexpr bool value{is_serializable<T>::value && detail::is_valid_object<T>::value}; };

template<typename T>
struct is_deserializable_object
{ static constexpr bool value{is_deserializable<T>::value && detail::is_valid_object<T>::value}; };

template<typename T>
struct is_serializable_deserializable_object
{ static constexpr bool value{is_serializable_deserializable<T>::value && detail::is_valid_object<T>::value}; };



template<typename T>
struct is_constructible_serializable
{ static constexpr bool value{std::is_constructible<T>::value && is_serializable<T>::value}; };

template<typename T>
struct is_constructible_deserializable
{ static constexpr bool value{std::is_constructible<T>::value && is_deserializable<T>::value}; };

template<typename T>
struct is_constructible_serializable_deserializable
{ static constexpr bool value{is_constructible_serializable<T>::value && is_constructible_deserializable<T>::value}; };



template<typename T>
struct is_constructible_serializable_object
{ static constexpr bool value{is_constructible_serializable<T>::value && detail::is_valid_object<T>::value}; };

template<typename T>
struct is_constructible_deserializable_object
{ static constexpr bool value{is_constructible_deserializable<T>::value && detail::is_valid_object<T>::value}; };

template<typename T>
struct is_constructible_serializable_deserializable_object
{ static constexpr bool value{is_constructible_serializable_deserializable<T>::value && detail::is_valid_object<T>::value}; };

} // namespace alex::alex::serialization::type_traits

#endif // SERIALIZATION_TYPE_TRAITS_HPP
