#include <algorithm>

#include "vector.h"

#include "unit_test.h"

using std::all_of;
using mystl::vector;

////////////////////////////////////////////////////////////////////////////////
/// @brief Testing of vector
/// @ingroup Testing
////////////////////////////////////////////////////////////////////////////////
class vector_test : public test_class {

  protected:

    void test() {
      test_default_constructor();

      test_non_default_constructor();

      test_copy_constructor();

      test_copy_assign();

      test_iterators();

      test_const_iterators();

      test_resize();

      test_reserve();

      test_element_access();

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
      vector<int> v;

      assert_msg(v.size() == 0 && v.empty(),
          "Default construction failed.");
    }

    /// @brief Test non-default constructor
    void test_non_default_constructor() {
      vector<int> v(10, 1);

      assert_msg(v.size() == 10 && !v.empty() &&
          all_of(v.begin(), v.end(), [](int i){return i == 1;}),
          "Non-default construction failed.");
    }

    /// @brief Test copy constructor
    void test_copy_constructor() {
      vector<int> v1(10, 1);
      vector<int> v2(v1);

      assert_msg(v2.size() == 10 && all_of(v2.begin(), v2.end(), [](int i){return i == 1;}),
          "Copy construction failed.");
    }

    /// @brief Test copy assign
    void test_copy_assign() {
      vector<int> v1(10, 1);
      vector<int> v2(4, 3);

      v1 = v2;

      assert_msg(v1.size() == 4 && all_of(v1.begin(), v1.end(), [](int i){return i == 3;}),
          "Copy construction failed.");
    }

    /// @brief Test iterators
    void test_iterators() {
      vector<int> v(10, 1);

      for(auto&& i = v.begin(); i != v.end(); ++i)
        ++(*i);

      assert_msg(all_of(v.begin(), v.end(), [](int i){return i == 2;}),
          "Iterators failed.");
    }

    /// @brief Test const iterators
    void test_const_iterators() {
      vector<int> v(10, 1);

      int sum = 0;
      for(auto&& i = v.cbegin(); i != v.cend(); ++i)
        sum += *i;

      assert_msg(sum == 10, "Const iterators failed.");
    }

    /// @brief Test resize
    void test_resize() {
      vector<int> v(10, 1);

      v.resize(5);
      assert_msg(v.size() == 5, "Resize failed.");


      v.resize(15, 1);
      assert_msg(v.size() == 15 && all_of(v.begin(), v.end(), [](int i){return i == 1;}),
          "Resize failed.");
    }

    /// @brief Test reserve
    void test_reserve() {
      vector<int> v(10, 1);

      v.reserve(20);
      assert_msg(v.capacity() == 20, "Reserve failed.");

      v.reserve(15);
      assert_msg(v.capacity() == 20, "Reserve failed.");
    }

    /// @brief Test element access
    void test_element_access() {
      vector<int> v(10, 1);

      v[5] += 7;

      assert_msg(v.at(5) == 8, "Element access failed");
    }

    /// @brief Test push back
    void test_push_back() {
      vector<int> v1;
      vector<int> v2(10, 1);

      v1.push_back(2);
      v2.push_back(2);

      assert_msg(v1.size() == 1 && v2.size() == 11 &&
          v1.back() == 2 && v2.back() == 2,
          "Push front failed.");
    }

    /// @brief Test pop back
    void test_pop_back() {
      vector<int> v(10, 1);

      v.pop_back();

      assert_msg(v.size() == 9 && v.back() == 1, "Pop back failed");
    }

    /// @brief Test insert
    void test_insert() {
      vector<int> v(10, 1);

      v.insert(v.begin(), 7);

      assert_msg(v.front() == 7 && v.size() == 11, "Insert failed.");
    }

    /// @brief Test erase
    void test_erase() {
      vector<int> v(10, 1);

      v.erase(v.begin());

      assert_msg(v.front() == 1 && v.size() == 9, "Erase failed.");
    }

    /// @brief Test clear
    void test_clear() {
      vector<int> v(10, 1);

      v.clear();

      assert_msg(v.empty(), "Clear failed.");
    }
};

int main() {
  vector_test vt;

  if(vt.run())
    std::cout << "All tests passed." << std::endl;

  return 0;
}

