#ifndef _MEMORY_LOCATION_CHECK_HPP_
#define _MEMORY_LOCATION_CHECK_HPP_

namespace alex::utils::memory_location
{
    namespace impl
    {
        enum class location_type : short
        { stack, heap, null_ptr };

        class location_cheker
        {
        public:
            location_cheker() = default;
            location_cheker(const location_cheker&) = delete;
            location_cheker(location_cheker&&) = delete;
            location_cheker& operator=(const location_cheker&) = delete;
            location_cheker& operator=(location_cheker&&) = delete;

            template<typename T>
            location_type get_location_type(T* ptr) noexcept
            {
                if (ptr == nullptr) {
                    return location_type::null_ptr;
                }

                char local;

                if ((reinterpret_cast<void*>(ptr) < reinterpret_cast<void*>(&local)) == (reinterpret_cast<void*>(this) < reinterpret_cast<void*>(&local))) {
                    return location_type::stack;
                }

                return location_type::heap;
            }
        };
    } // namespace alex::utils::memory_location::impl

    using impl::location_type;
    using memory_location_checker = impl::location_cheker;
} // namespace alex::utils::memory_location

#endif // _MEMORY_LOCATION_CHECK_HPP_