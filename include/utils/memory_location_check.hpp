#ifndef MEMORY_LOCATION_CHECK_HPP
#define MEMORY_LOCATION_CHECK_HPP

namespace alex::utils::memory_location {

enum class memory_location_type : short
{ stack, heap, null_ptr };

class checker
{
public:
    checker(const checker&) = delete;
    checker(checker&&) = delete;
    checker& operator=(const checker&) = delete;
    checker& operator=(checker&&) = delete;

    template<typename T>
    memory_location_type get_location_type(T* ptr) noexcept
    {
        if (ptr == nullptr) {
            return memory_location_type::null_ptr;
        }

        char local;

        if ((reinterpret_cast<void*>(ptr) < reinterpret_cast<void*>(&local)) == (reinterpret_cast<void*>(this) < reinterpret_cast<void*>(&local))) {
            return memory_location_type::stack;
        }

        return memory_location_type::heap;
    }
};

} // namespace alex::utils::memory_location

#endif // MEMORY_LOCATION_CHECK_HPP
