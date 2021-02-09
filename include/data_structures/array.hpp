/* array.hpp
 *
 * Just a simple safe-wrapper over C-style arrays (yes, i know that it already exists in STD)
*/



#include <type_traits>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

#ifndef ARRAY_HPP
#define ARRAY_HPP

namespace alex::data_structutes {
namespace detail {

template<std::size_t val, std::size_t compare>
struct is_greater_than
{ constexpr static bool value{val > compare}; };

} // namespace alex::data_structutes::detail



template<typename T, std::size_t N, typename = std::enable_if_t<detail::is_greater_than<N, 0>::value>>
struct array
{
    using value_type                = T;
    using size_type                 = std::size_t;
    using difference_type           = std::ptrdiff_t;
    using pointer                   = value_type*;
    using const_pointer             = const value_type*;
    using reference                 = value_type&;
    using const_reference           = const value_type&;
    using iterator                  = pointer;
    using const_iterator            = const_pointer;
    using reverse_iterator          = std::reverse_iterator<iterator>;
    using const_reverse_iterator    = std::reverse_iterator<const_iterator>;

    constexpr array() noexcept : arr_{} {}

    constexpr array(std::initializer_list<T> init_list) noexcept
    { std::move(init_list.begin(), init_list.end(), begin()); }

    constexpr size_type size() const noexcept   { return N; }
    constexpr bool is_empty() const noexcept    { return N == 0; }

    constexpr reference operator[](size_type index) noexcept                { return arr_[index]; }
    constexpr const_reference operator[](size_type index) const noexcept    { return arr_[index]; }

    constexpr reference at(size_type index)
    {
        if (index >= N) { throw std::out_of_range("array::at(): index out of range!"); }
        return arr_[index];
    }

    constexpr const_reference at(size_type index) const
    {
        if (index >= N) { throw std::out_of_range("array::at(): index out of range!"); }
        return arr_[index];
    }

    constexpr void fill(const_reference value)  { std::fill_n(begin(), N, value); }

    template<typename U, typename = std::enable_if_t<std::is_nothrow_swappable_v<U>>>
    constexpr void swap(U& other) noexcept              { std::swap_ranges(begin(), end(), other.begin()); }
    constexpr void swap(array& other_array) noexcept    { std::swap_ranges(begin(), end(), other_array.begin()); }

    constexpr iterator begin() noexcept                         { return iterator{arr_}; }
    constexpr iterator end() noexcept                           { return iterator{arr_ + N}; }
    constexpr reverse_iterator rbegin() noexcept                { return reverse_iterator{end()}; }
    constexpr reverse_iterator rend() noexcept                  { return reverse_iterator{begin()}; }
    constexpr const_iterator cbegin() const noexcept            { return const_iterator{arr_}; }
    constexpr const_iterator cend() const noexcept              { return const_iterator{arr_ + N}; }
    constexpr const_reverse_iterator crbegin() const noexcept   { return const_reverse_iterator{cend()}; }
    constexpr const_reverse_iterator crend() const noexcept     { return const_reverse_iterator{cbegin()}; }

    constexpr reference front() noexcept                { return *begin(); }
    constexpr reference back() noexcept                 { return *end(); }
    constexpr const_reference front() const noexcept    { return *cbegin(); }
    constexpr const_reference back() const noexcept     { return *cend(); }

private:
    T arr_[N];
};

template<typename T, typename... U>
array(T, U...) -> array<std::enable_if_t<(std::is_same_v<T, U> && ...), T>, (sizeof...(U)) + 1>;

} // namespace alex::data_structutes

#endif // ARRAY_HPP
