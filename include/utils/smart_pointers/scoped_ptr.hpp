#include <utility> // std::forward
#include <cstddef>

#ifndef SCOPED_PTR_HPP
#define SCOPED_PTR_HPP

namespace alex::utils::smart_pointers {
namespace detail {

template<typename T>
struct default_deleter
{ void operator()(T* ptr) const { delete ptr; } };

template<typename T>
struct default_deleter<T[]>
{ void operator()(T* ptr) const { delete[] ptr; } };

} // namespace alex::smart_pointers::detail



template<typename T, typename Deleter = detail::default_deleter<T>>
struct scoped_ptr
{
    template<typename... Args>
    scoped_ptr(Args&&... args)
        : ptr_{new T{std::forward<Args>(args)...}}
        , deleter_{Deleter{}}
    {}

    scoped_ptr(T* ptr, Deleter deleter = Deleter{})
        : ptr_{ptr}
        , deleter_{deleter}
    {}

    ~scoped_ptr()
    { deleter_(ptr_); }

    T& operator*() noexcept
    { return *ptr_; }

    const T& operator*() const noexcept
    { return *ptr_; }

    T* operator->() noexcept
    { return ptr_; }

    const T* const operator->() const noexcept
    { return ptr_; }

    // No copy, no move
    scoped_ptr(const scoped_ptr&) = delete;
    scoped_ptr& operator=(const scoped_ptr&) = delete;
    scoped_ptr(scoped_ptr&&) = delete;
    scoped_ptr& operator=(scoped_ptr&&) = delete;

private:
    T* ptr_;
    Deleter deleter_;
};



// Partial specialization for arrays
template<typename T, typename Deleter>
struct scoped_ptr<T[], Deleter>
{
    scoped_ptr(T* ptr, Deleter deleter = Deleter{})
        : ptr_{ptr}
        , deleter_{deleter}
    {}

    ~scoped_ptr()
    { deleter_(ptr_); }

    auto& operator*() noexcept
    { return *ptr_; }

    const auto& operator*() const noexcept
    { return *ptr_; }

    auto& operator[](const std::size_t index) noexcept
    { return ptr_[index]; }

    const auto& operator[](const std::size_t index) const noexcept
    { return ptr_[index]; }

    T* operator+(const std::size_t offset) noexcept
    { return (ptr_ + offset); }

    const T* const operator+(const std::size_t offset) const noexcept
    { return (ptr_ + offset); }

    // No copy, no move
    scoped_ptr(const scoped_ptr&) = delete;
    scoped_ptr& operator=(const scoped_ptr&) = delete;
    scoped_ptr(scoped_ptr&&) = delete;
    scoped_ptr& operator=(scoped_ptr&&) = delete;

private:
    T* ptr_;
    Deleter deleter_;
};

} // namespace alex::utils::smart_pointers

#endif // SCOPED_PTR_HPP
