#include <iostream>

#include "utils/overload.hpp"
#include "utils/universal_function_pointer.hpp"
#include "utils/transparent_invoke.hpp"
#include "utils/memory_location_check.hpp"
#include "utils/smart_pointers/scoped_ptr.hpp"
#include "serialization/serialization.hpp"

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
