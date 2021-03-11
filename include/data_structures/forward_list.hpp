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
      forward_list_node(forward_list_node* next, const T& data)
        : next_{next} , data_{data}
      {}

      template<typename... Args>
      forward_list_node(forward_list_node* next, Args&&... args)
        : next_{next} , data_{std::forward<Args>(args)...}
      {}

      forward_list_node* next_;
      T data_;
    };

    template<typename T>
    struct forward_list_iterator
    {
      using value_type          = T;
      using pointer             = value_type*;
      using reference           = value_type&;
      using difference_type     = std::ptrdiff_t;
      using iterator_category   = std::forward_iterator_tag;

    private:
      forward_list_node<T>* ptr_;
    };

    template<typename T>
    struct forward_list_const_iterator
    {
    private:
      forward_list_node<T>* ptr_;
    };
  } // namespace alex::data_structures::detail::fw_list

  template<typename T>
  struct forward_list
  {
    using node = detail::fw_list::forward_list_node<T>;

#if 1
    using value_type        = T;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;
    using pointer           = value_type*;
    using const_pointer     = const value_type*;
    using reference         = value_type&;
    using const_reference   = const value_type&;
    using iterator          = detail::fw_list::forward_list_iterator<T>;
    using const_iterator    = const iterator;
#endif

    forward_list()
      : head_{nullptr}
      , last_{nullptr}
      , size_{0}
    {}

    void push_back(const T& data)
    {
      if (head_ == nullptr)
      {
        head_ = new node{nullptr, data};
        last_ = head_;
      }
      else
      {
        node* list_node{head_};

        while (list_node->next_ != nullptr)
        {
          list_node = list_node->next_;
        }

        list_node->next_ = new node{nullptr, data};
        last_ = list_node->next_;
      }
      size_++;
    }

    template<typename... Args>
    void emplace_back(Args&&... args)
    {
      if (head_ == nullptr)
      {
        head_ = new node{nullptr, std::forward<Args>(args)...};
        last_ = head_;
      }
      else
      {
        node* list_node{head_};

        while (list_node->next_ != nullptr)
        {
          list_node = list_node->next_;
        }

        list_node->next_ = new node{nullptr, std::forward<Args>(args)...};
        last_ = list_node->next_;
      }
      size_++;
    }

    void push_front(const T& data)
    {
      head_ = new node{head_, data};
      size_++;
    }

    template<typename... Args>
    void emplace_front(Args&&... args)
    {
      head_ = new node{head_, std::forward<Args>(args)...};
      size_++;
    }

    reference front()
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
