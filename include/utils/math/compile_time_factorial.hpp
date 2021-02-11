/* compile_time_factorial.hpp
 *
 * Calculating factorial at compile time using recursive templates instantiation
 * Requires Boost.Multiprecision library
*/



#include <boost/multiprecision/cpp_int.hpp>



#ifndef COMPILE_TIME_FACTORIAL_HPP
#define COMPILE_TIME_FACTORIAL_HPP

#warning "Be careful when using large numbers!"
#warning "Add the -ftemplate-depth=N flag to increase the depth of template instantiation!"



#define __DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(namespace_, integer_type)  \
template<size_t N>  \
struct ct_factorial_##integer_type  \
{ static constexpr namespace_::integer_type value{N * ct_factorial_##integer_type<N - 1>::value}; };  \
template<>  \
struct ct_factorial_##integer_type<0> \
{ static constexpr namespace_::integer_type value{1}; }



#define __DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(integer_type)  \
template<size_t N>  \
struct ct_factorial_##integer_type  \
{ static constexpr integer_type value{static_cast<integer_type>(N) * ct_factorial_##integer_type<N - 1>::value}; };  \
template<>  \
struct ct_factorial_##integer_type<0> \
{ static constexpr integer_type value{1}; }



namespace alex::utils::math::ct_factorial {
namespace int_types {

// Signed int types
using boost::multiprecision::int128_t;
using boost::multiprecision::int256_t;
using boost::multiprecision::int512_t;
using boost::multiprecision::int1024_t;

// Unsigned int types
using boost::multiprecision::uint128_t;
using boost::multiprecision::uint256_t;
using boost::multiprecision::uint512_t;
using boost::multiprecision::uint1024_t;

// Safety signed safe int types
using boost::multiprecision::checked_int128_t;
using boost::multiprecision::checked_int256_t;
using boost::multiprecision::checked_int512_t;
using boost::multiprecision::checked_int1024_t;

// Safety unsigned int types
using boost::multiprecision::checked_uint128_t;
using boost::multiprecision::checked_uint256_t;
using boost::multiprecision::checked_uint512_t;
using boost::multiprecision::checked_uint1024_t;
} // namespace alex::utils::math::ct_factorial::int_types



__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(int8_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(int16_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(int32_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(int64_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(intmax_t);

__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(uint8_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(uint16_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(uint32_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(uint64_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(uintmax_t);

__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(int_fast8_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(int_fast16_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(int_fast32_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(int_fast64_t);

__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(int_least8_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(int_least16_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(int_least32_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(int_least64_t);

__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(uint_fast8_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(uint_fast16_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(uint_fast32_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(uint_fast64_t);

__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(uint_least8_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(uint_least16_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(uint_least32_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_NATIVE_TYPE__(uint_least64_t);



__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, int128_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, int256_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, int512_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, int1024_t);

__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, uint128_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, uint256_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, uint512_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, uint1024_t);

__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, checked_int128_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, checked_int256_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, checked_int512_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, checked_int1024_t);

__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, checked_uint128_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, checked_uint256_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, checked_uint512_t);
__DECLARE_CT_FACTORIAL_ON_STRUCTS_WITH_CUSTOM_TYPE_FRON_NAMESAPCE__(int_types, checked_uint1024_t);

} // namespace alex::utils::math::ct_factorial

#endif // COMPILE_TIME_FACTORIAL_HPP
