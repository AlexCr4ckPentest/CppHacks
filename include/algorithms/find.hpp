/* find.hpp
 *
 * Some find algorithms
*/



#include <concepts>
#include <iterator>



#ifndef FIND_ALGO_HPP
#define FIND_ALGO_HPP

namespace alex::algorithms::find
{
  // [first, last)
  template<std::input_iterator Iterator, typename T>
  constexpr auto find(Iterator first, Iterator last, const T& value)
  {
    for (; first != last; ++first)
    {
      if (*first == value)
      {
        break;
      }
    }
    return first;
  }

  template<std::input_iterator Iterator, typename UnaryPredicate>
  constexpr auto find_if(Iterator first, Iterator last, UnaryPredicate&& pred)
  {
    for (; first != last; ++first)
    {
      if (pred(*first))
      {
        break;
      }
    }
    return first;
  }

  // Since C++11
  template<std::input_iterator Iterator, typename UnaryPredicate>
  constexpr auto find_if_not(Iterator first, Iterator last, UnaryPredicate&& pred)
  { return find_if(first, last, std::not1(pred)); }

  template<std::input_iterator Iterator, typename BinaryPredicate = std::equal_to<>>
  auto find_first_of(Iterator first, Iterator last,
                      Iterator first_, Iterator last_, BinaryPredicate&& pred = BinaryPredicate{})
  {
    for (; first != last; ++first)
    {
      for (Iterator it{first_}; it != last_; ++it)
      {
        if (pred(*first, *it))
        {
          return first;
        }
      }
    }
    return last;
  }
} // namesapce alex::algorithms::find

#endif // FIND_ALGO_HPP