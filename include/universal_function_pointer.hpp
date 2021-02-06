/* universal_function_pointer.hpp
 *
 * My own implementation of simple wrapper over function pointers
 *
 * Usage example:
 *  void foo() { code ... }         // 1
 *  int bar(int x) { return x; }    // 2
 *
 *  alex::universal_function_pointer p_foo{foo};
 *  alex::universal_function_pointer p_bar{bar};
 *
 *  p_foo();    // call 1
 *  int x = p_bar(10);  // call 2 with arguments forwarding
 *
 *  void(*pure_p_foo)() = p_foo; // universal_function_pointer class can be converted to a pure function pointer
*/



#include <bits/move.h> // std::forward



#ifndef UNIVERSAL_FUNCTION_POINTER_HPP
#define UNIVERSAL_FUNCTION_POINTER_HPP

namespace alex {

template<typename FuncSignature>
class universal_function_pointer
{
    using function_pointer = FuncSignature(*);
public:
    constexpr universal_function_pointer()
        : callable_{nullptr}
    {}

    constexpr universal_function_pointer(function_pointer callable)
        : callable_{callable}
    {}

    constexpr universal_function_pointer(const universal_function_pointer& other)
        : callable_{other.callable_}
    {}

    constexpr universal_function_pointer& operator=(const universal_function_pointer& other)
    {
        callable_ = other.callable_;
        return *this;
    }

    constexpr universal_function_pointer(universal_function_pointer&& other) = default;
    constexpr universal_function_pointer& operator=(universal_function_pointer&& other) = default;

    template<typename... Args>
    constexpr decltype(auto) operator()(Args&&... args) const
    { return callable_(std::forward<Args&&>(args)...); } // Perfect forwarding, no copy, just only forward argument in function

    constexpr operator function_pointer() const noexcept
    { return callable_; }

private:
    function_pointer callable_;
};

} // namespace alex

#endif // UNIVERSAL_FUNCTION_POINTER_HPP
