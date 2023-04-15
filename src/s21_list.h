#ifndef _list_
#define _list_

#include <iostream>
#include <memory>

namespace s21 {

template <typename T, typename A = std::allocator<T>> struct list_node {
  list_node *prev;
  list_node *next;
  T key;
  explicit list_node(const T &val = T(), list_node *p = nullptr,
                     list_node *n = nullptr)
      : prev{p}, next{n}, key{val} {}
};

template <typename T, typename A = std::allocator<T>> class list {
public:
  typedef A allocator_type;
  typedef typename A::value_type value_type;
  typedef typename A::reference reference;
  typedef typename A::const_reference const_reference;
  typedef typename A::difference_type difference_type;
  typedef typename A::size_type size_type;
  typedef typename A::template rebind<list_node<T, A>>::other NodeAllocator;

  typedef list_node<T, A> node;
  typedef list_node<T, A> *node_ptr;

  class iterator {
  public:
    typedef typename A::difference_type difference_type;
    typedef typename A::value_type value_type;
    typedef typename A::reference reference;
    typedef typename A::pointer pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    iterator() : ptr{nullptr} {}
    explicit iterator(node_ptr p) : ptr{p} {}
    iterator(const iterator &iter) : ptr{iter.ptr} {}
    ~iterator() { ptr = nullptr; }

    iterator &operator=(const iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    bool operator==(const iterator &other) const { return ptr == other.ptr; }
    bool operator!=(const iterator &other) const { return ptr != other.ptr; }

    iterator &operator++() {
      ptr = ptr->next;
      return *this;
    }

    iterator operator++(int) {
      iterator tmp = *this;
      ptr = ptr->next;
      return tmp;
    }

    iterator &operator--() {
      ptr = ptr->prev;
      return *this;
    }

    iterator operator--(int) {
      iterator tmp = *this;
      ptr = ptr->prev;
      return tmp;
    }

    reference operator*() const { return ptr->key; }
    node_ptr get_ptr() const { return ptr; }

  private:
    node_ptr ptr;
  };

  class const_iterator {
  public:
    typedef typename A::difference_type difference_type;
    typedef typename A::value_type value_type;
    typedef typename A::const_reference reference;
    typedef typename A::const_pointer pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    const_iterator() : ptr{nullptr} {}
    explicit const_iterator(node_ptr p) : ptr{p} {}
    const_iterator(const const_iterator &iter) : ptr{iter.ptr} {}
    ~const_iterator() { ptr = nullptr; }

    const_iterator &operator=(const const_iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    bool operator==(const const_iterator &other) const {
      return ptr == other.ptr;
    }
    bool operator!=(const const_iterator &other) const {
      return ptr != other.ptr;
    }

    const_iterator &operator++() {
      ptr = ptr->next;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator tmp = *this;
      ptr = ptr->next;
      return tmp;
    }

    const_iterator &operator--() {
      ptr = ptr->prev;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator tmp = *this;
      ptr = ptr->prev;
      return tmp;
    }

    reference operator*() const { return ptr->key; }
    node_ptr get_ptr() const { return ptr; }

  private:
    node_ptr ptr;
  };

  class reverse_iterator {
  public:
    typedef typename A::difference_type difference_type;
    typedef typename A::value_type value_type;
    typedef typename A::reference reference;
    typedef typename A::pointer pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    reverse_iterator() : ptr{nullptr} {}
    explicit reverse_iterator(node_ptr p) : ptr{p} {}
    reverse_iterator(const reverse_iterator &iter) : ptr{iter.ptr} {}
    ~reverse_iterator() { ptr = nullptr; }

    reverse_iterator &operator=(const reverse_iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    bool operator==(const reverse_iterator &other) const {
      return ptr == other.ptr;
    }
    bool operator!=(const reverse_iterator &other) const {
      return ptr != other.ptr;
    }

    reverse_iterator &operator++() {
      ptr = ptr->prev;
      return *this;
    }

    reverse_iterator operator++(int) {
      reverse_iterator tmp = *this;
      ptr = ptr->prev;
      return tmp;
    }

    reverse_iterator &operator--() {
      ptr = ptr->next;
      return *this;
    }

    reverse_iterator operator--(int) {
      reverse_iterator tmp = *this;
      ptr = ptr->next;
      return tmp;
    }

    reference operator*() const { return ptr->key; }

  private:
    node_ptr ptr;
  };

  class const_reverse_iterator {
  public:
    typedef typename A::difference_type difference_type;
    typedef typename A::value_type value_type;
    typedef typename A::const_reference reference;
    typedef typename A::const_pointer pointer;
    typedef std::bidirectional_iterator_tag iterator_category;

    const_reverse_iterator() : ptr{nullptr} {}
    explicit const_reverse_iterator(node_ptr p) : ptr{p} {}
    const_reverse_iterator(const const_reverse_iterator &iter)
        : ptr{iter.ptr} {}
    ~const_reverse_iterator() { ptr = nullptr; }

    const_reverse_iterator &operator=(const const_reverse_iterator &other) {
      ptr = other.ptr;
      return *this;
    }

    bool operator==(const const_reverse_iterator &other) const {
      return ptr == other.ptr;
    }
    bool operator!=(const const_reverse_iterator &other) const {
      return ptr != other.ptr;
    }

    const_reverse_iterator &operator++() {
      ptr = ptr->prev;
      return *this;
    }

    const_reverse_iterator operator++(int) {
      const_reverse_iterator tmp = *this;
      ptr = ptr->prev;
      return tmp;
    }

    const_reverse_iterator &operator--() {
      ptr = ptr->next;
      return *this;
    }

    const_reverse_iterator operator--(int) {
      const_reverse_iterator tmp = *this;
      ptr = ptr->next;
      return tmp;
    }

    reference operator*() const { return ptr->key; }

  private:
    node_ptr ptr;
  };

  list() : list(A()) {}
  explicit list(const A &alloc)
      : head{nullptr}, tail{nullptr}, sz{0}, allocator{alloc} {}
  explicit list(size_type count, const T &value, const A &alloc = A())
      : head{nullptr}, tail{nullptr}, sz{0}, allocator{alloc} {
      for (size_type i = 0; i < count; ++i)
        push_back(value);
  }

  explicit list(size_type count, const A &alloc = A())
      : list(count, T(), alloc) {}

  list(const list &other) : list(other, other.allocator) {}

  list(const list &other, const A &alloc) : list(alloc) {
      for (node_ptr i = other.head; i; i = i->next)
        push_back(i->key);
  }

  list &operator=(const list &other) {
    if (this == &other)
      return *this;
    list tmp{other};
    std::swap(*this, tmp);
    return *this;
  }

  list(list &&other) noexcept : list(other, other.allocator) {}

  list(list &&other, const A &alloc) noexcept
      : head{other.head}, tail{other.tail}, sz{other.sz}, allocator{alloc} {
    other.head = other.tail = nullptr;
  }

  list &operator=(list &&other) {
    std::swap(*this, other);
    return *this;
  }

  template <typename InputIt,
            typename = typename std::enable_if<
                std::is_base_of<std::input_iterator_tag,
                                typename std::iterator_traits<
                                    InputIt>::iterator_category>::value>::type>
  list(InputIt first, InputIt last, const A& alloc = A()) : list(alloc) {
    if (!(last > first))
      throw std::length_error("last <= first");

    for (InputIt i = first; i < last; ++i)
      push_back(*i);
  }

  explicit list(std::initializer_list<T> init, const A &alloc = A())
      : list(init.begin(), init.end(), alloc) {}

  ~list() { dealloc(0); }

  list &operator=(std::initializer_list<T> ilist) {
    list tmp{ilist};
    std::swap(*this, tmp);
    return *this;
  }

  void assign(size_type count, const T &value) {
    list tmp{count, value};
    *this = tmp;
  }

  template <typename InputIt,
            typename = typename std::enable_if<
                std::is_base_of<std::input_iterator_tag,
                                typename std::iterator_traits<
                                    InputIt>::iterator_category>::value>::type>
  void assign(InputIt first, InputIt last) {
    list tmp{first, last};
    std::swap(*this, tmp);
  }

  void assign(std::initializer_list<T> ilist) {
    list tmp{ilist};
    *this = tmp;
  }

  allocator_type get_allocator() const noexcept { return allocator; }

  /* Element access */

  reference front() { return head->key; }
  const_reference front() const { return head->key; }

  reference back() { return tail->key; }
  const_reference back() const { return tail->key; }

  /* Iterators */

  iterator begin() noexcept { return iterator{head}; }
  const_iterator begin() const noexcept { return const_iterator(head); }
  const_iterator cbegin() const noexcept { return const_iterator(head); }

  iterator end() noexcept { return iterator{nullptr}; }
  const_iterator end() const noexcept { return const_iterator(nullptr); }
  const_iterator cend() const noexcept { return const_iterator(nullptr); }

  reverse_iterator rbegin() noexcept { return reverse_iterator(tail); }
  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(tail);
  }
  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(tail);
  }

  reverse_iterator rend() noexcept { return reverse_iterator(nullptr); }
  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(nullptr);
  }
  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(nullptr);
  }

  /* Capacity */

  bool empty() const noexcept { return size() == 0; }
  size_type size() const noexcept { return sz; }
  size_type max_size() const noexcept { return allo.max_size(); }

  /* Modifiers */

  void clear() noexcept { resize(0); }

  iterator insert ( const_iterator pos, const T& value ) {
    iterator new_iterator(pos.get_ptr());
    if (new_iterator == begin()) {
      push_front(value);
      new_iterator = iterator(head);
    } else if (new_iterator == end()) {
      push_back(value);
      new_iterator = iterator(tail);
    } else {
      node_ptr tmp = pos.get_ptr();
      node_ptr new_node = allo.allocate(1);
      new_node->key = value;
      new_node->prev = tmp->prev;
      new_node->next = tmp;
      tmp->prev->next = new_node;
      tmp->prev = new_node;
      new_iterator = iterator(new_node);
      ++sz;
    }
    return new_iterator;
  }


  iterator insert ( const_iterator pos, T&& value ) {
    iterator new_iterator(pos.get_ptr());
    if (new_iterator == begin()) {
      push_front(value);
      new_iterator = iterator(head);
    } else if (new_iterator == end()) {
      push_back(value);
      new_iterator = iterator(tail);
    } else {
      node_ptr tmp = pos.get_ptr();
      node_ptr new_node = allo.allocate(1);
      new_node->key = std::move(value);
      new_node->prev = tmp->prev;
      new_node->next = tmp;
      tmp->prev->next = new_node;
      tmp->prev = new_node;
      new_iterator = iterator(new_node);
      ++sz;
    }
    return new_iterator;
  }

  iterator insert ( const_iterator pos, size_type count, const T& value ) {
    iterator first_iterator(pos.get_ptr());
    bool first_iteration = true;
    while (count--) {
      if (first_iteration) {
        first_iteration = false;
        first_iterator = insert(pos, value);
      } else {
        insert(pos, value);
      }
    }
    return first_iterator;
  }

  template <typename InputIt,
            typename = typename std::enable_if<
                std::is_base_of<std::input_iterator_tag,
                                typename std::iterator_traits<
                                    InputIt>::iterator_category>::value>::type>
    iterator insert ( const_iterator pos, InputIt first, InputIt last ) {
      iterator first_iterator(pos.get_ptr());
      bool first_iteration = true;
      while (first != last) {
        if (first_iteration) {
          first_iteration = false;
          first_iterator = insert(pos, *first++);
        } else {
          insert(pos, *first++);
        }
      }
      return first_iterator;
    }

  iterator insert ( const_iterator pos, std::initializer_list<T> ilist ) {
    iterator first_iterator(pos.get_ptr());
    bool first_iteration = true;
    for (auto it = ilist.begin(); it != ilist.end(); ++it) {
      if (first_iteration) {
        first_iteration = false;
        first_iterator = insert(pos, *it);
      } else {
        insert(pos, *it);
      }
    }
    return first_iterator;
  }

  template< class... Args >
    iterator emplace ( const_iterator pos, Args&&... args ) {
      iterator it(pos.get_ptr());
      if (it == begin()) {
        emplace_front(args...);
        it = iterator(head);
      } else if (it == end()) {
        emplace_back(args...);
        it = iterator(tail);
      } else {
        node_ptr tmp = pos.get_ptr();
        node_ptr new_node = allo.allocate(1);
        try {
          allocator.construct(&new_node->key, std::forward<Args>(args)...);
          new_node->prev = tmp->prev;
          new_node->next = tmp;
          tmp->prev->next = new_node;
          tmp->prev = new_node;
          ++sz;
          it = iterator(new_node);
        } catch (...) {
          allo.deallocate(new_node, 1);
          throw;
        }
      }
      return it;
    }

  iterator erase ( const_iterator pos ) {
    node_ptr tmp = pos.get_ptr();
    iterator it(tmp);
    if (tmp == head) {
      pop_front();
      it = iterator(head);
    }
    else if(tmp == tail) {
      pop_back();
      it = iterator(tail);
    } else {
      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;
      it = iterator(tmp->next);
      allo.deallocate(tmp, 1);
      --sz;
    }
    return it;
  }

  void push_back(const T &value) {
    node_ptr new_node = allo.allocate(1);
    new_node->key = value;
    new_node->prev = tail;
    new_node->next = nullptr;
    if (tail != nullptr) tail->next = new_node;
    tail = new_node;
    if (head == nullptr)
      head = tail;
    sz++;
  }

  void push_back(T &&value) {
    node_ptr new_node = allo.allocate(1);
    new_node->key = std::move(value);
    new_node->prev = tail;
    new_node->next = nullptr;
    if (tail)
      tail->next = new_node;
    tail = new_node;
    if (head == nullptr)
      head = tail;
    sz++;
  }

  template< class... Args >
    reference emplace_back( Args&&... args ) {
      node_ptr new_node = allo.allocate(1);
      try {
        allocator.construct(&new_node->key, std::forward<Args>(args)...);
        new_node->prev = tail;
        new_node->next = nullptr;
        if (tail)
          tail->next = new_node;
        tail = new_node;
        if (head == nullptr)
            head = tail;
          sz++;
        return tail->key;
      } catch (...) {
        allo.deallocate(new_node, 1);
        throw;
      }
    }

  void pop_back() { dealloc(size() - 1); }

  void push_front(const T &value) {
    node_ptr new_node = allo.allocate(1);
    new_node->key = value;
    new_node->prev = nullptr;
    new_node->next = head;
    if (head)
      head->prev = new_node;
    head = new_node;
    if (tail == nullptr)
      tail = head;
    sz++;
  }

  void push_front(T &&value) {
    node_ptr new_node = allo.allocate(1);
    new_node->key = std::move(value);
    new_node->prev = nullptr;
    new_node->next = head;
    if (head)
      head->prev = new_node;
    head = new_node;
    if (tail == nullptr)
      tail = head;
    sz++;
  }

  template< class... Args >
    reference emplace_front( Args&&... args ) {
      node_ptr new_node = allo.allocate(1);
      try {
      allocator.construct(&new_node->key, std::forward<Args>(args)...);
      new_node->prev = nullptr;
      new_node->next = head;
      if (head)
        head->prev = new_node;
      head = new_node;
      if (tail == nullptr)
        tail = head;
      sz++;
      return head->key;
      } catch (...) {
        allo.deallocate(new_node, 1);
        throw;
      }
    }

  void pop_front() {
    node_ptr ptr = head;
    head = head->next;
    head->prev = nullptr;
    allo.deallocate(ptr, 1);
    --sz;
  }

  void resize(size_type count) { resize(count, T()); }

  void resize(size_type count, const T &value) {
    if (sz == count) return;
    if (count > sz)
      while (sz != count)
        push_back(value);
    else
      dealloc(count);
  }

  void swap( list& other ) noexcept {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(sz, other.sz);
  }

  /* Operations */

  void merge( list&& other ) {
    if (this == &other) return;
    // merge SORTED lists
    const_iterator start = cbegin();
    const_iterator o_start = other.cbegin();

    while (o_start != other.end() && start != end()) {
      if (*o_start < *start) {
        insert(start, *o_start);
        ++o_start;
      } else {
        ++start;
      }
    }
    while (o_start != other.end()) {
      push_back(*o_start);
      ++o_start;
    }
    other.clear();
  }
  /* template< class Compare > */
  /*   void merge( list&& other, Compare comp ) {} */

  /* void splice( const_iterator pos, list&& other ) {} */
  /* void splice( const_iterator pos, list&& other, const_iterator it ) {} */
  /* void splice( const_iterator pos, list&& other, */
  /*              const_iterator first, const_iterator last ) {} */

  /* void remove( const T& value ) {} */

  /* void reverse() noexcept {} */

  /* void unique() {} */

  void sort() { head = MergeSort(head); }

private:
  node_ptr MergeSort(node_ptr head_) {
    if (head_ == nullptr || head_->next == nullptr)
      return head_;

    node_ptr middle = GetMiddle(head_, nullptr);
    node_ptr nextToMiddle = middle->next;

    middle->next = nullptr;

    node_ptr leftHead = MergeSort(head_);
    node_ptr rightHead = MergeSort(nextToMiddle);

    return Merge(leftHead, rightHead);
  }

  node_ptr GetMiddle(node_ptr start, node_ptr end) {
    node_ptr slow = start;
    node_ptr fast = start->next;

    while (fast != end) {
      fast = fast->next;
      if (fast != end) {
        slow = slow->next;
        fast = fast->next;
      }
    }

    return slow;
  }

  node_ptr Merge(node_ptr leftHead, node_ptr rightHead) {
    node dummy;
    node_ptr tail_ = &dummy;
    while (leftHead != nullptr && rightHead != nullptr) {
      if (leftHead->key < rightHead->key) {
        tail_->next = leftHead;
        leftHead->prev = tail_;
        leftHead = leftHead->next;
      } else {
        tail_->next = rightHead;
        rightHead->prev = tail_;
        rightHead = rightHead->next;
      }

      tail_ = tail_->next;
    }

    if (leftHead != nullptr) {
      tail_->next = leftHead;
      leftHead->prev = tail_;
    } else {
      tail_->next = rightHead;
      rightHead->prev = tail_;
    }

    while (tail_->next != nullptr)
      tail_ = tail_->next;

    tail_->next = nullptr;
    tail = tail_;

    return dummy.next;
  }


  void dealloc(size_type count) {
    if (tail && sz > count) {
      node_ptr tmp = tail, pre = tmp->prev;
      for (; sz != count; tmp = pre, pre = tmp ? tmp->prev : nullptr, --sz)
        allo.deallocate(tmp, 1);
      if (tmp)
        tmp->next = nullptr;
      tail = tmp;
      if (sz == 0)
        head = tail;
    }
  }


private:
  list_node<T, A> *head;
  list_node<T, A> *tail;
  size_type sz;
  A allocator;
  NodeAllocator allo;
};
} // namespace s21

#endif // _list_
