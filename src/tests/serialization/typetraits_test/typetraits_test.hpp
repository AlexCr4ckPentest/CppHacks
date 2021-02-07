#ifndef SERIALIZATION_TYPETRAITS_TEST_HPP
#define SERIALIZATION_TYPETRAITS_TEST_HPP

#include "impl/MainObject_typetraits_test.hpp"
#include "impl/Serializable_typetraits_test.hpp"
#include "impl/Deserializable_typetraits_test.hpp"
#include "impl/SerializableDeserializable_typetraits_test.hpp"

namespace tests::serialization {
constexpr bool run_typetraits_test() noexcept
{
    namespace MainObject_typetraits_test = impl::MainObject_typetraits_test;
    namespace Serializable_typetraits_test = impl::Serializable_typetraits_test;
    namespace Deserializable_typetraits_test = impl::Deserializable_typetraits_test;
    namespace SerializableDeserializable_typetraits_test = impl::SerializableDeserializable_typetraits_test;

    constexpr bool MainObject_typetraits_test_result{MainObject_typetraits_test::run_test()};
    constexpr bool Serializable_typetraits_test_result{Serializable_typetraits_test::run_test()};
    constexpr bool Deserializable_typetraits_test_result{Deserializable_typetraits_test::run_test()};
    constexpr bool SerializableDeserializable_typetraits_test_result{SerializableDeserializable_typetraits_test::run_test()};

    return (MainObject_typetraits_test_result && Serializable_typetraits_test_result &&
            Deserializable_typetraits_test_result && SerializableDeserializable_typetraits_test_result);
}
} // namespace tests::serialization

#endif // SERIALIZATION_TYPETRAITS_TEST_HPP
