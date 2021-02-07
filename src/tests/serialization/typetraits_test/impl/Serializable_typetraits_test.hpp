#include "serialization/serialization.hpp"

#ifndef SERIALIZABLE_TYPETRAITS_TEST_HPP
#define SERIALIZABLE_TYPETRAITS_TEST_HPP

namespace tests::serialization::impl::Serializable_typetraits_test {

using alex::serialization::Serializable;
using alex::serialization::SerializableObject;

class class_A {};
class class_B : public Serializable {};

class class_C : public Serializable
{
public:
    nlohmann::json toJson() const override { return {}; }
};

class class_D : public SerializableObject {};

class class_E : public SerializableObject
{
public:
    nlohmann::json toJson() const override { return {}; }
};



constexpr bool run_test() noexcept
{
    using alex::serialization::type_traits::is_serializable;
    using alex::serialization::type_traits::is_serializable_object;
    using alex::serialization::type_traits::is_constructible_serializable;
    using alex::serialization::type_traits::is_constructible_serializable_object;

    constexpr bool is_serializable_result {
        !is_serializable<class_A>::value &&
        is_serializable<class_B>::value &&
        is_serializable<class_C>::value &&
        is_serializable<class_D>::value &&
        is_serializable<class_E>::value
    };

    constexpr bool is_serializable_object_result {
        !is_serializable_object<class_A>::value &&
        !is_serializable_object<class_B>::value &&
        !is_serializable_object<class_C>::value &&
        is_serializable_object<class_D>::value &&
        is_serializable_object<class_E>::value
    };

    constexpr bool is_constructible_serializable_result {
        !is_constructible_serializable<class_A>::value &&
        !is_constructible_serializable<class_B>::value &&
        is_constructible_serializable<class_C>::value &&
        !is_constructible_serializable<class_D>::value &&
        is_constructible_serializable<class_E>::value
    };

    constexpr bool is_constructible_serializable_object_result {
        !is_constructible_serializable_object<class_A>::value &&
        !is_constructible_serializable_object<class_B>::value &&
        !is_constructible_serializable_object<class_C>::value &&
        !is_constructible_serializable_object<class_D>::value &&
        is_constructible_serializable_object<class_E>::value
    };

    return (is_serializable_result && is_serializable_object_result &&
            is_constructible_serializable_result && is_constructible_serializable_object_result);
}

} // namespace tests::serialization::impl::Serializable_typetraits_test

#endif // SERIALIZABLE_TYPETRAITS_TEST_HPP
