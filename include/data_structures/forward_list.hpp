/* forward_list.hpp
 *
 * Simple forward list with custom iterator
*/



#include <utility>
#include <iterator>



#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

namespace alex::data_structures
{
  namespace detail::fw_list
  {
    template<typename T>
    struct forward_list_node
    {
      forward_list_node(forward_list_node* next) : next_{next} , data_{} {}

      template<typename... Args>
      forward_list_node(forward_list_node* next, Args&&... args)
        : next_{next_}
        , data_{std::forward<Args>(args)...}
      {}

      forward_list_node* next_;
      T data_;
    };

    struct forward_list_iterator {};
    struct forward_list_reverse_iterator {};
  } // namespace alex::data_structures::detail::fw_list

  template<typename T>
  struct forward_list
  {
    using node = detail::fw_list::forward_list_node<T>;

    using value_type        = T;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;
    using pointer           = value_type*;
    using const_pointer     = const value_type*;
    using reference         = value_type&;
    using const_reference   = const value_type&;
    using iterator          = detail::fw_list::forward_list_iterator;
    using reverse_iterator  = detail::fw_list::forward_list_reverse_iterator;



    forward_list()
      : head_{nullptr}
      , last_{nullptr}
      , size_{0}
    {}

    void push_back(const T& data)
    {}

    template<typename... Args>
    void emplace_back(Args&&... args)
    {
      node* new_node = new node{nullptr, args...};
      last_ = new_node;
    }



    reference front() noexcept
    { return head_->data_; }

    const_reference front() const noexcept
    { return head_->data_; }

    reference back() noexcept
    { return last_->data_; }

    const_reference back() const noexcept
    { return last_->data_; }

  private:
    node* head_;
    node* last_;
    size_t size_;
  };
} // namespace alex::data_structures

#endif // FORWARD_LIST_HPP