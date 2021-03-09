/* transparent_invoke.hpp
 *
*/

#include <utility> // std::forword

#ifndef TRANSPARENT_INVOKE_HPP
#define TRANSPARENT_INVOKE_HPP

namespace alex::utils
{
template<typename Callable, typename... Args>
decltype(auto) transparent_invoke(Callable&& callable, Args&&... args)
{
    return callable(std::forward<Args>(args)...);
}
} // namespace alex::utils

#endif // TRANSPARENT_INVOKE_HPP
