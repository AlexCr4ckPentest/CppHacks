/* transparent_invoke.hpp
 *
*/



#ifndef _TRANSPARENT_INVOKE_HPP_
#define _TRANSPARENT_INVOKE_HPP_

#include <utility> // std::forword



namespace alex::utils
{
    template<typename Callable, typename... Args>
    decltype(auto) transparent_invoke(Callable&& callable, Args&&... args)
    {
        return callable(std::forward<Args>(args)...);
    }
} // namespace alex::utils

#endif // _TRANSPARENT_INVOKE_HPP_