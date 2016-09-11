#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <iostream>
namespace mystl {

////////////////////////////////////////////////////////////////////////////////
/// @brief Queue container adapter
/// @ingroup MySTL
/// @tparam T Value type
/// @tparam Container Underlying container of queue
////////////////////////////////////////////////////////////////////////////////
template<typename T, class Container>
class queue {
  public:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructors
    /// @{

    /// @brief Constructor
    queue() {}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Capacity
    /// @{

    /// @return Size of queue
    size_t size() const {return c.size();}
    /// @return Does the queue contain anything?
    bool empty() const {return c.empty();}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Element Access
    /// @{

    /// @return Front of queue
    T& front() {return c.front();}
    /// @return Front of queue
    const T& front() const {return c.front();}
    /// @return Back of queue
    T& back() {return c.back();}
    /// @return Back of queue
    const T& back() const {return c.back();}

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Modifiers
    /// @{

    /// @brief Add element to back of queue
    /// @param val Element
    void push(const T& val) {
      /// @bonus Implement queue push
        c.push_back(val);
    }
    /// @brief Remove front element from queue
    void pop() {
      /// @bonus Implement queue pop
        c.pop_front();
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:
    Container c; ///< Container for queue
};

}

#endif
