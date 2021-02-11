/* overload.hpp
 *
 * Usage example:
 *
 * auto func = alex::utils::overload {
 *     []() { some code ... },              // 1
 *     [](int) { some code ... },           // 2
 *     [](const char*) { some code ... },   // 3
 *     [](float x) { return x; }            // 4
 * };
 *
 * func(); // call 1
 *
 * func(10); // call 2
 *
 * func("something"); // call 3
 *
 * double result = func(10.f) // call 4
*/



#ifndef OVERLOAD_HPP
#define OVERLOAD_HPP

namespace alex::utils {

template<typename... CallableObject>
struct overload : CallableObject...   // Because lambda is the struct with overloaded operator()
{ using CallableObject::operator()...; }; // Since C++17, it's very cool!! Just one line of code ))

// CTAD
template<typename... CallableObject> overload(CallableObject...) -> overload<CallableObject...>;

} // namespace alex::utils

#endif // OVERLOAD_HPP
