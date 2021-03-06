/* forward_list.hpp
 *
 * Simple forward list with custom iterator
*/



#ifndef _FORWARD_LIST_HPP_
#define _FORWARD_LIST_HPP_

#include <utility>
#include <iterator>



namespace alex::data_structures
{
  namespace detail::forward_list
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

      forward_list_iterator() noexcept : ptr_{nullptr} {}
      forward_list_iterator(forward_list_node<T>* head) noexcept : ptr_{head} {}

      forward_list_iterator(forward_list_iterator&&) noexcept = default;
      forward_list_iterator(const forward_list_iterator&) noexcept = default;
      forward_list_iterator& operator=(forward_list_iterator&&) noexcept = default;
      forward_list_iterator& operator=(const forward_list_iterator&) noexcept = default;

      forward_list_iterator operator++(int) noexcept
      {
        forward_list_iterator tmp{ptr_};
        ptr_ = ptr_->next_;
        return tmp;
      }

      forward_list_iterator& operator++() noexcept
      {
        ptr_ = ptr_->next_;
        return *this;
      }

      forward_list_iterator& operator+(const difference_type offset)
      {
        for (difference_type i{0}; i < offset; i++)
        {
          operator++();
        }
        return *this;
      }

      bool operator==(const forward_list_iterator& other) const noexcept
      { return ptr_ == other.ptr_; }

      bool operator!=(const forward_list_iterator& other) const noexcept
      { return !(*this == other); }

      reference operator*() const noexcept
      { return ptr_->data_; }

    private:
      forward_list_node<T>* ptr_;
    };
  } // namespace alex::data_structures::detail::forward_list

  template<typename T>
  struct forward_list
  {
  private:
    using forward_list_node = detail::forward_list::forward_list_node<T>;

  public:
    using value_type        = T;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;
    using iterator          = detail::forward_list::forward_list_iterator<T>;
    using const_iterator    = detail::forward_list::forward_list_iterator<const T>;

    forward_list() noexcept
      : head_{nullptr}
      , last_{nullptr}
      , size_{0}
    {}

    ~forward_list()
    { clear(); }

    void push_back(const T& data)
    {
      if (head_ == nullptr)
      {
        head_ = new forward_list_node{nullptr, data};
        last_ = head_;
      }
      else
      {
        forward_list_node* list_node{head_};

        while (list_node->next_ != nullptr)
        {
          list_node = list_node->next_;
        }

        list_node->next_ = new forward_list_node{nullptr, data};
        last_ = list_node->next_;
      }
      size_++;
    }

    template<typename... Args>
    void emplace_back(Args&&... args)
    {
      if (head_ == nullptr)
      {
        head_ = new forward_list_node{nullptr, std::forward<Args>(args)...};
        last_ = head_;
      }
      else
      {
        forward_list_node* list_node{head_};

        while (list_node->next_ != nullptr)
        {
          list_node = list_node->next_;
        }

        list_node->next_ = new forward_list_node{nullptr, std::forward<Args>(args)...};
        last_ = list_node->next_;
      }
      size_++;
    }

    void push_front(const T& data)
    {
      head_ = new forward_list_node{head_, data};
      size_++;
    }

    template<typename... Args>
    void emplace_front(Args&&... args)
    {
      head_ = new forward_list_node{head_, std::forward<Args>(args)...};
      size_++;
    }

    void pop_back() noexcept
    {
      if (head_ != nullptr)
      {
        if (size_ == 1)
        {
          delete last_;
          last_ = nullptr;
        }
        else
        {
          forward_list_node* list_node{head_};

          while (list_node->next_->next_ != nullptr)
          {
            list_node = list_node->next_;
          }

          delete list_node->next_;
          list_node->next_ = nullptr;
          last_ = list_node;
        }
        size_--;
      }
    }

    void pop_front() noexcept
    {
      if (head_ != nullptr)
      {
        forward_list_node* list_node{head_};
        head_ = head_->next_;

        delete list_node;
        size_--;
      }
    }

    void clear() noexcept
    {
      while (size_ != 0)
      {
        pop_front();
      }
    }

    void insert(const T& data, size_type index)
    {
      if (index >= size_)
      {
        std::__throw_out_of_range_fmt("%s: index %zu out of range!", __PRETTY_FUNCTION__, index);
      }
      else if (index == 0)
      {
        push_front(data);
      }
      else if (index == (size_ - 1))
      {
        push_back(data);
      }
      else
      {
        
      }
    }



    size_type size() const noexcept
    { return size_; }

    bool is_empty() const noexcept
    { return size_ == 0; }

    reference front() noexcept
    { return head_->data_; }

    const_reference front() const noexcept
    { return head_->data_; }

    reference back() noexcept
    { return last_->data_; }

    const_reference back() const noexcept
    { return last_->data_; }



    iterator begin() noexcept
    { return iterator{head_}; }

    iterator end() noexcept
    { return iterator{last_->next_}; }

    const_iterator begin() const noexcept
    { return const_iterator{head_}; }

    iterator end() const noexcept
    { return iterator{last_->next_}; }

    const_iterator cbegin() const noexcept
    { return const_iterator{head_}; }

    const_iterator cend() const noexcept
    { return const_iterator{last_->next_}; }

  private:
    forward_list_node* head_;
    forward_list_node* last_;
    size_type size_;
  };  
} // namespace alex::data_structures

#endif // _FORWARD_LIST_HPP_