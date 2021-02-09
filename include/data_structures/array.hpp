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

template<typename T, std::size_t N>
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

    constexpr array() noexcept : arr_{}
    {}

    constexpr array(std::initializer_list<T> init_list) noexcept : arr_{init_list}
    {}

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
    { return static_cast<const_reference>(at(index)); }

    void fill(const_reference value) { std::fill_n(begin(), N, value); }

    constexpr iterator begin() noexcept                         { return iterator{arr_}; }
    constexpr iterator end() noexcept                           { return iterator{arr_ + (N - 1)}; }
    constexpr reverse_iterator rbegin() noexcept                { return reverse_iterator{end()}; }
    constexpr reverse_iterator rend() noexcept                  { return reverse_iterator{begin()}; }
    constexpr const_iterator cbegin() const noexcept            { return const_iterator{arr_}; }
    constexpr const_iterator cend() const noexcept              { return const_iterator{arr_ + (N - 1)}; }
    constexpr const_reverse_iterator crbegin() const noexcept   { return const_reverse_iterator{cend()}; }
    constexpr const_reverse_iterator crend() const noexcept     { return const_reverse_iterator{cbegin()}; }

    constexpr reference front() noexcept                { return *begin(); }
    constexpr reference back() noexcept                 { return *end(); }
    constexpr const_reference front() const noexcept    { return *cbegin(); }
    constexpr const_reference back() const noexcept     { return *cend(); }

private:
    T arr_[N];
};

} // namespace alex::data_structutes

#endif // ARRAY_HPP
