#ifndef __STRING_IS_PALINDROME_HPP__
#define __STRING_IS_PALINDROME_HPP__

#include <string>
#include <utility>



namespace alex::algorithms::string
{

/**
 * @brief Check for palindrome in input sequence
 * ---------------------------------------------
 *
 *                              <-- rbegin()
 *                                    |
 *     [ # ] ====================== [ # ]
 *       |
 *    begin() -->
 *
 * ---------------------------------------------
 *
 *                     <-- reverse_iterator
 *                         |
 *     ======= [ # ] === [ # ] =======
 *               |
 *        iterator -->
 *
 */
template <typename Iterator, typename ReverseIterator>
constexpr bool is_palindrome(Iterator start, Iterator stop,
                             ReverseIterator r_start,
                             ReverseIterator r_stop) noexcept
{
  for (; start != stop && r_start != r_stop; ++start, ++r_start)
    if (*start != *r_start)
      return false;

  return true;
}

constexpr bool is_palindrome(std::string_view str) noexcept
{ return is_palindrome(str.begin(), str.end(), str.rbegin(), str.rend()); }
} // namespace alex::algorithms::string

#endif /* __STRING_IS_PALINDROME__ */
