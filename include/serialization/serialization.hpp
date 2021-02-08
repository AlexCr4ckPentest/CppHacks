#include <type_traits>
#include <typeinfo>

#include "lib/nlohmann/json.hpp"

#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

namespace alex::serialization {

struct Serializable
{ virtual nlohmann::json toJson() const = 0; };

struct Deserializable
{ virtual void fromJson(const nlohmann::json&) = 0; };

struct SerializableDeserializable : public Serializable, public Deserializable {};

template<typename Derived>
class MainObject
{
public:
    constexpr MainObject() noexcept
    { Derived::__init__(); }

    constexpr MainObject(const MainObject& other) noexcept
    { name_ = other.name_; }

    constexpr MainObject(MainObject&&) = default;

    MainObject& operator=(const MainObject&) = delete;
    MainObject& operator=(const MainObject&&) = delete;

    constexpr static const char* getObjectName() noexcept { return name_; }
    constexpr static void setObjectName(const char* name) noexcept { name_ = name; }

protected:
    static const char* name_;
};

template<typename Derived>
const char* MainObject<Derived>::name_{};

template<typename Derived>
struct SerializableObject : public Serializable, public MainObject<Derived> {};

template<typename Derived>
struct DeserializableObject : public Deserializable, public MainObject<Derived> {};

template<typename Derived>
struct SerializableDeserializableObject : public SerializableDeserializable, public MainObject<Derived> {};

} // namespace alex::serialization



#include "type_traits/serialization_type_traits.hpp"



#define MAIN_OBJECT_INIT(class_name)    \
private:    \
    static void __init__() noexcept \
    {   \
        name_ = typeid(class_name).name();  \
    }   \
    friend class MainObject<class_name>;



#endif // SERIALIZATION_HPP
