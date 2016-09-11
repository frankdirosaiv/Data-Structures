#include "list.h"
#include "stack.h"

#include "unit_test.h"

using mystl::list;
using mystl::stack;

////////////////////////////////////////////////////////////////////////////////
/// @brief Testing of stack
/// @ingroup Testing
////////////////////////////////////////////////////////////////////////////////
class stack_test : public test_class {

  protected:

    void test() {

      test_push();

      test_pop();

    }

  private:

    /// @brief Test push
    void test_push() {
      stack<int, list<int>> s;

      s.push(2);

      assert_msg(s.size() == 1 && !s.empty() && s.top() == 2,
          "Push failed.");
    }

    /// @brief Test pop front
    void test_pop() {
      stack<int, list<int>> s;
      s.push(10);
      s.push(9);

      s.pop();

      assert_msg(s.size() == 1 && s.top() == 10, "Pop failed");
    }

};

int main() {
  stack_test st;

  if(st.run())
    std::cout << "All tests passed." << std::endl;

  return 0;
}

