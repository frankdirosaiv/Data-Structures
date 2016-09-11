#include <algorithm>

#include "list.h"

#include "unit_test.h"

using std::all_of;
using mystl::list;

////////////////////////////////////////////////////////////////////////////////
/// @brief Testing of list
/// @ingroup Testing
////////////////////////////////////////////////////////////////////////////////
class list_test : public test_class {

  protected:

    void test() {
      test_default_constructor();

      test_non_default_constructor();

      test_copy_constructor();

      test_copy_assign();

      test_iterators();

      test_const_iterators();

      test_resize();

      test_push_front();

      test_pop_front();

      test_push_back();

      test_pop_back();

      /// @bonus Uncomment these tests for bonus.
      test_insert();

      test_erase();

      test_clear();
    }

  private:

    /// @brief Test default constructor
    void test_default_constructor() {
      list<int> l = list<int>();

      assert_msg(l.size() == 0 && l.empty(),
          "Default construction failed.");
    }

    /// @brief Test non-default constructor
    void test_non_default_constructor() {
      list<int> l(10, 1);

      assert_msg(l.size() == 10 && !l.empty() &&
          all_of(l.begin(), l.end(), [](int i){return i == 1;}),
          "Non-default construction failed.");
    }

    /// @brief Test copy constructor
    void test_copy_constructor() {
      list<int> l1(10, 1);
      list<int> l2(l1);

      assert_msg(l2.size() == 10 && all_of(l2.begin(), l2.end(), [](int i){return i == 1;}),
          "Copy construction failed.");
    }

    /// @brief Test copy assign
    void test_copy_assign() {
      list<int> l1(10, 1);
      list<int> l2(4, 3);

      l1 = l2;

      assert_msg(l1.size() == 4 && all_of(l1.begin(), l1.end(), [](int i){return i == 3;}),
          "Copy construction failed.");
    }

    /// @brief Test iterators
    void test_iterators() {
      list<int> l(10, 1);

      for(auto&& i = l.begin(); i != l.end(); ++i)
        ++(*i);

      assert_msg(all_of(l.begin(), l.end(), [](int i){return i == 2;}),
          "Iterators failed.");
    }

    /// @brief Test const iterators
    void test_const_iterators() {
      list<int> l(10, 1);

      int sum = 0;
      for(auto&& i = l.cbegin(); i != l.cend(); ++i)
        sum += *i;

      assert_msg(sum == 10, "Const iterators failed.");
    }

    /// @brief Test resize
    void test_resize() {
      list<int> l(10, 1);

      l.resize(5);
      assert_msg(l.size() == 5, "Resize failed.");


      l.resize(15, 1);
      assert_msg(l.size() == 15 && all_of(l.begin(), l.end(), [](int i){return i == 1;}),
          "Resize failed.");
    }

    /// @brief Test push front
    void test_push_front() {
      list<int> l1;
      list<int> l2(10, 1);

      l1.push_front(2);
      l2.push_front(2);

      assert_msg(l1.size() == 1 && l2.size() == 11 &&
          l1.front() == 2 && l2.front() == 2,
          "Push front failed.");
    }

    /// @brief Test pop front
    void test_pop_front() {
      list<int> l(10, 1);

      l.pop_front();

      assert_msg(l.size() == 9 && l.back() == 1, "Pop front failed");
    }

    /// @brief Test push back
    void test_push_back() {
      list<int> l1;
      list<int> l2(10, 1);

      l1.push_back(2);
      l2.push_back(2);

      assert_msg(l1.size() == 1 && l2.size() == 11 &&
          l1.back() == 2 && l2.back() == 2,
          "Push front failed.");
    }

    /// @brief Test pop back
    void test_pop_back() {
      list<int> l(10, 1);

      l.pop_back();

      assert_msg(l.size() == 9 && l.back() == 1, "Pop back failed");
    }

    /// @brief Test insert
    void test_insert() {
      list<int> l(10, 1);
      
      l.insert(l.begin(), 7);

      assert_msg(l.front() == 7 && l.size() == 11, "Insert failed.");
    }

    /// @brief Test erase
    void test_erase() {
      list<int> l(10, 1);

      l.erase(l.begin());

      assert_msg(l.front() == 1 && l.size() == 9, "Erase failed.");
    }

    /// @brief Test clear
    void test_clear() {
      list<int> l(10, 1);

      l.clear();

      assert_msg(l.empty(), "Clear failed.");
    }
};

int main() {
  list_test lt;

  if(lt.run())
    std::cout << "All tests passed." << std::endl;

  return 0;
}

