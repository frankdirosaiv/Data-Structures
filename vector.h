#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>
#include <stdexcept>
#include <cstddef>
#include <iostream>

namespace mystl {

////////////////////////////////////////////////////////////////////////////////
/// @brief Vector abstract data type
/// @ingroup MySTL
/// @tparam T Data type
///
/// Assumes the following: There is always enough memory for allocations (not a
/// good assumption, just good enough for our purposes); Functions not
/// well-defined on an empty container will exhibit undefined behavior, e.g.,
/// front().
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class vector {
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Types
    /// @{

    typedef T* iterator;             ///< Random access iterator
    typedef const T* const_iterator; ///< Const random access iterator

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{

    /// @brief Default constructor
    /// @param n Size
    /// @param val Initial value
    vector(size_t n = 0, const T& val = T()) : cap(std::max(size_t(10), 2*n)), sz(n) {
      /// @todo Implement default construction -PASSED
      t = new T[cap];
      for (size_t i = 0; i < sz; i++) {
        t[i] = val; 
      }
    }
    /// @brief Copy constructor
    /// @param v
    vector(const vector& v) : cap(v.cap), sz(v.sz) {
      /// @todo Implement copy construction -PASSED
      t = new T[cap];
      for (size_t i = 0; i < cap; i++) {
        t[i] = v[i];
      }
    }
    /// @brief Destructor
    ~vector() {
      /// @todo Implement destruction -PASSED
        delete[] t;
    }

    /// @brief Copy assignment
    /// @param v
    /// @return Reference to self
    vector& operator=(const vector& v) {
      /// @todo Implement copy assignment -PASSED
        if (&v == this) {return *this;}
        if (&v != this) {
            delete[] t;
            t = new T[v.cap];
           for (size_t i = 0; i < v.sz; i++) {
            t[i] = v[i];
           }
           sz = v.sz;
           cap = v.cap;
        }
      return *this;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Iterators
    /// @{

    /// @return Iterator to beginning
    iterator begin() {return t;}
    /// @return Iterator to beginning
    const_iterator cbegin() const {return t;}
    /// @return Iterator to end
    iterator end() {return &t[sz];}
    /// @return Iterator to end
    const_iterator cend() const {return &t[sz];}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Capacity
    /// @{

    /// @return Size of vector
    size_t size() const {return sz;}
    /// @return Capacity of underlying array
    size_t capacity() const {return cap;}
    /// @return Does the vector contain anything?
    bool empty() const {return sz == 0;}

    /// @brief Resize the array
    /// @param n Size
    /// @param val Value if size is greater of default elements
    ///
    /// If the new size is less than the current progressively remove elements
    /// in the array. Otherwise progressively insert values at the end equal to
    /// \c val.
    void resize(size_t n, const T& val = T()) {
      /// @todo Implement resize (hint: use push_back and pop_back) -PASSED
        while (n < sz) {
            pop_back();
        }
        while (n > sz) {
            push_back(val);
        }
    }
    /// @brief Request a change in the capacity
    /// @param c Capacity
    ///
    /// If the capacity is equal or less than the current capacity, nothing
    /// happens. If the capacity is greater, then the vector is reallocated and
    /// and contents copied.
    void reserve(size_t c) {
      /// @todo Implement reserve (hint: this function can be reused elsewhere) -PASSED
        if (c > cap) {
            T* tmp = new T[c];
            for (size_t i = 0; i < sz; ++i) {
                tmp[i] = t[i];
            }
            delete[] t;
            t = tmp;
            cap = c;
        }
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Element Access
    /// @{

    /// @brief Element access without range check
    /// @param i Index
    /// @return Element at \c i
    T& operator[](size_t i) {return t[i];}
    /// @brief Element access without range check
    /// @param i Index
    /// @return Element at \c i
    const T& operator[](size_t i) const {return t[i];}
    /// @brief Element access with range check
    /// @param i Index
    /// @return Element at \c i
    T& at(size_t i) {
      if(i < 0 || i >= sz)
        throw std::out_of_range("Invalid Array Access");
      return t[i];
    }
    /// @brief Element access with range check
    /// @param i Index
    /// @return Element at \c i
    const T& at(size_t i) const {
      if(i < 0 || i >= sz)
        throw std::out_of_range("Invalid Array Access");
      return t[i];
    }
    /// @return Element at front of vector
    T& front() {return t[0];}
    /// @return Element at front of vector
    const T& front() const {return t[0];}
    /// @return Element at back of vector
    T& back() {return t[sz-1];}
    /// @return Element at back of vector
    const T& back() const {return t[sz-1];}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Modifiers
    /// @{

    /// @brief Add element to end of vector, when capacity is reached perform
    ///        doubling strategy.
    /// @param val Element
    void push_back(const T& val) {
      /// @todo Implement push back -PASSED
        if (sz == cap) {
            reserve(cap*2);
        }
        t[sz] = val;
        ++sz;
    }
    /// @brief Add element to end of vector, when capacity is reached perform
    ///        incremental strategy.
    /// @param val Element
    void push_back_incremental(const T& val) {
      /// @todo Implement push back with incremental capacity increase -PASSED
        if (sz == cap) {
            reserve(cap + 1);
        }
        t[sz] = val;
        ++sz;
    }
    /// @brief Remove the last element of the vector
    void pop_back() {
      /// @todo Implement pop back -PASSED
        if (! empty()) {
            t[sz - 1] = T(); //not necessary, but included for testing purposes.
            --sz;
        }
    }
    /// @brief Insert element before specified position
    /// @param i Position
    /// @param val Value
    /// @return Position of new value
    iterator insert(iterator i, const T& val) {
      /// @bonus Implement insert for bonus
        if (sz < cap) {
            size_t tmp = sz;
            T* indx = &t[sz];
            while (i != indx) {
                --tmp;
                push_back(t[tmp]);
                --indx;
                --sz;
            }
            t[tmp] = val;
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
        if (! empty()){
            T* indx = t;
            size_t tmp = 0;
            while (i != indx) {
                ++tmp;
                ++indx;
            }
            for (size_t j = tmp; j < cap - 1; ++j) {
                t[j] = t[j + 1];
            }
            --sz;
        }
      return i;
    }
    /// @brief Removes all elements without resizing the capacity of the array
    void clear() {
      /// @todo Implement clear -PASSED
        for (int i = sz; i > 0; --i) {
            pop_back();
        }
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:
    T* t;       ///< Dynamically allocated array
    size_t cap; ///< Capacity
    size_t sz;  ///< Size
};

}

#endif
