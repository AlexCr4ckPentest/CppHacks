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
  template<std::random_access_iterator Iterator, typename Comparator = std::less<>>
  void bubble_sort(Iterator first, Iterator last, Comparator&& comp = Comparator{}) {}

  template<std::random_access_iterator Iterator, typename Comparator = std::less<>>
  void quick_sort(Iterator first, Iterator last, Comparator&& comp = Comparator{}) {}

  template<std::random_access_iterator Iterator, typename Comparator = std::less<>>
  void merge_sort(Iterator first, Iterator last, Comparator&& comp = Comparator{}) {}
} // namespace alex::algorithms::sort

#endif // SORT_ALGO_HPP