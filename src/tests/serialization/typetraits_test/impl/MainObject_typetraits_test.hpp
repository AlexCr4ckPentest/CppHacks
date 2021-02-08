#include "serialization/serialization.hpp"

#ifndef MAINOBJECT_TYPETRAITS_TEST_HPP
#define MAINOBJECT_TYPETRAITS_TEST_HPP

namespace tests::serialization::impl::MainObject_typetraits_test {

class class_A {};

class class_B
{
public:
    constexpr const int* getObjectName() const noexcept { return nullptr; }
    constexpr void setObjectName() noexcept {}
};

class class_C : public alex::serialization::MainObject<class_C>
{ MAIN_OBJECT_INIT(class_C)
private:
    using alex::serialization::MainObject<class_C>::getObjectName;
    using alex::serialization::MainObject<class_C>::setObjectName;
};

class class_D : public alex::serialization::MainObject<class_D>
{ MAIN_OBJECT_INIT(class_D)
public:
    constexpr const char* getObjectName() const noexcept { return nullptr; }
    constexpr void setObjectName(const char*) noexcept {}
};

class class_E : public alex::serialization::MainObject<class_E>
{ MAIN_OBJECT_INIT(class_E)
};



constexpr bool run_test() noexcept
{
    using alex::serialization::type_traits::detail::has_valid_getObjectName_setObjectName_methods;
    using alex::serialization::type_traits::detail::is_valid_object;

    // must be true
    constexpr bool has_valid_getObjectName_setObjectName_methods_is_ok {
        !has_valid_getObjectName_setObjectName_methods<class_A>::value &&  // has no methods - false
        !has_valid_getObjectName_setObjectName_methods<class_B>::value &&  // has no valid methods, and not derived from MainObject - false
        !has_valid_getObjectName_setObjectName_methods<class_C>::value &&  // has a private methods - false
        !has_valid_getObjectName_setObjectName_methods<class_D>::value &&  // has overlapped methods - false
        has_valid_getObjectName_setObjectName_methods<class_E>::value      // all is ok - true
    };

    // must be true
    constexpr bool is_valid_object_is_ok {
        !is_valid_object<class_A>::value &&
        !is_valid_object<class_B>::value &&
        !is_valid_object<class_C>::value &&
        !is_valid_object<class_D>::value &&
        is_valid_object<class_E>::value
    };

    return (has_valid_getObjectName_setObjectName_methods_is_ok && is_valid_object_is_ok);
}

} // namespace tests::serialization::impl::MainObject_typetraits_test

#endif // MAINOBJECT_TYPETRAITS_TEST_HPP
