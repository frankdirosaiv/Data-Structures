#include "list.h"
#include "queue.h"

#include "unit_test.h"

using mystl::list;
using mystl::queue;

////////////////////////////////////////////////////////////////////////////////
/// @brief Testing of queue
/// @ingroup Testing
////////////////////////////////////////////////////////////////////////////////
class queue_test : public test_class {

  protected:

    void test() {

      /// @bonus Uncomment these tests for bonus.
      test_push();

      test_pop();

    }

  private:

    /// @brief Test push
    void test_push() {
      queue<int, list<int>> s;

      s.push(2);

      assert_msg(s.size() == 1 && !s.empty() && s.front() == 2 && s.back() == 2,
          "Push failed.");
    }

    /// @brief Test pop front
    void test_pop() {
      queue<int, list<int>> s;
      s.push(10);
      s.push(9);

      s.pop();

      assert_msg(s.size() == 1 && s.front() == 9, "Pop failed");
    }

};

int main() {
  queue_test qt;

  if(qt.run())
    std::cout << "All tests passed." << std::endl;

  return 0;
}

