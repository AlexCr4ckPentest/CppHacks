#include "serialization/serialization.hpp"

#ifndef SERIALIZABLE_DESERIALIZABLE_TYPETRAITS_TEST_HPP
#define SERIALIZABLE_DESERIALIZABLE_TYPETRAITS_TEST_HPP

namespace tests::serialization::impl::SerializableDeserializable_typetraits_test {

using alex::serialization::SerializableDeserializable;
using alex::serialization::SerializableDeserializableObject;

class class_A {};
class class_B : public SerializableDeserializable {};

class class_C : public SerializableDeserializable
{
public:
    nlohmann::json toJson() const override { return {}; }
    void fromJson(const nlohmann::json&) override {}
};

class class_D : public SerializableDeserializableObject {};

class class_E : public SerializableDeserializableObject
{
public:
    nlohmann::json toJson() const override { return {}; }
    void fromJson(const nlohmann::json&) override {}
};



constexpr bool run_test() noexcept
{
    using alex::serialization::type_traits::is_serializable_deserializable;
    using alex::serialization::type_traits::is_serializable_deserializable_object;
    using alex::serialization::type_traits::is_constructible_serializable_deserializable;
    using alex::serialization::type_traits::is_constructible_serializable_deserializable_object;

    constexpr bool is_serializable_deserializable_result {
        !is_serializable_deserializable<class_A>::value &&
        is_serializable_deserializable<class_B>::value &&
        is_serializable_deserializable<class_C>::value &&
        is_serializable_deserializable<class_D>::value &&
        is_serializable_deserializable<class_E>::value
    };

    constexpr bool is_serializable_deserializable_object_result {
        !is_serializable_deserializable_object<class_A>::value &&
        !is_serializable_deserializable_object<class_B>::value &&
        !is_serializable_deserializable_object<class_C>::value &&
        is_serializable_deserializable_object<class_D>::value &&
        is_serializable_deserializable_object<class_E>::value
    };

    constexpr bool is_constructible_serializable_deserializable_result {
        !is_constructible_serializable_deserializable<class_A>::value &&
        !is_constructible_serializable_deserializable<class_B>::value &&
        is_constructible_serializable_deserializable<class_C>::value &&
        !is_constructible_serializable_deserializable<class_D>::value &&
        is_constructible_serializable_deserializable<class_E>::value
    };

    constexpr bool is_constructible_serializable_deserializable_object_result {
        !is_constructible_serializable_deserializable_object<class_A>::value &&
        !is_constructible_serializable_deserializable_object<class_B>::value &&
        !is_constructible_serializable_deserializable_object<class_C>::value &&
        !is_constructible_serializable_deserializable_object<class_D>::value &&
        is_constructible_serializable_deserializable_object<class_E>::value
    };

    return (is_serializable_deserializable_result &&
            is_serializable_deserializable_object_result &&
            is_constructible_serializable_deserializable_result &&
            is_constructible_serializable_deserializable_object_result);
}

} // namespace detail::SerializableDeserizalizable_typetraits_classes

#endif // SERIALIZABLE_DESERIALIZABLE_TYPETRAITS_TEST_HPP
