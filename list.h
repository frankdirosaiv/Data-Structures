#ifndef _LIST_H_
#define _LIST_H_
#include <iostream>
#include <iterator>

namespace mystl {

////////////////////////////////////////////////////////////////////////////////
/// @brief Doubly-linked list
/// @ingroup MySTL
/// @tparam T Data type
///
/// Assumes the following: There is always enough memory for allocations (not a
/// good assumption, just good enough for our purposes); Functions not
/// well-defined on an empty container will exhibit undefined behavior, e.g.,
/// front().
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class list {

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Internal structure for linked list
  //////////////////////////////////////////////////////////////////////////////
  struct node {
    T t;        ///< Value
    node* prev; ///< Previous node
    node* next; ///< Next node

    /// @brief Default Constructor
    /// @param val Value
    /// @param p Previous node
    /// @param n Next node
    node(const T& val = T(), node* p = NULL, node* n = NULL) : t(val), prev(p), next(n) {}
  };

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Bidirectional iterator
  //////////////////////////////////////////////////////////////////////////////
  template<typename U>
  class list_iterator : public std::iterator<std::bidirectional_iterator_tag, U> {
    public:
      //////////////////////////////////////////////////////////////////////////
      /// @name Constructors
      /// @{

      /// @brief Construction
      /// @param v Pointer to element of vector
      list_iterator(node* v = NULL) : n(v) {}
      /// @brief Copy construction
      /// @param i Iterator
      list_iterator(const list_iterator& i) : n(i.n) {}
      /// @brief Destruction
      ~list_iterator() {}

      /// @brief Copy assignment
      /// @param i Iterator
      list_iterator& operator=(const list_iterator& i) {n = i.n;}

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Comparison
      /// @{

      /// @brief Equality comparison
      /// @param i Iterator
      bool operator==(const list_iterator& i) const {return n == i.n;}
      /// @brief Inequality comparison
      /// @param i Iterator
      bool operator!=(const list_iterator& i) const {return n != i.n;}

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Dereference
      /// @{

      /// @brief Dereference operator
      U& operator*() const {return n->t;}
      /// @brief Dereference operator
      U* operator->() const {return &n->t;}

      /// @}
      //////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////
      /// @name Advancement
      /// @{

      /// @brief Pre-increment
      list_iterator& operator++() {n = n->next; return *this;}
      /// @brief Post-increment
      list_iterator operator++(int) {list_iterator tmp(*this); ++(*this); return tmp;}
      /// @brief Pre-decrement
      list_iterator& operator--() {n = n->prev; return *this;}
      /// @brief Post-decrement
      list_iterator operator--(int) {list_iterator tmp(*this); --(*this); return tmp;}

      /// @}
      //////////////////////////////////////////////////////////////////////////

      friend class list;

    private:
      node* n; ///< List node
  };

  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Types
    /// @{

    typedef list_iterator<T>
      iterator;               ///< Random access iterator
    typedef list_iterator<const T>
      const_iterator;         ///< Const random access iterator

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{

    /// @brief Default constructor
    /// @param n Initial size
    /// @param val Initial value
    list(size_t n = 0, const T& val = T()) : head(NULL), tail(NULL), sz(0) {
      /// @todo Implement default construction
      while (sz < n) {
        push_back(val);
      }
    }
    /// @brief Copy constructor
    /// @param v
    list(const list& v) {
      /// @todo Implement copy construction 
      sz = 0;
      head = NULL;
      tail = NULL;
      for (const_iterator it = v.cbegin(); it != v.cend(); ++it) {
        push_back(*it);
      }
    }
    /// @brief Destructor
    ~list() {
      /// @todo Implement destruction
      while (sz > 0) {
        pop_front();
      }
    }

    /// @brief Copy assignment
    /// @param v
    /// @return Reference to self
    list& operator=(const list& v) {
      /// @todo Copy assignment
      clear();
      for (const_iterator it = v.cbegin(); it != v.cend(); ++it) {
        push_back(*it);
      }
      return *this;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Iterators
    /// @{

    /// @return Iterator to beginning
    iterator begin() {return iterator(head);}
    /// @return Iterator to beginning
    const_iterator cbegin() const {return const_iterator(head);}
    /// @return Iterator to end
    iterator end() {return iterator();}
    /// @return Iterator to end
    const_iterator cend() const {return const_iterator();}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Capacity
    /// @{

    /// @return Size of list
    size_t size() const {return sz;}
    /// @return Does the list contain anything?
    bool empty() const {return sz == 0;}

    /// @brief Resize the list
    /// @param n Size
    /// @param val Value if size is greater of default elements
    ///
    /// If the new size is less than the current progressively remove elements
    /// in the list. Otherwise progressively insert values at the end equal to
    /// \c val.
    void resize(size_t n, const T& val = T()) {
      /// @todo Implement resize (hint: use push_back and pop_back)
      while (sz < n) {
        push_back(val);
      }
      while (sz > n) {
        pop_back();
      }
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Element Access
    /// @{

    /// @return Element at front of list
    T& front() {return head->t;}
    /// @return Element at front of list
    const T& front() const {return head->t;}
    /// @return Element at back of list
    T& back() {return tail->t;}
    /// @return Element at back of list
    const T& back() const {return tail->t;}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Modifiers
    /// @{

    /// @brief Add element to front of list
    /// @param val Element
    void push_front(const T& val) {
      /// @todo Implement push front (hint: don't forget the case when the list
      ///       is empty)
      if (empty()) {
        //if list is empty, create a new node that head and tail point to.
        node* midNode = new node(val, NULL, NULL);
        head = midNode;
        tail = midNode;
      }
      else {
        node* midNode = new node(val, NULL, head);
        head->prev = midNode;
        head = midNode;
      }
      ++sz;
    }
    /// @brief Remove the first element of the list. Destroy the element as well.
    void pop_front() {
      /// @todo Implement pop front (hint: don't forget the case when the list
      ///       becomes empty)
      if (empty()) {return;}
      else if (sz == 1) {
        delete head;
        tail = NULL;
        head = NULL;
      }
      else {
      head = head->next;
      delete head->prev;
      head->prev = NULL;
      }
      --sz;
    }
    /// @brief Add element to end of list
    /// @param val Element
    void push_back(const T& val) {
      /// @todo Implement push back (hint: don't forget the case when the list
      ///       is empty)
      if (empty()) {
        //if list is empty, create a new node that head and tail point to.
        node* midNode = new node(val, NULL, NULL);
        head = midNode;
        tail = midNode;
      }
      else {
        node* midNode = new node(val, tail, NULL);
        tail->next = midNode;
        tail = midNode;
      }
      ++sz;
    }
    /// @brief Remove the last element of the list. Destroy the element as well.
    void pop_back() {
      /// @todo Implement pop back (hint: don't forget the case when the list
      ///       becomes empty)
      if (empty()) {return;}
      else if (sz == 1) {
        delete tail;
        tail = NULL;
        head = NULL;
      }
      else {
      tail = tail->prev;
      delete tail->next;
      tail->next = NULL;
      }
      --sz;
    }
    /// @brief Insert element before specified position
    /// @param i Position
    /// @param val Value
    /// @return Position of new value
    iterator insert(iterator i, const T& val) {
      /// @bonus Implement insert for bonus
      if (i == begin()) {push_front(val);}
      else if (i == end()) {push_back(val);}
      else{
        node* midNode = new node(val, i.n->prev, i.n);
        i.n->prev->next = midNode;
        i.n->prev = midNode;
        ++sz;
      }
      return i;
    }
    /// @brief Remove element at specified position
    /// @param i Position
    /// @return Position of new location of element which was after eliminated
    ///         one
    iterator erase(iterator i) {
      /// @bonus Implement erase for bonus
      if (i == begin()) {pop_front();}
      else if (i == end()) {pop_back();}
      else{
        i.n->next->prev = i.n->prev;
        i.n->prev->next = i.n->next;
        delete i.n;
        --sz;
      }
      return i;
    }
    /// @brief Removes all elements
    void clear() {
      /// @todo Implement clear
      for (iterator it = begin(); it != end(); ++it) {
        pop_front();
      }
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:
    node* head; ///< Head of list
    node* tail; ///< Tail of list
    size_t sz;  ///< Size of list
};

}

#endif
