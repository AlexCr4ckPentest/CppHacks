/* sort.hpp
 *
 * Some sort algorithms
*/



#include <type_traits>
#include <concepts>
#include <iterator>



#ifndef SORT_ALGO_HPP
#define SORT_ALGO_HPP

namespace alex::algorithms::sort
{
  namespace detail
  {
    template<typename T>
    concept RandomAccessIterable = requires (T t)
    {
      { t.begin() }   -> std::random_access_iterator;
      { t.end() }     -> std::random_access_iterator;
      { t.cbegin() }  -> std::random_access_iterator;
      { t.cend() }    -> std::random_access_iterator;
      { t.rbegin() }  -> std::random_access_iterator;
      { t.rend() }    -> std::random_access_iterator;
      { t.crbegin() } -> std::random_access_iterator;
      { t.crend() }   -> std::random_access_iterator;
    };
  } // namesapce alex::algorithms::sort::detail

  // Overload: bubble_sort(begin, end)
  template<std::random_access_iterator Iterator, typename Comparator = std::greater<>>
  void bubble_sort(Iterator first, Iterator last, Comparator&& comp = Comparator{})
  {
    const auto diff{std::distance(first, last)};

    for (auto i{0}; i < diff; i++)
    {
      for (Iterator it{first}; it != (last - i - 1); ++it)
      {
        if (comp(*it, *std::next(it)))
        {
          std::swap(*it, *std::next(it));
        }
      }
    }
  }

  // Overload: bubble_sort(collection)
  template<detail::RandomAccessIterable Collection, typename Comparator = std::greater<>>
  void bubble_sort(Collection&& collection, Comparator&& comp = Comparator{})
  { bubble_sort(std::begin(collection), std::end(collection), comp); }

  template<std::random_access_iterator Iterator, typename Comparator = std::less<>>
  void quick_sort(Iterator first, Iterator last, Comparator&& comp = Comparator{})
  { /* Implementation here */ }

  template<std::random_access_iterator Iterator, typename Comparator = std::less<>>
  void merge_sort(Iterator first, Iterator last, Comparator&& comp = Comparator{})
  { /* Implementation here */ }
} // namespace alex::algorithms::sort

#endif // SORT_ALGO_HPP