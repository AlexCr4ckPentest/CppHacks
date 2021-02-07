#include <type_traits>

#include "lib/nlohmann/json.hpp"

#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

namespace alex::serialization {

struct Serializable
{ virtual nlohmann::json toJson() const = 0; };

struct Deserializable
{ virtual void fromJson(const nlohmann::json&) = 0; };

struct SerializableDeserializable : public Serializable, public Deserializable {};

struct MainObject
{
    constexpr MainObject() noexcept
        : name_{nullptr}
    {}

    constexpr MainObject(const MainObject& other) noexcept
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

} // namespace alex::serialization



#include "type_traits/serialization_type_traits.hpp"



#define CREATE_OBJECT(class_name, object_name, ...) \
    class_name object_name{__VA_ARGS__}; object_name.setObjectName(#object_name)

#endif // SERIALIZATION_HPP
