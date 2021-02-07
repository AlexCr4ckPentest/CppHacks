/* transparent_invoke.hpp
 *
*/

#include <bits/move.h>

#ifndef TRANSPARENT_INVOKE_HPP
#define TRANSPARENT_INVOKE_HPP

namespace alex {

template<typename Callable, typename... Args>
decltype(auto) transparent_invoke(Callable&& callable, Args&&... args)
{
    return callable(std::forward<Args&&>(args)...);
}

} // namespace alex

#endif // TRANSPARENT_INVOKE_HPP
