#include <type_traits>
#include <typeinfo>

#include "lib/nlohmann/json.hpp"

#ifndef SERIALIZABLE_DESERIALIZABLE_HPP
#define SERIALIZABLE_DESERIALIZABLE_HPP

namespace alex { namespace serialization {

struct Serializable
{ virtual nlohmann::json toJson() const = 0; };

struct Deserializable
{ virtual void fromJson(const nlohmann::json&) = 0; };

struct SerializableDeserializable : public Serializable, public Deserializable {};

struct MainObject
{
    constexpr MainObject()
        : name_{nullptr}
    {}

    constexpr MainObject(const MainObject& other)
        : name_{other.name_}
    {}

    constexpr MainObject(MainObject&&) = default;

    MainObject& operator=(const MainObject&) = delete;
    MainObject& operator=(const MainObject&&) = delete;

    constexpr const char* getObjectName() const noexcept { return name_; }
    constexpr void setObjectName(const char* name) noexcept { name_ = name; }

private:
    const char* name_;
};

struct SerializableObject : public Serializable, public MainObject {};

struct DeserializableObject : public Deserializable, public MainObject {};

struct SerializableDeserializableObject : public SerializableDeserializable, public MainObject {};



// Some helpers
namespace detail {

template<typename T>
using is_derived_from_MainObject = std::is_base_of<MainObject, T>;

template<typename T>
using method_getObjectName_is_valid = std::is_same<decltype(&T::getObjectName), decltype(&MainObject::getObjectName)>;

template<typename T>
using method_setObjectName_is_valid = std::is_same<decltype(&T::setObjectName), decltype(&MainObject::setObjectName)>;

template<typename T>
struct has_valid_getObjectName_method
{
    template<typename U, typename = std::enable_if_t<method_getObjectName_is_valid<U>::value, U>>
    static char check(decltype(&U::getObjectName));

    template<typename...> static int check(...);

    static constexpr bool value{sizeof(check<T>(nullptr)) == sizeof(char)};
};

template<typename T>
struct has_valid_setObjectName_method
{
    template<typename U, typename = std::enable_if_t<method_setObjectName_is_valid<U>::value, U>>
    static char check(decltype(&U::setObjectName));

    template<typename...> static int check(...);

    static constexpr bool value{sizeof(check<T>(nullptr)) == sizeof(char)};
};

template<typename T>
struct has_valid_getObjectName_setObjectName_methods
{ static constexpr bool value{has_valid_getObjectName_method<T>::value && has_valid_setObjectName_method<T>::value}; };

template<typename T>
struct is_valid_object
{ static constexpr bool value{is_derived_from_MainObject<T>::value && has_valid_getObjectName_setObjectName_methods<T>::value}; };

} // namespace detail



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

}} // namespace alex::serialization



#define CREATE_OBJECT(class_name, object_name, ...) \
    class_name object_name{__VA_ARGS__}; object_name.setObjectName(#object_name)

#endif // SERIALIZABLE_DESERIALIZABLE_HPP
