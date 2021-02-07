#include <iostream>

#include "overload.hpp"
#include "universal_function_pointer.hpp"
#include "serialization/serialization.hpp"
#include "transparent_invoke.hpp"

#include "tests/serialization/typetraits_test/typetraits_test.hpp"



int main()
{    
    constexpr bool serialization_typetraits_test_result{tests::serialization::run_typetraits_test()};

    switch (1) {
    case serialization_typetraits_test_result:      std::cout << "tests::serialization::run_typetraits_test(): PASSED!\n";  break;
    case !(serialization_typetraits_test_result):   std::cout << "tests::serialization::run_typetraits_test: FAILED!\n";    break;
    }

    return 0;
}
