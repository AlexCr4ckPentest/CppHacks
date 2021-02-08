#include "serialization/serialization.hpp"

#ifndef DESERIALIZABLE_TYPETRAITS_TEST_HPP
#define DESERIALIZABLE_TYPETRAITS_TEST_HPP

namespace tests::serialization::impl::Deserializable_typetraits_test {

using alex::serialization::Deserializable;
using alex::serialization::DeserializableObject;

class class_A {};
class class_B : public Deserializable {};

class class_C : public Deserializable
{
public:
    void fromJson(const nlohmann::json&) override {}
};

class class_D : public DeserializableObject<class_D>
{ MAIN_OBJECT_INIT(class_D)
};

class class_E : public DeserializableObject<class_E>
{ MAIN_OBJECT_INIT(class_E)
public:
    void fromJson(const nlohmann::json&) override {}
};



constexpr bool run_test() noexcept
{
    using alex::serialization::type_traits::is_deserializable;
    using alex::serialization::type_traits::is_deserializable_object;
    using alex::serialization::type_traits::is_constructible_deserializable;
    using alex::serialization::type_traits::is_constructible_deserializable_object;

    constexpr bool is_deserializable_result {
        !is_deserializable<class_A>::value &&
        is_deserializable<class_B>::value &&
        is_deserializable<class_C>::value &&
        is_deserializable<class_D>::value &&
        is_deserializable<class_E>::value
    };

    constexpr bool is_deserializable_object_result {
        !is_deserializable_object<class_A>::value &&
        !is_deserializable_object<class_B>::value &&
        !is_deserializable_object<class_C>::value &&
        is_deserializable_object<class_D>::value &&
        is_deserializable_object<class_E>::value
    };

    constexpr bool is_constructible_deserializable_result {
        !is_constructible_deserializable<class_A>::value &&
        !is_constructible_deserializable<class_B>::value &&
        is_constructible_deserializable<class_C>::value &&
        !is_constructible_deserializable<class_D>::value &&
        is_constructible_deserializable<class_E>::value
    };

    constexpr bool is_constructible_deserializable_object_result {
        !is_constructible_deserializable_object<class_A>::value &&
        !is_constructible_deserializable_object<class_B>::value &&
        !is_constructible_deserializable_object<class_C>::value &&
        !is_constructible_deserializable_object<class_D>::value &&
        is_constructible_deserializable_object<class_E>::value
    };

    return (is_deserializable_result && is_deserializable_object_result &&
            is_constructible_deserializable_result && is_constructible_deserializable_object_result);
}

} // namespace tests::serialization::impl::Deserializable_typetraits_test

#endif // DESERIALIZABLE_TYPETRAITS_TEST_HPP
