#include <iostream>

#include "overload.hpp"
#include "universal_function_pointer.hpp"
#include "serialization/serialization.hpp"
#include "transparent_invoke.hpp"

#include "tests/serialization/typetraits_test/typetraits_test.hpp"



class Human : public alex::serialization::SerializableDeserializableObject<Human>
{
    MAIN_OBJECT_INIT(Human)
public:
    Human() {};

    void fromJson(const nlohmann::json&) override {}
    nlohmann::json toJson() const override { return {}; }
};



int main()
{    
    constexpr bool serialization_typetraits_test_result{tests::serialization::run_typetraits_test()};

    switch (1) {
    case serialization_typetraits_test_result:      std::cout << "tests::serialization::run_typetraits_test(): PASSED!\n";  break;
    case !(serialization_typetraits_test_result):   std::cout << "tests::serialization::run_typetraits_test: FAILED!\n";    break;
    }

    Human h;

    std::cout << h.getObjectName() << "\n";

    return 0;
}
